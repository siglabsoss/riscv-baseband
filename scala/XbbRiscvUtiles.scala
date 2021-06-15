package vexriscv.demo

import spinal.core._
import spinal.lib.bus.amba3.apb.{Apb3, Apb3Config, Apb3SlaveFactory}
import spinal.lib.bus.misc.SizeMapping
import spinal.lib.misc.{InterruptCtrl, Prescaler, Timer}
import spinal.lib._
import vexriscv.plugin.{DBusSimpleBus, IBusSimpleBus}

class XbbRiscvSimpleBusToApbBridge(apb3Config: Apb3Config, pipelineBridge : Boolean, simpleBusConfig : SimpleBusConfig) extends Component{
  assert(apb3Config.dataWidth == simpleBusConfig.dataWidth)

  val io = new Bundle {
    val simpleBus = slave(SimpleBus(simpleBusConfig))
    val apb = master(Apb3(apb3Config))
  }

  val simpleBusStage = SimpleBus(simpleBusConfig)
  simpleBusStage.cmd << (if(pipelineBridge) io.simpleBus.cmd.halfPipe() else io.simpleBus.cmd)
  simpleBusStage.rsp >-> io.simpleBus.rsp

  val state = RegInit(False)
  simpleBusStage.cmd.ready := False

  io.apb.PSEL(0) := simpleBusStage.cmd.valid
  io.apb.PENABLE := state
  io.apb.PWRITE  := simpleBusStage.cmd.wr
  io.apb.PADDR   := simpleBusStage.cmd.address.resized
  io.apb.PWDATA  := simpleBusStage.cmd.data

  simpleBusStage.rsp.valid := False
  simpleBusStage.rsp.data  := io.apb.PRDATA
  when(!state) {
    state := simpleBusStage.cmd.valid
  } otherwise {
    when(io.apb.PREADY){
      state := False
      simpleBusStage.rsp.valid := !simpleBusStage.cmd.wr
      simpleBusStage.cmd.ready := True
    }
  }
}

class XbbSimpleBusDecoder(master_dbus : DBusSimpleBus, simpleBusConfig : SimpleBusConfig, specification : List[(SimpleBus,SizeMapping)], pipelineMaster : Boolean) extends Area{
  val dbus2simple = new DBus2Simple(simpleBusConfig = simpleBusConfig)
  dbus2simple.io.dbus <> master_dbus
  val master = SimpleBus(simpleBusConfig)
  master <> dbus2simple.io.bus

  val masterPipelined = SimpleBus(simpleBusConfig)
  if(!pipelineMaster) {
    masterPipelined.cmd << master.cmd
    masterPipelined.rsp >> master.rsp
  } else {
    masterPipelined.cmd <-< master.cmd
    masterPipelined.rsp >> master.rsp
  }

  val slaveBuses = specification.map(_._1)
  val memorySpaces = specification.map(_._2)

  val hits = for((slaveBus, memorySpace) <- specification) yield {
    val hit = memorySpace.hit(masterPipelined.cmd.address)
    slaveBus.cmd.valid   := masterPipelined.cmd.valid && hit
    slaveBus.cmd.payload := masterPipelined.cmd.payload
    hit
  }
  val noHit = !hits.orR && masterPipelined.cmd.valid
  masterPipelined.cmd.ready := (hits,slaveBuses).zipped.map(_ && _.cmd.ready).orR || noHit

  val rspPending  = RegInit(False) clearWhen(masterPipelined.rsp.valid) setWhen(masterPipelined.cmd.fire && !masterPipelined.cmd.wr)
  val rspNoHit    = RegNext(False) init(False) setWhen(noHit)
  val rspSourceId = RegNextWhen(OHToUInt(hits), masterPipelined.cmd.fire)
  masterPipelined.rsp.valid   := slaveBuses.map(_.rsp.valid).orR || (rspPending && rspNoHit)
  masterPipelined.rsp.payload := slaveBuses.map(_.rsp.payload).read(rspSourceId)

  when(rspPending && !masterPipelined.rsp.valid) { //Only one pending read request is allowed
    masterPipelined.cmd.ready := False
    slaveBuses.foreach(_.cmd.valid := False)
  }
}


class XbbSimpleBusRam(memInit: String, onChipRamSize : BigInt, onChipRamHexFile : String, simpleBusConfig : SimpleBusConfig) extends Component{
  val generic = new Generic {
    val MEMINIT = XbbSimpleBusRam.this.memInit;
  }
  val io = new Bundle{
    val bus = slave(SimpleBus(simpleBusConfig))
  }

  val ram = Mem(Bits(32 bits), onChipRamSize / 4)
  io.bus.rsp.valid := RegNext(io.bus.cmd.fire && !io.bus.cmd.wr) init(False)
  io.bus.rsp.data := ram.readWriteSync(
    address = (io.bus.cmd.address >> 2).resized,
    data  = io.bus.cmd.data,
    enable  = io.bus.cmd.valid,
    write  = io.bus.cmd.wr,
    mask  = io.bus.cmd.mask
  )
  io.bus.cmd.ready := True

  if(onChipRamHexFile != null){
    def readHexFile(path : String, callback : (Int, Int) => Unit): Unit ={
      import scala.io.Source
      def hToI(that : String, start : Int, size : Int) = Integer.parseInt(that.substring(start,start + size), 16)

      var offset = 0
      for (line <- Source.fromFile(path).getLines) {
        if (line.charAt(0) == ':'){
          val byteCount = hToI(line, 1, 2)
          val nextAddr = hToI(line, 3, 4) + offset
          val key = hToI(line, 7, 2)
          key match {
            case 0 =>
              for(i <- 0 until byteCount){
                callback(nextAddr + i, hToI(line, 9 + i * 2, 2))
              }
            case 2 =>
              offset = hToI(line, 9, 4) << 4
            case 4 =>
              offset = hToI(line, 9, 4) << 16
            case 3 =>
            case 5 =>
            case 1 =>
          }
        }
      }
    }

    val initContent = Array.fill[BigInt](ram.wordCount)(0)
    readHexFile(onChipRamHexFile,(address,data) => {
      val addressWithoutOffset = address + Int.MinValue
      initContent(addressWithoutOffset >> 2) |= BigInt(data) << ((addressWithoutOffset & 3)*8)
    })
    ram.initBigInt(initContent)
  }
}

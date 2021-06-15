package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class DmaReset() extends Bundle with IMasterSlave{
  val dmaReset = Bool

  override def asMaster(): Unit = {
    out(dmaReset)
  }
}

case class DmaInterruptClear() extends Bundle with IMasterSlave{
  val interrupt_clear = Bool

  override def asMaster(): Unit = {
    out(interrupt_clear)
  }
}
  
case class DmaConfig() extends Bundle{
  val startAddr = UInt(32 bits)
  val length = UInt(32 bits)
  val timerInit = UInt(32 bits)
  val slicer = UInt(32 bits)
  val reverse = Bool
  val last_or_run_till_last = Bool
  val demapper_constellation = UInt(4 bits)
  val demapper_two_over_sigma_sq = UInt(16 bits)
}

case class DmaStatus() extends Bundle with IMasterSlave{
  val status = UInt(32 bits)

  override def asMaster(): Unit = {
    out(status)
  }
}

case class DmaConfigStream() extends Bundle with IMasterSlave{
  val config = Stream(DmaConfig())

  override def asMaster(): Unit = {
    master(config)
  }

}

class DmaCsrPlugin(enum: String, baseAddress: Int) extends Plugin[VexRiscv]{
  var dma : DmaConfigStream = null
  var status : DmaStatus = null
  var interrupt_clear : DmaInterruptClear = null
  var reset : DmaReset = null
  val e : String = enum

  override def setup(pipeline: VexRiscv): Unit = {
    dma = master(DmaConfigStream()).setName("dma_".concat(enum))
    status = slave(DmaStatus()).setName("dma_".concat(enum))
    interrupt_clear = master(DmaInterruptClear()).setName("dma_".concat(enum))
    reset = master(DmaReset()).setName("dma_".concat(enum))
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val startAddrReg, lengthReg, timerInitReg, slicerReg = Reg(UInt(32 bits))
      val reverseReg = Reg(Bool) init(False)
      val last_or_run_till_lastReg = Reg(Bool) init(False)
      val demapper_constellationReg = Reg(UInt(4 bits)) init(0)
      val demapper_two_over_sigma_sqReg = Reg(UInt(16 bits)) init(4096)
      val configPush = Stream(DmaConfig())
      val configFifo = StreamFifo(
        dataType = DmaConfig(),
        depth=16
      )


      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0, startAddrReg)
      csrService.rw(baseAddress+1, lengthReg)
      csrService.rw(baseAddress+2, timerInitReg)
      csrService.rw(baseAddress+8, slicerReg)
      csrService.rw(baseAddress+9, reverseReg)
      csrService.rw(baseAddress+10, last_or_run_till_lastReg)
      csrService.rw(baseAddress+11, demapper_constellationReg)
      csrService.rw(baseAddress+12, demapper_two_over_sigma_sqReg)

      configPush.startAddr := startAddrReg
      configPush.length := lengthReg
      configPush.timerInit := timerInitReg
      configPush.slicer := slicerReg
      configPush.reverse := reverseReg
      configPush.last_or_run_till_last := last_or_run_till_lastReg
      configPush.demapper_constellation := demapper_constellationReg
      configPush.demapper_two_over_sigma_sq := demapper_two_over_sigma_sqReg

      when(csrService.isWriting(baseAddress+3)) {
        last_or_run_till_lastReg := False
      }

      configPush.valid := csrService.isWriting(baseAddress+3)
      

      configFifo.io.push << configPush
      configFifo.io.pop >> dma.config

      csrService.r(baseAddress+4, status)
      csrService.r(baseAddress+5, configFifo.io.occupancy)
      configFifo.io.flush := csrService.isWriting(baseAddress+6)
      reset.dmaReset := RegNext(csrService.isWriting(baseAddress+6))

      interrupt_clear.interrupt_clear := csrService.isWriting(baseAddress+7)

    }
  }
}

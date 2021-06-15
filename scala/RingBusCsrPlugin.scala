package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.{Flow,master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}


case class RingBusInterruptClear() extends Bundle with IMasterSlave{
  val interrupt_clear = Bool()

  override def asMaster(): Unit = {
    out(interrupt_clear)
  }
}

case class RingBusWrite() extends Bundle{
  val write_data = UInt(32 bits)
  val write_addr = UInt(32 bits)
}

case class RingBusWriteStream() extends Bundle with IMasterSlave{
  val config = Stream(RingBusWrite())

  override def asMaster(): Unit = {
    master(config)
  }
}

case class RingBusStatus() extends Bundle with IMasterSlave{
  val write_done = Bool()

  override def asMaster(): Unit = {
    out(write_done)
  }
}

case class RingBusRead() extends Bundle{
  val read_data = UInt(32 bits)

}

case class RingBusReadStream() extends Bundle with IMasterSlave{
  val read = Stream(RingBusRead())

  override def asMaster(): Unit = {
    master(read)
  }
}

class RingBusCsrPlugin(enum: String, baseAddress: Int) extends Plugin[VexRiscv]{
  var interrupt_clear : RingBusInterruptClear = null
  var write : RingBusWriteStream = null
  var read : RingBusReadStream = null
  var status : RingBusStatus = null
  val e : String = enum

  override def setup(pipeline: VexRiscv): Unit = {
    interrupt_clear = master(RingBusInterruptClear()).setName("ringbus_".concat(enum))
    write = master(RingBusWriteStream()).setName("ringbus_".concat(enum))
    read = slave(RingBusReadStream()).setName("ringbus_".concat(enum))
    status = slave(RingBusStatus()).setName("ringbus_".concat(enum))
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._
    pipeline plug new Area{
      val writeAddrReg, writeDataReg = Reg(UInt(32 bits))
      val writePush = Stream(RingBusWrite())
      val writeFifo = StreamFifo(
        dataType = RingBusWrite(),
        depth = 16
      )

      val readPush = Stream(RingBusRead())
      val readPop = Stream(RingBusRead())
      val readFifo = StreamFifo(
        dataType = RingBusRead(),
        depth = 16
      )

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0,writeAddrReg)
      csrService.rw(baseAddress+1,writeDataReg)

      writePush.write_addr := writeAddrReg
      writePush.write_data := writeDataReg
      writePush.valid := csrService.isWriting(baseAddress+2)

      writeFifo.io.push << writePush
      writeFifo.io.pop >> write.config

      csrService.r(baseAddress+3,status.write_done)

      //csrService.r(baseAddress+4,read.read_data)

      interrupt_clear.interrupt_clear := csrService.isWriting(baseAddress+5)

      csrService.r(baseAddress+6,writeFifo.io.occupancy)
      
      writeFifo.io.flush := csrService.isWriting(baseAddress+7)

      // Read
      csrService.r(baseAddress + 8, readPop.payload.read_data)

      readPush.payload := read.read.payload
      readPush.valid := read.read.valid
      read.read.ready := readPush.ready

      readFifo.io.push << readPush

      readFifo.io.pop >> readPop

      readPop.ready := csrService.isReading(baseAddress + 8)
      csrService.r(baseAddress + 9, readFifo.io.occupancy)
      readFifo.io.flush := csrService.isWriting(baseAddress + 10)
    }
  }
}

package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class InterruptConfig() extends Bundle with IMasterSlave{
  val mask = UInt(32 bits)
  val clear = Bool

  override def asMaster(): Unit = {
    out(mask,clear)
  }
}

case class InterruptStatus() extends Bundle with IMasterSlave{
  val interruptVector = UInt(32 bits)
  val serviceInterrupt = UInt(32 bits)

  override def asMaster(): Unit = {
    out(interruptVector,serviceInterrupt)
  }
}


class InterruptCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var intConfig : InterruptConfig = null
  var intStatus : InterruptStatus = null

  override def setup(pipeline: VexRiscv): Unit = {
    intConfig = master(InterruptConfig()).setName("interrupt")
    intStatus = slave(InterruptStatus()).setName("interrupt")
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val maskReg = Reg(UInt(32 bits))

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0, maskReg)
      csrService.r(baseAddress+1, intStatus.interruptVector)
      csrService.r(baseAddress+2, intStatus.serviceInterrupt)

      intConfig.mask := maskReg
      intConfig.clear := csrService.isWriting(baseAddress+3)

    }
  }
}

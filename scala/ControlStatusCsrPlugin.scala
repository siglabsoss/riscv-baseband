package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class CSStatus() extends Bundle with IMasterSlave{
  val status = UInt(32 bits)

  override def asMaster(): Unit = {
    out(status)
  }
}

case class CSControl() extends Bundle with IMasterSlave{
  val control = UInt(32 bits)

  override def asMaster(): Unit = {
    out(control)
  }
}

class ControlStatusCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var status : CSStatus = null
  var control : CSControl = null

  override def setup(pipeline: VexRiscv): Unit = {
    status = slave(CSStatus()).setName("status")
    control = master(CSControl()).setName("control")
  }
  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val controlReg = Reg(UInt(32 bits))

      val csrService = pipeline.service(classOf[CsrInterface])

      csrService.r(baseAddress+0,status.status)
      csrService.rw(baseAddress+1,controlReg)
      control.control := controlReg

    }
  }
}

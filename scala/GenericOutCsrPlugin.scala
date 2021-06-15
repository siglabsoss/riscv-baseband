package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class GenericOutBundle() extends Bundle with IMasterSlave{
  val value = UInt(32 bits)

  override def asMaster(): Unit = {
    out(value)
  }
}

class GenericOutCsrPlugin(enum: String, baseAddress: Int) extends Plugin[VexRiscv]{
  var value : GenericOutBundle = null
  val e : String = enum
  override def setup(pipeline: VexRiscv): Unit = {
    value = master(GenericOutBundle()).setName(enum)
  }
  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val valueReg = Reg(UInt(32 bits))

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0,valueReg)

      value.value := RegNext(valueReg)
    }
  }
}

package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class DEngineConfigBundle() extends Bundle with IMasterSlave{
  val reset = Bool
  val func0MinThreshold = UInt(32 bits)
  val func0MaxThreshold = UInt(32 bits)
  val func1MinThreshold = UInt(32 bits)
  val func1MaxThreshold = UInt(32 bits)

  override def asMaster(): Unit = {
    out(reset)
    out(func0MinThreshold)
    out(func0MaxThreshold)
    out(func1MinThreshold)
    out(func1MaxThreshold)
  }
}

class DEngineCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var configBundle : DEngineConfigBundle = null
  override def setup(pipeline: VexRiscv): Unit = {
    configBundle = master(DEngineConfigBundle()).setName("dengine")
  }
  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val resetReg = Reg(Bool) init(False)
      val func0MinThresholdReg = Reg(UInt(32 bits)) init(0)
      val func0MaxThresholdReg = Reg(UInt(32 bits)) init(0)
      val func1MinThresholdReg = Reg(UInt(32 bits)) init(0)
      val func1MaxThresholdReg = Reg(UInt(32 bits)) init(0)

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0,resetReg)
      csrService.rw(baseAddress+1,func0MinThresholdReg)
      csrService.rw(baseAddress+2,func0MaxThresholdReg)
      csrService.rw(baseAddress+3,func1MinThresholdReg)
      csrService.rw(baseAddress+4,func1MaxThresholdReg)

      configBundle.reset := resetReg
      configBundle.func0MinThreshold := func0MinThresholdReg
      configBundle.func0MaxThreshold := func0MaxThresholdReg
      configBundle.func1MinThreshold := func1MinThresholdReg
      configBundle.func1MaxThreshold := func1MaxThresholdReg

    }
  }
}

package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class TimerStatus() extends Bundle with IMasterSlave{
  val gtimer = UInt(32 bits)

  override def asMaster(): Unit = {
    out(gtimer)
  }
}

class TimerCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var ctimer : TimerStatus = null

  override def setup(pipeline: VexRiscv): Unit = {
    ctimer = master(TimerStatus()).setName("timerCsr")
  }
  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val timerReg = Reg(UInt(32 bits)) init(0)

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.r(baseAddress+0,timerReg)

      timerReg := timerReg + 1
      csrService.onWrite(baseAddress+1) {
        timerReg := 0
      }

      ctimer.gtimer := timerReg
    }
  }
}

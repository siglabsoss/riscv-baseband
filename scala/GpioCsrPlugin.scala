package vexriscv.demo

import spinal.core._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

class GpioCsrPlugin(width: Int, baseAddress: Int) extends Plugin[VexRiscv]{
  var gpio : TriStateArray = null


  override def setup(pipeline: VexRiscv): Unit = {
    gpio = master(TriStateArray(width bits)).setName("gpio")
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val writeReg, writeEnableReg = Reg(Bits(width bits))

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0, writeReg)
      csrService.rw(baseAddress+1, writeEnableReg)
      csrService.r(baseAddress+2, gpio.read)

      gpio.writeEnable := writeEnableReg
      gpio.write := writeReg
    }
  }
}

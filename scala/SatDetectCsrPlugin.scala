package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class SatDetectBundle() extends Bundle with IMasterSlave{
  val satDetect = Bool

  override def asMaster(): Unit = {
    out(satDetect)
  }
}

class SatDetectCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var satDetect : SatDetectBundle = null
  override def setup(pipeline: VexRiscv): Unit = {
    satDetect = slave(SatDetectBundle())
  }
  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val satDetectReg = Reg(Bool)
      val satCountReg = Reg(UInt(16 bits))
      val satTimeReg = Reg(UInt(16 bits))
      val satReg = UInt(32 bits)

      satDetectReg := satDetect.satDetect

      satTimeReg := satTimeReg+1
      satCountReg := satCountReg
      when(satTimeReg === 0xFFFF) {
        satCountReg := 0
      }
      when(satDetectReg === True) {
        satCountReg := satCountReg+1
      }


      //      satReg = RegNext(satCountReg<<16+satTimeReg)
      satReg := satCountReg @@ satTimeReg //U"h1234" ## U"h5678" //(satCountReg ## satTimeReg)

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.r(baseAddress+0,satReg)
      when(csrService.isReading(baseAddress+0)){
        satCountReg := 0
        satTimeReg := 0
      }


    }
  }
}

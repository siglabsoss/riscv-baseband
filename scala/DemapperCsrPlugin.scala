package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class DemapperControl() extends Bundle with IMasterSlave{
  val constellation = UInt(4 bits)
  val two_over_sigma_sq = UInt(16 bits)


  override def asMaster(): Unit = {
    out(constellation)
    out(two_over_sigma_sq)
  }
}

class DemapperCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var demapper_control : DemapperControl = null

  override def setup(pipeline: VexRiscv): Unit = {
    demapper_control = master(DemapperControl()).setName("mapmovCsr")
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val constellation_reg = Reg(UInt(4 bits)) init(0)
      val two_over_sigma_sq_reg = Reg(UInt(16 bits)) init(4096)

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0,constellation_reg)
      csrService.rw(baseAddress+1,two_over_sigma_sq_reg)

      demapper_control.constellation := constellation_reg
      demapper_control.two_over_sigma_sq := two_over_sigma_sq_reg

    }
  }
}

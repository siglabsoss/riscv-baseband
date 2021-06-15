package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class NCOReset() extends Bundle with IMasterSlave{
  val ncoReset = Bool

  override def asMaster(): Unit = {
    out(ncoReset)
  }
}

case class NCOConfig() extends Bundle{
  val startAngle = UInt(32 bits)
  val length = UInt(32 bits)
  val delta = UInt(32 bits)
}

case class NCOStatus() extends Bundle with IMasterSlave{
  val busy =Bool

  override def asMaster(): Unit = {
    out(busy)
  }
}

case class NCOConfigStream() extends Bundle with IMasterSlave{
  val config = Stream(NCOConfig())

  override def asMaster(): Unit = {
    master(config)
  }

}

class NCOCsrPlugin(enum: String, baseAddress: Int) extends Plugin[VexRiscv]{
  var nco : NCOConfigStream = null
  var status : NCOStatus = null
  var reset : NCOReset = null
  val e : String = enum

  override def setup(pipeline: VexRiscv): Unit = {
    nco = master(NCOConfigStream()).setName("nco_".concat(enum))
    status = slave(NCOStatus()).setName("nco_".concat(enum))
    reset = master(NCOReset()).setName("nco_".concat(enum))
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val startAngleReg, lengthReg, deltaReg = Reg(UInt(32 bits))
      val configPush = Stream(NCOConfig())
      val configFifo = StreamFifo(
        dataType = NCOConfig(),
        depth=16
      )


      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0, startAngleReg)
      csrService.rw(baseAddress+1, lengthReg)
      csrService.rw(baseAddress+2, deltaReg)

      configPush.startAngle := startAngleReg
      configPush.length := lengthReg
      configPush.delta := deltaReg

      configPush.valid := csrService.isWriting(baseAddress+3)

      configFifo.io.push << configPush
      configFifo.io.pop >> nco.config

      csrService.r(baseAddress+4, status)
      csrService.r(baseAddress+5, configFifo.io.occupancy)
      configFifo.io.flush := csrService.isWriting(baseAddress+6)
      reset.ncoReset := RegNext(csrService.isWriting(baseAddress+6))


    }
  }
}

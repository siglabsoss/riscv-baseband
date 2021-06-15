package vexriscv.demo

import spinal.core._
import spinal.lib._
import vexriscv.ip._
import vexriscv._
import vexriscv.plugin.Plugin
import vexriscv.{Stageable, DecoderService, VexRiscv}

case class XbasebandCmd() extends Bundle{
  val instruction = Bits(32 bit)
  val rs1 = Bits(32 bit)
}

case class XbasebandBus() extends Bundle with IMasterSlave{
  val cmd = Stream(XbasebandCmd())

  override def asMaster(): Unit = {
    master(cmd)
  }
}

class Xbaseband extends Plugin[VexRiscv] {

  var xbaseband : XbasebandBus = null

  object IS_XBASEBAND extends Stageable(Bool)

  override def setup(pipeline: VexRiscv): Unit = {
    import pipeline.config._

    val decoderService = pipeline.service(classOf[DecoderService])

    decoderService.addDefault(IS_XBASEBAND, False)

    decoderService.add(
      // Bit pattern of the new XBASEBAND instruction
      //
      //      76543210        76543210
      //              76543210        76543210
      //      |S1||K ||S2||RS1||OP||DS|
      key = M"-------------------------0001011",

      // Decoding specification when the 'key' pattern is recognized in the instruction
      List(
        IS_XBASEBAND             -> True,
        REGFILE_WRITE_VALID      -> False, //Enable the register file write
        BYPASSABLE_EXECUTE_STAGE -> True, //Notify the hazard management unit that the instruction result is already accessible in the EXECUTE stage (Bypass ready)
        BYPASSABLE_MEMORY_STAGE  -> True, //Same as above but for the memory stage
        RS1_USE                  -> True  //Notify the hazard management unit that this instruction use the RS1 value
      )
    )
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    xbaseband = master(XbasebandBus()).setName("xbaseband")
    writeBack plug new Area {
      import writeBack._
      xbaseband.cmd.instruction := writeBack.input(INSTRUCTION)
      xbaseband.cmd.rs1 := writeBack.input(RS1)
      xbaseband.cmd.valid := writeBack.output(IS_XBASEBAND) && writeBack.arbitration.isValid //writeBack.arbitration.isFiring

      arbitration.haltItself.setWhen(writeBack.arbitration.isValid && !xbaseband.cmd.ready)
    }
  }
}

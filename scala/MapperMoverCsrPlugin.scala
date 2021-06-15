package vexriscv.demo

import vexriscv._
import spinal.core._
import spinal.lib._
import spinal.lib.io.TriStateArray
import spinal.lib.{Flow, master}
import vexriscv.plugin.{CsrInterface, Plugin}
import vexriscv.{DecoderService, Stageable, VexRiscv}

case class MapperMoverControl() extends Bundle with IMasterSlave{
  val mover_active = Bits(1024 bits)
  val trim_start = UInt(32 bits)
  val trim_end = UInt(32 bits)
  val pilot_ram_addr = UInt(10 bits)
  val pilot_ram_wdata = UInt(32 bits)
  val pilot_ram_we = Bool
  val reset = Bool
  val one_value = UInt(16 bits)
  val zero_value = UInt(16 bits)


  override def asMaster(): Unit = {
    out(mover_active)
    out(trim_start)
    out(trim_end)
    out(pilot_ram_addr)
    out(pilot_ram_wdata)
    out(pilot_ram_we)
    out(reset)
    out(one_value)
    out(zero_value)
  }
}

class MapperMoverCsrPlugin(baseAddress: Int) extends Plugin[VexRiscv]{
  var mapper_mover_control : MapperMoverControl = null

  override def setup(pipeline: VexRiscv): Unit = {
    mapper_mover_control = master(MapperMoverControl()).setName("mapmovCsr")
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    pipeline plug new Area{
      val mover_active_reg0 = Reg(UInt(32 bits))
      val mover_active_reg1 = Reg(UInt(32 bits)) init(65535)
      val mover_active_reg2 = Reg(UInt(32 bits))
      val mover_active_reg3 = Reg(UInt(32 bits))
      val mover_active_reg4 = Reg(UInt(32 bits))
      val mover_active_reg5 = Reg(UInt(32 bits))
      val mover_active_reg6 = Reg(UInt(32 bits))
      val mover_active_reg7 = Reg(UInt(32 bits))
      val mover_active_reg8 = Reg(UInt(32 bits))
      val mover_active_reg9 = Reg(UInt(32 bits))
      val mover_active_reg10 = Reg(UInt(32 bits))
      val mover_active_reg11 = Reg(UInt(32 bits))
      val mover_active_reg12 = Reg(UInt(32 bits))
      val mover_active_reg13 = Reg(UInt(32 bits))
      val mover_active_reg14 = Reg(UInt(32 bits))
      val mover_active_reg15 = Reg(UInt(32 bits))
      val mover_active_reg16 = Reg(UInt(32 bits))
      val mover_active_reg17 = Reg(UInt(32 bits))
      val mover_active_reg18 = Reg(UInt(32 bits))
      val mover_active_reg19 = Reg(UInt(32 bits))
      val mover_active_reg20 = Reg(UInt(32 bits))
      val mover_active_reg21 = Reg(UInt(32 bits))
      val mover_active_reg22 = Reg(UInt(32 bits))
      val mover_active_reg23 = Reg(UInt(32 bits))
      val mover_active_reg24 = Reg(UInt(32 bits))
      val mover_active_reg25 = Reg(UInt(32 bits))
      val mover_active_reg26 = Reg(UInt(32 bits))
      val mover_active_reg27 = Reg(UInt(32 bits))
      val mover_active_reg28 = Reg(UInt(32 bits))
      val mover_active_reg29 = Reg(UInt(32 bits))
      val mover_active_reg30 = Reg(UInt(32 bits))
      val mover_active_reg31 = Reg(UInt(32 bits))

      val trim_start_reg = Reg(UInt(32 bits)) init(0)
      val trim_end_reg = Reg(UInt(32 bits)) init(1023)
      val pilot_ram_wdata = Reg(UInt(32 bits))
      val pilot_ram_addr = Reg(UInt(10 bits))
      val pilot_ram_we = Reg(Bool)
      val reset = Reg(Bool)
      val one_value_reg = Reg(UInt(16 bits)) init(0x16a1)
      val zero_value_reg = Reg(UInt(16 bits)) init(0xe95f)

      val csrService = pipeline.service(classOf[CsrInterface])
      csrService.rw(baseAddress+0,mover_active_reg0)
      csrService.rw(baseAddress+1,mover_active_reg1)
      csrService.rw(baseAddress+2,mover_active_reg2)
      csrService.rw(baseAddress+3,mover_active_reg3)
      csrService.rw(baseAddress+4,mover_active_reg4)
      csrService.rw(baseAddress+5,mover_active_reg5)
      csrService.rw(baseAddress+6,mover_active_reg6)
      csrService.rw(baseAddress+7,mover_active_reg7)
      csrService.rw(baseAddress+8,mover_active_reg8)
      csrService.rw(baseAddress+9,mover_active_reg9)
      csrService.rw(baseAddress+10,mover_active_reg10)
      csrService.rw(baseAddress+11,mover_active_reg11)
      csrService.rw(baseAddress+12,mover_active_reg12)
      csrService.rw(baseAddress+13,mover_active_reg13)
      csrService.rw(baseAddress+14,mover_active_reg14)
      csrService.rw(baseAddress+15,mover_active_reg15)
      csrService.rw(baseAddress+16,mover_active_reg16)
      csrService.rw(baseAddress+17,mover_active_reg17)
      csrService.rw(baseAddress+18,mover_active_reg18)
      csrService.rw(baseAddress+19,mover_active_reg19)
      csrService.rw(baseAddress+20,mover_active_reg20)
      csrService.rw(baseAddress+21,mover_active_reg21)
      csrService.rw(baseAddress+22,mover_active_reg22)
      csrService.rw(baseAddress+23,mover_active_reg23)
      csrService.rw(baseAddress+24,mover_active_reg24)
      csrService.rw(baseAddress+25,mover_active_reg25)
      csrService.rw(baseAddress+26,mover_active_reg26)
      csrService.rw(baseAddress+27,mover_active_reg27)
      csrService.rw(baseAddress+28,mover_active_reg28)
      csrService.rw(baseAddress+29,mover_active_reg29)
      csrService.rw(baseAddress+30,mover_active_reg30)
      csrService.rw(baseAddress+31,mover_active_reg31)

      csrService.rw(baseAddress+32,trim_start_reg)
      csrService.rw(baseAddress+33,trim_end_reg)
      csrService.rw(baseAddress+34,pilot_ram_addr)
      csrService.rw(baseAddress+35,pilot_ram_wdata)
      pilot_ram_we := csrService.isWriting(baseAddress+36)
      reset := csrService.isWriting(baseAddress+37)
      csrService.rw(baseAddress+38,one_value_reg)
      csrService.rw(baseAddress+38,zero_value_reg)

      mapper_mover_control.mover_active := mover_active_reg31 ## mover_active_reg30 ## mover_active_reg29 ## mover_active_reg28 ## mover_active_reg27 ## mover_active_reg26 ## mover_active_reg25 ## mover_active_reg24 ## mover_active_reg23 ## mover_active_reg22 ## mover_active_reg21 ## mover_active_reg20 ## mover_active_reg19 ## mover_active_reg18 ## mover_active_reg17 ## mover_active_reg16 ## mover_active_reg15 ## mover_active_reg14 ## mover_active_reg13 ## mover_active_reg12 ## mover_active_reg11 ## mover_active_reg10 ## mover_active_reg9 ## mover_active_reg8 ## mover_active_reg7 ## mover_active_reg6 ## mover_active_reg5 ## mover_active_reg4 ## mover_active_reg3 ## mover_active_reg2 ## mover_active_reg1 ## mover_active_reg0

      mapper_mover_control.trim_start := trim_start_reg
      mapper_mover_control.trim_end := trim_end_reg
      mapper_mover_control.pilot_ram_addr := pilot_ram_addr
      mapper_mover_control.pilot_ram_wdata := pilot_ram_wdata
      mapper_mover_control.pilot_ram_we := pilot_ram_we
      mapper_mover_control.reset := reset
      mapper_mover_control.one_value := one_value_reg
      mapper_mover_control.zero_value := zero_value_reg
    }
  }
}

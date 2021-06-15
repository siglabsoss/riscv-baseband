package vexriscv.plugin

import math.atan
import math.Pi
import math.pow
import spinal.core._
import spinal.lib._
import spinal.lib.fsm._
import vexriscv.{Stageable, DecoderService, VexRiscv}



class XbbVectorCordic() extends Plugin[VexRiscv]{
  //Define the concept of IS_SIMD_ADD signals, which specify if the current instruction is destined fo this plugin
  object IS_VCORDIC extends Stageable(Bool)

  override def setup(pipeline: VexRiscv): Unit = {
    import pipeline.config._

    //Retrieve the DecoderService instance
    val decoderService = pipeline.service(classOf[DecoderService])

    //Specify the instruction decoding which should be applied when the instruction is decoded
    decoderService.addDefault(IS_VCORDIC, False)

    //Specify the instruction decoding which should be applied when the instruction m at6ch the 'key' pattern
    decoderService.add(
      // Bit pattern of the new VCORDIC instruction
      //
      //      76543210        76543210
      //              76543210        76543210
      //      |iter  |rs2 |rs1|| ||rd |
      key = M"-------------------------0101011",
      //Decoding specification when the 'key' pattern is recognized in the instruction
      List(
        IS_VCORDIC               -> True,
        REGFILE_WRITE_VALID      -> True, //Enable the register file write
        BYPASSABLE_EXECUTE_STAGE -> True, //Notify the hazard management unit that the instruction result is already accessible in the EXECUTE stage (Bypass ready)
        BYPASSABLE_MEMORY_STAGE  -> False, //Same as above but for the memory stage
        RS1_USE                  -> True, //Notify the hazard management unit that this instruciton uses the RS1 value
        RS2_USE                  -> True //Notify the hazard management unit that this instruciton uses the RS2 value
      )
    )
  }

  override def build(pipeline: VexRiscv): Unit = {
    import pipeline._
    import pipeline.config._

    //Add a new scope on the execute stage (used to give a name to signals)
    execute plug new Area {
      import execute._
      //Define some signals used internally to the plugin
      val rs1 = execute.input(RS1).asUInt
      val rs2 = execute.input(RS2).asUInt

      val iters = RegNext(rs2(3 downto 0))

      val rd = UInt(32 bits)

      val maxIters = 16
      val theta = new Array[SFix](maxIters)
      
      for( i <- 0 to maxIters-1){
        theta(i) = SFix(1 exp, 17 bits)
        theta(i) := atan(pow(2,-1*i))/(Pi/2)
      }


      //      val inputLUT = Mem(Bits(16 bits), initialContent = theta)

      val vfsm = new StateMachine {
        val x = Reg(SInt(18 bits)) init(0) //SFix(1 exp, 16 bits)
        val y = Reg(SInt(18 bits)) init(0) //SFix(1 exp, 16 bits)
        val xtmp = Reg(SInt(18 bits)) init(0) //SFix(1 exp, 16 bits)
        val ytmp = Reg(SInt(18 bits)) init(0) //SFix(1 exp, 16 bits)
        val z = Reg(SInt(17 bits)) init(0)
        val viter = Reg(UInt(log2Up(maxIters) bits)) init(0)
        val sign = Reg(UInt(2 bits)) init(0)

        viter := viter + 1
        val isvcordic = Bool
        isvcordic := input(IS_VCORDIC)
        val stateInit : State = new State with EntryPoint{
          whenIsActive {
            when(arbitration.isValid && isvcordic ){
              when(rs1(15)){
                x := (U(0, 2 bits) ## ~rs1(15 downto 0)).asSInt
                xtmp := (U(0, 2 bits) ## ~rs1(15 downto 0)).asSInt
              }.otherwise{
                x := (U(0, 2 bits) ## rs1(15 downto 0)).asSInt
                xtmp := (U(0, 2 bits) ## rs1(15 downto 0)).asSInt
              }
              y := (rs1(31) ## rs1(31) ## rs1(31) ## rs1(30 downto 16)).asSInt
              ytmp := (rs1(31) ## rs1(31) ## rs1(31) ## rs1(30 downto 16)).asSInt
              z := 0
              sign := U(rs1(31) ## rs1(15))
              arbitration.haltItself := True
              goto(stateCompute)
            }
            viter := 0
          }
        }

        val stateCompute : State = new State{
          val xval = SInt(18 bits)
          val yval = SInt(18 bits)
          xval := 0
          yval := 0
          whenIsActive{
            arbitration.haltItself := True
            when(y < S(0, 18 bits)){
              xval := x - ytmp
              yval := y + xtmp
              //              z := z - B(inputLUT(viter)).asSInt
            }.otherwise {
              xval := x + ytmp
              yval := y - xtmp
              //              z := z + B(inputLUT(viter)).asSInt
            }
            x := xval
            y := yval
            //            xtmp := xval >> (viter + 1)
            //            ytmp := yval >> (viter + 1)

            switch(viter){
              is(U(0, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(0)).asSInt
                }.otherwise {
                  z := z + B(theta(0)).asSInt
                }
                xtmp := xval >> U(1)
                ytmp := yval >> U(1)
              }
              is(U(1, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(1)).asSInt
                }.otherwise {
                  z := z + B(theta(1)).asSInt
                }
                xtmp := xval >> U(2)
                ytmp := yval >> U(2)
              }
              is(U(2, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(2)).asSInt
                }.otherwise {
                  z := z + B(theta(2)).asSInt
                }
                xtmp := xval >> U(3)
                ytmp := yval >> U(3)
              }
              is(U(3, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(3)).asSInt
                }.otherwise {
                  z := z + B(theta(3)).asSInt
                }
                xtmp := xval >> U(4)
                ytmp := yval >> U(4)
              }
              is(U(4, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(4)).asSInt
                }.otherwise {
                  z := z + B(theta(4)).asSInt
                }
                xtmp := xval >> U(5)
                ytmp := yval >> U(5)
              }
              is(U(5, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(5)).asSInt
                }.otherwise {
                  z := z + B(theta(5)).asSInt
                }
                xtmp := xval >> U(6)
                ytmp := yval >> U(6)
              }
              is(U(6, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(6)).asSInt
                }.otherwise {
                  z := z + B(theta(6)).asSInt
                }
                xtmp := xval >> U(7)
                ytmp := yval >> U(7)
              }
              is(U(7, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(7)).asSInt
                }.otherwise {
                  z := z + B(theta(7)).asSInt
                }
                xtmp := xval >> U(8)
                ytmp := yval >> U(8)
              }
              is(U(8, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(8)).asSInt
                }.otherwise {
                  z := z + B(theta(8)).asSInt
                }
                xtmp := xval >> U(9)
                ytmp := yval >> U(9)
              }
              is(U(9, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(9)).asSInt
                }.otherwise {
                  z := z + B(theta(9)).asSInt
                }
                xtmp := xval >> U(10)
                ytmp := yval >> U(10)
              }
              is(U(10, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(10)).asSInt
                }.otherwise {
                  z := z + B(theta(10)).asSInt
                }
                xtmp := xval >> U(11)
                ytmp := yval >> U(11)
              }
              is(U(11, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(11)).asSInt
                }.otherwise {
                  z := z + B(theta(11)).asSInt
                }
                xtmp := xval >> U(12)
                ytmp := yval >> U(12)
              }
              is(U(12, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(12)).asSInt
                }.otherwise {
                  z := z + B(theta(12)).asSInt
                }
                xtmp := xval >> U(13)
                ytmp := yval >> U(13)
              }
              is(U(13, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(13)).asSInt
                }.otherwise {
                  z := z + B(theta(13)).asSInt
                }
                xtmp := xval >> U(14)
                ytmp := yval >> U(14)
              }
              is(U(14, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(14)).asSInt
                }.otherwise {
                  z := z + B(theta(14)).asSInt
                }
                xtmp := xval >> U(15)
                ytmp := yval >> U(15)
              }
              is(U(15, log2Up(maxIters) bits)){
                when(y < S(0, 18 bits)){
                  z := z - B(theta(15)).asSInt
                }.otherwise {
                  z := z + B(theta(15)).asSInt
                }
                xtmp := xval >> U(16)
                ytmp := yval >> U(16)
              }
            }
            
            when(viter === (iters)){
              //arbitration.haltItself := False
              goto(stateSaturate)
              z := z
              x := x
              y := y
              //execute.output(REGFILE_WRITE_DATA) := x(17 downto 2) ## z(15 downto 0)
              /*when(sign(0)){
                execute.output(REGFILE_WRITE_DATA) := x(17 downto 2) ## (z(15) ## z(15 downto 1))
              }.otherwise{
                execute.output(REGFILE_WRITE_DATA) := x(17 downto 2) ## (z(15) ## z(15 downto 1))
              }*/
            }
          }
        }

        val stateSaturate : State = new State{
          whenIsActive{
            arbitration.haltItself := True
            when(z(16) =/= z(15)){
              z.setAllTo(~z(16))
              z(15):=z(16)
              z(16):=z(16)
            }
            goto(stateNormalize)
          }
        }

        val stateNormalize : State = new State{
          whenIsActive{
            arbitration.haltItself := True
            when(sign(0) && ~z(15)){
              z := 0x7FFF-(z>>U(1))
            }.elsewhen(sign(0) && z(15)){
              z := 0x8000-(z>>U(1))
            }.otherwise{
              z := z>>U(1)
            }
            goto(stateOutput)
          }
        }

        val stateOutput : State = new State{
          whenIsActive{
            arbitration.haltItself := False
            goto(stateInit)
            execute.output(REGFILE_WRITE_DATA) := x(17 downto 2) ## z(15 downto 0)
          }
        }
      }
    }
  }
}

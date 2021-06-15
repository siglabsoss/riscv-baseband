package vexriscv.demo

import vexriscv.plugin._
import vexriscv.ip.{DataCacheConfig, InstructionCacheConfig}
import vexriscv.{plugin, VexRiscv, VexRiscvConfig}
import spinal.core._

object GenFullNoMmuNoCacheXbaseband extends App{
  def cpu() = new VexRiscv(
    config = VexRiscvConfig(
      plugins = List(
        new CsrPlugin(CsrPluginConfig(catchIllegalAccess = false,
          mvendorid      = null,
          marchid        = null,
          mimpid         = null,
          mhartid        = null,
          misaExtensionsInit = 66,
          misaAccess     = CsrAccess.NONE,
          mtvecAccess    = CsrAccess.NONE,
          mtvecInit      = 0x00000020l,
          mepcAccess     = CsrAccess.READ_WRITE,
          mscratchGen    = false,
          mcauseAccess   = CsrAccess.READ_ONLY,
          mbadaddrAccess = CsrAccess.READ_ONLY,
          mcycleAccess   = CsrAccess.NONE,
          minstretAccess = CsrAccess.NONE,
          ecallGen       = false,
          wfiGen         = true,
          ucycleAccess   = CsrAccess.NONE)),
        new DmaCsrPlugin("0",0xB08),
        new DmaCsrPlugin("1",0xC08),
        new InterruptCsrPlugin(0xD00),
        new TimerCsrPlugin(0xE00),
        new RingBusCsrPlugin("0",0xE10),
        new GpioCsrPlugin(22,0xE20),
        new RingBusCsrPlugin("1",0xE30),
        new PcManagerSimplePlugin(
          resetVector = 0x00000000l,
          relaxedPcCalculation = true
        ),
        new IBusSimplePlugin(
          interfaceKeepData = false,
          catchAccessFault = false
        ),
        new DBusSimplePlugin(
          catchAddressMisaligned = false,
          catchAccessFault = false
        ),
        new DecoderSimplePlugin(
          catchIllegalInstruction = true
        ),
        new RegFilePlugin(
          regFileReadyKind = plugin.SYNC,
          zeroBoot = false
        ),
        new IntAluPlugin,
        new SrcPlugin(
          separatedAddSub = false,
          executeInsertion = true
        ),
        new FullBarrielShifterPlugin,
        new HazardSimplePlugin(
          bypassExecute           = true,
          bypassMemory            = true,
          bypassWriteBack         = true,
          bypassWriteBackBuffer   = true,
          pessimisticUseSrc       = false,
          pessimisticWriteRegFile = false,
          pessimisticAddressMatch = false
        ),
        // new MulPlugin,
        // new DivPlugin,
        
        new DebugPlugin(ClockDomain.current.clone(reset = Bool().setName("debugReset"))),
        new Xbaseband,
        new BranchPlugin(
          earlyBranch = false,
          catchAddressMisaligned = true,
          prediction = STATIC
        ),
        

        new YamlPlugin("cpu0.yaml")
      )
    )
  )

  SpinalVerilog(cpu())
}

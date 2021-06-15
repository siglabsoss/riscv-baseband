package vexriscv.demo

import spinal.core._
import spinal.lib._
import spinal.lib.bus.amba3.apb._
import spinal.lib.bus.misc.SizeMapping
import spinal.lib.com.jtag.Jtag
import spinal.lib.com.uart._
import spinal.lib.io.{InOutWrapper, TriStateArray}
import spinal.lib.misc.{InterruptCtrl, Prescaler, Timer}
import spinal.lib.soc.pinsec.{PinsecTimerCtrl, PinsecTimerCtrlExternal}
import vexriscv.plugin._
import vexriscv.{VexRiscv, VexRiscvConfig, plugin}

import scala.collection.mutable.ArrayBuffer


case class XbbRiscvConfig(coreFrequency : HertzNumber,
  onChipRam          : Boolean,
  onChipRamSize      : BigInt,
  onChipRamHexFile   : String,
  pipelineDBus       : Boolean,
  pipelineMainBus    : Boolean,
  pipelineApbBridge  : Boolean,
  gpioWidth          : Int,
  uartCtrlConfig     : UartCtrlMemoryMappedConfig,
  cpuPlugins         : ArrayBuffer[Plugin[VexRiscv]]){
  require(pipelineApbBridge || pipelineMainBus, "At least pipelineMainBus or pipelineApbBridge should be enable to avoid wipe transactions")
}

object XbbRiscvConfig{
  def default =  XbbRiscvConfig(
    coreFrequency         = 125 MHz,
    onChipRam             = false,
    onChipRamSize         = 8 kB,
    onChipRamHexFile      = null,
    pipelineDBus          = true,
    pipelineMainBus       = true,
    pipelineApbBridge     = true,
    gpioWidth = 32,
    uartCtrlConfig     = UartCtrlMemoryMappedConfig(
      uartCtrlConfig = UartCtrlGenerics(
        dataWidthMax = 8,
        clockDividerWidth = 20,
        preSamplingSize = 1,
        samplingSize = 3,
        postSamplingSize = 1
      ),
      initConfig = UartCtrlInitConfig(
        baudrate = 115200,
        dataLength = 7,
        parity = UartParityType.NONE,
        stop = UartStopType.ONE
      ),
      txFifoDepth = 16,
      rxFifoDepth = 16
    ),
    cpuPlugins = ArrayBuffer( //DebugPlugin added by the toplevel
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
          //        earlyInjection = false
      ),
      //      new CsrPlugin(CsrPluginConfig.smallest(mtvecInit = 0x80000020l)),
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
        wfiGen         = false,
        ucycleAccess   = CsrAccess.NONE)),
      new DmaCsrPlugin("0",0xB08),
      new DmaCsrPlugin("1",0xB18),
      new DmaCsrPlugin("2",0xB28),
      //Reserve 0xB30-0xB3F for riscv profiling
      new MapperMoverCsrPlugin(0xC00),
      //        new InterruptCsrPlugin(0xD00),
      new TimerCsrPlugin(0xE00),
      new RingBusCsrPlugin("0",0xE10),
      new GpioCsrPlugin(32,0xE20),
      new RingBusCsrPlugin("1",0xE30),
      new NCOCsrPlugin("0",0xE40),
      new GenericOutCsrPlugin("slicer",0xE50),
      new SatDetectCsrPlugin(0xE60),
      new ControlStatusCsrPlugin(0xE70),
      new DEngineCsrPlugin(0xE80),
      //new DemapperCsrPlugin(0xE80),
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
      new MulPlugin,
      new DivPlugin,
      new FullBarrielShifterPlugin,
      new HazardSimplePlugin(
        bypassExecute = true,
        bypassMemory = true,
        bypassWriteBack = true,
        bypassWriteBackBuffer = true,
        pessimisticUseSrc = false,
        pessimisticWriteRegFile = false,
        pessimisticAddressMatch = false
      ),
      new Xbaseband,
      new XbbVectorCordic,
      new BranchPlugin(
        earlyBranch = false,
        catchAddressMisaligned = true,
        prediction = STATIC
      ),
      new YamlPlugin("cpu0.yaml")
    )
  )

  def fast = {
    val config = default

    //Replace HazardSimplePlugin to get datapath bypass
    config.cpuPlugins(config.cpuPlugins.indexWhere(_.isInstanceOf[HazardSimplePlugin])) = new HazardSimplePlugin(
      bypassExecute = true,
      bypassMemory = true,
      bypassWriteBack = true,
      bypassWriteBackBuffer = true
    )
    //    config.cpuPlugins(config.cpuPlugins.indexWhere(_.isInstanceOf[LightShifterPlugin])) = new FullBarrielShifterPlugin()

    config
  }

  def onChipRamConfig = {
    val config = default

    //Change reset vector to 0x80000000l
    config.cpuPlugins(config.cpuPlugins.indexWhere(_.isInstanceOf[PcManagerSimplePlugin])) = new PcManagerSimplePlugin(
      resetVector = 0x80000000l,
      relaxedPcCalculation = true
    )

    config
  }
}


case class XbbRiscv(config : XbbRiscvConfig) extends Component{
  import config._

  val io = new Bundle {
    //Clocks / reset
    val asyncReset = in Bool
    val mainClk = in Bool

    val iBus = master(IBusSimpleBus(false)).setName("iBus")

    val externalInterrupt = in Bits(6 bits)
    //Main components IO
    val jtag = slave(Jtag()).setName("jtag")
    val uart = master(Uart())
    /*val simpleBusConfig = SimpleBusConfig(
     addressWidth = 32,
     dataWidth = 32
     )*/
    val scalarMemBus = master(SimpleBus(SimpleBusConfig(addressWidth = 32, dataWidth = 32))).setName("scalarMemBus")
    val vmemBus = master(SimpleBus(SimpleBusConfig(addressWidth = 32, dataWidth = 32)))

    val xbasebandBus = master(XbasebandBus()).setName("xbaseband")

    //CSRs
    //DMA In
    val iDmaReset = master(DmaReset()).setName("dma_0")
    val iDmaStatus = slave(DmaStatus()).setName("dma_0")
    val iDmaInterruptClear = master(DmaInterruptClear()).setName("dma_0")
    val iDmaConfigStream = master(DmaConfigStream()).setName("dma_0")
    //DMA Out
    val oDmaReset = master(DmaReset()).setName("dma_1")
    val oDmaStatus = slave(DmaStatus()).setName("dma_1")
    val oDmaInterruptClear = master(DmaInterruptClear()).setName("dma_1")
    val oDmaConfigStream = master(DmaConfigStream()).setName("dma_1")
    //DMA In - NCO
    val ncoDmaReset = master(DmaReset()).setName("dma_2")
    val ncoDmaStatus = slave(DmaStatus()).setName("dma_2")
    val ncoDmaInterruptClear = master(DmaInterruptClear()).setName("dma_2")
    val ncoDmaConfigStream = master(DmaConfigStream()).setName("dma_2")

    val mapmov = master(MapperMoverControl()).setName("mapmov")

    //Timer
    val timerStatus = master(TimerStatus())

    //Ringbus 0
    val ringbusInterruptClear_0 = master(RingBusInterruptClear()).setName("ringbus_0")
    val ringbusWrite_0 = master(RingBusWriteStream()).setName("ringbus_0")
    val ringbusRead_0 = slave(RingBusReadStream()).setName("ringbus_0")
    val ringbusStatus_0 = slave(RingBusStatus()).setName("ringbus_0")
    //Ringbus 1
    val ringbusInterruptClear_1 = master(RingBusInterruptClear()).setName("ringbus_1")
    val ringbusWrite_1 = master(RingBusWriteStream()).setName("ringbus_1")
    val ringbusRead_1 = slave(RingBusReadStream()).setName("ringbus_1")
    val ringbusStatus_1 = slave(RingBusStatus()).setName("ringbus_1")

    //    NCO config
    val ncoReset = master(NCOReset()).setName("nco")
    val ncoStatus = slave(NCOStatus()).setName("nco")
    val ncoConfigStream = master(NCOConfigStream()).setName("nco")

    //GPIO
    val gpio = master(TriStateArray(32 bits))

    //Generic Out
    val slicer = master(GenericOutBundle()).setName("slicer")

    //Sat Detect
    val satDetect = slave(SatDetectBundle()).setName("satDetect")

    //Control and Status
    val csStatus = slave(CSStatus()).setName("status")
    val csControl = master(CSControl()).setName("control")

    //D-Engine config
    val dengineConfig = master(DEngineConfigBundle()).setName("dengine");
    //    val demapperControl = master(DemapperControl()).setName("demapper")
    //Peripherals IO
    //    val gpioA = master(TriStateArray(gpioWidth bits))
    //    val uart = master(Uart())
  }


  val resetCtrlClockDomain = ClockDomain(
    clock = io.mainClk,
    config = ClockDomainConfig(
      resetKind = BOOT
    )
  )

  val resetCtrl = new ClockingArea(resetCtrlClockDomain) {
    val mainClkResetUnbuffered  = False

    //Implement an counter to keep the reset axiResetOrder high 64 cycles
    // Also this counter will automatically do a reset when the system boot.
    val systemClkResetCounter = Reg(UInt(6 bits)) init(0)
    when(systemClkResetCounter =/= U(systemClkResetCounter.range -> true)){
      systemClkResetCounter := systemClkResetCounter + 1
      mainClkResetUnbuffered := True
    }
    when(BufferCC(io.asyncReset)){
      systemClkResetCounter := 0
    }

    //Create all reset used later in the design
    val mainClkReset = RegNext(mainClkResetUnbuffered)
    val systemReset  = RegNext(mainClkResetUnbuffered)
  }


  val systemClockDomain = ClockDomain(
    clock = io.mainClk,
    reset = resetCtrl.systemReset,
    frequency = FixedFrequency(coreFrequency)
  )

  val debugClockDomain = ClockDomain(
    clock = io.mainClk,
    reset = resetCtrl.mainClkReset,
    frequency = FixedFrequency(coreFrequency)
  )

  val system = new ClockingArea(systemClockDomain) {
    val simpleBusConfig = SimpleBusConfig(
      addressWidth = 32,
      dataWidth = 32
    )

    //Arbiter of the cpu dBus/iBus to drive the mainBus
    //Priority to dBus, !! cmd transactions can change on the fly !!
    //    val mainBusArbiter = new XbbMasterArbiter(simpleBusConfig)

    val dBus = DBusSimpleBus()
    val sbus = SimpleBus(simpleBusConfig)
    //Instanciate the CPU
    val cpu = new VexRiscv(
      config = VexRiscvConfig(
        plugins = cpuPlugins += new DebugPlugin(debugClockDomain)
      )
    )

    //Checkout plugins used to instanciate the CPU to connect them to the SoC
    val timerInterrupt = False
    val externalInterrupt = Bits(6 bits)
    for(plugin <- cpu.plugins) plugin match{
      case plugin : IBusSimplePlugin => io.iBus <> plugin.iBus
      case plugin : DBusSimplePlugin => {
        if(!pipelineDBus)
          dBus <> plugin.dBus
        else {
          dBus.cmd << plugin.dBus.cmd.halfPipe()
          dBus.rsp <> plugin.dBus.rsp
        }
      }
      case plugin : CsrPlugin        => {
        //        plugin.externalInterrupt := externalInterrupt
        plugin.timerInterrupt := timerInterrupt
        io.externalInterrupt <> plugin.externalInterrupt
      }
      case plugin : DebugPlugin         => plugin.debugClockDomain{
        resetCtrl.systemReset setWhen(RegNext(plugin.io.resetOut))
        io.jtag <> plugin.io.bus.fromJtag()
      }
      case plugin : DmaCsrPlugin => {
        if(plugin.e == "0") {
          io.iDmaConfigStream <> plugin.dma
          io.iDmaStatus <> plugin.status
          io.iDmaInterruptClear <> plugin.interrupt_clear
          io.iDmaReset <> plugin.reset
        }
        else if (plugin.e == "1") {
          io.oDmaConfigStream <> plugin.dma
          io.oDmaStatus <> plugin.status
          io.oDmaInterruptClear <> plugin.interrupt_clear
          io.oDmaReset <> plugin.reset
        }
        else if (plugin.e == "2") {
          io.ncoDmaConfigStream <> plugin.dma
          io.ncoDmaStatus <> plugin.status
          io.ncoDmaInterruptClear <> plugin.interrupt_clear
          io.ncoDmaReset <> plugin.reset
        }

      }
      case plugin : MapperMoverCsrPlugin => {
        io.mapmov <> plugin.mapper_mover_control
      }
      case plugin : TimerCsrPlugin => {
        io.timerStatus <> plugin.ctimer
      }

      case plugin : RingBusCsrPlugin => {
        if(plugin.e == "0") {
          io.ringbusInterruptClear_0 <> plugin.interrupt_clear
          io.ringbusWrite_0 <> plugin.write
          io.ringbusRead_0 <> plugin.read
          io.ringbusStatus_0 <> plugin.status
        }
        else if (plugin.e == "1") {
          io.ringbusInterruptClear_1 <> plugin.interrupt_clear
          io.ringbusWrite_1 <> plugin.write
          io.ringbusRead_1 <> plugin.read
          io.ringbusStatus_1 <> plugin.status
        }

      }
      case plugin : GpioCsrPlugin => {
        io.gpio <> plugin.gpio
      }
      case plugin : Xbaseband => {
        io.xbasebandBus <> plugin.xbaseband
      }
      case plugin : NCOCsrPlugin => {
        if(plugin.e == "0") {
          io.ncoReset <> plugin.reset
          io.ncoStatus <> plugin.status
          io.ncoConfigStream <> plugin.nco
        }
      }
      case plugin : GenericOutCsrPlugin => {
        if(plugin.e == "slicer") {
          io.slicer <> plugin.value
        }
      }
      case plugin : SatDetectCsrPlugin => {
        io.satDetect <> plugin.satDetect
      }
      case plugin : ControlStatusCsrPlugin => {
        io.csControl <> plugin.control
        io.csStatus <> plugin.status
      }

      case plugin : DEngineCsrPlugin => {
        io.dengineConfig <> plugin.configBundle
      }
      /*      case plugin : DemapperCsrPlugin => {
       io.demapperControl <> plugin.demapper_control
       }*/
      //      case plugin
      case _ =>
    }



    //****** MainBus slaves ********
      val ram = if(onChipRam) new XbbSimpleBusRam(
        memInit = "xbb_scalar_mem.hex",
        onChipRamSize = onChipRamSize,
        onChipRamHexFile = onChipRamHexFile,
        simpleBusConfig = simpleBusConfig
      ) else null

    val apbBridge = new XbbRiscvSimpleBusToApbBridge(
      apb3Config = Apb3Config(
        addressWidth = 20,
        dataWidth = 32
      ),
      pipelineBridge = pipelineApbBridge,
      simpleBusConfig = simpleBusConfig
    )



    //******** APB peripherals *********
    /*val gpioACtrl = Apb3Gpio(gpioWidth = gpioWidth)
     io.gpioA <> gpioACtrl.io.gpio*/

    val uartCtrl = Apb3UartCtrl(uartCtrlConfig)
    uartCtrl.io.uart <> io.uart
    //    externalInterrupt(0) setWhen(uartCtrl.io.interrupt)
    /*
     val timer = new MuraxApb3Timer()
     timerInterrupt setWhen(timer.io.interrupt)*/



    //******** Memory mappings *********
    val apbDecoder = Apb3Decoder(
      master = apbBridge.io.apb,
      slaves = List[(Apb3, SizeMapping)](
        uartCtrl.io.apb  -> (0x00000, 4 kB)
      )
    )
    /*    val dbus2simple = new DBus2Simple(simpleBusConfig = simpleBusConfig)
     dbus2simple.io.dbus := dBus
     sbus := dbus2simple.io.bus*/


    val mainBusDecoder = new Area {
      //      val dbus2simple  = new DBus2Simple(dbus = dBus, simpleBusConfig = simpleBusConfig)
      if(onChipRam) {
        val logic = new XbbSimpleBusDecoder(
          master_dbus = dBus,
          simpleBusConfig = simpleBusConfig,
          specification = List[(SimpleBus,SizeMapping)](
            io.scalarMemBus -> (0x00000000l, onChipRamSize),
            io.vmemBus -> (0x0040000l, 1 MB),
            ram.io.bus -> (0x80000000l, onChipRamSize),
            apbBridge.io.simpleBus -> (0xF0000000l, 1 MB)
          ),
          pipelineMaster = pipelineMainBus
        )
      } else {
        val logic = new XbbSimpleBusDecoder(
          master_dbus = dBus,
          simpleBusConfig = simpleBusConfig,
          specification = List[(SimpleBus,SizeMapping)](
            io.scalarMemBus -> (0x00000000l, onChipRamSize),
            io.vmemBus -> (0x0040000l, 1 MB),
            apbBridge.io.simpleBus -> (0xF0000000l, 1 MB)
          ),
          pipelineMaster = pipelineMainBus
        )
      }
    }
  }
}

object XbbRiscv{
  def main(args: Array[String]) {
    SpinalVerilog(InOutWrapper(XbbRiscv(XbbRiscvConfig.default.copy(onChipRamSize = 256 kB, onChipRamHexFile = "src/main/ressource/hex/muraxDemo.hex"))))
  }
}

object XbbRiscvWithRam{
  def main(args: Array[String]) {
    SpinalVerilog(InOutWrapper(XbbRiscv(XbbRiscvConfig.onChipRamConfig.copy(onChipRam = true, onChipRamSize = 256 kB))))
  }
}


object XbbRiscvDhrystoneReady{
  def main(args: Array[String]) {
    SpinalVerilog(XbbRiscv(XbbRiscvConfig.fast.copy(onChipRamSize = 256 kB)))
  }
}

object XbbRiscvDhrystoneReadyMulDivStatic{
  def main(args: Array[String]) {
    SpinalVerilog({
      val config = XbbRiscvConfig.fast.copy(onChipRamSize = 256 kB)
      config.cpuPlugins += new MulPlugin
      config.cpuPlugins += new DivPlugin
      config.cpuPlugins.remove(config.cpuPlugins.indexWhere(_.isInstanceOf[BranchPlugin]))
      config.cpuPlugins +=new BranchPlugin(
        earlyBranch = false,
        catchAddressMisaligned = false,
        prediction = STATIC
      )
      config.cpuPlugins.remove(config.cpuPlugins.indexWhere(_.isInstanceOf[LightShifterPlugin]))
      config.cpuPlugins += new FullBarrielShifterPlugin
      XbbRiscv(config)
    })
  }
}

//Will blink led and echo UART RX to UART TX   (in the verilator sim, type some text and press enter to send UART frame to the XbbRiscv RX pin)
object XbbRiscvWithRamInit{
  def main(args: Array[String]) {
    SpinalVerilog(XbbRiscv(XbbRiscvConfig.default.copy(onChipRamSize = 256 kB, onChipRamHexFile = "src/main/ressource/hex/muraxDemo.hex")))
  }
}


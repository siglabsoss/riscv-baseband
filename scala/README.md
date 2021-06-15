RISCV processor with custom extensions

## GenFullNoMmuNoCacheXbaseband

  * RV32I
  * 5 stage pipeline
  * no MMU
  * no Cache
  * Xbaseband plugin
  * CSR plugin

### Xbaseband plugin

`Xbaseband.scala`

### DMA plugin

`DmaCsr.scala`

## Build steps

### local

```sh
cd ~/work/github/SpinalHDL/VexRiscv
cp ../../siglabsoss/riscv-baseband/scala/* src/main/scala/vexriscv/demo/
sbt "run-main vexriscv.demo.GenFullNoMmuNoCacheXbaseband"
cp VexRiscv.v ../../siglabsoss/riscv-baseband/hdl/generated/VexRiscv.v
```

### system

```sh
export VEX_PATH=/mnt/overflow/work/VexRiscv
export BASEBAND_GIT_PATH=/home/x/work/riscv-baseband

cd ${VEX_PATH}
cp ${BASEBAND_GIT_PATH}/scala/* src/main/scala/vexriscv/demo/
sbt "run-main vexriscv.demo.GenFullNoMmuNoCacheXbaseband"
cp VexRiscv.v ${BASEBAND_GIT_PATH}/hdl/generated/VexRiscv.v
```

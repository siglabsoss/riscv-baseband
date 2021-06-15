## ISA space

  * Greenfield or Brownfield ?
  * Name: `Xbaseband` ?

```
xxxxxxxx_xxxxxxxx_xxxxxxxx_xxxbbb11 32-bit (bbb !== 111)

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx00011
                            00      LOAD      (I)
                            01      STORE     (I)
                            10      MADD
                            01      BRANCH    (I)

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx00111
                            00      LOAD-FP
                            01      STORE-FP
                            10      MSUB
                            01      JALR      (I)

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx01011
                            00      Custom-0            <--
                            01      Custom-1            <--
                            10      NMSUB               <--
                            01      reserved            <--

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx01111
                            00      MISC-MEM  (I)
                            01      AMO
                            10      NMADD
                            01      JAL       (I)

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx10011
                            00      OP-IMM    (I)
                            01      OP        (I, M)
                            10      OP-FP
                            01      SYSTEM    (I)

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx10111
                            00      AUIPC     (I)
                            01      LUI       (I)
                            10      reserved
                            01      reserved

xxxxxxxx_xxxxxxxx_xxxxxxxx_xxx11011
                            00      OP-IMM-32 (64I)     <--
                            01      OP-32     (64I)     <--
                            10      Custom-2            <--
                            01      Custom-3            <--
```

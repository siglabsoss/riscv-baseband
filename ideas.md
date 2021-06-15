#### Memory map

Each slice instruction generates address for own memory slice.

Memory map is divided into multiple logical regions with different properties.

Logical regions are mapped to the same (smaller) physical memory.

Total physical memory: `32 banks x 2048 depth x 32 bit = 256 KiB`


When used as address, vector register has the following format:

![vreg-format](assets/vreg-format.svg)

  * **Bank Address** directly used as word address inside own memory slice;
  * **g** guard bit. Wrap around mechanism;
  * **permutation** controls permutation network
  * **size** size of memory access operation;

##### vreg.size

| size | access type    |
|:-----|:---------------|
| 0    | word           |
| 1    | low half word  |
| 2    | high half word |
| 3    | byte 0         |
| 4    | byte 1         |
| 5    | byte 2         |
| 6    | byte 3         |
| 7    | black hole     |

**Reads from Black Hole should return 0x00000000**

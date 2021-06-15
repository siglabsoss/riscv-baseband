import re
import argparse
import sys


class HexHandler:
    def __init__(self):
        self.program_opcode = []
        self.V_MEM_START = 0x40000
        self.V_MEM_LEN = 0x40000


    def get_vmem(self):
        return self.program_opcode[(self.V_MEM_START/4):((self.V_MEM_START+self.V_MEM_LEN)/4)]

    def open_get_hex(self, filepath):
        try:
            with open(filepath) as bootprogram:
                self.program_opcode = []
                line = bootprogram.readline()

                self.program_opcode = [0] * ((self.V_MEM_START+self.V_MEM_LEN)/4)

                self._parse_hex_reset()
                while line:
                    self._parse_hex(line)
                    line = bootprogram.readline()

        except IOError:
            logger.info('File ' + filepath + ' does not exist')

    def _parse_hex_reset(self):
        '''We have hex files that have an address "roll over" event
        We need _parse_hex to keep state, and this resets that state

        :return:
        '''
        self.parse_hex_upper = 0


    def _parse_hex(self, line):
        '''Method to parse bootloader program in HEX form

        Args:
            fpga (str): Name of FPGA to parse opcode from HEX
            line (str): A line of Intel Hex code
        '''
        line = line[1:]
        bytecount = int(line[0:2], 16)
        address = int(line[2:6], 16) + self.parse_hex_upper
        rec_type = int(line[6:8], 16)
        if rec_type == 2:
            # we need to catch this record type for upper addresses (vmem)
            new_base = int(line[8:8+4], 16)
            self.parse_hex_upper = new_base*16
            print("new base ", self.parse_hex_upper)
        if rec_type == 0:
            data_out = line[8:(8+2*(bytecount))]
            for index in range(0, len(data_out), 8):
                opcode = int(data_out[index + 6:index + 8] +\
                             data_out[index + 4:index + 6] +\
                             data_out[index + 2: index+ 4] +\
                             data_out[index: index + 2], 16)

                array_index = (address / 4) + (index / 8)
                # print("index", index, "address", address, "calcaddr", hex(array_index*4), "op", hex(opcode))
                # print("  " + line[2:6])

                self.program_opcode[array_index] = opcode




def main(pathin, pathsout):
    global current_line
    #
    assert len(pathsout) == 16

    hh = HexHandler()

    hh.open_get_hex(pathin)

    vmem = hh.get_vmem()
    # print(hh.get_vmem())

    #
    inf = open(pathin, 'r')
    ofs = [open(path, 'w') for path in pathsout]

    vmem_bank_index=0
    vmem_bank_addr=0
    for word in vmem:
        ofs[vmem_bank_index].write('\n@')
        ofs[vmem_bank_index].write(hex((vmem_bank_addr))[2:])
        ofs[vmem_bank_index].write('\n')

        data_line = hex(word)[2:]
        data_line = "0" * (8-len(data_line)) + data_line

        ofs[vmem_bank_index].write(data_line)
        ofs[vmem_bank_index].write('\n')

        vmem_bank_index+=1
        if vmem_bank_index==16:
            vmem_bank_addr+=1
        vmem_bank_index%=16



help_text = """
This script takes gcc's .hex output from a compiled RiscV program,
and creates 4 mif files which we will load into memory and execute.

For Example:

  scripts/hex2mif.py -i cpp/first_try/build/atomic.hex -o0 prog0.mif -o1 prog1.mif -o2 prog2.mif -o3 prog3.mif
"""


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=help_text, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-i', action='store', default=None, help='Input assembly file')
    parser.add_argument('-o0', action='store', default=None, help='Output mif file 0')
    parser.add_argument('-o1', action='store', default=None, help='Output mif file 1')
    parser.add_argument('-o2', action='store', default=None, help='Output mif file 2')
    parser.add_argument('-o3', action='store', default=None, help='Output mif file 3')
    parser.add_argument('-o4', action='store', default=None, help='Output mif file 4')
    parser.add_argument('-o5', action='store', default=None, help='Output mif file 5')
    parser.add_argument('-o6', action='store', default=None, help='Output mif file 6')
    parser.add_argument('-o7', action='store', default=None, help='Output mif file 7')
    parser.add_argument('-o8', action='store', default=None, help='Output mif file 8')
    parser.add_argument('-o9', action='store', default=None, help='Output mif file 9')
    parser.add_argument('-o10', action='store', default=None, help='Output mif file 10')
    parser.add_argument('-o11', action='store', default=None, help='Output mif file 11')
    parser.add_argument('-o12', action='store', default=None, help='Output mif file 12')
    parser.add_argument('-o13', action='store', default=None, help='Output mif file 13')
    parser.add_argument('-o14', action='store', default=None, help='Output mif file 14')
    parser.add_argument('-o15', action='store', default=None, help='Output mif file 15')
    options = parser.parse_args()

    if options.i and options.o0 and options.o1 and options.o2 and options.o3 and options.o4 and options.o5 and options.o6 and options.o7 and options.o8 and options.o9 and options.o10 and options.o11 and options.o12 and options.o13 and options.o14 and options.o15:
        main(options.i, [options.o0, options.o1, options.o2, options.o3, options.o4, options.o5, options.o6, options.o7, options.o8, options.o9, options.o10, options.o11, options.o12, options.o13, options.o14, options.o15])
    else:
        parser.print_help()


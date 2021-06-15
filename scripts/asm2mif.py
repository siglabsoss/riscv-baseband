import re
import argparse


def main(pathin, pathsout):

    assert len(pathsout) == 4

    inf = open(pathin, 'r')
    ofs = [open(path, 'w') for path in pathsout]

    shift = [0, 8, 16, 24]
    mask = [0xff, 0xff00, 0xff0000, 0xff000000]

    baseaddr = False

    for l in inf:

        if 'file format elf32' in l:
            [of.write('\n// ') for of in ofs]
            [of.write(l) for of in ofs]
        elif 'Disassembly of section' in l:
            [of.write('\n// ') for of in ofs]
            [of.write(l) for of in ofs]
        else:
            # in the message below, a comma means "followed by"

            # look for the beginning of the line, (a single hex character, as many non spaces as possible), (any characters)
            r1 = re.search(r'^([0123456789abcdefABCDEF][^ ]*)(.*)', l)
            if r1:
                baseaddr = int(r1.group(1), 16)
                [of.write('\n') for of in ofs]  # extra newline to make the sections look nice
                [of.write('@') for of in ofs]
                [of.write(  hex(int(baseaddr/4))[2:]  ) for of in ofs]
                [of.write(' //') for of in ofs]
                [of.write(r1.group(2)) for of in ofs]
                [of.write('\n') for of in ofs]
            # look for the beginnign of the line, 1-5 spaces, 1-8 hex characters, a :, a tab, (a single hex character, as many non spaces as possible), (any characters)
            r2 = re.search(r'^ {1,5}([0123456789abcdefABCDEF]{1,8}):\t([0123456789abcdefABCDEF][^ ]*)(.*)', l)
            if r2:
                # group 1 is the 1c: part of the line
                # as far as I can tell from this limited example, we don't need to interpret this
                # print r2.group(2), r2.group(3)

                opcode = int(r2.group(2),16)
                for i, of in enumerate(ofs):
                    subop = (opcode & mask[i]) >> shift[i]

                    subop_hex = hex(subop)[2:]

                    if len(subop_hex) == 1:
                        subop_hex = '0' + subop_hex

                    of.write(subop_hex)
                    of.write(' //')
                    of.write(r2.group(3))
                    of.write('\n')

                # print(r1.group(1), r1.group(2))

        # mo = re.search(r'^00', l)
        # print(mo)

    # after the for above
    [of.write('\n') for of in ofs]
    [of.close() for of in ofs]
    for path in pathsout:
        print("writing " + path)


help_text = """
This script takes gcc's .asm output from a compiled RiscV program,
and creates 4 mif files which we will load into memory and execute.

For Example:

  scripts/asm2mif.py -i cpp/first_try/build/atomic.asm -o0 prog0.mif -o1 prog1.mif -o2 prog2.mif -o3 prog3.mif
"""


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description=help_text, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-i', action='store', default=None, help='Input assembly file')
    parser.add_argument('-o0', action='store', default=None, help='Output mif file 0')
    parser.add_argument('-o1', action='store', default=None, help='Output mif file 1')
    parser.add_argument('-o2', action='store', default=None, help='Output mif file 2')
    parser.add_argument('-o3', action='store', default=None, help='Output mif file 3')
    options = parser.parse_args()

    if options.i and options.o0 and options.o1 and options.o2 and options.o3:
        main(options.i, [options.o0,options.o1,options.o2,options.o3])
    else:
        parser.print_help()


    # pathin = 'cpp/first_try/build/atomic.asm'
    #
    # p = [None,None,None,None]
    #
    # p[0] = 'myout0.mif'
    # p[1] = 'myout1.mif'
    # p[2] = 'myout2.mif'
    # p[3] = 'myout3.mif'
    #
    #
    # main(pathin, p)
import re
import argparse




current_line = ""

def parse_hex_line( line ):
    global current_line
    if len( current_line ) == 0: return None
    bytecount = int( line[0:2], 16 )
    address = int( line[2:6], 16 )
    rec_type = int( line[6:8], 16 )

    data_out = None


    rec_output = str(hex(address)) + '\t' + str(bytecount) + '\t'
    if rec_type == 0:
        rec_output += 'data'
        rec_output += '\t\t' + line[8:(8+2*(bytecount))]
        data_out = line[8:(8+2*(bytecount))]
    elif rec_type == 1:
        rec_output += 'end of file'
    elif rec_type == 2:
        rec_output += 'ext segment addr'
    elif rec_type == 3:
        rec_output += 'start segment address'
    elif rec_type == 4:
        rec_output += 'ext linear addr'
    elif rec_type == 5:
        rec_output += 'start linear address'
    # print(rec_output)
    return address, bytecount, data_out





def main(pathin, pathsout):
    global current_line
    #
    assert len(pathsout) == 4
    #
    inf = open(pathin, 'r')
    ofs = [open(path, 'w') for path in pathsout]


    sec = []

    byte = "1"  # initial placeholder
    # print "Address\tLength\tType\t\tData"
    while byte != "":
        byte = inf.read(1)
        if byte == ":":
            #   (1) Parse the current line!
            res = parse_hex_line(current_line)

            if res is not None and res[2] is not None:
                sec.append(res)

            #   (2) Reset the current line to build the next one!
            current_line = ""
        else:
            current_line += byte
    # called 1 last time?
    res = parse_hex_line(current_line)
    if res is not None and res[2] is not None:
        sec.append(res)

    ###### disaster above ######
    flag=False
    for x in sec:
        addr = x[0]
        if(addr==0)&(flag==False):
            flag=True
        elif(addr==0)&(flag==True):
            break
        llen = x[1]
        bytes = x[2]

        consume = 0

        # check that every line is consitent
        assert llen * 2 == len(bytes)


        # assert llen >= 4, "if this fails, it means we wrote a new section to a mif file with no data"
        # start with addr

        # normally the hex file gives us 16 at a time
        # if this line has file 1 byte it in for instance
        # we would only write a section and bytes to 1 file
        llen_pegged = min(llen, 4)

        if llen_pegged < 4:
            ben=False

        # rip a new address section in each file
        # normally llen_pegged is 4
        for jj in range(llen_pegged):
            ofs[jj].write('\n@')
            ofs[jj].write(hex(int(addr/4))[2:])
            ofs[jj].write('\n')


        while consume < llen*2:
            bank = (consume/2) % 4
            bankrev = 3 - bank

            ofs[bank].write(bytes[consume:consume+2])
            ofs[bank].write('\n')

            consume += 2




        # print addr, llen, bytes



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
    options = parser.parse_args()

    if options.i and options.o0 and options.o1 and options.o2 and options.o3:
        main(options.i, [options.o0,options.o1,options.o2,options.o3])
    else:
        parser.print_help()


    # pathin = 'cpp/bootloader_example/build/atomic.hex'
    # #
    # p = [None,None,None,None]
    # #
    # p[0] = 'scalar0.mif'
    # p[1] = 'scalar1.mif'
    # p[2] = 'scalar2.mif'
    # p[3] = 'scalar3.mif'
    # #
    # #
    # main(pathin, p)
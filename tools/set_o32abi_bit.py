#!/usr/bin/env python3

import argparse
import struct
import sys

parser = argparse.ArgumentParser()

parser.add_argument('file', help='input file')
args = parser.parse_args()

with open(args.file, 'r+b') as f:
    magic = struct.unpack('>I', f.read(4))[0]
    if magic != 0x7F454C46:
        print('Error: Not an ELF file')
        sys.exit(1)

    f.seek(36)
    flags = struct.unpack('>I', f.read(4))[0]

    flags |= 0x00001000 # set EF_MIPS_ABI_O32
    f.seek(36)
    f.write(struct.pack('>I', flags))

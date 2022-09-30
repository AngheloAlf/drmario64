#!/usr/bin/env python3

import argparse
import struct

def main():
    description = "Extract an array of data from a binary file using a specified format.";

    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawTextHelpFormatter);
    parser.add_argument("file", help="Binary file to extract from");
    parser.add_argument("offset", help="Address into binary to start extraction");
    parser.add_argument("format", help="Python format-reading string denoting the structure of one element");
    parser.add_argument("count", help="Number of entries to extract");
    args = parser.parse_args()

    file = args.file;
    offset = int(args.offset, 16);
    format = args.format;
    count = int(args.count);

    size = struct.calcsize(format);

    f = open(file, "rb");

    f.seek(offset);

    i = 0;
    while (i < count):
        stuff = f.read(size);
        row = struct.unpack(format, stuff);
        print("{ ", end="");
        print(*map(hex, row), sep=", ", end=" },\n");
        i += 1;




if __name__ == "__main__":
    main();
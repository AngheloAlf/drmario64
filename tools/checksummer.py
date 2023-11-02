#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import ipl3checksum
from pathlib import Path
import struct
import sys

DEBUGGING = False

def printDebug(*args, **kwargs):
    if not DEBUGGING:
        return
    kwargs["flush"] = True
    print(*args, **kwargs)

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def updateChecksum(romBytes: bytearray):
    # Detect CIC
    cicKind = ipl3checksum.detectCIC(romBytes)
    if cicKind is None:
        eprint("Not able to detect CIC, defaulting to 6102")
        cicKind = ipl3checksum.CICKind.CIC_6102_7101
    printDebug(f"CIC kind: {cicKind.name}")

    # Calculate checksum
    calculatedChecksum = ipl3checksum.calculateChecksum(romBytes, cicKind)
    assert calculatedChecksum is not None, "Not able to calculate checksum"
    printDebug(f"checksum1: {calculatedChecksum[0]:X}")
    printDebug(f"checksum2: {calculatedChecksum[1]:X}")

    # Write checksum
    struct.pack_into(f">II", romBytes, 0x10, calculatedChecksum[0], calculatedChecksum[1])

def updaterMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="input rom filename")
    parser.add_argument("out_rom", help="output rom filename")
    parser.add_argument("-d", "--debug", help="Enable debug prints", action="store_true")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    outPath = Path(args.out_rom)

    global DEBUGGING
    DEBUGGING = args.debug

    printDebug(f"inPath:  {inPath}")
    printDebug(f"outPath: {outPath}")

    romBytes = bytearray(inPath.read_bytes())

    updateChecksum(romBytes)

    outPath.parent.mkdir(parents=True, exist_ok=True)
    outPath.write_bytes(romBytes)

if __name__ == "__main__":
    updaterMain()

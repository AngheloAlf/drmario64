#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import spimdisasm
from pathlib import Path

import compression_common


def romDecompressorMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="compressed input rom filename")
    parser.add_argument("out_rom", help="decompressed output rom filename")
    parser.add_argument("segments", help="path to segments file")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    outPath = Path(args.out_rom)
    segmentsPath = Path(args.segments)

    segmentDict = compression_common.readSegmentsCsv(segmentsPath)

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    sortedSegments = sorted(segmentDict.values())


    uncompressedSegments = []

    if sortedSegments[0].compressedRomOffset != 0:
        firstEntry = compression_common.SegmentEntry("", 0, sortedSegments[0].compressedRomOffset, "", compressed=False)
        uncompressedSegments.append(firstEntry)

    for i, entry in enumerate(sortedSegments[:-1]):
        # print(entry.compressedRomOffset)
        if entry.compressedRomOffsetEnd != sortedSegments[i+1].compressedRomOffset:
            newEntry = compression_common.SegmentEntry("", entry.compressedRomOffsetEnd, sortedSegments[i+1].compressedRomOffset, "", compressed=False)
            uncompressedSegments.append(newEntry)

    sortedSegments += uncompressedSegments
    sortedSegments.sort()

    with outPath.open("wb") as outRom:
        for entry in sortedSegments:
            # print(f"{entry.compressedRomOffset:X} {entry.compressedRomOffsetEnd:X}")
            segmentBytearray = inRom[entry.compressedRomOffset:entry.compressedRomOffsetEnd]
            if entry.compressed:
                print(f"Range [0x{entry.compressedRomOffset:06X}:0x{entry.compressedRomOffsetEnd:06X}]: Decompressing")
                outBytearray = compression_common.decompressZlib(segmentBytearray)
            else:
                print(f"Range [0x{entry.compressedRomOffset:06X}:0x{entry.compressedRomOffsetEnd:06X}]: Writing as-is")
                outBytearray = segmentBytearray
            outRom.write(outBytearray)

if __name__ == "__main__":
    romDecompressorMain()

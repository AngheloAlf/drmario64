#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import spimdisasm
from pathlib import Path

import compression_common

BASEROM_HASHES = {
    "us": "1a7936367413e5d6874abda6d623ad32",
    "cn": "dd291b9c65420fd892107f6c665b7a45",
    "gw": "697db27690b4f031cf91f28bc445a29f",
}


def romDecompressorMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="compressed input rom filename")
    parser.add_argument("out_rom", help="decompressed output rom filename")
    parser.add_argument("segments", help="path to segments file")
    parser.add_argument("version", help="version to process")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    outPath = Path(args.out_rom)
    segmentsPath = Path(args.segments)

    segmentDict = compression_common.readSegmentsCsv(segmentsPath, args.version)

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    romHash = spimdisasm.common.Utils.getStrHash(inRom)
    assert romHash == BASEROM_HASHES[args.version], f"Baserom's hash differs\n Expected '{BASEROM_HASHES[args.version]}', got '{romHash}'"

    sortedSegments = sorted(segmentDict.values())


    uncompressedSegments = []

    if sortedSegments[0].compressedRomOffset != 0:
        firstEntry = compression_common.SegmentEntry("", 0, sortedSegments[0].compressedRomOffset, "", 0, args.version, compressed=False)
        uncompressedSegments.append(firstEntry)

    for i, entry in enumerate(sortedSegments[:-1]):
        # print(entry.compressedRomOffset)
        if entry.compressedRomOffsetEnd != sortedSegments[i+1].compressedRomOffset:
            newEntry = compression_common.SegmentEntry("", entry.compressedRomOffsetEnd, sortedSegments[i+1].compressedRomOffset, "", 0, args.version, compressed=False)
            uncompressedSegments.append(newEntry)

    lastCompressedSegment = sortedSegments[-1]
    if lastCompressedSegment.compressedRomOffsetEnd != len(inRom):
        newEntry = compression_common.SegmentEntry("", lastCompressedSegment.compressedRomOffsetEnd, len(inRom), "", 0, args.version, compressed=False)
        uncompressedSegments.append(newEntry)

    sortedSegments += uncompressedSegments
    sortedSegments.sort()

    with outPath.open("wb") as outRom:
        offset = 0
        for entry in sortedSegments:
            # print(f"{entry.compressedRomOffset:X} {entry.compressedRomOffsetEnd:X}")
            segmentBytearray = inRom[entry.compressedRomOffset:entry.compressedRomOffsetEnd]
            if entry.compressed:
                print(f"Range [0x{entry.compressedRomOffset:06X}:0x{entry.compressedRomOffsetEnd:06X}]: Decompressing at offset 0x{offset:06X}")
                outBytearray = compression_common.decompressZlib(segmentBytearray)
            else:
                print(f"Range [0x{entry.compressedRomOffset:06X}:0x{entry.compressedRomOffsetEnd:06X}]: Writing as-is at offset 0x{offset:06X}")
                outBytearray = segmentBytearray

            # Align to a 0x10 boundary
            while len(outBytearray) % 0x10 != 0:
                outBytearray.append(0)

            outRom.write(outBytearray)
            offset += len(outBytearray)

if __name__ == "__main__":
    romDecompressorMain()

#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
import spimdisasm
from pathlib import Path


@dataclasses.dataclass
class SegmentEntry:
    compressedPath: Path
    uncompressedPath: Path
    uncompressedHash: str


def readSegmentsCsv(segmentsPath: Path) -> dict[str, SegmentEntry]:
    segmentsCsv = spimdisasm.common.Utils.readCsv(segmentsPath)
    segmentDict = {}

    for row in segmentsCsv:
        name, comprPath, uncPath, segmentHash = row
        segmentDict[f".{name}"] = SegmentEntry(Path(comprPath), Path(uncPath), segmentHash)

    return segmentDict

def align(value: int, n: int) -> int:
    return (((value) + ((n)-1)) & ~((n)-1))


def align8MB(value: int) -> int:
    return align(value, 0x100000)


def romCompressorMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="uncompressed input rom filename")
    parser.add_argument("out_rom", help="compressed output rom filename")
    parser.add_argument("elf", help="path to the uncompressed rom elf file")
    parser.add_argument("segments", help="path to segments file")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    outPath = Path(args.out_rom)
    elfPath = Path(args.elf)
    segmentsPath = Path(args.segments)

    segmentDict = readSegmentsCsv(segmentsPath)

    elfBytearray = spimdisasm.common.Utils.readFileAsBytearray(elfPath)
    assert len(elfBytearray) > 0, f"'{elfPath}' could not be opened"

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    offset = 0
    sizeWrote = 0

    elfFile = spimdisasm.elf32.Elf32File(elfBytearray)
    with outPath.open("wb") as outRom:
        for entry in elfFile.sectionHeaders.sections:
            sectionEntryName = elfFile.shstrtab[entry.name]

            if entry.type != spimdisasm.elf32.Elf32SectionHeaderType.PROGBITS.value:
                continue
            # print(sectionEntryName, f"{offset:X}", f"{entry.size:X}")

            segmentEntry = segmentDict.get(sectionEntryName)
            if segmentEntry is None:
                # write as-is
                outRom.write(inRom[offset:offset+entry.size])
                sizeWrote += entry.size
            else:
                # check if uncompressed segment matches
                uncompressedBytearray = spimdisasm.common.Utils.readFileAsBytearray(segmentEntry.uncompressedPath)
                if spimdisasm.common.Utils.getStrHash(uncompressedBytearray) == segmentEntry.uncompressedHash:
                    compressedBytearray = spimdisasm.common.Utils.readFileAsBytearray(segmentEntry.compressedPath)
                    assert len(compressedBytearray) > 0, f"'{segmentEntry.compressedPath}' could not be opened"
                    outRom.write(compressedBytearray)
                    sizeWrote += len(compressedBytearray)
                else:
                    assert False, "non-matching compression is not supported yet"
                    # sizeWrote += len(compressedBytearray)
            offset += entry.size

        # print(f"{offset:X}")

        alignedSize = align8MB(sizeWrote)
        # pad
        outRom.write(bytearray((alignedSize - sizeWrote) * [0xFF]))

if __name__ == "__main__":
    romCompressorMain()

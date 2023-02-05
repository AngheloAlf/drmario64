#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import spimdisasm
from pathlib import Path

import compression_common


DEBUGGING = False

def printDebug(*args, **kwargs):
    if not DEBUGGING:
        return
    kwargs["flush"] = True
    print(*args, **kwargs)


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
    parser.add_argument("version", help="version to process")
    parser.add_argument("-d", "--debug", help="Enable debug prints", action="store_true")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    outPath = Path(args.out_rom)
    elfPath = Path(args.elf)
    segmentsPath = Path(args.segments)

    global DEBUGGING
    DEBUGGING = args.debug

    segmentDict = compression_common.readSegmentsCsv(segmentsPath, args.version)

    elfBytearray = spimdisasm.common.Utils.readFileAsBytearray(elfPath)
    assert len(elfBytearray) > 0, f"'{elfPath}' could not be opened"

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    offset = 0
    sizeWrote = 0

    segmentOffsets: dict[str, tuple[int, int]] = {}
    relsOffetsToApply = {}
    romOffsetValues: dict[str, int] = {}

    elfFile = spimdisasm.elf32.Elf32File(elfBytearray)
    with outPath.open("wb") as outRom:
        for entry in elfFile.sectionHeaders.sections:
            sectionEntryName = elfFile.shstrtab[entry.name]

            if entry.type == spimdisasm.elf32.Elf32SectionHeaderType.REL.value:
                if segmentDict.get(sectionEntryName) is None:
                    # only apply relocs to uncompressed segments
                    sectionRels = spimdisasm.elf32.Elf32Rels(sectionEntryName, elfBytearray, entry.offset, entry.size)
                    referencedSegment = sectionEntryName.replace(".rel.", ".")
                    for rel in sectionRels.relocations:

                        if elfFile.symtab is not None:
                            sym = elfFile.symtab[rel.rSym]
                            # symValue = f"{sym.value:08X}"
                            if elfFile.strtab is not None:
                                symName = elfFile.strtab[sym.name]

                                if symName.endswith("_ROM_START") or symName.endswith("_ROM_END"):
                                    relVram = rel.offset

                                    rType = spimdisasm.elf32.Elf32Relocs.fromValue(rel.rType)
                                    assert rType is not None

                                    relRomOffset = relVram - segmentOffsets[referencedSegment][1] + segmentOffsets[referencedSegment][0]
                                    relsOffetsToApply[relRomOffset] = (symName, rType)

            if entry.type != spimdisasm.elf32.Elf32SectionHeaderType.PROGBITS.value:
                printDebug(f"Skiping segment {sectionEntryName} because it isn't PROGBITS")
                continue

            segmentOffsets[sectionEntryName] = (offset, entry.addr)
            romStartSymbol = f"{sectionEntryName[1:]}_ROM_START"
            romEndSymbol = f"{sectionEntryName[1:]}_ROM_END"
            #print(romStartSymbol)
            offsetStart = sizeWrote

            printDebug(f"Segment {sectionEntryName}: offset=0x{offset:06X} entry.offset=0x{entry.offset:06X} entry.size=0x{entry.size:06X}")

            segmentEntry = segmentDict.get(sectionEntryName)
            segmentBytearray = inRom[offset:offset+entry.size]

            assert len(segmentBytearray) == entry.size, f"{sectionEntryName}: 0x{len(segmentBytearray):X} 0x{entry.size:X}"

            if segmentEntry is None:
                # write as-is
                outRom.write(segmentBytearray)
                offsetEnd = entry.size + offsetStart
                sizeWrote += entry.size
            else:
                # check if uncompressed segment matches
                uncompressedHash = spimdisasm.common.Utils.getStrHash(segmentBytearray)

                if uncompressedHash == segmentEntry.uncompressedHash:
                    compressedBytearray = spimdisasm.common.Utils.readFileAsBytearray(segmentEntry.compressedPath)
                    assert len(compressedBytearray) > 0, f"'{segmentEntry.compressedPath}' could not be opened"
                else:
                    spimdisasm.common.Utils.eprint(f"Segment {sectionEntryName} doesn't match, should have hash '{segmentEntry.uncompressedHash}' but has hash '{uncompressedHash}'.")
                    printDebug(f"Segment {sectionEntryName} is at offset 0x{offset:06X} and has a size of 0x{entry.size:06X} (ends at offset 0x{offset+entry.size:06X}).")
                    spimdisasm.common.Utils.eprint(f"Compressing...\n")
                    compressedBytearray = compression_common.compressZlib(segmentBytearray)

                    # with open(f"{sectionEntryName}.bin", "wb") as compressedBinFile:
                    #     compressedBinFile.write(compressedBytearray)

                # Align to a 0x10 boundary
                while len(compressedBytearray) % 0x10 != 0:
                    compressedBytearray.append(0)

                outRom.write(compressedBytearray)

                offsetEnd = offsetStart + len(compressedBytearray)
                sizeWrote += len(compressedBytearray)

            romOffsetValues[romStartSymbol] = offsetStart
            romOffsetValues[romEndSymbol] = offsetEnd
            offset += entry.size

        alignedSize = align8MB(sizeWrote)
        if args.version != "cn":
            # pad
            outRom.write(bytearray((alignedSize - sizeWrote) * [0xFF]))

        for relRomOffset, (symName, rType) in relsOffetsToApply.items():
            value = romOffsetValues[symName]
            hiValue = value >> 16
            loValue = value & 0xFFFF
            if loValue >= 0x8000:
                hiValue += 1

            outRom.seek(relRomOffset)
            if rType == spimdisasm.elf32.Elf32Relocs.MIPS_HI16:
                outRom.seek(relRomOffset+2)
                outRom.write(bytearray([hiValue >> 8, hiValue & 0xFF]))
            elif rType == spimdisasm.elf32.Elf32Relocs.MIPS_LO16:
                outRom.seek(relRomOffset+2)
                outRom.write(bytearray([loValue >> 8, loValue & 0xFF]))
            elif rType == spimdisasm.elf32.Elf32Relocs.MIPS_32:
                outRom.write(bytearray([(value >> 24) & 0xFF, (value >> 16) & 0xFF, (value >> 8) & 0xFF, (value >> 0) & 0xFF]))
            else:
                assert False, rType

if __name__ == "__main__":
    romCompressorMain()

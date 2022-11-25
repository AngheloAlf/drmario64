#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import spimdisasm
from pathlib import Path

import compression_common



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

    segmentDict = compression_common.readSegmentsCsv(segmentsPath)

    elfBytearray = spimdisasm.common.Utils.readFileAsBytearray(elfPath)
    assert len(elfBytearray) > 0, f"'{elfPath}' could not be opened"

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    offset = 0
    sizeWrote = 0

    segmentOffsets: dict[str, tuple[int, int]] = {}
    relsOffetsToApply = {}
    compressedRomValues = {}

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

                                for segmentEntry in segmentDict.values():
                                    compressedRomStart = f"{segmentEntry.compressedName}_ROM_START"
                                    compressedRomEnd = f"{segmentEntry.compressedName}_ROM_END"

                                    if symName == compressedRomStart or symName == compressedRomEnd:
                                        relVram = rel.offset

                                        rType = spimdisasm.elf32.Elf32Relocs.fromValue(rel.rType)
                                        assert rType is not None

                                        relRomOffset = relVram - segmentOffsets[referencedSegment][1] + segmentOffsets[referencedSegment][0]
                                        relsOffetsToApply[relRomOffset] = (symName, rType)

                                        break

            if entry.type != spimdisasm.elf32.Elf32SectionHeaderType.PROGBITS.value:
                continue

            segmentOffsets[sectionEntryName] = (offset, entry.addr)

            segmentEntry = segmentDict.get(sectionEntryName)
            segmentBytearray = inRom[offset:offset+entry.size]
            if segmentEntry is None:
                # write as-is
                outRom.write(segmentBytearray)
                sizeWrote += entry.size
            else:
                # check if uncompressed segment matches
                uncompressedBytearray = segmentBytearray

                if spimdisasm.common.Utils.getStrHash(uncompressedBytearray) == segmentEntry.uncompressedHash:
                    compressedBytearray = spimdisasm.common.Utils.readFileAsBytearray(segmentEntry.compressedPath)
                    assert len(compressedBytearray) > 0, f"'{segmentEntry.compressedPath}' could not be opened"
                else:
                    compressedBytearray = compression_common.compressZlib(uncompressedBytearray)

                outRom.write(compressedBytearray)

                compressedRomStart = f"{segmentEntry.compressedName}_ROM_START"
                compressedRomEnd = f"{segmentEntry.compressedName}_ROM_END"
                compressedRomValues[compressedRomStart] = sizeWrote
                compressedRomValues[compressedRomEnd] = sizeWrote + len(compressedBytearray)

                sizeWrote += len(compressedBytearray)
            offset += entry.size

        alignedSize = align8MB(sizeWrote)
        # pad
        outRom.write(bytearray((alignedSize - sizeWrote) * [0xFF]))

        for relRomOffset, (symName, rType) in relsOffetsToApply.items():
            value = compressedRomValues[symName]
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
            else:
                assert False, rType

if __name__ == "__main__":
    romCompressorMain()

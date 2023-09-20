#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2023 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path
import spimdisasm
import struct
import sys

import compression_common


DEBUGGING = False

def printDebug(*args, **kwargs):
    if not DEBUGGING:
        return
    kwargs["flush"] = True
    print(*args, **kwargs)

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def align(value: int, n: int) -> int:
    return (((value) + ((n)-1)) & ~((n)-1))


def align8MB(value: int) -> int:
    return align(value, 0x100000)

def addSymbolToRelocate(relsOffetsToApply: dict[int, tuple[str, spimdisasm.common.RelocType]], symName: str, rel: spimdisasm.elf32.Elf32RelEntry, segmentRomOffset: int, segmentVram: int):
    relVram = rel.offset

    rType = spimdisasm.common.Relocation.RelocType.fromValue(rel.rType)
    assert rType is not None, rel.rType

    relRomOffset = relVram - segmentVram + segmentRomOffset
    relsOffetsToApply[relRomOffset] = (symName, rType)

def romCompressorMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="uncompressed input rom filename")
    parser.add_argument("out_rom", help="compressed output rom filename")
    parser.add_argument("elf", help="path to the uncompressed rom elf file")
    parser.add_argument("segments", help="path to segments file")
    parser.add_argument("version", help="version to process")
    parser.add_argument("-d", "--debug", help="Enable debug prints", action="store_true")
    parser.add_argument("-c", "--checksum", help="Force always updating the checksum header", action="store_true")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    outPath = Path(args.out_rom)
    elfPath = Path(args.elf)
    segmentsPath = Path(args.segments)
    forceChecksum: bool = args.checksum

    global DEBUGGING
    DEBUGGING = args.debug

    if not DEBUGGING:
        spimdisasm.common.GlobalConfig.VERBOSE = False

    segmentDict = compression_common.readSegmentsCsv(segmentsPath, args.version)

    elfBytearray = spimdisasm.common.Utils.readFileAsBytearray(elfPath)
    assert len(elfBytearray) > 0, f"'{elfPath}' could not be opened"

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    offset = 0
    sizeWrote = 0

    segmentOffsets: dict[str, tuple[int, int]] = {}
    relsOffetsToApply: dict[int, tuple[str, spimdisasm.common.RelocType]] = {}
    romOffsetValues: dict[str, int] = {}

    elfFile = spimdisasm.elf32.Elf32File(elfBytearray)

    assert elfFile.symtab is not None, "The elf->z64 process and compression algorithm requires a symtab, but is was not present"
    assert elfFile.strtab is not None, "The elf->z64 process and compression algorithm requires a strtab, but is was not present"

    outRomBin = bytearray()

    for entry in elfFile.sectionHeaders.sections:
        sectionEntryName = elfFile.shstrtab[entry.name]

        if entry.type == spimdisasm.elf32.Elf32SectionHeaderType.REL.value:
            # Find any symbol that needs to be updated

            if segmentDict.get(sectionEntryName) is None:
                # Only apply relocs to uncompressed segments

                sectionRels = spimdisasm.elf32.Elf32Rels(sectionEntryName, elfBytearray, entry.offset, entry.size)
                referencedSegment = sectionEntryName.replace(".rel.", ".")
                for rel in sectionRels.relocations:
                    sym = elfFile.symtab[rel.rSym]

                    symName = elfFile.strtab[sym.name]

                    if symName.endswith("_ROM_START") or symName.endswith("_ROM_END"):
                        segmentData = segmentOffsets[referencedSegment]

                        addSymbolToRelocate(relsOffetsToApply, symName, rel, segmentData[0], segmentData[1])

        if entry.type != spimdisasm.elf32.Elf32SectionHeaderType.PROGBITS.value:
            printDebug(f"Skiping segment '{sectionEntryName}' because it isn't PROGBITS")
            continue

        entryFlags, unknownFlags = spimdisasm.elf32.Elf32SectionHeaderFlag.parseFlags(entry.flags)
        if spimdisasm.elf32.Elf32SectionHeaderFlag.ALLOC not in entryFlags:
            printDebug(f"Skiping segment '{sectionEntryName}' because it doesn't have the alloc flag")
            continue

        segmentOffsets[sectionEntryName] = (offset, entry.addr)
        romStartSymbol = f"{sectionEntryName[1:]}_ROM_START"
        romEndSymbol = f"{sectionEntryName[1:]}_ROM_END"
        #print(romStartSymbol)
        offsetStart = sizeWrote

        printDebug(f"Segment '{sectionEntryName}': offset=0x{offset:06X} entry.offset=0x{entry.offset:06X} entry.size=0x{entry.size:06X}")

        segmentEntry = segmentDict.get(sectionEntryName)
        segmentBytearray = inRom[offset:offset+entry.size]

        assert len(segmentBytearray) == entry.size, f"'{sectionEntryName}': 0x{len(segmentBytearray):X} 0x{entry.size:X}"

        if segmentEntry is None:
            # write as-is
            offsetEnd = entry.size + offsetStart
            printDebug(f"Writing as is the segment '{sectionEntryName}' at rom offset 0x{offsetStart:06X} to 0x{offsetEnd:06X}.")
            outRomBin.extend(segmentBytearray)
            sizeWrote += entry.size
        else:
            # check if uncompressed segment matches
            uncompressedHash = spimdisasm.common.Utils.getStrHash(segmentBytearray)

            if uncompressedHash == segmentEntry.uncompressedHash:
                compressedBytearray = spimdisasm.common.Utils.readFileAsBytearray(segmentEntry.compressedPath)
                assert len(compressedBytearray) > 0, f"'{segmentEntry.compressedPath}' could not be opened"
            else:
                spimdisasm.common.Utils.eprint(f"Segment '{sectionEntryName}' doesn't match, should have hash '{segmentEntry.uncompressedHash}' but has hash '{uncompressedHash}'.")
                printDebug(f"Segment '{sectionEntryName}' is at offset 0x{offset:06X} and has a size of 0x{entry.size:06X} (ends at offset 0x{offset+entry.size:06X}).")
                spimdisasm.common.Utils.eprint(f"Compressing...\n")
                compressedBytearray = compression_common.compressZlib(segmentBytearray)

                # with open(f"'{sectionEntryName}'.bin", "wb") as compressedBinFile:
                #     compressedBinFile.write(compressedBytearray)

            # Align to a 0x10 boundary
            while len(compressedBytearray) % 0x10 != 0:
                compressedBytearray.append(0)

            offsetEnd = offsetStart + len(compressedBytearray)
            outRomBin.extend(compressedBytearray)
            printDebug(f"Writing compressed the segment '{sectionEntryName}' at rom offset 0x{offsetStart:06X} to 0x{offsetEnd:06X}.")

            sizeWrote += len(compressedBytearray)

        romOffsetValues[romStartSymbol] = offsetStart
        romOffsetValues[romEndSymbol] = offsetEnd
        offset += entry.size

    alignedSize = align8MB(sizeWrote)
    if args.version != "cn":
        # pad
        outRomBin.extend(bytearray((alignedSize - sizeWrote) * [0xFF]))

    for relRomOffset, (symName, rType) in relsOffetsToApply.items():
        value = romOffsetValues[symName]
        hiValue = value >> 16
        loValue = value & 0xFFFF
        if loValue >= 0x8000:
            hiValue += 1

        if rType == spimdisasm.common.Relocation.RelocType.MIPS_HI16:
            struct.pack_into(f">H", outRomBin, relRomOffset+2, hiValue)
        elif rType == spimdisasm.common.Relocation.RelocType.MIPS_LO16:
            struct.pack_into(f">H", outRomBin, relRomOffset+2, loValue)
        elif rType == spimdisasm.common.Relocation.RelocType.MIPS_32:
            struct.pack_into(f">I", outRomBin, relRomOffset, value)
        else:
            assert False, rType

    outPath.write_bytes(outRomBin)

if __name__ == "__main__":
    romCompressorMain()

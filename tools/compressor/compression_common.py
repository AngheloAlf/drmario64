#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import spimdisasm
from pathlib import Path
import zlib


def decompressZlib(data: bytearray) -> bytearray:
    decomp = zlib.decompressobj(-zlib.MAX_WBITS)
    output = bytearray()
    output.extend(decomp.decompress(data))
    while decomp.unconsumed_tail:
        output.extend(decomp.decompress(decomp.unconsumed_tail))
    output.extend(decomp.flush())
    return output


def compressZlib(data: bytearray) -> bytearray:
    comp = zlib.compressobj(9, wbits=-zlib.MAX_WBITS)
    output = bytearray()
    output.extend(comp.compress(data))
    # while comp.unconsumed_tail:
    #     output.extend(comp.decompress(comp.unconsumed_tail))
    output.extend(comp.flush())
    return output


@dataclasses.dataclass
class SegmentEntry:
    segmentName: str
    compressedRomOffset: int
    compressedRomOffsetEnd: int
    uncompressedHash: str

    compressed: bool = True

    @property
    def compressedPath(self) -> Path:
        return Path("bin") / f"{self.segmentName}.bin"

    @property
    def compressedSegmentSize(self) -> int:
        return self.compressedRomOffsetEnd - self.compressedRomOffset

    def __lt__(self, other):
        return self.compressedRomOffset < other.compressedRomOffset


def readSegmentsCsv(segmentsPath: Path) -> dict[str, SegmentEntry]:
    segmentsCsv = spimdisasm.common.Utils.readCsv(segmentsPath)
    segmentDict = {}
    header = True

    for row in segmentsCsv:
        if header:
            header = False
            continue
        if len(row) == 0:
            continue
        name, compressedRomOffset, compressedRomOffsetEnd, segmentHash = row
        segmentDict[f".{name}"] = SegmentEntry(name, int(compressedRomOffset, 0), int(compressedRomOffsetEnd, 0), segmentHash)

    return segmentDict

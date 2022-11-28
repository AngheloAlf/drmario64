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
    compressedName: str
    compressedPath: Path
    uncompressedHash: str


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
        name, compressedName, comprPath, segmentHash = row
        segmentDict[f".{name}"] = SegmentEntry(compressedName, Path(comprPath), segmentHash)

    return segmentDict

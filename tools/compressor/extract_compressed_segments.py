#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import spimdisasm
from pathlib import Path

import compression_common


def extractCompressedSegmentsMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_rom", help="compressed input rom filename")
    parser.add_argument("segments", help="path to segments file")

    args = parser.parse_args()

    inPath = Path(args.in_rom)
    segmentsPath = Path(args.segments)

    segmentDict = compression_common.readSegmentsCsv(segmentsPath)

    inRom = spimdisasm.common.Utils.readFileAsBytearray(inPath)
    assert len(inRom) > 0, f"'{inPath}' could not be opened"

    for segmentName, entry in segmentDict.items():
        print(f"Extracting {entry.compressedPath}")
        entry.compressedPath.parent.mkdir(parents=True, exist_ok=True)
        with entry.compressedPath.open("wb") as out:
            out.write(inRom[entry.compressedRomOffset:entry.compressedRomOffsetEnd])


if __name__ == "__main__":
    extractCompressedSegmentsMain()

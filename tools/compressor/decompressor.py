#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import spimdisasm
from pathlib import Path

import compression_common


def decompressorMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("segments", help="path to segments file")
    parser.add_argument("version", help="version to process")

    args = parser.parse_args()

    segmentsPath = Path(args.segments)

    segmentDict = compression_common.readSegmentsCsv(segmentsPath, args.version)

    for segmentName, entry in segmentDict.items():
        # print(entry.compressedPath)
        print(f"Decompressing '{entry.segmentName}'")
        data = spimdisasm.common.Utils.readFileAsBytearray(entry.compressedPath)
        assert len(data) > 0, f"'{entry.compressedPath}' could not be opened"
        decompressed = compression_common.decompressZlib(data)
        spimdisasm.common.Utils.writeBytearrayToFile(entry.compressedPath.with_stem(f"{entry.compressedPath.stem}_decompressed"), decompressed)


if __name__ == "__main__":
    decompressorMain()

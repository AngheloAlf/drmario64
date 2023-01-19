#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


ASMPATH = Path("asm")
NONMATCHINGS = "nonmatchings"


def getProgress(mapPath: Path, version: str) -> tuple[mapfile_parser.ProgressStats, dict[str, mapfile_parser.ProgressStats]]:
    mapFile = mapfile_parser.MapFile()
    mapFile.readMapFile(mapPath)

    for file in mapFile:
        if len(file.symbols) == 0:
            continue

        filepathParts = list(file.filepath.parts)
        if version in filepathParts:
            filepathParts.remove(version)
        file.filepath = Path(*filepathParts)

    nonMatchingsPath = ASMPATH / version / NONMATCHINGS

    return mapFile.filterBySegmentType(".text").getProgress(ASMPATH / version, nonMatchingsPath, aliases={"ultralib": "libultra"})

def progressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--version", help="version to process", default="us")

    args = parser.parse_args()

    mapPath = Path("build") / f"drmario64.{args.version}.map"
    print(mapPath)

    totalStats, progressPerFolder = getProgress(mapPath, args.version)

    mapfile_parser.progress_stats.printStats(totalStats, progressPerFolder)

if __name__ == "__main__":
    progressMain()

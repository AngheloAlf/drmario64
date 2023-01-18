#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


ASMPATH = Path("asm") / "us"
NONMATCHINGSPATH = ASMPATH / "nonmatchings"


def getProgress(mapPath: Path) -> tuple[mapfile_parser.ProgressStats, dict[str, mapfile_parser.ProgressStats]]:
    mapFile = mapfile_parser.MapFile()
    mapFile.readMapFile(mapPath)

    return mapFile.filterBySegmentType(".text").getProgress(ASMPATH, NONMATCHINGSPATH, aliases={"ultralib": "libultra"})

def progressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", "--map", default="build/drmario64.us.map", type=Path)

    args = parser.parse_args()

    totalStats, progressPerFolder = getProgress(args.map)

    mapfile_parser.progress_stats.printStats(totalStats, progressPerFolder)

if __name__ == "__main__":
    progressMain()

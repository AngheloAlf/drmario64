#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


ASMPATH = Path("asm")
NONMATCHINGS = "nonmatchings"


def getProgressFromMapFile(mapFile: mapfile_parser.MapFile, asmPath: Path, nonmatchings: Path, aliases: dict[str, str]=dict(), pathIndex: int=2) -> tuple[mapfile_parser.ProgressStats, dict[str, mapfile_parser.ProgressStats]]:
    totalStats = mapfile_parser.ProgressStats()
    progressPerFolder: dict[str, mapfile_parser.ProgressStats] = dict()

    for file in mapFile:
        if len(file.symbols) == 0:
            continue

        folder = file.filepath.parts[pathIndex]
        if folder in aliases:
            folder = aliases[folder]

        if folder not in progressPerFolder:
            progressPerFolder[folder] = mapfile_parser.ProgressStats()

        originalFilePath = Path(*file.filepath.parts[pathIndex:])
        fullAsmFile = asmPath / originalFilePath.with_suffix(".s")
        wholeFileIsUndecomped = fullAsmFile.exists()

        for func in file.symbols:
            if func.name.endswith(".NON_MATCHING"):
                continue

            funcNonMatching = f"{func.name}.NON_MATCHING"

            if wholeFileIsUndecomped:
                totalStats.undecompedSize += func.size
                progressPerFolder[folder].undecompedSize += func.size
            elif mapFile.findSymbolByName(funcNonMatching) is not None:
                totalStats.undecompedSize += func.size
                progressPerFolder[folder].undecompedSize += func.size
            else:
                totalStats.decompedSize += func.size
                progressPerFolder[folder].decompedSize += func.size

    return totalStats, progressPerFolder


def getProgress(mapPath: Path, version: str, subpaths: bool=False) -> tuple[mapfile_parser.ProgressStats, dict[str, mapfile_parser.ProgressStats]]:
    mapFile = mapfile_parser.MapFile()
    mapFile.readMapFile(mapPath)

    for file in mapFile:
        if len(file.symbols) == 0:
            continue

        filepathParts = list(file.filepath.parts)
        if version in filepathParts:
            filepathParts.remove(version)
        file.filepath = Path(*filepathParts)

        # Fix symbol size calculation because of NON_MATCHING symbols
        for sym in file.symbols:
            if sym.name.endswith(".NON_MATCHING") and sym.size != 0:
                realSym = file.findSymbolByName(sym.name.replace(".NON_MATCHING", ""))
                if realSym is not None and realSym.size == 0:
                    realSym.size = sym.size
                    sym.size = 0

    nonMatchingsPath = ASMPATH / version / NONMATCHINGS

    pathIndex = 2
    if subpaths:
        pathIndex += 1

    return getProgressFromMapFile(mapFile.filterBySegmentType(".text"), ASMPATH / version, nonMatchingsPath, aliases={"ultralib": "libultra"}, pathIndex=pathIndex)

def progressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--version", help="version to process", default="us")
    parser.add_argument("-p", "--subpaths", help="Make a summary for one level deeper in the path tree", action="store_true")
    parser.add_argument("-s", "--sort", help="Sort by decomped size instead of the ROM sorting", action="store_true")

    args = parser.parse_args()

    mapPath = Path("build") / f"drmario64.{args.version}.map"

    totalStats, progressPerFolder = getProgress(mapPath, args.version, args.subpaths)

    mapfile_parser.ProgressStats.printHeader()
    totalStats.print("all", totalStats)
    print()

    progressesList = list(progressPerFolder.items())
    if args.sort:
        progressesList.sort(key=lambda x: (x[1].decompedSize / x[1].total, x[1].total), reverse=True)
    for folder, statsEntry in progressesList:
        statsEntry.print(folder, totalStats)


if __name__ == "__main__":
    progressMain()

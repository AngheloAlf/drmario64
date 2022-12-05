#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
from pathlib import Path

from repo_64scripts import get_map_functions_sizes


@dataclasses.dataclass
class ProgressStats:
    undecompedSize: int = 0
    decompedSize: int = 0

    @property
    def total(self) -> int:
        return self.undecompedSize + self.decompedSize


    @staticmethod
    def printHeader():
        print(f"{'FolderName':<20}: {'DecompedSize':>12} / {'Total':>6} {'OfFolder':>10}%  ({'OfTotal':>20}%)")

    def print(self, folder: str, totalStats: ProgressStats):
        print(f"{folder:<20}: {self.decompedSize:>12} / {self.total:>6} {self.decompedSize / self.total * 100:>10.4f}%  ({self.decompedSize / totalStats.total * 100:>8.4f}% / {self.total / totalStats.total * 100:>8.4f}%)")


def getFileListFromMap(mapFile: str) -> list[get_map_functions_sizes.File]:
    filesList = get_map_functions_sizes.parseMapFile(mapFile, "\n build/")
    return get_map_functions_sizes.removeDottedSymbols(filesList)

def getProgressFromFileList(filesList: list[get_map_functions_sizes.File], detailed: bool, aliases: dict[str, str]) -> tuple[ProgressStats, dict[str, ProgressStats]]:
    totalStats = ProgressStats()
    progressPerFolder: dict[str, ProgressStats] = dict()

    for file in filesList:
        functionList = file.functions
        funcCount = len(functionList)

        if funcCount == 0:
            continue

        if detailed:
            folder = str(Path(*Path(file.name).parts[:-1]))
        else:
            folder = Path(file.name).parts[0]

        if folder in aliases:
            folder = aliases[folder]

        if folder not in progressPerFolder:
            progressPerFolder[folder] = ProgressStats()

        fullAsmFile = Path("asm") / f"{file.name}.s"
        wholeFileIsUndecomped = fullAsmFile.exists()

        for func in functionList:
            funcAsmPath = Path("asm") / "nonmatchings" / file.name / f"{func.name}.s"

            if wholeFileIsUndecomped:
                totalStats.undecompedSize += func.size
                progressPerFolder[folder].undecompedSize += func.size
            elif funcAsmPath.exists():
                totalStats.undecompedSize += func.size
                progressPerFolder[folder].undecompedSize += func.size
            else:
                totalStats.decompedSize += func.size
                progressPerFolder[folder].decompedSize += func.size
    return totalStats, progressPerFolder

def getProgress(map: str, detailed: bool=False, aliases: dict[str, str]={}) -> tuple[ProgressStats, dict[str, ProgressStats]]:
    filesList = getFileListFromMap(map)
    # get_map_functions_sizes.printFunctionsCsv(filesList)
    return getProgressFromFileList(filesList, detailed, aliases)


def printProgressHeader():
    print(f"{'FolderName':<20}: {'DecompedSize':>12} / {'Total':>6} {'OfFolder':>10}%  ({'OfTotal':>20}%)")

def printProgressEntry(folder: str, statsEntry: ProgressStats, totalStats: ProgressStats):
    print(f"{folder:<20}: {statsEntry.decompedSize:>12} / {statsEntry.total:>6} {statsEntry.decompedSize / statsEntry.total * 100:>10.4f}%  ({statsEntry.decompedSize / totalStats.total * 100:>8.4f}% / {statsEntry.total / totalStats.total * 100:>8.4f}%)")



def progressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", "--map", default="build/drmario64_uncompressed.map")
    parser.add_argument("-d", "--detailed", action="store_true")

    args = parser.parse_args()

    totalStats, progressPerFolder = getProgress(args.map, args.detailed, {"ultralib": "libultra"})

    ProgressStats.printHeader()
    totalStats.print("all", totalStats)
    print()

    for folder, statsEntry in progressPerFolder.items():
        statsEntry.print(folder, totalStats)

if __name__ == "__main__":
    progressMain()

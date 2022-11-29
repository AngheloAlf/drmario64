#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

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


MAP_FILE = "build/drmario64_uncompressed.map"

filesList = get_map_functions_sizes.parseMapFile(MAP_FILE, "\n build/")
filesList = get_map_functions_sizes.removeDottedSymbols(filesList)

# get_map_functions_sizes.printFunctionsCsv(filesList)

progressPerFolder: dict[str, ProgressStats] = dict()
totalStats = ProgressStats()

for file in filesList:
    functionList = file.functions
    funcCount = len(functionList)

    if funcCount == 0:
        continue

    folder = Path(file.name).parts[0]
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

print(f"{'FolderName':<16}: {'DecompedSize':>12} / {'Total':>6} {'OfFolder':>10}%  ({'OfTotal':>8}%)")

print(f"{'all':<16}: {totalStats.decompedSize:>12} / {totalStats.total:>6} {totalStats.decompedSize / totalStats.total * 100:>10.4f}%  ({totalStats.decompedSize / totalStats.total * 100:>8.4f}%)")
print()

for folder, stats in progressPerFolder.items():
    print(f"{folder:<16}: {stats.decompedSize:>12} / {stats.total:>6} {stats.decompedSize / stats.total * 100:>10.4f}%  ({stats.decompedSize / totalStats.total * 100:>8.4f}%)")

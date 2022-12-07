#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path

from repo_64scripts import get_map_functions_sizes


def getFileListFromMap(mapFile: str) -> list[get_map_functions_sizes.File]:
    filesList = get_map_functions_sizes.parseMapFile(mapFile, "\n build/")
    return get_map_functions_sizes.removeDottedSymbols(filesList)


def mapToPj64symsMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output", default="DR.MARIO 64.sym")
    parser.add_argument("-m", "--map", default="build/drmario64_uncompressed.map")

    args = parser.parse_args()

    output = Path(args.output)

    filesList = getFileListFromMap(args.map)

    with output.open("w") as symsFile:
        for file in filesList:
            for func in file.functions:
                symsFile.write(f"{func.vram:08X},code,{func.name}\n")

if __name__ == "__main__":
    mapToPj64symsMain()

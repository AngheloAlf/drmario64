#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path


def splitPlfObjdumpMain():
    parser = argparse.ArgumentParser(description="Splits the output produced by `powerpc-linux-gnu-objdump --disassemble-all --reloc --line-numbers --wide`")
    parser.add_argument("objdump_output", help="Path to objdump output")
    parser.add_argument("output_folder", help="Folder path where processed files will be stored")

    args = parser.parse_args()

    objdumpOutput = Path(args.objdump_output)
    outputFolder = Path(args.output_folder)

    with objdumpOutput.open() as f:
        objdumpLines = f.readlines()

    outputFolder.mkdir(parents=True, exist_ok=True)

    # search for first function:
    index = 0
    for line in objdumpLines:
        if ">:" in line:
            break
        index += 1
    objdumpLines = objdumpLines[index:]

    gatheredFiles: dict[str, list[list[str]]] = {}
    filesOffsets: dict[str, int] = {}
    currentFile = ""
    functionOffset = 0
    functionLines: list[str] = []
    for line in objdumpLines:
        if "<" in line and ">:" in line:
            if currentFile != "":
                gatheredFiles[currentFile].append(list(functionLines))
                functionLines = []
            # currentFunctionName = line.split("<")[1].split(">:")[0]
            functionOffset = int(line.split("<")[0], 16)
        elif "C:\\" in line:
            currentFile = line.split("\\")[-1].split(":")[0]
            if currentFile not in gatheredFiles:
                gatheredFiles[currentFile] = []
                filesOffsets[currentFile] = functionOffset

        functionLines.append(line)

    for filename, functionList in gatheredFiles.items():
        fileOffset = filesOffsets[filename]
        newfile = outputFolder / f"{fileOffset:08}_{filename}.dump"

        with newfile.open("w") as f:
            for functionLines in functionList:
                f.writelines(functionLines)


if __name__ == "__main__":
    splitPlfObjdumpMain()

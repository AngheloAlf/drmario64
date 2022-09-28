#!/usr/bin/env python3

from repo_64scripts import get_map_functions_sizes
from pathlib import Path

MAP_FILE = "build/drmario64.map"

filesList = get_map_functions_sizes.parseMapFile(MAP_FILE, "\n build/")

# get_map_functions_sizes.printFunctionsCsv(filesList)

totalSize = 0
undecompedSize = 0
for file in filesList:
    functionList: list[get_map_functions_sizes.Function] = file.functions
    funcCount = len(functionList)

    if funcCount == 0:
        continue

    fullAsmFile = Path("asm") / f"{file.name}.s"
    wholeFileIsUndecomped = fullAsmFile.exists()

    for func in functionList:
        totalSize += func.size

        funcAsmPath = Path("asm") / "nonmatchings" / file.name / f"{func.name}.s"

        if wholeFileIsUndecomped:
            undecompedSize += func.size
        elif funcAsmPath.exists():
            undecompedSize += func.size

decompedSize = totalSize - undecompedSize
print(f"{decompedSize} / {totalSize}")
print(f"{decompedSize / totalSize * 100:.4f}%")

#!/usr/bin/env python3

from pathlib import Path

with Path("puzzle_collection/Dr_MARIO.plf.disassembly").open() as f:
    disasm = f.readlines()

newFunction = True
funcName = ""
functions: dict[str, list[str]] = dict()
currentFunc = list()
for line in disasm:
    line = line.strip()
    if line == "":
        newFunction = True
        functions[funcName] = currentFunc
        currentFunc = list()
    elif newFunction:
        newFunction = False
        if "<" in line:
            funcName = line.split("<")[1].split(">")[0]
    else:
        currentFunc.append(line)

print(len(functions))

def searchForInstruction(functions: dict[str, list[str]], instr: str, amount: int):
    filteredFunctions = dict()
    for funcName, funcBody in functions.items():
        filteredFunctions[funcName] = 0
        for line in funcBody:
            # print(line)
            if f"\t{instr} " in line:
                filteredFunctions[funcName] += 1
    return {funcName for funcName, num in filteredFunctions.items() if amount == num}
    # return filteredFunctions

print(searchForInstruction(functions, "bl", 2))

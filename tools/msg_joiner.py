#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 AngheloAlf
# SPDX-License-Identifier: MIT

import argparse
from pathlib import Path


def readMsgFile(filepath: Path) -> list[tuple[str, list[str]]]:
    allEntries: list[tuple[str, list[str]]] = []

    with filepath.open() as f:
        entry: list[str] = []

        symName = None

        for line in f:
            line = line.strip()

            if line == "":
                assert symName is not None
                allEntries.append((symName, entry))
                symName = None
                entry = []
            elif symName is None:
                symName = line
            else:
                entry.append(line)


        if symName is not None and len(entry) > 0:
            allEntries.append((symName, entry))
            symName = None
            entry = []

    return allEntries

parser = argparse.ArgumentParser()

parser.add_argument("us_path", type=Path)
parser.add_argument("cn_path", type=Path)

args = parser.parse_args()

usMsgs = readMsgFile(args.us_path)
cnMsgs = readMsgFile(args.cn_path)

assert len(usMsgs) == len(cnMsgs)

for i, (symName, usEntry) in enumerate(usMsgs):
    cnEntry = cnMsgs[i][1]

    print(f"const char {symName}[] =")

    print(f"#if VERSION_US")
    for line in usEntry:
        print(f"    {line}")
    print(f"#endif")

    print(f"#if VERSION_CN")
    for line in cnEntry:
        print(f"    {line}")
    print(f"#endif")

    print(f"    MSG_END;")
    print()


#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path

def textReencoderMain():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_path", help="input filename")
    parser.add_argument("out_path", help="output filename")
    parser.add_argument("out_encoding", help="output encoding")

    args = parser.parse_args()

    inPath = Path(args.in_path)
    outPath = Path(args.out_path)
    outEncoding = str(args.out_encoding)

    inputText = inPath.read_text()

    # First line contains file/line information from cpp. Write it as is
    prevIndex = inputText.find("\n")+1
    outputText = inputText[:prevIndex]

    while True:
        # Find everything before a string and write it as is
        index = inputText.find("\"", prevIndex)
        if index == -1:
            break

        # look for line information from cpp
        lineInfoIndex = inputText.find("\n# ", prevIndex, index)
        if lineInfoIndex != -1:
            # Don't process the line information from cpp
            index = inputText.find("\n", index+1)+1
            outputText += inputText[prevIndex:index]
            prevIndex = index
            continue

        outputText += inputText[prevIndex:index]
        # Skip the quote symbol
        prevIndex = index+1

        # Find where this string ends
        index = inputText.find("\"", prevIndex)
        if index == -1:
            break

        # Re encode string contents
        stringContents = inputText[prevIndex:index]
        outputText += "\""

        for character in stringContents.encode(outEncoding):
            if character >= 0x20 and character <= 0x7E:
                outputText += chr(character)
            else:
                outputText += f"\\x{character:02X}\"\""
        outputText += "\""

        # Skip the quote symbol
        prevIndex = index+1

    outputText += inputText[prevIndex:]

    outPath.write_text(outputText, encoding="ASCII", newline="\n")

if __name__ == "__main__":
    textReencoderMain()

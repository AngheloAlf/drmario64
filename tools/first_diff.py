#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


def firstDiffMain():
    parser = argparse.ArgumentParser(description="Find the first difference(s) between the built ROM and the base ROM.")

    parser.add_argument("-c", "--count", type=int, default=5, help="find up to this many instruction difference(s)")
    parser.add_argument("-v", "--version", help="Which version should be processed", default="us")

    args = parser.parse_args()

    buildFolder = Path("build")

    BUILTROM = buildFolder / f"drmario64_uncompressed.{args.version}.z64"
    BUILTMAP = buildFolder / f"drmario64.{args.version}.map"

    EXPECTEDROM = "expected" / BUILTROM
    EXPECTEDMAP = "expected" / BUILTMAP

    exit(mapfile_parser.frontends.first_diff.doFirstDiff(BUILTMAP, EXPECTEDMAP, BUILTROM, EXPECTEDROM, args.count, mismatchSize=True))

if __name__ == "__main__":
    firstDiffMain()

#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path


BUILTROM = Path(f"build/drmario64_uncompressed.z64")
BUILTMAP = Path(f"build/drmario64_uncompressed.map")

EXPECTEDROM = Path(f"expected/build/drmario64_uncompressed.z64")
EXPECTEDMAP = Path(f"expected/build/drmario64_uncompressed.map")

def firstDiffMain():
    parser = argparse.ArgumentParser(description="Find the first difference(s) between the built ROM and the base ROM.")

    parser.add_argument("-c", "--count", type=int, default=5, help="find up to this many instruction difference(s)")

    args = parser.parse_args()

    exit(mapfile_parser.frontends.first_diff.doFirstDiff(BUILTMAP, EXPECTEDMAP, BUILTROM, EXPECTEDROM, args.count, mismatchSize=True))

if __name__ == "__main__":
    firstDiffMain()

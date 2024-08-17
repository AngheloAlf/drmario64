#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path

def main_inc_from_bin():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_path", help="input filename")
    parser.add_argument("out_path", help="output filename")

    args = parser.parse_args()

    in_path = Path(args.in_path)
    out_path = Path(args.out_path)

    in_bytes = in_path.read_bytes()
    with out_path.open("w") as f:
        i = 0
        for x in in_bytes:
            if i == 0:
                f.write(f"    /* 0x{i:06X} */")
            elif i % 8 == 0:
                f.write(f"\n    /* 0x{i:06X} */")
            f.write(f" 0x{x:02X},")
            i += 1

if __name__ == "__main__":
    main_inc_from_bin()

#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

import argparse
import mapfile_parser
from pathlib import Path


def get_comparison(map_path: Path, expected_map_path: Path, *, reverse_check: bool=True) -> mapfile_parser.MapsComparisonInfo:
    buildMap = mapfile_parser.MapFile()
    buildMap.readMapFile(map_path)

    expectedMap = mapfile_parser.MapFile()
    expectedMap.readMapFile(expected_map_path)

    return buildMap.compareFilesAndSymbols(expectedMap, checkOtherOnSelf=reverse_check)

def do_reordering_check(map_path: Path, expected_map_path: Path, hideGoods: bool, *, print_all: bool=False, reverse_check: bool=True) -> int:
    if not map_path.exists():
        mapfile_parser.utils.eprint(f"{map_path} must exist")
        return 1
    if not expected_map_path.exists():
        mapfile_parser.utils.eprint(f"{expected_map_path} must exist")
        return 1

    comparison_info = get_comparison(map_path, expected_map_path, reverse_check=reverse_check)
    mapfile_parser.frontends.bss_check.printSymbolComparison(comparison_info, print_all, printGoods=not hideGoods, printingStyle="listing")

    if len(comparison_info.badFiles) + len(comparison_info.missingFiles) != 0:
        mapfile_parser.frontends.bss_check.printFileComparison(comparison_info)
        return 1

    mapfile_parser.utils.eprint("")
    mapfile_parser.utils.eprint("  GOOD")

    return 0

def check_reordering_main():
    parser = argparse.ArgumentParser(description="Check that globally visible symbols has not been reordered.")

    parser.add_argument("-v", "--version", help="Which version should be processed", default="us")
    parser.add_argument("-g", "--hide-goods", help="Hide \"GOOD\" symbols from output", action="store_true")

    args = parser.parse_args()

    build_folder = Path("build")

    BUILTMAP = build_folder / args.version / f"drmario64.{args.version}.map"
    EXPECTEDMAP = "expected" / BUILTMAP

    exit(do_reordering_check(BUILTMAP, EXPECTEDMAP, bool(args.hide_goods)))

if __name__ == "__main__":
    check_reordering_main()

#!/usr/bin/env python3

import argparse
from pathlib import Path

def add_custom_arguments(parser: argparse.ArgumentParser):
    version = "us"

    make_options = Path(".make_options")
    if make_options.exists():
        with make_options.open() as f:
            for line in f:
                if "VERSION" in line and "=" in line:
                    version = line.split("=")[1].strip()

    parser.add_argument("-v", "--version", default=version)

def apply(config: dict, args: argparse.Namespace):
    version = args.version

    config["baseimg"] = f"expected/build/{version}/drmario64_uncompressed.{version}.z64"
    config["myimg"]   = f"build/{version}/drmario64_uncompressed.{version}.z64"
    config["mapfile"] = f"build/{version}/drmario64.{version}.map"
    config["source_directories"] = ["./src", "./include", "./asm", "./lib"]
    config["objdump_flags"] = ["-Mreg-names=32"]
    # config["objdump_flags"].append("-Mno-aliases")
    config["makeflags"] = ["KEEP_MDEBUG=1", "WERROR=0", f"VERSION={version}", "OBJDUMP_BUILD=0", "PERMUTER=1"]

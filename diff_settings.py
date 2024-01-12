#!/usr/bin/env python3

from pathlib import Path

def apply(config, args):
    version = "us"

    make_options = Path(".make_options")
    if make_options.exists():
        with make_options.open() as f:
            for line in f:
                if "VERSION" in line and "=" in line:
                    version = line.split("=")[1].strip()

    config["baseimg"] = f"expected/build/drmario64_uncompressed.{version}.z64"
    config["myimg"]   = f"build/drmario64_uncompressed.{version}.z64"
    config["mapfile"] = f"build/drmario64.{version}.map"
    config["source_directories"] = ["./src", "./include", "./asm", "./lib"]
    config["objdump_flags"] = ["-Mreg-names=32"]
    # config["objdump_flags"].append("-Mno-aliases")
    config["makeflags"] = ["KEEP_MDEBUG=1", "WERROR=0", f"VERSION={version}", "OBJDUMP_BUILD=0", "PERMUTER=1"]

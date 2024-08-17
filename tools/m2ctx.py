#!/usr/bin/env python3

import argparse
import os
import sys
import subprocess
import tempfile
from pathlib import Path

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))

# Project-specific
CPP_FLAGS = [
    "-I.",
    "-Iinclude",
    "-Ibin/us",
    "-Ibin/cn",
    "-Ibin/gw",
    "-Ibuild/bin/us",
    "-Ibuild/bin/cn",
    "-Ibuild/bin/gw",
    "-Ilib/ultralib/include",
    "-Ilib/ultralib/include/gcc",
    "-Ilib/ultralib/include/PR",
    "-Ilib/ultralib/src",
    "-Ilib/libmus/src",
    "-Ilib/libmus/include",
    "-D_LANGUAGE_C",
    "-DF3DEX_GBI_2",
    "-D__USE_ISOC99",
    "-DNDEBUG",
    "-D_FINALROM",
    "-D_MIPS_SZLONG=32",
    "-D__USE_ISOC99",
    "-DSCRIPT(test...)={}"
    "-D__attribute__(test...)=",
    "-D__asm__(test...)=",
    "-ffreestanding",
    "-DM2CTX",
    "-DCC_CHECK=1",
    "-DNON_MATCHING",
    "-D_OS_HOST_H_",
    "-std=gnu89",
]

def import_c_file(in_file, version: str) -> str:
    in_file = os.path.relpath(in_file, root_dir)

    if version == "us":
        CPP_FLAGS.append("-DVERSION_US=1")
        CPP_FLAGS.append("-D__IS_KMC__=1")
    elif version == "cn":
        CPP_FLAGS.append("-DVERSION_CN=1")
        CPP_FLAGS.append("-DBBPLAYER=1")
        CPP_FLAGS.append("-D__IS_EGCS__=1")
    elif version == "gw":
        CPP_FLAGS.append("-DVERSION_GW=1")
        CPP_FLAGS.append("-D__IS_KMC__=1")

    CPP_FLAGS.append(f"-Ibuild/{version}/{Path(in_file).parent}")

    cpp_command = ["gcc", "-E", "-P", "-undef", "-dM", *CPP_FLAGS, in_file]
    cpp_command2 = ["gcc", "-E", "-P", "-undef", *CPP_FLAGS, in_file]

    with tempfile.NamedTemporaryFile(suffix=".c") as tmp:
        stock_macros = subprocess.check_output(["gcc", "-E", "-P", "-undef", "-dM", tmp.name], cwd=root_dir, encoding="utf-8")

    out_text = ""
    try:
        out_text += subprocess.check_output(cpp_command, cwd=root_dir, encoding="utf-8")
        out_text += subprocess.check_output(cpp_command2, cwd=root_dir, encoding="utf-8")
    except subprocess.CalledProcessError:
        print(
            "Failed to preprocess input file, when running command:\n"
            + " ".join(cpp_command),
            file=sys.stderr,
            )
        sys.exit(1)

    if not out_text:
        print("Output is empty - aborting")
        sys.exit(1)

    for line in stock_macros.strip().splitlines():
        out_text = out_text.replace(line + "\n", "")
    return out_text

def main():
    parser = argparse.ArgumentParser(
        description="""Create a context file which can be used for m2c"""
    )
    parser.add_argument(
        "c_file",
        help="""File from which to create context""",
    )
    parser.add_argument("-v", "--version", help="Which version should be processed", default="us", choices=["us", "cn", "gw"])
    args = parser.parse_args()

    output = import_c_file(args.c_file, args.version)

    with open(os.path.join(root_dir, "ctx.c"), "w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()

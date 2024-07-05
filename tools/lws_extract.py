#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

import argparse
from pathlib import Path
import struct
import subprocess


NUMBER_05 = 0x05000000

# vram: (type, size, is_array)
SYMBOLS: dict[int, tuple[str, int, bool]] = {

}

TYPE_SIZES: dict[str, int] = {
    "Lws": 0x18, # larger?
    "Lws *": 0x4,
    "Lws_unk_10": 0x18,
    "Lws_unk_14": 0x1C,
    "Gfx": 0x8,
    "Vtx": 0x10,
    "Palette16": 16*2,
    "Palette256": 16*16*2,
    "CI4": 0x1,
    "CI8": 0x1,
    "I4": 0x1,
    "I8": 0x1,
}

GFX_END = 0xDF000000

TLUT_TO_CI: dict[int, int|None] = {}
CI_TO_TLUT: dict[int, int|None] = {}

TEX_DIMENSIONS: dict[int, tuple[int, int]] = {}

LWS_INFO: dict[int, tuple[int, int, int]] = {}
UNK_10_PARENT: dict[int, int] = {}
UNK_14_PARENT: dict[int, int] = {}


def read_s32(in_bytes: bytes, offset: int) -> int:
    return struct.unpack_from(">i", in_bytes, offset)[0]

def read_u32(in_bytes: bytes, offset: int) -> int:
    return struct.unpack_from(">I", in_bytes, offset)[0]

def read_s16(in_bytes: bytes, offset: int) -> int:
    return struct.unpack_from(">h", in_bytes, offset)[0]


def parse_lws(data: bytes, offset: int, vram: int):
    SYMBOLS[vram] = ("Lws", TYPE_SIZES["Lws"], False)
    count = read_s32(data, offset + 0xC)

    unk_10_vram = read_u32(data, offset + 0x10)
    unk_14_vram = read_u32(data, offset + 0x14)

    LWS_INFO[vram] = (count, unk_10_vram, unk_14_vram)
    UNK_10_PARENT[unk_10_vram] = vram
    UNK_14_PARENT[unk_14_vram] = vram

    unk_10_size = TYPE_SIZES["Lws_unk_10"]
    unk_14_size = TYPE_SIZES["Lws_unk_14"]
    SYMBOLS[unk_10_vram] = ("Lws_unk_10", unk_10_size * count, True)
    SYMBOLS[unk_14_vram] = ("Lws_unk_14", unk_14_size * count, True)

    for i in range(count):
        unk_10_offset = unk_10_vram - NUMBER_05 + i * unk_10_size

        unk_00_gfx_vram = read_u32(data, unk_10_offset + 0x0)
        gfx_count = 1
        gfx_size = TYPE_SIZES["Gfx"]
        unk_00_gfx_offset = unk_00_gfx_vram - NUMBER_05
        gfx_raw = ""
        while read_u32(data, unk_00_gfx_offset) != GFX_END:
            word0 = read_u32(data, unk_00_gfx_offset)
            word1 = read_u32(data, unk_00_gfx_offset + 0x4)
            gfx_raw += f"{word0:08X}{word1:08X}"
            opcode = word0 >> 24
            if opcode == 0x01: # VTX
                vtx_count = (word0 >> 12) & 0xFF
                SYMBOLS[word1] = ("Vtx", TYPE_SIZES["Vtx"] * vtx_count, True)
            gfx_count += 1
            unk_00_gfx_offset += gfx_size

        # This is terrible
        disassembled_gfx = subprocess.check_output(["gfxdis.f3dex2", "-x", "-dc", "-d", gfx_raw]).decode()
        last_tlut: int|None = None
        last_ci: int|None = None
        for line in disassembled_gfx.split("\n"):
            if "gsDPLoadTLUT_pal16" in line:
                addr = int(line.split("),")[0].split(", ")[1], 16)
                SYMBOLS[addr] = ("Palette16", TYPE_SIZES["Palette16"], True)
                last_tlut = addr
                if addr not in TLUT_TO_CI:
                    TLUT_TO_CI[addr] = last_ci
                    if last_ci is not None and CI_TO_TLUT.get(last_ci) is None:
                        CI_TO_TLUT[last_ci] = addr
            elif "gsDPLoadTLUT_pal256" in line:
                addr = int(line.split("),")[0].split("(")[1], 16)
                SYMBOLS[addr] = ("Palette256", TYPE_SIZES["Palette256"], True)
                last_tlut = addr
                if addr not in TLUT_TO_CI:
                    TLUT_TO_CI[addr] = last_ci
                    if last_ci is not None and CI_TO_TLUT.get(last_ci) is None:
                        CI_TO_TLUT[last_ci] = addr
            elif "gsDPLoadTextureBlock_4b" in line:
                addr, fmt, width, height, *_ = line.split("(")[1].split(", ")
                addr = int(addr, 16)
                width = int(width)
                height = int(height)
                TEX_DIMENSIONS[addr] = (width, height)
                if fmt == "G_IM_FMT_CI":
                    SYMBOLS[addr] = ("CI4", TYPE_SIZES["CI4"] * width * height // 2, True)
                    last_ci = addr
                    if addr not in CI_TO_TLUT:
                        CI_TO_TLUT[addr] = last_tlut
                        if last_tlut is not None and TLUT_TO_CI.get(last_tlut) is None:
                            TLUT_TO_CI[last_tlut] = addr
                elif fmt == "G_IM_FMT_I":
                    SYMBOLS[addr] = ("I4", TYPE_SIZES["I4"] * width * height // 2, True)
                else:
                    assert False, f"0x{addr:08X}"
            elif "gsDPLoadTextureBlock" in line:
                addr, fmt, siz, width, height, *_ = line.split("(")[1].split(", ")
                addr = int(addr, 16)
                width = int(width)
                height = int(height)
                TEX_DIMENSIONS[addr] = (width, height)
                if fmt == "G_IM_FMT_CI":
                    SYMBOLS[addr] = ("CI8", TYPE_SIZES["CI8"] * width * height, True)
                    last_ci = addr
                    if addr not in CI_TO_TLUT:
                        CI_TO_TLUT[addr] = last_tlut
                        if last_tlut is not None and TLUT_TO_CI.get(last_tlut) is None:
                            TLUT_TO_CI[last_tlut] = addr
                else:
                    assert False, f"0x{addr:08X}"

        SYMBOLS[unk_00_gfx_vram] = ("Gfx", gfx_size * gfx_count, True)


def emit(out_path: Path, data: bytes, rom_offset: int, inc_path: str, sym_prefix: str):
    symbols = sorted(SYMBOLS.items())

    with out_path.open("w") as f:
        f.write("#include \"libc/assert.h\"\n")
        f.write("\n")
        f.write("#include \"lws.h\"\n")
        f.write("#include \"macros_defines.h\"\n")
        f.write("\n")

        for lws_vram, (lws_count, lws_unk_10, lws_unk_14) in LWS_INFO.items():
            f.write(f"#define D_{lws_vram:08X}_COUNT ({lws_count})\n")
        f.write("\n")

        for index in range(len(symbols)):
            vram, (typ, size, is_array) = symbols[index]

            if typ in {"Palette16", "Palette256"}:
                typ = "u16"
            elif typ in {"CI4", "CI8", "I4", "I8"}:
                typ = "u8"

            f.write(f"extern {typ} D_{vram:08X}")
            if is_array:
                f.write("[]")
            f.write(";\n")

            if index + 1 == len(symbols):
                next_vram = len(data) + NUMBER_05
            else:
                next_vram = symbols[index+1][0]

            new_vram = vram + size
            assert new_vram <= next_vram, f"0x{vram:08X} 0x{new_vram:08X} 0x{next_vram:08X}"
            if new_vram < next_vram:
                f.write(f"extern u32 D_{new_vram:08X}[];\n")


        f.write("\n")

        prev_end = 0

        for index in range(len(symbols)):
            vram, (typ, size, is_array) = symbols[index]
            count = size // TYPE_SIZES[typ]
            offset = vram - NUMBER_05

            if typ == "Lws *":
                assert is_array
                f.write(f"{typ}D_{vram:08X}[] = {{\n")
                for i in range(count):
                    f.write(f"    &D_{read_u32(data, offset):08X},\n")
                    offset += 4
                f.write(f"}};\n\n")
            elif typ == "Lws":
                assert not is_array
                f.write(f"{typ} D_{vram:08X} = {{\n")
                f.write(f"    {read_s32(data, offset+0x0)}, {read_s32(data, offset+0x4)}, {read_s32(data, offset+0x8)}, D_{vram:08X}_COUNT,\n")
                f.write(f"    D_{read_u32(data, offset+0x10):08X}, D_{read_u32(data, offset+0x14):08X},\n")
                f.write(f"}};\n\n")
                offset += size

            elif typ == "Lws_unk_10":
                assert is_array
                f.write(f"{typ} D_{vram:08X}[] = {{\n")

                for i in range(count):
                    f.write(f"    {{ D_{read_u32(data, offset+0x0):08X}, {read_s32(data, offset+0x4)}, {read_s32(data, offset+0x8)}, {read_s32(data, offset+0xC)}, {read_s32(data, offset+0x10)}, {read_s32(data, offset+0x14)} }},\n")
                    offset += TYPE_SIZES[typ]

                f.write(f"}};\n")
                f.write(f"static_assert(ARRAY_COUNT(D_{vram:08X}) == D_{UNK_10_PARENT[vram]:08X}_COUNT, \"\");\n")
                f.write("\n")

            elif typ == "Lws_unk_14":
                assert is_array
                f.write(f"{typ} D_{vram:08X}[] = {{\n")

                for i in range(count):
                    f.write(f"    {{ {read_s32(data, offset+0x0)}, {read_s32(data, offset+0x4)}, {read_s16(data, offset+0x8)}, {read_s16(data, offset+0xA)}, {read_s16(data, offset+0xC)}, {read_s16(data, offset+0xE)}, {read_s16(data, offset+0x10)}, {read_s16(data, offset+0x12)}, {read_s16(data, offset+0x14)}, {read_s16(data, offset+0x16)}, {read_s16(data, offset+0x18)} }},\n")
                    offset += TYPE_SIZES[typ]

                f.write(f"}};\n")
                f.write(f"static_assert(ARRAY_COUNT(D_{vram:08X}) == D_{UNK_14_PARENT[vram]:08X}_COUNT, \"\");\n")
                f.write("\n")

            elif typ == "Gfx":
                assert is_array
                f.write(f"{typ} D_{vram:08X}[] = ")

                gfx_raw = ""
                for i in range(count):
                    word0 = read_u32(data, offset + 0x0)
                    word1 = read_u32(data, offset + 0x4)
                    gfx_raw += f"{word0:08X}{word1:08X}"
                    # f.write(f"    {{ 0x{read_u32(data, offset+0x0):08X}, 0x{read_u32(data, offset+0x4):08X} }},\n")
                    offset += TYPE_SIZES[typ]
                disassembled_gfx = subprocess.check_output(["gfxdis.f3dex2", "-x", "-dc", "-d", gfx_raw]).decode()
                disassembled_gfx = disassembled_gfx.replace("0x050", "D_050")
                f.write(disassembled_gfx[:-1])

                f.write(f";\n\n")

            elif typ == "Vtx":
                assert is_array
                f.write(f"{typ} D_{vram:08X}[] = {{\n")

                f.write(f"#include \"{inc_path}/{sym_prefix}D_{vram:08X}.vtx.inc.c\"\n")
                offset += size

                f.write(f"}};\n\n")

                this_start = rom_offset + vram - NUMBER_05
                if this_start != prev_end:
                    print(f"          - [0x{prev_end:06X}]")
                print(f"          - {{ start: 0x{this_start:06X}, type: vtx, data_only: True, name: {sym_prefix}D_{vram:08X} }}")

                prev_end = rom_offset + vram - NUMBER_05 + size


            elif typ in {"Palette16", "Palette256"}:
                assert is_array
                f.write(f"u16 D_{vram:08X}[] = {{\n")

                assert TLUT_TO_CI[vram] is not None, f"0x{vram:08X}"
                f.write(f"#include \"{inc_path}/{sym_prefix}D_{TLUT_TO_CI[vram]:08X}.palette.inc\"\n")
                offset += size

                f.write(f"}};\n\n")

                this_start = rom_offset + vram - NUMBER_05
                if this_start != prev_end:
                    print(f"          - [0x{prev_end:06X}]")
                print(f"          - [0x{this_start:06X}, palette, {sym_prefix}D_{TLUT_TO_CI[vram]:08X}]")

                prev_end = rom_offset + vram - NUMBER_05 + size


            elif typ == "CI4":
                assert is_array
                f.write(f"u8 D_{vram:08X}[] = {{\n")

                assert CI_TO_TLUT[vram] is not None, f"0x{vram:08X}"
                f.write(f"#include \"{inc_path}/{sym_prefix}D_{vram:08X}.ci4.inc\"\n")
                offset += size

                f.write(f"}};\n\n")

                this_start = rom_offset + vram - NUMBER_05
                if this_start != prev_end:
                    print(f"          - [0x{prev_end:06X}]")

                width, height =TEX_DIMENSIONS[vram]
                print(f"          - [0x{this_start:06X}, ci4, {sym_prefix}D_{vram:08X}, {width}, {height}]")

                prev_end = rom_offset + vram - NUMBER_05 + size


            elif typ == "CI8":
                assert is_array
                f.write(f"u8 D_{vram:08X}[] = {{\n")

                assert CI_TO_TLUT[vram] is not None, f"0x{vram:08X}"
                f.write(f"#include \"{inc_path}/{sym_prefix}D_{vram:08X}.ci8.inc\"\n")
                offset += size

                f.write(f"}};\n\n")

                this_start = rom_offset + vram - NUMBER_05
                if this_start != prev_end:
                    print(f"          - [0x{prev_end:06X}]")

                width, height =TEX_DIMENSIONS[vram]
                print(f"          - [0x{this_start:06X}, ci8, {sym_prefix}D_{vram:08X}, {width}, {height}]")

                prev_end = rom_offset + vram - NUMBER_05 + size

            elif typ == "I4":
                assert is_array
                f.write(f"u8 D_{vram:08X}[] = {{\n")

                f.write(f"#include \"{inc_path}/{sym_prefix}D_{vram:08X}.i4.inc\"\n")
                offset += size

                f.write(f"}};\n\n")

                this_start = rom_offset + vram - NUMBER_05
                if this_start != prev_end:
                    print(f"          - [0x{prev_end:06X}]")

                width, height =TEX_DIMENSIONS[vram]
                print(f"          - [0x{this_start:06X}, i4, {sym_prefix}D_{vram:08X}, {width}, {height}]")

                prev_end = rom_offset + vram - NUMBER_05 + size

            elif typ == "I8":
                assert is_array
                f.write(f"u8 D_{vram:08X}[] = {{\n")

                f.write(f"#include \"{inc_path}/{sym_prefix}D_{vram:08X}.i8.inc\"\n")
                offset += size

                f.write(f"}};\n\n")

                this_start = rom_offset + vram - NUMBER_05
                if this_start != prev_end:
                    print(f"          - [0x{prev_end:06X}]")

                width, height =TEX_DIMENSIONS[vram]
                print(f"          - [0x{this_start:06X}, i8, {sym_prefix}D_{vram:08X}, {width}, {height}]")

                prev_end = rom_offset + vram - NUMBER_05 + size


            else:
                assert False, f"0x{vram:08X}, {typ}"

            if index + 1 == len(symbols):
                next_vram = len(data) + NUMBER_05
            else:
                next_vram = symbols[index+1][0]

            new_vram = vram + size
            assert new_vram <= next_vram, f"0x{vram:08X} 0x{new_vram:08X} 0x{next_vram:08X}"
            if new_vram < next_vram:
                f.write(f" /* unreferenced data */\n")
                f.write(f"u32 D_{new_vram:08X}[] = {{\n")

                i = 0
                while new_vram < next_vram:
                    # f.write(f"    /* 0x{offset:06X} 0x{new_vram:08X} */ 0x{read_u32(data, offset):08X},\n")

                    if i == 0:
                        f.write("   ")
                    elif i % 8 == 0:
                        f.write("\n   ")
                    f.write(f" 0x{read_u32(data, offset):08X},")

                    offset += 4
                    new_vram += 4
                    i += 1

                f.write(f"\n")
                f.write(f"}};\n\n")

        print(f"          - [0x{prev_end:06X}]")

def main_lws_extract():
    description = ""
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("in_path", help="input filename")
    parser.add_argument("out_path", help="output filename")
    parser.add_argument("rom_offset", help="offset of the segment within the whole rom")
    parser.add_argument("inc_path", help="path for included binaries")
    parser.add_argument("--array", help="count")
    parser.add_argument("--sym-prefix", help="")

    args = parser.parse_args()

    in_path = Path(args.in_path)
    out_path = Path(args.out_path)
    rom_offset = int(args.rom_offset, 0)
    inc_path = str(args.inc_path)

    if args.sym_prefix is not None:
        sym_prefix = args.sym_prefix
    else:
        sym_prefix = ""


    in_bytes = in_path.read_bytes()

    if args.array is not None:
        array_len = int(args.array)
        SYMBOLS[NUMBER_05] = ("Lws *", 4 * array_len, True)
        for i in range(array_len):
            vram = struct.unpack_from(">I", in_bytes, i * 4)[0]
            offset = vram - NUMBER_05
            parse_lws(in_bytes, offset, vram)
    else:
        parse_lws(in_bytes, 0, NUMBER_05)

    emit(out_path, in_bytes, rom_offset, inc_path, sym_prefix)

if __name__ == "__main__":
    main_lws_extract()

#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path
import struct
import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def read_u8(b: bytes, offset: int) -> int:
    return struct.unpack_from(">B", b, offset)[0]

def read_u16(b: bytes, offset: int) -> int:
    return struct.unpack_from(">H", b, offset)[0]

def read_u32(b: bytes, offset: int) -> int:
    return struct.unpack_from(">I", b, offset)[0]


def extract_anime_main():
    parser = argparse.ArgumentParser()
    parser.add_argument("anime_segment_bin")
    parser.add_argument("name")
    parser.add_argument("--rom-addr", default="0")

    args = parser.parse_args()

    anime_segment_bin = Path(args.anime_segment_bin)
    name = str(args.name)
    rom_addr = int(args.rom_addr, 0)

    anime_segment_bytes = anime_segment_bin.read_bytes()

    temp_a0 = read_u32(anime_segment_bytes, 0x0)
    temp_v0 = read_u32(anime_segment_bytes, 0x4)

    metadata_addr = read_u32(anime_segment_bytes, 0x8)
    metadata_len_addr = read_u32(anime_segment_bytes, 0xC)

    print(f"""\
#include "tex_func.h"
#include "char_anime.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData {name}_titexdata[];
extern s32 {name}_titexdata_len;
extern u8 *{name}_metadata[];
extern s32 {name}_metadata_len;

AnimeHeader {name}_header = {{
    {name}_titexdata,
    &{name}_titexdata_len,
    {name}_metadata,
    &{name}_metadata_len,
}};
""")

    count1 = read_u32(anime_segment_bytes, temp_v0)

    # print(f"arr:   {temp_a0:08X}")
    # print(f"count: {count1:08X}")

    textues: list[tuple[int, str, str, int, int, int]] = []

    for i in range(count1):
        ptr = temp_a0 + i * 0x8
        # print(f"{ptr:08X} ", end="")
        texs_addr = read_u32(anime_segment_bytes, ptr)
        info_addr = read_u32(anime_segment_bytes, ptr+0x4)
        # print(f"{texs_addr:08X} {info_addr:08X}")

        tlut_addr = read_u32(anime_segment_bytes, texs_addr + 0x0)
        tex_addr = read_u32(anime_segment_bytes, texs_addr + 0x4)

        tlut_name = "NULL"
        if tlut_addr != 0:
            tlut_name = f"{name}_titexdata_{i:02}_texs_tlut"
            print(f"extern u16 {tlut_name}[];\n")

        assert tex_addr != 0
        assert tlut_addr != tex_addr

        width = read_u16(anime_segment_bytes, info_addr + 0x0)
        height = read_u16(anime_segment_bytes, info_addr + 0x2)
        fmt = read_u16(anime_segment_bytes, info_addr + 0x4)
        bitflags = read_u16(anime_segment_bytes, info_addr + 0x6)

        assert fmt in {0x4, 0x8, 0x10}
        tex_type = "u8"
        if tex_type == 0x10:
            tex_type = "u16"

        if tlut_addr != 0:
            assert fmt in {0x4, 0x8}
            tex_fmt = f"ci{fmt}"
        else:
            if fmt == 0x10:
                tex_fmt = f"rgba16"
            else:
                tex_fmt = f"i{fmt}"

        tex_name = f"{name}_titexdata_{i:02}_texs_tex"
        print(f"extern {tex_type} {tex_name}[];\n")

        # print(f"{tlut_addr:08X} {tex_addr:08X}")
        # print(f"    {width} {height} {fmt} {bitflags}")

        print(f"""\
TiTexDataTextures {name}_titexdata_{i:02}_texs = {{
    {tlut_name},
    {tex_name},
}};
""")
        print(f"""\
u16 {name}_titexdata_{i:02}_info[] = {{
    {width}, {height}, {fmt}, {bitflags},
}};
""")
        if tlut_addr == 0:
            print(f"""\
{tex_type} {tex_name}[] ALIGNED(8) = {{
#include "assets/anime/{name}/{tex_name}.{tex_fmt}.inc"
}};
""")
        elif tlut_addr < tex_addr:
            print(f"""\
u16 {tlut_name}[] ALIGNED(8) = {{
#include "assets/anime/{name}/{tlut_name}.rgba16.inc"
}};
""")
            print(f"""\
{tex_type} {tex_name}[] ALIGNED(8) = {{
#include "assets/anime/{name}/{tex_name}.{tex_fmt}.inc"
}};
""")
        else:
            print(f"""\
{tex_type} {tex_name}[] ALIGNED(8) = {{
#include "assets/anime/{name}/{tex_name}.{tex_fmt}.inc"
}};
""")
            print(f"""\
u16 {tlut_name}[] ALIGNED(8) = {{
#include "assets/anime/{name}/{tlut_name}.rgba16.inc"
}};
""")

        mult = 1
        op = ""
        tlut_width = 16
        tlut_height = 16
        if fmt == 4:
            mult = 1 / 2
            op = " / 2"
            tlut_width = 4
            tlut_height = 4
        if fmt == 0x10:
            mult = 2

        if tlut_addr != 0:
            print(f"static_assert(ARRAY_COUNT({tlut_addr}) == {tlut_width} * {tlut_height}, \"\");")
            textues.append((tlut_addr, "rgba16", f"assets/anime/{name}/{tlut_name}.rgba16", tlut_width, tlut_height, tlut_width * tlut_height))

        print(f"static_assert(ARRAY_COUNT({tex_name}) == {width} * {height}{op}, \"\");")
        print()
        textues.append((tex_addr, tex_fmt, f"assets/anime/{name}/{tex_name}.{tex_fmt}", width, height, int(width * height * mult)))

    print(f"TiTexData {name}_titexdata[] = {{")
    for i in range(count1):
        print(f"    {{ &{name}_titexdata_{i:02}_texs, {name}_titexdata_{i:02}_info }},")
    print(f"}};")
    print()

    print(f"s32 {name}_titexdata_len = ARRAY_COUNT({name}_titexdata);")


    print()

    metadata_len = read_u32(anime_segment_bytes, metadata_len_addr)

    # print(f"arr:   {metadata_addr:08X}")
    # print(f"count: {metadata_len:08X}")

    for i in range(metadata_len):
        ptr = metadata_addr + i * 4
        # print(f"{ptr:08X} ", end="")
        data = read_u32(anime_segment_bytes, ptr)
        # print(f"{data:08X}")

        # print(f"/* {data:08X} */")
        print(f"""\
u8 {name}_metadata_{i:02}[] = {{
    \
""", end="")
        while True:
            val = read_u8(anime_segment_bytes, data)
            print(f"0x{val:02X}, ", end="")
            if val == 0xFF:
                print()
                break
            data += 1
        print(f"}};")
        print()

    print(f"u8 *{name}_metadata[] = {{")
    for i in range(metadata_len):
        print(f"    {name}_metadata_{i:02},")
    print(f"}};")
    print()

    print(f"s32 {name}_metadata_len = ARRAY_COUNT({name}_metadata);")

    textues.sort()
    eprint(f"          - [0x{rom_addr:06X}]")
    i = 0
    for addr, tex_fmt, tex_path, width, height, size in textues:
        eprint(f"          - [0x{addr+rom_addr:06X}, {tex_fmt}, {tex_path}, {width}, {height}]")
        if i + 1 < len(textues):
            if addr + size != textues[i+1][0]:
                eprint(f"          - [0x{addr + rom_addr + size:06X}]")
        else:
            eprint(f"          - [0x{addr + rom_addr + size:06X}]")


if __name__ == "__main__":
    extract_anime_main()

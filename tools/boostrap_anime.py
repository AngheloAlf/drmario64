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


def emit_texture(tex_name: str, tex_type: str, tex_fmt: str, seg_name: str):
    print(f"""\
{tex_type} {tex_name}[] ALIGNED(8) = {{
#include "assets/anime/{seg_name}/{tex_name}.{tex_fmt}.inc"
}};
""")

def emit_tlut(tlut_name: str, seg_name: str):
    print(f"""\
u16 {tlut_name}[] ALIGNED(8) = {{
#include "assets/anime/{seg_name}/{tlut_name}.rgba16.inc"
}};
""")

TI_FMTS = {
    4: "TITEX_FORMAT_4",
    8: "TITEX_FORMAT_8",
    16: "TITEX_FORMAT_16",
}

TI_BITFLAGS = {
    0: "TITEX_FLAGS_TILE",
    1: "TITEX_FLAGS_BLOCK",
}

METADATA_CMDS = {
    0xF0: "ANIME_METADATA_CMD_F0",
    0xF1: "ANIME_METADATA_CMD_F1",
    0xF2: "ANIME_METADATA_CMD_F2",
}

def emit_splat_info(textues: list[tuple[int, str, str, int, int, int, bool]], rom_addr: int, seg_name: str):
    textues.sort()

    eprint(f"""\
    type: code
    start: 0x{rom_addr:06X}
    vram: 0x0
    exclusive_ram_id: anime
    subsegments:
      - [auto, c, assets/anime/{seg_name}]
      - start: 0x{rom_addr:06X}
        type: .data
        name: assets/anime/{seg_name}
        subsegments:\
""")

    eprint(f"          - [0x{rom_addr:06X}]")
    i = 0
    for addr, tex_fmt, tex_path, width, height, size, is_ci in textues:
        comment = ""
        if is_ci:
            comment = " # TODO: extract as ci"
        eprint(f"          - [0x{addr+rom_addr:06X}, {tex_fmt}, {tex_path}, {width}, {height}]{comment}")
        if i + 1 < len(textues):
            if addr + size != textues[i+1][0]:
                eprint(f"          - [0x{addr + rom_addr + size:06X}]")
        else:
            eprint(f"          - [0x{addr + rom_addr + size:06X}]")

def emit_titexdata_pad(next_addr: int, actual_next_addrs: int, index: int, seg_name: str):
    if next_addr + 3 < actual_next_addrs:
        pad_size = actual_next_addrs-next_addr
        pad_size = pad_size // 4 * 4
        print(f"""\
u8 {seg_name}_titexdata_{index:02}_pad[0x{pad_size:X}] = {{
    0
}};
""")


def extract_anime_main():
    parser = argparse.ArgumentParser()
    parser.add_argument("anime_segment_bin")
    parser.add_argument("seg_name")
    parser.add_argument("-a", "--rom-addr", default="0")

    args = parser.parse_args()

    anime_segment_bin = Path(args.anime_segment_bin)
    seg_name = str(args.seg_name)
    rom_addr = int(args.rom_addr, 0)

    anime_segment_bytes = anime_segment_bin.read_bytes()

    texData = read_u32(anime_segment_bytes, 0x0)
    texDataLen = read_u32(anime_segment_bytes, 0x4)
    metadata_addr = read_u32(anime_segment_bytes, 0x8)
    metadata_len_addr = read_u32(anime_segment_bytes, 0xC)

    assert texData != 0
    assert texDataLen != 0
    assert metadata_addr != 0
    assert metadata_len_addr != 0

    print(f"""\
#include "tex_func.h"
#include "char_anime.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData {seg_name}_titexdata[];
extern s32 {seg_name}_titexdata_len;
extern u8 *{seg_name}_metadata[];
extern s32 {seg_name}_metadata_len;

AnimeHeader {seg_name}_header = {{
    {seg_name}_titexdata,
    &{seg_name}_titexdata_len,
    {seg_name}_metadata,
    &{seg_name}_metadata_len,
}};
""")

    count1 = read_u32(anime_segment_bytes, texDataLen)

    # print(f"arr:   {texData:08X}")
    # print(f"count: {count1:08X}")

    textues: list[tuple[int, str, str, int, int, int, bool]] = []
    next_addr: int|None = None

    for i in range(count1):
        ptr = texData + i * 0x8
        # print(f"{ptr:08X} ", end="")
        texs_addr = read_u32(anime_segment_bytes, ptr)
        info_addr = read_u32(anime_segment_bytes, ptr+0x4)
        # print(f"{texs_addr:08X} {info_addr:08X}")

        if texs_addr == 0 and info_addr == 0:
            continue

        if next_addr is not None:
            emit_titexdata_pad(next_addr, texs_addr, i-1, seg_name)

        print(f"/* titexdata_{i:02} */\n")

        assert texs_addr != 0
        assert info_addr != 0

        tlut_addr = read_u32(anime_segment_bytes, texs_addr + 0x0)
        tex_addr = read_u32(anime_segment_bytes, texs_addr + 0x4)

        assert tex_addr != 0
        assert tlut_addr != tex_addr

        width = read_u16(anime_segment_bytes, info_addr + 0x0)
        height = read_u16(anime_segment_bytes, info_addr + 0x2)
        fmt = read_u16(anime_segment_bytes, info_addr + 0x4)
        bitflags = read_u16(anime_segment_bytes, info_addr + 0x6)

        assert fmt in {0x4, 0x8, 0x10}, f"{fmt:X}"
        assert bitflags in {0, 1}, f"{bitflags:X}"

        tex_type = "u8"
        if tex_type == 0x10:
            tex_type = "u16"

        is_ci = False

        if tlut_addr != 0:
            assert fmt in {0x4, 0x8}
            # tex_fmt = f"ci{fmt}"
            tex_fmt = f"i{fmt}"
            is_ci = True
        else:
            if fmt == 0x10:
                tex_fmt = f"rgba16"
            else:
                tex_fmt = f"i{fmt}"

        fmt_name = TI_FMTS[fmt]
        bitflag_name = TI_BITFLAGS[bitflags]

        tex_name = f"{seg_name}_titexdata_{i:02}_texs_tex"

        tex_name_width = f"{seg_name}_titexdata_{i:02}_texs_tex_width"
        tex_name_height = f"{seg_name}_titexdata_{i:02}_texs_tex_height"

        print(f"#define {tex_name_width} {width}")
        print(f"#define {tex_name_height} {height}")

        print(f"extern {tex_type} {tex_name}[];")

        tlut_name = "NULL"
        if tlut_addr != 0:
            tlut_name = f"{seg_name}_titexdata_{i:02}_texs_tlut"
            print(f"extern u16 {tlut_name}[];")

        print()

        # print(f"{tlut_addr:08X} {tex_addr:08X}")
        # print(f"    {width} {height} {fmt} {bitflags}")

        print(f"""\
TiTexDataTextures {seg_name}_titexdata_{i:02}_texs = {{
    {tlut_name},
    {tex_name},
}};
""")
        print(f"""\
u16 {seg_name}_titexdata_{i:02}_info[] = {{
    {tex_name_width}, {tex_name_height}, {fmt_name}, {bitflag_name},
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

        if tlut_addr == 0:
            emit_texture(tex_name, tex_type, tex_fmt, seg_name)
            next_addr = tex_addr + int(width * height * mult)
        elif tlut_addr < tex_addr:
            emit_tlut(tlut_name, seg_name)
            emit_texture(tex_name, tex_type, tex_fmt, seg_name)
            next_addr = tex_addr + int(width * height * mult)
        else:
            emit_texture(tex_name, tex_type, tex_fmt, seg_name)
            emit_tlut(tlut_name, seg_name)
            next_addr = tlut_addr + tlut_width * tlut_height

        if tlut_addr != 0:
            print(f"static_assert(ARRAY_COUNT({tlut_name}) == {tlut_width} * {tlut_height}, \"The dimensions of `{tlut_name}` does not match the size of the actual tlut\");")
            textues.append((tlut_addr, "rgba16", f"assets/anime/{seg_name}/{tlut_name}.rgba16", tlut_width, tlut_height, tlut_width * tlut_height * 2, is_ci))

        print(f"static_assert(ARRAY_COUNT({tex_name}) == {tex_name_width} * {tex_name_height}{op}, \"The dimensions of `{tex_name}` does not match the size of the actual texture\");")
        print()
        textues.append((tex_addr, tex_fmt, f"assets/anime/{seg_name}/{tex_name}.{tex_fmt}", width, height, int(width * height * mult), is_ci))

    if next_addr is not None:
        emit_titexdata_pad(next_addr, texData, count1-1, seg_name)

    print(f"TiTexData {seg_name}_titexdata[] = {{")
    for i in range(count1):
        ptr = texData + i * 0x8
        texs_addr = read_u32(anime_segment_bytes, ptr)
        info_addr = read_u32(anime_segment_bytes, ptr+0x4)

        texs_name = f"&{seg_name}_titexdata_{i:02}_texs"
        if texs_addr == 0:
            texs_name = "NULL"
        info_name = f"{seg_name}_titexdata_{i:02}_info"
        if info_addr == 0:
            info_name = "NULL"

        print(f"    {{ {texs_name}, {info_name} }},")
    print(f"}};")
    print()

    print(f"s32 {seg_name}_titexdata_len = ARRAY_COUNT({seg_name}_titexdata);")


    print()

    metadata_len = read_u32(anime_segment_bytes, metadata_len_addr)

    # print(f"arr:   {metadata_addr:08X}")
    # print(f"count: {metadata_len:08X}")

    for i in range(metadata_len):
        ptr = metadata_addr + i * 4
        # print(f"{ptr:08X} ", end="")
        data = read_u32(anime_segment_bytes, ptr)
        # print(f"{data:08X}")

        next_ptr = ptr + 4
        next_data = read_u32(anime_segment_bytes, next_ptr)

        # print(f"/* {data:08X} */")
        print(f"""\
u8 {seg_name}_metadata_{i:02}[] = {{
    \
""", end="")
        while data < metadata_addr:
            if data == next_data:
                print()
                break

            val = read_u8(anime_segment_bytes, data)
            cmd = METADATA_CMDS.get(val)
            if cmd is not None:
                data += 1
                val2 = read_u8(anime_segment_bytes, data)
                print(f"{cmd}(0x{val2:02X}),", end="")
            elif val == 0xFF:
                print(f"ANIME_METADATA_END,", end="")
            else:
                print(f"0x{val:02X},", end="")
            if val == 0xFF:
                print()
                break
            print(f" ", end="")
            data += 1
        print(f"}};")
        print()

    print(f"u8 *{seg_name}_metadata[] = {{")
    for i in range(metadata_len):
        print(f"    {seg_name}_metadata_{i:02},")
    print(f"}};")
    print()

    print(f"s32 {seg_name}_metadata_len = ARRAY_COUNT({seg_name}_metadata);")

    emit_splat_info(textues, rom_addr, seg_name)


if __name__ == "__main__":
    extract_anime_main()

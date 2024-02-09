#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

#
# Utilities to bootstrap C files for TiTexData assets.
# Usually this assets use the tiMappingAddr function
#

from __future__ import annotations

import dataclasses
import struct
import sys


@dataclasses.dataclass
class TextureInfo:
    addr: int
    tex_fmt: str
    tex_path: str
    width: int
    height: int
    size: int
    is_ci: bool


def emit_splat_info(textues: list[TextureInfo], rom_addr: int, seg_name: str):
    textues.sort(key=lambda x: x.addr)

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
    for tex_info in textues:
        comment = ""
        if tex_info.is_ci:
            comment = " # TODO: extract as ci"
        eprint(f"          - [0x{tex_info.addr+rom_addr:06X}, {tex_info.tex_fmt}, {tex_info.tex_path}, {tex_info.width}, {tex_info.height}]{comment}")
        if i + 1 < len(textues):
            if tex_info.addr + tex_info.size != textues[i+1].addr:
                eprint(f"          - [0x{tex_info.addr + rom_addr + tex_info.size:06X}]")
        else:
            eprint(f"          - [0x{tex_info.addr + rom_addr + tex_info.size:06X}]")


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


def emit_titexdata_pad(next_addr: int, actual_next_addrs: int, index: int, seg_name: str):
    if next_addr + 3 < actual_next_addrs:
        pad_size = actual_next_addrs-next_addr
        pad_size = pad_size // 4 * 4
        print(f"""\
u8 {seg_name}_titexdata_{index:02}_pad[0x{pad_size:X}] = {{
    0
}};
""")


def emit_ti_tex_data(tex_data_addr: int, tex_data_count: int, segment_bytes: bytes, seg_name: str) -> tuple[list[TextureInfo], int|None]:
    textues: list[TextureInfo] = []
    next_addr: int|None = None

    for i in range(tex_data_count):
        ptr = tex_data_addr + i * 0x8
        # print(f"{ptr:08X} ", end="")
        texs_addr = read_u32(segment_bytes, ptr)
        info_addr = read_u32(segment_bytes, ptr+0x4)
        # print(f"{texs_addr:08X} {info_addr:08X}")

        if texs_addr == 0 and info_addr == 0:
            continue

        if next_addr is not None:
            emit_titexdata_pad(next_addr, texs_addr, i-1, seg_name)

        print(f"/* titexdata_{i:02} */\n")

        assert texs_addr != 0
        assert info_addr != 0

        tlut_addr = read_u32(segment_bytes, texs_addr + 0x0)
        tex_addr = read_u32(segment_bytes, texs_addr + 0x4)

        assert tex_addr != 0
        assert tlut_addr != tex_addr

        width = read_u16(segment_bytes, info_addr + 0x0)
        height = read_u16(segment_bytes, info_addr + 0x2)
        fmt = read_u16(segment_bytes, info_addr + 0x4)
        bitflags = read_u16(segment_bytes, info_addr + 0x6)

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
            textues.append(TextureInfo(tlut_addr, "rgba16", f"assets/anime/{seg_name}/{tlut_name}.rgba16", tlut_width, tlut_height, tlut_width * tlut_height * 2, is_ci))

        print(f"static_assert(ARRAY_COUNT({tex_name}) == {tex_name_width} * {tex_name_height}{op}, \"The dimensions of `{tex_name}` does not match the size of the actual texture\");")
        print()
        textues.append(TextureInfo(tex_addr, tex_fmt, f"assets/anime/{seg_name}/{tex_name}.{tex_fmt}", width, height, int(width * height * mult), is_ci))

    return textues, next_addr

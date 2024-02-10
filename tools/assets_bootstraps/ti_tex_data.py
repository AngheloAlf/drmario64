#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

#
# Utilities to bootstrap C files for TiTexData assets.
# Usually this assets use the tiMappingAddr function
#

from __future__ import annotations

import dataclasses
import enum
import struct
import sys


ASSET_TYPE = ""


@dataclasses.dataclass
class TextureInfo:
    addr: int
    tex_fmt: str
    tex_path: str
    width: int
    height: int
    size: int
    is_ci: bool
    is_tlut: bool

    def c_type(self) -> str:
        if self.tex_fmt == "rgba16":
            return "u16"
        return "u8"


class SymbolType(enum.Enum):
    TiTexDataTextures = "TiTexDataTextures"
    TiTexDataInfo = "TiTexDataInfo"
    Texture = "Texture"
    Tlut = "Tlut"

@dataclasses.dataclass
class Symbol:
    addr: int
    sym_type: SymbolType
    size: int
    tex: TextureInfo|None=None
    name: str|None=None

    def __str__(self) -> str:
        return f"addr: 0x{self.addr:06X}, size: 0x{self.size:04X}, type: {self.sym_type.name}"


def emit_splat_info(textues: list[TextureInfo], rom_addr: int, seg_name: str):
    textues.sort(key=lambda x: x.addr)

    eprint(f"""\
    type: code
    start: 0x{rom_addr:06X}
    vram: 0x0
    exclusive_ram_id: {ASSET_TYPE}
    subsegments:
      - [auto, c, assets/{ASSET_TYPE}/{seg_name}]
      - start: 0x{rom_addr:06X}
        type: .data
        name: assets/{ASSET_TYPE}/{seg_name}
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


def emit_includes():
    print(f"""\
#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"
""")


def emit_texture(tex_name: str, tex_type: str, tex_fmt: str, seg_name: str):
    assert tex_name != "NULL"
    print(f"""\
{tex_type} {tex_name}[] ALIGNED(8) = {{
#include "assets/{ASSET_TYPE}/{seg_name}/{tex_name}.{tex_fmt}.inc"
}};
""")

def emit_tlut(tlut_name: str, seg_name: str):
    assert tlut_name != "NULL"
    print(f"""\
u16 {tlut_name}[] ALIGNED(8) = {{
#include "assets/{ASSET_TYPE}/{seg_name}/{tlut_name}.rgba16.inc"
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


def emit_ti_tex_data(tex_data_addr: int, tex_data_count: int, segment_bytes: bytes, seg_name: str) -> list[TextureInfo]:
    textues: list[TextureInfo] = []
    next_addr: int|None = None

    # print(f"arr:   {tex_data_addr:08X}")
    # print(f"count: {tex_data_count:08X}")

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

        if tex_addr != 0:
            print(f"extern {tex_type} {tex_name}[];")
        else:
            tex_name = "NULL"

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
        elif tex_addr == 0:
            emit_tlut(tlut_name, seg_name)
            next_addr = tlut_addr + tlut_width * tlut_height
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
            textues.append(TextureInfo(tlut_addr, "rgba16", f"assets/{ASSET_TYPE}/{seg_name}/{tlut_name}.rgba16", tlut_width, tlut_height, tlut_width * tlut_height * 2, is_ci, True))

        if tex_addr != 0:
            print(f"static_assert(ARRAY_COUNT({tex_name}) == {tex_name_width} * {tex_name_height}{op}, \"The dimensions of `{tex_name}` does not match the size of the actual texture\");")
            textues.append(TextureInfo(tex_addr, tex_fmt, f"assets/{ASSET_TYPE}/{seg_name}/{tex_name}.{tex_fmt}", width, height, int(width * height * mult), is_ci, False))
        print()

    if next_addr is not None:
        emit_titexdata_pad(next_addr, tex_data_addr, tex_data_count-1, seg_name)

    print(f"TiTexData {seg_name}_titexdata[] = {{")
    for i in range(tex_data_count):
        ptr = tex_data_addr + i * 0x8
        texs_addr = read_u32(segment_bytes, ptr)
        info_addr = read_u32(segment_bytes, ptr+0x4)

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

    return textues



def _scan_ti_tex_data_entry(segment_bytes: bytes, texs_addr: int, info_addr: int) -> dict[int, Symbol]:
    """Data pointed by TiTexData"""

    symbols: dict[int, Symbol] = {}

    tlut_addr = read_u32(segment_bytes, texs_addr + 0x0)
    tex_addr = read_u32(segment_bytes, texs_addr + 0x4)

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

    # print(f"{tlut_addr:08X} {tex_addr:08X}")
    # print(f"    {width} {height} {fmt} {bitflags}")

    mult = 1
    tlut_width = 16
    tlut_height = 16
    if fmt == 4:
        mult = 1 / 2
        tlut_width = 4
        tlut_height = 4
    if fmt == 0x10:
        mult = 2

    if tlut_addr != 0:
        tex_info = TextureInfo(tlut_addr, "rgba16", f"", tlut_width, tlut_height, tlut_width * tlut_height * 2, is_ci, True)
        sym = Symbol(tlut_addr, SymbolType.Tlut, tlut_width * tlut_height * 2, tex=tex_info)
        symbols[tlut_addr] = sym

    if tex_addr != 0:
        tex_info = TextureInfo(tex_addr, tex_fmt, f"", width, height, int(width * height * mult), is_ci, False)
        sym = Symbol(tex_addr, SymbolType.Texture, int(width * height * mult), tex=tex_info)
        symbols[tex_addr] = sym

    return symbols


def scan_ti_tex_data_array(segment_bytes: bytes, tex_data_addr: int, tex_data_count: int) -> dict[int, Symbol]:
    """TiTexData array"""

    symbols: dict[int, Symbol] = {}

    for i in range(tex_data_count):
        entry_addr = tex_data_addr + i * 0x8
        texs_addr = read_u32(segment_bytes, entry_addr)
        info_addr = read_u32(segment_bytes, entry_addr+0x4)

        if texs_addr == 0 and info_addr == 0:
            continue
        assert info_addr != 0, f"{info_addr:06X}"
        assert info_addr != 0, f"{texs_addr:06X}"

        sym = Symbol(texs_addr, SymbolType.TiTexDataTextures, 8)
        symbols[texs_addr] = sym

        sym = Symbol(info_addr, SymbolType.TiTexDataInfo, 2*4)
        symbols[info_addr] = sym

        for new_addr, new_sym in _scan_ti_tex_data_entry(segment_bytes, texs_addr, info_addr).items():
            symbols[new_addr] = new_sym

    return symbols

def name_symbols(symbols: dict[int, Symbol], seg_name: str):
    index = -1

    for addr in sorted(symbols.keys()):
        sym = symbols[addr]

        if sym.sym_type == SymbolType.TiTexDataTextures:
            index += 1
            sym.name = f"{seg_name}_titexdata_{index:02}_texs"
        elif sym.sym_type == SymbolType.TiTexDataInfo:
            sym.name = f"{seg_name}_titexdata_{index:02}_info"
        elif sym.sym_type == SymbolType.Texture:
            sym.name = f"{seg_name}_titexdata_{index:02}_texs_tex"
            assert sym.tex is not None, sym.name
            sym.tex.tex_path = f"assets/{ASSET_TYPE}/{seg_name}/{sym.name}.{sym.tex.tex_fmt}"
        elif sym.sym_type == SymbolType.Tlut:
            sym.name = f"{seg_name}_titexdata_{index:02}_texs_tlut"
            assert sym.tex is not None, sym.name
            sym.tex.tex_path = f"assets/{ASSET_TYPE}/{seg_name}/{sym.name}.{sym.tex.tex_fmt}"
        else:
            assert False, sym.sym_type


def _emit_TiTexDataTextures(sym: Symbol, symbols: dict[int, Symbol], segment_bytes: bytes):
    assert sym.name is not None, sym.addr

    tlut_addr = read_u32(segment_bytes, sym.addr + 0x0)
    tex_addr = read_u32(segment_bytes, sym.addr + 0x4)

    tlut_name = "NULL"
    tex_name = "NULL"

    skip = False

    if tlut_addr != 0:
        tlut_sym = symbols[tlut_addr]
        tlut_name = tlut_sym.name
        assert tlut_name is not None, f"{tlut_addr:06X}"
        assert tlut_sym.tex is not None, f"{tlut_addr:06X}"
        print(f"extern {tlut_sym.tex.c_type()} {tlut_name}[];")
        skip = True
    if tex_addr != 0:
        tex_sym = symbols[tex_addr]
        tex_name = tex_sym.name
        assert tex_name is not None, f"{tex_addr:06X}"
        assert tex_sym.tex is not None, f"{tex_addr:06X}"
        print(f"extern {tex_sym.tex.c_type()} {tex_name}[];")
        skip = True

    if skip:
        print()

    print(f"""\
TiTexDataTextures {sym.name} = {{
    {tlut_name},
    {tex_name},
}};
""")

def _emit_TiTexDataInfo(sym: Symbol, symbols: dict[int, Symbol], segment_bytes: bytes):
    assert sym.name is not None, sym.addr

    width = read_u16(segment_bytes, sym.addr + 0x0)
    height = read_u16(segment_bytes, sym.addr + 0x2)
    fmt = read_u16(segment_bytes, sym.addr + 0x4)
    bitflags = read_u16(segment_bytes, sym.addr + 0x6)

    fmt_name = TI_FMTS[fmt]
    bitflag_name = TI_BITFLAGS[bitflags]

    tex_name = sym.name.replace("_info", "_texs_tex")

    width_name = f"{tex_name}_width"
    height_name = f"{tex_name}_height"

    print(f"#define {width_name} {width}")
    print(f"#define {height_name} {height}")
    print()

    print(f"""\
u16 {sym.name}[] = {{
    {width_name}, {height_name}, {fmt_name}, {bitflag_name},
}};
""")


def _emit_texture(sym: Symbol, symbols: dict[int, Symbol], segment_bytes: bytes):
    assert sym.name is not None, sym.addr
    assert sym.name != "NULL", sym.addr
    assert sym.tex is not None, sym.addr

    if sym.tex.is_tlut:
        tex_dims = f"{sym.tex.width} * {sym.tex.height}"
        typ = "tlut"
    else:
        op = ""
        if sym.tex.tex_fmt in {"i4", "ci4"}:
            op = " / 2"
        tex_dims = f"{sym.name}_width * {sym.name}_height{op}"
        typ = "texture"

    print(f"""\
{sym.tex.c_type()} {sym.name}[] ALIGNED(8) = {{
#include "{sym.tex.tex_path}.inc"
}};
static_assert(ARRAY_COUNT({sym.name}) == {tex_dims}, \"The dimensions of `{sym.name}` does not match the size of the actual {typ}\");
""")


def emit_pad(next_addr: int, actual_next_addrs: int, index: int, i: int, seg_name: str):
    if next_addr + 3 < actual_next_addrs:
        pad_size = actual_next_addrs-next_addr
        pad_size = pad_size // 4 * 4
        print(f"""\
u8 {seg_name}_titexdata_{index:02}_{i:02}_pad[0x{pad_size:X}] = {{
    0
}};
""")


def emit_symbols(symbols: dict[int, Symbol], segment_bytes: bytes, seg_name: str, tex_data_addr: int):
    index = -1

    symbols_list = sorted(symbols.items())

    for i, (addr, sym) in enumerate(symbols_list):
        if sym.sym_type == SymbolType.TiTexDataTextures:
            index += 1
            print(f"/* titexdata_{index:02} */\n")
            _emit_TiTexDataTextures(sym, symbols, segment_bytes)
        elif sym.sym_type == SymbolType.TiTexDataInfo:
            _emit_TiTexDataInfo(sym, symbols, segment_bytes)
        elif sym.sym_type == SymbolType.Texture:
            _emit_texture(sym, symbols, segment_bytes)
        elif sym.sym_type == SymbolType.Tlut:
            _emit_texture(sym, symbols, segment_bytes)
        else:
            assert False, sym.sym_type

        next_addr = addr + sym.size
        if i + 1 < len(symbols_list):
            emit_pad(next_addr, symbols_list[i+1][0], index, i, seg_name)
        else:
            emit_pad(next_addr, tex_data_addr, index, i, seg_name)


def emit_ti_tex_data_array(segment_bytes: bytes, tex_data_addr: int, tex_data_count: int, symbols: dict[int, Symbol], seg_name: str):
    print(f"TiTexData {seg_name}_titexdata[] = {{")
    for i in range(tex_data_count):
        entry_addr = tex_data_addr + i * 0x8
        texs_addr = read_u32(segment_bytes, entry_addr)
        info_addr = read_u32(segment_bytes, entry_addr+0x4)

        texs_name = "NULL"
        info_name = "NULL"

        if texs_addr != 0:
            texs_name = symbols[texs_addr].name
            assert texs_name is not None, f"0x{texs_addr:06X}"
            texs_name = f"&{texs_name}"
        if info_addr != 0:
            info_name = symbols[info_addr].name
            assert info_name is not None, f"0x{info_addr:06X}"

        print(f"    {{ {texs_name}, {info_name} }},")
    print(f"}};")
    print()

    print(f"s32 {seg_name}_titexdata_len = ARRAY_COUNT({seg_name}_titexdata);")

def emit_splat_subsegments_for_symbols(symbols: dict[int, Symbol], rom_addr: int, seg_name: str):
    symbols_list = sorted(symbols.items())

    eprint(f"""\
  - name: segment_{seg_name} # compressed
    type: code
    start: 0x{rom_addr:06X}
    vram: 0x0
    exclusive_ram_id: {ASSET_TYPE}
    subsegments:
      - [auto, c, assets/{ASSET_TYPE}/{seg_name}]
      - start: 0x{rom_addr:06X}
        type: .data
        name: assets/{ASSET_TYPE}/{seg_name}
        subsegments:\
""")

    eprint(f"          - [0x{rom_addr:06X}]")
    i = 0
    for addr, sym in symbols_list:
        if sym.sym_type not in {SymbolType.Texture, SymbolType.Tlut}:
            continue
        assert sym.tex is not None

        comment = ""
        if sym.tex.is_ci:
            comment = " # TODO: extract as ci"
        eprint(f"          - [0x{sym.tex.addr+rom_addr:06X}, {sym.tex.tex_fmt}, {sym.tex.tex_path}, {sym.tex.width}, {sym.tex.height}]{comment}")
        if i + 1 < len(symbols_list):
            if sym.tex.addr + sym.tex.size != symbols_list[i+1][1].addr:
                eprint(f"          - [0x{sym.tex.addr + rom_addr + sym.tex.size:06X}]")
        else:
            eprint(f"          - [0x{sym.tex.addr + rom_addr + sym.tex.size:06X}]")
    eprint()

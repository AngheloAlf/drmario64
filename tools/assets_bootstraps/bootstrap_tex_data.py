#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path

import ti_tex_data


def extract_texdata_main():
    parser = argparse.ArgumentParser()
    parser.add_argument("segment_bin")
    parser.add_argument("seg_name")
    parser.add_argument("asset_type")
    parser.add_argument("-a", "--rom-addr", default="0")

    args = parser.parse_args()

    segment_bin = Path(args.segment_bin)
    seg_name = str(args.seg_name)
    ti_tex_data.ASSET_TYPE = args.asset_type
    rom_addr = int(args.rom_addr, 0)

    segment_bytes = segment_bin.read_bytes()

    texData = ti_tex_data.read_u32(segment_bytes, 0x0)
    texDataLen = ti_tex_data.read_u32(segment_bytes, 0x4)

    assert texData != 0
    assert texDataLen != 0

    ti_tex_data.emit_includes()

    print(f"""\
extern TiTexData {seg_name}_titexdata[];
extern s32 {seg_name}_titexdata_len;

TiTexDataHeader {seg_name}_header = {{
    {seg_name}_titexdata,
    &{seg_name}_titexdata_len,
}};
""")

    count1 = ti_tex_data.read_u32(segment_bytes, texDataLen)

    symbols = ti_tex_data.scan_ti_tex_data_array(segment_bytes, texData, count1)
    ti_tex_data.name_symbols(symbols, seg_name)
    ti_tex_data.emit_symbols(symbols, segment_bytes, seg_name, texData)
    ti_tex_data.emit_ti_tex_data_array(segment_bytes, texData, count1, symbols, seg_name)

    ti_tex_data.emit_splat_subsegments_for_symbols(symbols, rom_addr, seg_name)

if __name__ == "__main__":
    extract_texdata_main()

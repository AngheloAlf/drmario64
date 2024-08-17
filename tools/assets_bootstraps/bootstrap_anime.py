#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2024 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path

import ti_tex_data

ti_tex_data.ASSET_TYPE = "anime"

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

    texData = ti_tex_data.read_u32(anime_segment_bytes, 0x0)
    texDataLen = ti_tex_data.read_u32(anime_segment_bytes, 0x4)
    metadata_addr = ti_tex_data.read_u32(anime_segment_bytes, 0x8)
    metadata_len_addr = ti_tex_data.read_u32(anime_segment_bytes, 0xC)

    assert texData != 0
    assert texDataLen != 0
    assert metadata_addr != 0
    assert metadata_len_addr != 0

    print(f"""\
#include "char_anime.h"
""")

    ti_tex_data.emit_includes()

    print(f"""\
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

    count1 = ti_tex_data.read_u32(anime_segment_bytes, texDataLen)

    textues = ti_tex_data.emit_ti_tex_data(texData, count1, anime_segment_bytes, seg_name)

    print()

    metadata_len = ti_tex_data.read_u32(anime_segment_bytes, metadata_len_addr)

    # print(f"arr:   {metadata_addr:08X}")
    # print(f"count: {metadata_len:08X}")

    for i in range(metadata_len):
        ptr = metadata_addr + i * 4
        # print(f"{ptr:08X} ", end="")
        data = ti_tex_data.read_u32(anime_segment_bytes, ptr)
        # print(f"{data:08X}")

        next_ptr = ptr + 4
        next_data = ti_tex_data.read_u32(anime_segment_bytes, next_ptr)

        # print(f"/* {data:08X} */")
        print(f"""\
u8 {seg_name}_metadata_{i:02}[] = {{
    \
""", end="")
        while data < metadata_addr:
            if data == next_data:
                print()
                break

            val = ti_tex_data.read_u8(anime_segment_bytes, data)
            cmd = ti_tex_data.METADATA_CMDS.get(val)
            if cmd is not None:
                data += 1
                val2 = ti_tex_data.read_u8(anime_segment_bytes, data)
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

    ti_tex_data.emit_splat_info(textues, rom_addr, seg_name)


if __name__ == "__main__":
    extract_anime_main()

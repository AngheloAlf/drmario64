#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import spimdisasm
from pathlib import Path
import subprocess
import tempfile
import zlib


def decompressZlib(data: bytearray) -> bytearray:
    decomp = zlib.decompressobj(-zlib.MAX_WBITS)
    output = bytearray()
    output.extend(decomp.decompress(data))
    while decomp.unconsumed_tail:
        output.extend(decomp.decompress(decomp.unconsumed_tail))
    output.extend(decomp.flush())
    return output


def compressZlib(data: bytearray) -> bytearray:
    comp = zlib.compressobj(9, wbits=-zlib.MAX_WBITS)
    output = bytearray()
    output.extend(comp.compress(data))
    # while comp.unconsumed_tail:
    #     output.extend(comp.decompress(comp.unconsumed_tail))
    output.extend(comp.flush())
    return output

def compressGzip(data: bytearray, compressionLevel: int, name: str, version: str, debug: bool=False) -> bytearray:
    input_temp_file = tempfile.NamedTemporaryFile(mode="wb", suffix=".bin", prefix=f"{version}_{name}.", delete=False)
    output_temp_file = tempfile.NamedTemporaryFile(suffix=".bin.gz", prefix=f"{version}_{name}.", delete=False)

    if debug:
        print(f"Creating temp files: {input_temp_file.name}, {output_temp_file.name}")

    input_temp_file.write(data)
    input_temp_file.close()

    output_temp_file.close()

    command = ["tools/gzip-1.3.3-ique/gzip", f"-{compressionLevel}", input_temp_file.name, output_temp_file.name]
    if debug:
        print(f"Running command: {' '.join(command)}")
    subprocess.run(command, check=True)

    out = bytearray(Path(output_temp_file.name).read_bytes()[0xA:])

    if not debug:
        Path(input_temp_file.name).unlink()
        Path(output_temp_file.name).unlink()

    return out


@dataclasses.dataclass
class SegmentEntry:
    segmentName: str
    compressedRomOffset: int
    compressedRomOffsetEnd: int
    uncompressedHash: str
    compressionLevel: int

    version: str

    compressed: bool = True

    @property
    def compressedPath(self) -> Path:
        return Path("bin") / self.version / "compressed_segments" / f"{self.segmentName}_compressed.bin"

    @property
    def compressedSegmentSize(self) -> int:
        return self.compressedRomOffsetEnd - self.compressedRomOffset

    def __lt__(self, other):
        return self.compressedRomOffset < other.compressedRomOffset


def readSegmentsCsv(segmentsPath: Path, version: str) -> dict[str, SegmentEntry]:
    segmentsCsv = spimdisasm.common.Utils.readCsv(segmentsPath)
    segmentDict = {}
    header = True

    for row in segmentsCsv:
        if header:
            header = False
            continue
        if len(row) == 0:
            continue
        name, compressedRomOffset, compressedRomOffsetEnd, segmentHash, compressionLevel = row
        segmentDict[f".{name}"] = SegmentEntry(name, int(compressedRomOffset, 0), int(compressedRomOffsetEnd, 0), segmentHash, int(compressionLevel), version)

    return segmentDict

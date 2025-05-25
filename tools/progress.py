#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import dataclasses
import decomp_settings
import json
import mapfile_parser
from pathlib import Path


def writeReport(version: str, settings: decomp_settings.Config) -> Path:
    selectedVersion = settings.get_version_by_name(version)
    assert selectedVersion is not None
    mapPath = Path(selectedVersion.paths.map)
    outputPath = Path(selectedVersion.paths.build_dir) / "report.json"

    specificSettings = mapfile_parser.frontends.objdiff_report.SpecificSettings.fromDecompConfig(settings)
    assert specificSettings is not None
    prefixesToTrim = specificSettings.prefixesToTrim
    pathIndex = specificSettings.pathIndex
    assert pathIndex is not None

    reportCategories = mapfile_parser.ReportCategories()
    for cat in specificSettings.categories:
        reportCategories.push(cat.ide, cat.name, cat.paths)

    if specificSettings.checkAsmPaths:
        assert selectedVersion.paths.asm is not None
        asmPath = Path(selectedVersion.paths.asm)
    else:
        asmPath = None

    mapFile = mapfile_parser.MapFile.newFromMapFile(mapPath)
    mapFile.writeObjdiffReportToFile(
        outputPath,
        prefixesToTrim,
        reportCategories,
        pathIndex=pathIndex,
        asmPath=asmPath,
    )

    return outputPath

@dataclasses.dataclass
class Report:
    measures: ReportMeasures
    categories: list[ReportCategory]
    units: list[ReportUnit]

    @staticmethod
    def fromDict(info: dict) -> Report:
        categories: list[ReportCategory] = []
        units: list[ReportUnit] = []

        measures = ReportMeasures.fromDict(info["measures"])
        assert measures is not None, "all"
        for cat in info["categories"]:
            x = ReportCategory.fromDict(cat)
            if x is not None:
                categories.append(x)
        for unit in info["units"]:
            x = ReportUnit.fromDict(unit)
            if x is not None:
                units.append(x)

        return Report(
            measures = measures,
            categories = categories,
            units = units,
        )

@dataclasses.dataclass
class ReportCategory:
    id: str
    name: str
    measures: ReportMeasures

    @staticmethod
    def fromDict(info: dict) -> ReportCategory | None:
        measures = ReportMeasures.fromDict(info["measures"])
        if measures is None:
            return None
        return ReportCategory(
            id = info["id"],
            name = info["name"],
            measures = measures,
        )

@dataclasses.dataclass
class ReportUnit:
    name: str
    measures: ReportMeasures
    # sections: 
    # metadata: 

    @staticmethod
    def fromDict(info: dict) -> ReportUnit | None:
        measures = ReportMeasures.fromDict(info["measures"])
        if measures is None:
            return None
        return ReportUnit(
            name = info["name"],
            measures = measures,
        )

@dataclasses.dataclass
class ReportMeasures:
    fuzzy_match_percent: float
    total_code: int
    matched_code: int
    matched_code_percent: float
    matched_data_percent: float
    matched_functions_percent: float
    complete_code_percent: float
    complete_data_percent: float
    total_units: int

    @staticmethod
    def fromDict(info: dict) -> ReportMeasures|None:
        fuzzy_match_percent = info.get("fuzzy_match_percent")
        total_code = info.get("total_code")
        matched_code = info.get("matched_code")
        matched_code_percent = info.get("matched_code_percent")
        matched_data_percent = info.get("matched_data_percent")
        matched_functions_percent = info.get("matched_functions_percent")
        complete_code_percent = info.get("complete_code_percent")
        complete_data_percent = info.get("complete_data_percent")
        total_units = info.get("total_units")
        if total_units is None:
            return None
        return ReportMeasures(
            fuzzy_match_percent = fuzzy_match_percent if fuzzy_match_percent is not None else 0.0,
            total_code = int(total_code) if total_code is not None else 0,
            matched_code = int(matched_code) if matched_code is not None else 0,
            matched_code_percent = matched_code_percent if matched_code_percent is not None else 0.0,
            matched_data_percent = matched_data_percent if matched_data_percent is not None else 0.0,
            matched_functions_percent = matched_functions_percent if matched_functions_percent is not None else 0.0,
            complete_code_percent = complete_code_percent if complete_code_percent is not None else 0.0,
            complete_data_percent = complete_data_percent if complete_data_percent is not None else 0.0,
            total_units = total_units,
        )

    def as_entry_str(self, name: str, total_measures: ReportMeasures, column_size: int) -> str|None:
        categoryStr = "{0:<{1}}".format(name, column_size)
        matched_code = self.matched_code
        total_code = self.total_code
        matched_code_percent = self.matched_code_percent

        if total_measures.total_code == 0:
            return None

        decomped_percentage_total = matched_code / total_measures.total_code * 100
        total_total = total_code / total_measures.total_code * 100

        return f"{categoryStr}: {matched_code:>12} / {total_code:>8} {matched_code_percent:>12.4f}%  ({decomped_percentage_total:>8.4}% / {total_total:>8.4}%)"

def parseReport(reportPath: Path) -> Report:
    with reportPath.open() as f:
        report = json.load(f, parse_float=float, parse_int=int)

    return Report.fromDict(report)

def printTable(report: Report, sort: bool, remaining: bool, do_units: bool):
    new_cats: list[tuple[str, ReportMeasures]] = []
    if do_units:
        for unit in report.units:
            if unit.measures.total_code == 0:
                # Drop the ones we don't care about
                continue
            new_cats.append((unit.name, unit.measures))
    else:
        for cat in report.categories:
            if cat.measures.total_code == 0:
                # Drop the ones we don't care about
                continue
            new_cats.append((cat.name, cat.measures))

    # Calculate the size for the first column
    columnSize = 27
    for (name, _) in new_cats:
        if len(name) > columnSize:
            columnSize = len(name)
    columnSize += 1

    categoryStr = "{0:<{1}}".format('Category', columnSize)
    print(f"{categoryStr}: {'DecompedSize':>12} / {'Total':>8} {'OfCategory':>12}%  ({'OfTotal':>20}%)")

    entry_str = report.measures.as_entry_str("all", report.measures, columnSize)
    assert entry_str is not None
    print(entry_str)
    print()

    if sort:
        new_cats.sort(key=lambda cat: (cat[1].matched_code_percent, cat[1].total_code, cat[0]), reverse=True)

    for (name, measures) in new_cats:
        entry_str = measures.as_entry_str(name, report.measures, columnSize)
        if entry_str is None:
            continue
        print(entry_str, end="")
        if remaining and measures.matched_code_percent != 100:
            matched_code = measures.matched_code
            assert matched_code is not None
            assert report.measures.total_code is not None
            assert measures.total_code is not None
            decomped_percentage_total = matched_code / report.measures.total_code * 100
            remainingPercentage = measures.total_code / report.measures.total_code * 100 - decomped_percentage_total
            print(f" {remainingPercentage:>8.4f}%", end="")
        print()


def progressMain():
    settings = decomp_settings.scan_for_config()
    versionsChoices = [x.name for x in settings.versions]

    parser = argparse.ArgumentParser(description="Print the progress of category in your terminal.")
    parser.add_argument("-v", "--version", help="version to process", choices=versionsChoices, default=versionsChoices[0])
    parser.add_argument("-s", "--sort", help="Sort by decomped size", action="store_true")
    parser.add_argument("-r", "--remaining", help="Print an extra column indicating the remaining percentage to match of each entry", action="store_true")
    parser.add_argument("-u", "--units", help="Print units instead of categories", action="store_true")

    args = parser.parse_args()

    outputPath = writeReport(args.version, settings)
    report = parseReport(outputPath)

    printTable(report, args.sort, args.remaining, args.units)


if __name__ == "__main__":
    progressMain()

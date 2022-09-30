#!/usr/bin/env python3
import colorama
colorama.init()

import argparse
import os
import re
import collections

regex_fileDataEntry = re.compile(r"^\s+(?P<section>[^\s]+)\s+(?P<vram>0x[^\s]+)\s+(?P<size>0x[^\s]+)\s+(?P<name>[^\s]+)$")
regex_bssEntry = re.compile(r"^\s+(?P<vram>0x[^\s]+)\s+(?P<name>[^\s]+)$")
regex_label = re.compile(r"^(?P<name>L[0-9A-F]{8})$")


File = collections.namedtuple("File", ["name", "vram", "bssVariables"])
FileEntry = collections.namedtuple("File", ["vram", "bssVariables"])
Variable = collections.namedtuple("Variable", ["name", "vram"])
Compared = collections.namedtuple("Compared", ["expected", "build", "diff"])


def parseMapFile(mapPath: str):
    with open(mapPath) as f:
        mapData = f.read()
        startIndex = mapData.find("..makerom")
        mapData = mapData[startIndex:]
    # print(len(mapData))

    filesList = list()

    inFile = False

    mapLines = mapData.split("\n")
    for line in mapLines:
        if inFile:
            if line.startswith("                "):
                entryMatch = regex_bssEntry.search(line)

                # Find function
                if entryMatch is not None:
                    varName = entryMatch["name"]
                    varVram = int(entryMatch["vram"], 16)

                    # Filter out jump table labels
                    labelMatch = regex_label.search(varName)
                    if labelMatch is None:
                        filesList[-1].bssVariables[varName] = varVram # append(Variable(varName, varVram))
                    # print(hex(funcVram), funcName)

            else:
                inFile = False
        else:
            if line.startswith(" .bss "):
                inFile = False
                entryMatch = regex_fileDataEntry.search(line)

                # Find file
                if entryMatch is not None:
                    name = "/".join(entryMatch["name"].split("/")[2:])
                    name = ".".join(name.split(".")[:-1])
                    size = int(entryMatch["size"], 16)
                    vram = int(entryMatch["vram"], 16)

                    if size > 0:
                        inFile = True
                        filesList.append(File(name, vram, collections.OrderedDict()))

    resultFileDict = dict()

    for file in filesList:
        bssCount = len(file.bssVariables)

        # Filter out files with no bss
        if bssCount == 0:
            continue

        resultFileDict[file.name] = FileEntry(file.vram, file.bssVariables)

    return resultFileDict


def compareMapFiles(mapFileBuild: str, mapFileExpected: str):
    isOkay = dict()

    print("Build mapfile:    " + mapFileBuild, file=os.sys.stderr)
    print("Expected mapfile: " + mapFileExpected, file=os.sys.stderr)
    print("", file=os.sys.stderr)

    buildMap = parseMapFile(mapFileBuild)
    expectedMap = parseMapFile(mapFileExpected)

    comparedDict = collections.OrderedDict()

    for fileName in expectedMap:

        if not fileName in buildMap:
            print(f"File '{fileName}' not found in '{mapFileBuild}'. Has it been renamed?", file=os.sys.stderr)

            continue

        # print(fileName)
        # print(buildMap[fileName])
        # print(expectedMap[fileName])
        # print("")

        comparedDict[fileName] = collections.OrderedDict()
        isOkay[fileName] = True

        for symbol in expectedMap[fileName].bssVariables:
            if not symbol in buildMap[fileName].bssVariables:
                print(f"Variable {symbol} not found in {mapFileBuild}, file {fileName} . Has it been renamed?", file=os.sys.stderr)

                continue

            expectedAddress = expectedMap[fileName].bssVariables[symbol]
            buildAddress = buildMap[fileName].bssVariables[symbol]
            comparedDict[fileName][symbol] = Compared( expectedAddress , buildAddress , buildAddress - expectedAddress )
            isOkay[fileName] &= (comparedDict[fileName][symbol].diff == 0)

        # print(f"comparedDict: {comparedDict[fileName]}")
        # print("")
        # print(f"Is okay: {isOkay[fileName]}")
        # print("")

    return isOkay, comparedDict


def printCsv(isOkay, comparedDict, printAll = True):
    print("File,Symbol Name,Expected,Build,Difference,GOOD/BAD")

    allGood = True

    for file in comparedDict:
        allGood &= isOkay[file]

        if isOkay[file]:
            if not printAll:
                continue
        
        fileSymbols = comparedDict[file]

        for symbol in fileSymbols:
            addresses = fileSymbols[symbol]
            symbolGood = colorama.Fore.RED + "BAD"
            if addresses.diff == 0:
                symbolGood = colorama.Fore.GREEN + "GOOD"
            symbolGood += colorama.Style.RESET_ALL

            print(f"{file},{symbol},{addresses.expected:X},{addresses.build:X},{addresses.diff:X},{symbolGood}")
    
        # print("")

    return allGood


def main():
    description = "Check that bss has not been reordered"
    # TODO
    epilog = """\
    """

    parser = argparse.ArgumentParser(description=description, epilog=epilog, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("mapfile", help="Path to a map file.")
    parser.add_argument("mapFileExpected", help="Path to the expected map file.")
    parser.add_argument("-a", "--print-all", help="Print all bss, not just non-matching.", action="store_true")
    parser.add_argument("-n", "--no-fun-allowed", help="Remove amusing messages.", action="store_true")
    args = parser.parse_args()

    isOkay, comparedDict = compareMapFiles(args.mapfile, args.mapFileExpected)

    if printCsv(isOkay, comparedDict, args.print_all):
        print(colorama.Fore.LIGHTGREEN_EX + "  GOOD" + colorama.Style.RESET_ALL)
        if args.no_fun_allowed:
            return 0

        print("\n" + colorama.Fore.LIGHTWHITE_EX +
        colorama.Back.RED + "                           " + colorama.Back.BLACK + "\n" +
        colorama.Back.RED + "     CONGRATURATIONS!      " + colorama.Back.BLACK + "\n" +
        colorama.Back.RED + "    All BSS is correct.    " + colorama.Back.BLACK + "\n" +
        colorama.Back.RED + "        THANK YOU!         " + colorama.Back.BLACK + "\n" +
        colorama.Back.RED + "  You are great decomper!  " + colorama.Back.BLACK + "\n" +
        colorama.Back.RED + "                           " + colorama.Style.RESET_ALL , file=os.sys.stderr)

        return 0

    else:
        print("\n" + colorama.Fore.LIGHTRED_EX + "BAD" + colorama.Style.RESET_ALL, file=os.sys.stderr)
        badFiles = []

        for file in isOkay:
            if not isOkay[file]:
                badFiles.append("  ReOrdering in " + file)

        print("\n  ".join(badFiles), file=os.sys.stderr)

        if args.no_fun_allowed:
            return 1

        print(colorama.Fore.LIGHTWHITE_EX +
        "  BSS is REORDERED!!\n"
        "  Oh! MY GOD!!" 
        + colorama.Style.RESET_ALL, file=os.sys.stderr)

        return 1


if __name__ == "__main__":
    main()


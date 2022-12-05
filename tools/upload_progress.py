#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

import argparse
import subprocess
import requests

import progress


def get_git_commit_timestamp() -> int:
    return int(subprocess.check_output(['git', 'show', '-s', '--format=%ct']).decode('ascii').rstrip())

def get_git_commit_sha() -> str:
    return subprocess.check_output(['git', 'rev-parse', 'HEAD']).decode('ascii').strip()

def generate_url(base_url: str, project: str) -> str:
    return "/".join([base_url, "data", project])


def uploadProgressMain():
    parser = argparse.ArgumentParser()
    parser.add_argument("base_url", help="API base URL")
    parser.add_argument("project", help="Project slug")
    parser.add_argument("--api-key", help="API key")
    parser.add_argument("-m", "--map", default="build/drmario64_uncompressed.map")

    args = parser.parse_args()

    totalStats, progressPerFolder = progress.getProgress(args.map, aliases= {"ultralib": "libultra"})

    categories = {}
    categories["all"] = totalStats.decompedSize
    categories["all/total"] = totalStats.total

    progress.ProgressStats.printHeader()
    totalStats.print("all", totalStats)
    print()

    for folder, statsEntry in progressPerFolder.items():
        statsEntry.print(folder, totalStats)
        categories[folder] = statsEntry.decompedSize
        categories[f"{folder}/total"] = statsEntry.total
    print()

    entries = {
        "timestamp": get_git_commit_timestamp(),
        "git_hash": get_git_commit_sha(),
        "categories": {"rom": categories},
    }

    url = generate_url(args.base_url, args.project)

    print("Publishing entries to", url)

    for key, value in entries.items():
        print(f"\t{key}: {value}")

    api_key = args.api_key
    if not api_key:
        print("Missing api-key, exiting without uploading")
        return

    data = {
        "api_key": api_key,
        "entries": [entries],
    }
    r = requests.post(url, json=data)
    r.raise_for_status()
    print("Done!")

if __name__ == '__main__':
    uploadProgressMain()

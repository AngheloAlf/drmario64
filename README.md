# Dr. Mario 64 [![Build Status]][actions] ![Code Progress]

[Build Status]: <https://github.com/AngheloAlf/drmario64/actions/workflows/ci.yml/badge.svg>
[actions]: <https://github.com/AngheloAlf/drmario64/actions/workflows/ci.yml>
[Code Progress]: https://img.shields.io/endpoint?label=Code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fdrmario64%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dall

Matching decomp of Dr. Mario 64

[Progress graph :chart_with_upwards_trend:](https://angheloalf.github.io/drmario64/)

## Dependencies

The build process has the following package requirements:

* make
* git
* build-essential
* clang
* binutils-mips-linux-gnu
* gcc-mips-linux-gnu
* python3
* pip3

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential clang binutils-mips-linux-gnu gcc-mips-linux-gnu python3 python3-pip
```

To install the dependencies Python dependencies run:

```bash
pip3 install -r requirements.txt
```

## Building

Copy your big-endian Dr Mario 64 ROM into the repository's root directory and rename it to `baserom.us.z64`. Then run

```bash
make setup
make lib
make extract
make
```

to download the appropriate compiler versions, build libultra, extract data from the rom using splat, and build the files back into a rom. If successful, the last line of output should say

```bash
build/drmario64.us.z64: OK
```

### Other versions

This repo also has experimental support for the iQue version of this game too.

For building this place your ROM in the root of the repo and rename it to `baserom.cn.z64`. Pass `VERSION=cn` to the above make commands.

## Contributing

TODO: write some contributing guidelines.

Work should be done hopefully per-file but smaller efforts are still appreciated. Just open a PR and try to address any review comments left by other contributors c:

### Important note

This matching decomp effort is being done leak-free. If you have looked/worked with leaked materials (i.e. gigaleak) then it's a shame but you can't contribute to this project.

# Dr. Mario 64

[![Build Status]][actions]
[![Code us Progress]](https://decomp.dev/AngheloAlf/drmario64/us)
[![Code cn Progress]](https://decomp.dev/AngheloAlf/drmario64/cn)
[![Code gw Progress]](https://decomp.dev/AngheloAlf/drmario64/gw)

[Build Status]: <https://github.com/AngheloAlf/drmario64/actions/workflows/ci.yml/badge.svg>
[actions]: <https://github.com/AngheloAlf/drmario64/actions/workflows/ci.yml>
[Code us Progress]: https://decomp.dev/AngheloAlf/drmario64/us.svg?mode=shield&label=us&measure=matched_code_percent
[Code cn Progress]: https://decomp.dev/AngheloAlf/drmario64/cn.svg?mode=shield&label=cn&measure=matched_code_percent
[Code gw Progress]: https://decomp.dev/AngheloAlf/drmario64/gw.svg?mode=shield&label=gw&measure=matched_code_percent

Matching decomp of Dr. Mario 64

[Progress graph :chart_with_upwards_trend:](https://decomp.dev/AngheloAlf/drmario64?mode=history)

[Legacy progress graph :chart_with_upwards_trend:](https://angheloalf.github.io/drmario64/)

## Dependencies

All the instructions assume the user is using a Debian/Ubuntu based Linux
distro. If you are a Windows user then it is recommended to use WSL2 with
Ubuntu.

### System packages

The build process has the following package requirements:

* make
* git
* build-essential
* clang
* binutils-mips-linux-gnu
* gcc-mips-linux-gnu
* uv

Under Debian / Ubuntu (which we recommend using), you can install most of them
with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential clang binutils-mips-linux-gnu gcc-mips-linux-gnu
sudo apt install make git build-essential binutils-mips-linux-gnu
```

### `uv`

We use `uv` to manage Python and its dependencies.

See the official `uv` docs to install it:
<https://docs.astral.sh/uv/getting-started/installation/>

Then run `uv sync` to install and update Python and any dependency needed.

If you need to run any Python script directly you can use either
`uv run ./script.py` or enable the venv in your shell.

## Building

Copy your big-endian Dr Mario 64 ROM into the repository's `config/us`
directory and rename it to `baserom.us.z64`. Then run the following commands to
download the appropriate compiler versions, extract ROM data using splat, and
build the files back into a rom.

You can pass `-j N`, where `N` is the number of cores your processor has (you
can know this value by using `nproc`), to speedup the build by parallelizing.

```bash
make setup
make extract
make
```

If successful, the last line of output should say:

```bash
build/us/drmario64.us.z64: OK
```

### Other versions

This repository has support for the iQue and the Gateway versions of this game.

To build any of those versions place the corresponding ROM in the `config/cn/`
or `config/gw` directories of the repo and rename the rom to either
`baserom.cn.z64` or `baserom.gw.z64`, `cn` corresponding to the iQue version,
while `gw` corresponds to the Gateway one.
Run the above `make` commands but pass either `VERSION=cn` or `VERSION=gw` to
build each version respectively.

## Contributing

TODO: write some contributing guidelines.

Smaller efforts are appreciated. Just open a PR and try to address any review comments left by other contributors c:

This repository takes some heavy inspiration from the DWARF debug information
dumped from the Gamecube release. You can access the DWARF dump in this
repository: <https://github.com/AngheloAlf/puzzle_collection_dwarf>

### Important note

This matching decomp effort is being done leak-free. If you have looked/worked with leaked materials (i.e. gigaleak) then it's a shame but you can't contribute to this project.

## License

This repository is licensed under the [MIT license](LICENSE), except for

* files which declare a different license, and
* folders that have their own `LICENSE` file.

In such cases that license takes precedence.

In particular, the `src/` folder is licensed under the [CC0 license](src/LICENSE).

### N.B.

The intention of this project is to understand the inner workings of this game better, and to make it easier to modify its behaviour.

As such, over and above the actual licensing of the repo, the decomp team requests that this codebase not be used to build binaries targeting non-MIPS machines ("porting").

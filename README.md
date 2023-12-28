# Dr. Mario 64

[![Build Status]][actions] ![Code us Progress] ![Code cn Progress] ![Code gw Progress]

[Build Status]: <https://github.com/AngheloAlf/drmario64/actions/workflows/ci.yml/badge.svg>
[actions]: <https://github.com/AngheloAlf/drmario64/actions/workflows/ci.yml>
[Code us Progress]: https://img.shields.io/endpoint?label=Code%20us&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fdrmario64%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dall
[Code cn Progress]: https://img.shields.io/endpoint?label=Code%20cn&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fdrmario64%2Fcn%2Fcode%2F%3Fmode%3Dshield%26measure%3Dall
[Code gw Progress]: https://img.shields.io/endpoint?label=Code%20gw&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fdrmario64%2Fgw%2Fcode%2F%3Fmode%3Dshield%26measure%3Dall

Matching decomp of Dr. Mario 64

[Progress graph :chart_with_upwards_trend:](https://angheloalf.github.io/drmario64/)

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
* python3
* pip3
* venv
* Rust

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential clang binutils-mips-linux-gnu gcc-mips-linux-gnu python3 python3-pip python3-venv
```

### Python dependencies

First you'll need to create a virtual environment for the python packages:

```bash
python3 -m venv .venv
```

To start using the virtual environment on your current terminal run:

```bash
source .venv/bin/activate
```

Take in mind for each new terminal you'll need to **active** the Python virtual
environment again, there's no need to create the virtual environment again.

Now you can install the Python dependencies, to do so run:

```bash
python3 -m pip install -U -r requirements.txt
```

### Rust dependencies

To install Rust run the following command and follow the on-screen instructions

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

The following Rust programs are required by the build process:

* pigment64

To install those programs run the following commands:

```bash
cargo install pigment64 --version ">=0.3.0,<1.*"
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

This repository has experimental support for the iQue and the Gateway versions of this game too.

To build any of this versions place your ROM in the root of the repo and rename it to `baserom.cn.z64` or `baserom.gw.z64`. Pass `VERSION=cn` or `VERSION=gw` to the above make commands.

## Contributing

TODO: write some contributing guidelines.

Work should be done hopefully per-file but smaller efforts are still appreciated. Just open a PR and try to address any review comments left by other contributors c:

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

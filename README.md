# drmario64

Matching decomp of Dr. Mario 64

## Dependencies

The build process has the following package requirements:

* make
* git
* build-essential
* binutils-mips-linux-gnu
* gcc-mips-linux-gnu
* python3
* pip3

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential binutils-mips-linux-gnu gcc-mips-linux-gnu python3 python3-pip
```

## Building

Copy your ROM and rename it to `baserom.z64`.

```bash
make extract
make
```

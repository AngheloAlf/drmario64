# drmario64

Matching decomp of Dr. Mario 64

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

## Building

Copy your ROM and rename it to `baserom.z64`.

```bash
make setup
make lib
make extract
make
```

## Contributing

TODO: write some contributing guidelines.

Work should be done hopefully per-file but smaller efforts are still appreciated. Just open a PR and try to address any review comments left by other contributors c:

### Important note

This matching decomp effort is being done leak-free. If you have looked/worked with leaked materials (i.e. gigaleak) then it's a shame but you can't contribute to this project.

# drmario64

Matching decomp of Dr. Mario 64

## Dependencies

The build process has the following package requirements:

* make
* git
* build-essential
* clang
* binutils-mips-linux-gnu
* python3
* pip3

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential clang binutils-mips-linux-gnu python3 python3-pip
```

This project uses [Splat](https://github.com/ethteck/splat/); to install the dependencies for it, run

```bash
pip install -r tools/splat/requirements.txt
```

Also python tooling has their own package dependencies which are listed in the `requirements.txt` file. Those can be automatically installed using `pip`:

```bash
pip3 install -r requirements.txt
```

## Building

Copy your big-endian Dr Mario 64 ROM into the repository's root directory and rename it to `baserom.z64`. Then run

```bash
make setup
make lib
make extract
make
```

to download the appropriate compiler versions, build libultra, extract data from the rom using splat, and build the files back into a rom. If successful, the last line of output should say

```
build/drmario64.z64: OK
```

## Contributing

TODO: write some contributing guidelines.

Work should be done hopefully per-file but smaller efforts are still appreciated. Just open a PR and try to address any review comments left by other contributors c:

### Important note

This matching decomp effort is being done leak-free. If you have looked/worked with leaked materials (i.e. gigaleak) then it's a shame but you can't contribute to this project.

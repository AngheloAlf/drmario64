MAKE = make

VERSION ?= us


UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := windows
	HOST_TRIPLE := x86_64-pc-windows-msvc
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
	HOST_TRIPLE := x86_64-unknown-linux-musl
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := mac
	MAKE := gmake
	CPPFLAGS += -xc++
	HOST_TRIPLE := x86_64-apple-darwin
endif


ifeq ($(DETECTED_OS),windows)
$(error This repo does not support compiling on native Windows yet, please use WSL instead.)
endif


KMC_DIR         := gcc_kmc/$(DETECTED_OS)/2.7.2
KMC_GCC         := $(KMC_DIR)/gcc
KMC_BINUTILS    := $(KMC_DIR)/as

EGCS_DIR        := gcc_egcs/$(DETECTED_OS)/1.1.2-4
EGCS_GCC        := $(EGCS_DIR)/gcc
EGCS_BINUTILS   := $(EGCS_DIR)/as

SLINKY_DIR      := slinky
SLINKY          := $(SLINKY_DIR)/slinky-cli

PIGMENT64_DIR   := pigment64
PIGMENT64       := $(PIGMENT64_DIR)/pigment64

all: $(KMC_GCC) $(KMC_BINUTILS) $(EGCS_GCC) $(EGCS_BINUTILS) $(SLINKY) $(PIGMENT64)

clean:
	$(RM) -rf $(KMC_DIR) gcc_kmc $(EGCS_DIR) gcc_egcs $(SLINKY_DIR) $(PIGMENT64_DIR)

distclean: clean

.PHONY: all clean distclean

$(KMC_GCC): | $(KMC_DIR)
	wget https://github.com/decompals/mips-gcc-2.7.2/releases/latest/download/gcc-2.7.2-$(DETECTED_OS).tar.gz
	tar xf gcc-2.7.2-$(DETECTED_OS).tar.gz -C $(KMC_DIR)
	$(RM) gcc-2.7.2-$(DETECTED_OS).tar.gz

$(KMC_BINUTILS): | $(KMC_DIR)
	wget https://github.com/decompals/mips-binutils-2.6/releases/latest/download/binutils-2.6-$(DETECTED_OS).tar.gz
	tar xf binutils-2.6-$(DETECTED_OS).tar.gz -C $(KMC_DIR)
	$(RM) binutils-2.6-$(DETECTED_OS).tar.gz

$(EGCS_GCC): | $(EGCS_DIR)
	wget https://github.com/decompals/mips-gcc-egcs-2.91.66/releases/latest/download/mips-gcc-egcs-2.91.66-$(DETECTED_OS).tar.gz
	tar xf mips-gcc-egcs-2.91.66-$(DETECTED_OS).tar.gz -C $(EGCS_DIR)
	$(RM) mips-gcc-egcs-2.91.66-$(DETECTED_OS).tar.gz

$(EGCS_BINUTILS): | $(EGCS_DIR)
	wget https://github.com/decompals/mips-binutils-egcs-2.9.5/releases/latest/download/mips-binutils-egcs-2.9.5-$(DETECTED_OS).tar.gz
	tar xf mips-binutils-egcs-2.9.5-$(DETECTED_OS).tar.gz -C $(EGCS_DIR)
	$(RM) mips-binutils-egcs-2.9.5-$(DETECTED_OS).tar.gz

$(SLINKY): | $(SLINKY_DIR)
	wget https://github.com/decompals/slinky/releases/download/0.3.0/slinky-cli-$(HOST_TRIPLE).tar.gz
	tar xf slinky-cli-$(HOST_TRIPLE).tar.gz -C $(SLINKY_DIR)
	$(RM) slinky-cli-$(HOST_TRIPLE).tar.gz

$(PIGMENT64): | $(PIGMENT64_DIR)
	wget https://github.com/decompals/pigment64/releases/download/0.6.3/pigment64-$(HOST_TRIPLE).tar.gz
	tar xf pigment64-$(HOST_TRIPLE).tar.gz -C $(PIGMENT64_DIR)
	$(RM) pigment64-$(HOST_TRIPLE).tar.gz

$(KMC_DIR) $(EGCS_DIR) $(SLINKY_DIR) $(PIGMENT64_DIR):
	mkdir -p $@

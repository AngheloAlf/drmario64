MAKE = make

VERSION ?= us


UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := windows
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := macos
	MAKE := gmake
	CPPFLAGS += -xc++
endif


ifeq ($(DETECTED_OS),windows)
$(error This repo does not support compiling on native Windows yet, please use WSL instead.)
endif


KMC_DIR         := gcc_kmc/$(DETECTED_OS)/2.7.2
GCC-2.7.2       := $(KMC_DIR)/gcc
BINUTILS-2.6    := $(KMC_DIR)/as

EGCS_DIR        := gcc_egcs/$(DETECTED_OS)/1.1.2-4
GCC_EGCS        := $(EGCS_DIR)/mips-linux-gcc


all: $(GCC-2.7.2) $(BINUTILS-2.6) $(GCC_EGCS)

clean:
	$(RM) -rf $(KMC_DIR) gcc_kmc $(EGCS_DIR) gcc_egcs

distclean: clean

.PHONY: all clean distclean

$(GCC-2.7.2): | $(KMC_DIR)
	wget https://github.com/decompals/mips-gcc-2.7.2/releases/download/main/gcc-2.7.2-$(DETECTED_OS).tar.gz
	tar xf gcc-2.7.2-$(DETECTED_OS).tar.gz -C $(KMC_DIR)
	$(RM) gcc-2.7.2-$(DETECTED_OS).tar.gz

$(BINUTILS-2.6): | $(KMC_DIR)
	wget https://github.com/decompals/mips-binutils-2.6/releases/download/main/binutils-2.6-$(DETECTED_OS).tar.gz
	tar xf binutils-2.6-$(DETECTED_OS).tar.gz -C $(KMC_DIR)
	$(RM) binutils-2.6-$(DETECTED_OS).tar.gz

$(GCC_EGCS): | $(EGCS_DIR)
	wget https://github.com/AngheloAlf/egcs_1.1.2-4/releases/download/latest/egcs_1.1.2-4.tar.gz
	tar xf egcs_1.1.2-4.tar.gz -C $(EGCS_DIR)
	$(RM) egcs_1.1.2-4.tar.gz

$(KMC_DIR):
	mkdir -p $@

$(EGCS_DIR):
	mkdir -p $@

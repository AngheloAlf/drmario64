MAKE = make

VERSION ?= us


UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := windows
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := mac
	MAKE := gmake
	CPPFLAGS += -xc++
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


all: $(KMC_GCC) $(KMC_BINUTILS) $(EGCS_GCC) $(EGCS_BINUTILS)

clean:
	$(RM) -rf $(KMC_DIR) gcc_kmc $(EGCS_DIR) gcc_egcs

distclean: clean

.PHONY: all clean distclean

$(KMC_GCC): | $(KMC_DIR)
	wget https://github.com/decompals/mips-gcc-2.7.2/releases/download/main/gcc-2.7.2-$(DETECTED_OS).tar.gz
	tar xf gcc-2.7.2-$(DETECTED_OS).tar.gz -C $(KMC_DIR)
	$(RM) gcc-2.7.2-$(DETECTED_OS).tar.gz

$(KMC_BINUTILS): | $(KMC_DIR)
	wget https://github.com/decompals/mips-binutils-2.6/releases/download/main/binutils-2.6-$(DETECTED_OS).tar.gz
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

$(KMC_DIR):
	mkdir -p $@

$(EGCS_DIR):
	mkdir -p $@

MAKE = make

ifeq ($(OS),Windows_NT)
	DETECTED_OS=windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		DETECTED_OS=linux
	endif
	ifeq ($(UNAME_S),Darwin)
		DETECTED_OS=macos
		MAKE=gmake
		CPPFLAGS += -xc++
	endif
endif

ifeq ($(DETECTED_OS),windows)
	$(error This repo does not support compiling on native Windows yet, please use WSL instead.)
endif

COMPILER_DIR    := gcc_kmc/$(DETECTED_OS)/2.7.2
GCC-2.7.2       := $(COMPILER_DIR)/gcc
BINUTILS-2.6    := $(COMPILER_DIR)/as

all: $(GCC-2.7.2) $(BINUTILS-2.6)

clean:
	$(RM) -rf $(COMPILER_DIR) gcc_kmc

distclean: clean

.PHONY: all clean distclean

$(GCC-2.7.2): | $(COMPILER_DIR)
	wget https://github.com/decompals/mips-gcc-2.7.2/releases/download/main/gcc-2.7.2-$(DETECTED_OS).tar.gz
	tar xf gcc-2.7.2-$(DETECTED_OS).tar.gz -C $(COMPILER_DIR)
	$(RM) gcc-2.7.2-$(DETECTED_OS).tar.gz

$(BINUTILS-2.6): | $(COMPILER_DIR)
	wget https://github.com/decompals/mips-binutils-2.6/releases/download/main/binutils-2.6-$(DETECTED_OS).tar.gz
	tar xf binutils-2.6-$(DETECTED_OS).tar.gz -C $(COMPILER_DIR)
	$(RM) binutils-2.6-$(DETECTED_OS).tar.gz

$(COMPILER_DIR):
	mkdir -p $@

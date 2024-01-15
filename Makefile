# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules

SHELL = /bin/bash
.SHELLFLAGS = -o pipefail -c

#### Defaults ####

# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Disassembles all asm from the ROM instead of skipping files which are entirely in C
FULL_DISASM ?= 0
# Check code syntax with host compiler
RUN_CC_CHECK ?= 1
CC_CHECK_COMP ?= clang
# Dump build object files
OBJDUMP_BUILD ?= 1
# 
MULTISTEP_BUILD ?= 0
# If non-zero, passes -v to compiler
COMPILER_VERBOSE ?= 0
# If non-zero touching an assembly file will rebuild any file that depends on it
DEP_ASM ?= 1
# If non-zero touching an included file will rebuild any file that depends on it
DEP_INCLUDE ?= 1

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-


VERSION ?= us

BASEROM              := baserom.$(VERSION).z64
BASEROM_UNCOMPRESSED := baserom_uncompressed.$(VERSION).z64
TARGET               := drmario64


### Output ###

BUILD_DIR := build
ROM       := $(BUILD_DIR)/$(TARGET)_uncompressed.$(VERSION).z64
ELF       := $(BUILD_DIR)/$(TARGET).$(VERSION).elf
LD_MAP    := $(BUILD_DIR)/$(TARGET).$(VERSION).map
LD_SCRIPT := linker_scripts/$(VERSION)/$(TARGET).ld
ROMC      := $(BUILD_DIR)/$(TARGET).$(VERSION).z64


#### Setup ####

BUILD_DEFINES ?=

ifeq ($(VERSION),us)
	BUILD_DEFINES   += -DVERSION_US=1
else ifeq ($(VERSION),cn)
	BUILD_DEFINES   += -DVERSION_CN=1 -DBBPLAYER=1
else ifeq ($(VERSION),gw)
	BUILD_DEFINES   += -DVERSION_GW=1
else
$(error Invalid VERSION variable detected. Please use either 'us', 'cn' or 'gw')
endif

ifeq ($(NON_MATCHING),1)
	BUILD_DEFINES   += -DNON_MATCHING -DAVOID_UB
	COMPARE  := 0
endif

MAKE = make
CPPFLAGS += -fno-dollars-in-identifiers -P
LDFLAGS  := --no-check-sections --emit-relocs

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

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Please install or build $(MIPS_BINUTILS_PREFIX))
endif

ifeq ($(VERSION),$(filter $(VERSION), us gw))
COMPILER_DIR    := tools/gcc_kmc/$(DETECTED_OS)/2.7.2
else ifeq ($(VERSION),cn)
COMPILER_DIR    := tools/gcc_egcs/$(DETECTED_OS)/1.1.2-4
endif
CC              := COMPILER_PATH=$(COMPILER_DIR) $(COMPILER_DIR)/gcc

AS              := $(MIPS_BINUTILS_PREFIX)as
LD              := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY         := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP         := $(MIPS_BINUTILS_PREFIX)objdump
GCC             := $(MIPS_BINUTILS_PREFIX)gcc
CPP             := $(MIPS_BINUTILS_PREFIX)cpp
STRIP           := $(MIPS_BINUTILS_PREFIX)strip
ICONV           := iconv

SPLAT             ?= python3 -m splat split
SPLAT_YAML        ?= $(TARGET).$(VERSION).yaml

SPLAT_FLAGS       ?=
ifneq ($(FULL_DISASM),0)
    SPLAT_FLAGS       += --disassemble-all
endif

ROM_COMPRESSOR    ?= tools/compressor/rom_compressor.py
ROM_DECOMPRESSOR  ?= tools/compressor/rom_decompressor.py
SEGMENT_EXTRACTOR ?= tools/compressor/extract_compressed_segments.py
CHECKSUMMER       ?= tools/checksummer.py
MSG_REENCODER     ?= tools/buildtools/msg_reencoder.py
PIGMENT64         ?= pigment64

export SPIMDISASM_PANIC_RANGE_CHECK="True"


IINC       := -Iinclude -Ibin/$(VERSION) -I$(BUILD_DIR)/bin/$(VERSION) -I.
IINC       += -Ilib/ultralib/include -Ilib/ultralib/include/PR -Ilib/libmus/include

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wimplicit-fallthrough -Wno-unknown-pragmas -Wno-missing-braces -Wno-sign-compare -Wno-uninitialized -Wno-char-subscripts -Wno-pointer-sign -Wno-invalid-source-encoding

# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
ifneq ($(RUN_CC_CHECK),0)
#	The -MMD flags additionaly creates a .d file with the same name as the .o file.
	CC_CHECK          := $(CC_CHECK_COMP)
	CC_CHECK_FLAGS    := -MMD -MP -fno-builtin -funsigned-char -fsyntax-only -fdiagnostics-color -std=gnu89 -m32 -DNON_MATCHING -DAVOID_UB -DCC_CHECK=1
	ifneq ($(WERROR), 0)
		CHECK_WARNINGS += -Werror
	endif
else
	CC_CHECK          := @:
endif

CFLAGS          += -nostdinc -fno-PIC -G 0 -mgp32 -mfp32 -fno-common

WARNINGS        := -w
ASFLAGS         := -march=vr4300 -mabi=32 -G0 -no-pad-sections
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM
AS_DEFINES      := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
C_DEFINES       := -D_LANGUAGE_C
ENDIAN          := -EB

ifeq ($(VERSION),$(filter $(VERSION), us gw))
OPTFLAGS        := -O2
DBGFLAGS        :=
# DBGFLAGS        := -gdwarf
MIPS_VERSION    := -mips3
OUT_ENCODING    := Shift-JIS
CHAR_SIGN       := -funsigned-char
# libultra 2.0K
LIBULTRA_VERSION:= 8
else ifeq ($(VERSION),cn)
CFLAGS          += -mcpu=4300
OPTFLAGS        := -O2
DBGFLAGS        := -ggdb
MIPS_VERSION    := -mips2
OUT_ENCODING    := EUC-CN
CHAR_SIGN       := -fsigned-char
# libultra 2.0L
LIBULTRA_VERSION:= 9
endif

BUILD_DEFINES   += -DBUILD_VERSION=$(LIBULTRA_VERSION)

# Variable to simplify C compiler invocation
C_COMPILER_FLAGS = $(CFLAGS) $(CHAR_SIGN) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS) $(DBGFLAGS)

ICONV_FLAGS      = --from-code=UTF-8 --to-code=$(OUT_ENCODING)

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32 -Mno-aliases

ifneq ($(OBJDUMP_BUILD), 0)
	OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)
else
	OBJDUMP_CMD = @:
endif

ifneq ($(COMPILER_VERBOSE), 0)
	COMP_VERBOSE_FLAG := -v
else
	COMP_VERBOSE_FLAG :=
endif


#### Files ####

$(shell mkdir -p asm bin linker_scripts/$(VERSION)/auto)

SRC_DIRS      := $(shell find src -type d)
ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*" -not -path "asm/$(VERSION)/lib/*")
BIN_DIRS      := $(shell find bin/$(VERSION) -type d)

LIBULTRA_DIRS := $(shell find lib/ultralib/src -type d -not -path "lib/ultralib/src/voice")
LIBMUS_DIRS   := $(shell find lib/libmus/src -type d)

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
PNG_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.png))
TEXT_FILES    := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.msg))

O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f)

PNG_INC_FILES := $(foreach f,$(PNG_FILES:.png=.inc),$(BUILD_DIR)/$f)
TEXT_INC_FILES := $(foreach f,$(TEXT_FILES:.msg=.msg.inc),$(BUILD_DIR)/$f)

SEGMENTS_SCRIPTS := $(wildcard linker_scripts/$(VERSION)/partial/*.ld)
SEGMENTS_D       := $(SEGMENTS_SCRIPTS:.ld=.d)
SEGMENTS         := $(foreach f, $(SEGMENTS_SCRIPTS:.ld=), $(notdir $f))
SEGMENTS_O       := $(foreach f, $(SEGMENTS), $(BUILD_DIR)/segments/$(VERSION)/$f.o)

LINKER_SCRIPTS   := $(LD_SCRIPT) $(BUILD_DIR)/linker_scripts/$(VERSION)/hardware_regs.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/undefined_syms.ld $(BUILD_DIR)/linker_scripts/common_undef_syms.ld


# Automatic dependency files
DEP_FILES := $(LD_SCRIPT:.ld=.d) $(SEGMENTS_D)

ifneq ($(DEP_ASM), 0)
	DEP_FILES += $(O_FILES:.o=.asmproc.d)
endif

ifneq ($(DEP_INCLUDE), 0)
	DEP_FILES += $(O_FILES:.o=.d)
endif

# create build directories
$(shell mkdir -p $(BUILD_DIR)/linker_scripts/$(VERSION) $(BUILD_DIR)/linker_scripts/$(VERSION)/auto $(BUILD_DIR)/segments/$(VERSION))
$(shell mkdir -p $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS) $(LIBULTRA_DIRS) $(LIBMUS_DIRS),$(BUILD_DIR)/$(dir)))

# directory flags
$(BUILD_DIR)/src/libkmc/%.o:   OPTFLAGS := -O1
$(BUILD_DIR)/src/libnustd/%.o: OPTFLAGS := -O1

# per-file flags

$(BUILD_DIR)/asm/cn/data/main_segment/debug_menu.rodata.o: OUT_ENCODING := Shift-JIS
$(BUILD_DIR)/src/main_segment/debug_menu.o:                OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/asm/cn/data/main_segment/msgwnd.rodata.o: OUT_ENCODING := Shift-JIS
$(BUILD_DIR)/src/main_segment/msgwnd.o:                OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/src/main_segment/record.o:                OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/src/main_segment/main_menu.o:             OUT_ENCODING := Shift-JIS

#### Main Targets ###

all: compressed

uncompressed: $(ROM)
ifneq ($(COMPARE),0)
	@md5sum $(ROM)
	@md5sum -c $(TARGET)_uncompressed.$(VERSION).md5
endif

compressed: $(ROMC)
ifneq ($(COMPARE),0)
	@md5sum $(ROMC)
	@md5sum -c $(TARGET).$(VERSION).md5
endif

clean:
	$(RM) -r $(BUILD_DIR)/asm $(BUILD_DIR)/bin $(BUILD_DIR)/src $(ROM) $(ROMC) $(ELF)

libclean:
	$(RM) -r $(BUILD_DIR)/lib

distclean: clean
	$(RM) -r $(BUILD_DIR) asm/ bin/ .splat/
	$(RM) -r linker_scripts/$(VERSION)/auto $(LD_SCRIPT)
	$(MAKE) -C tools distclean

setup:
	$(ROM_DECOMPRESSOR) $(BASEROM) $(BASEROM_UNCOMPRESSED) tools/compressor/compress_segments.$(VERSION).csv $(VERSION)
	$(MAKE) -C tools

extract:
	$(RM) -r asm/$(VERSION) bin/$(VERSION) linker_scripts/$(VERSION)/partial $(LD_SCRIPT) $(LD_SCRIPT:.ld=.d)
	$(SPLAT) $(SPLAT_FLAGS) $(SPLAT_YAML)
	$(SEGMENT_EXTRACTOR) $(BASEROM) tools/compressor/compress_segments.$(VERSION).csv $(VERSION)

lib:
	$(MAKE) -C lib VERSION=$(VERSION)

diff-init: all
	$(RM) -rf expected/
	mkdir -p expected/
	cp -r $(BUILD_DIR) expected/$(BUILD_DIR)

init:
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) extract
	$(MAKE) lib
	$(MAKE) all
	$(MAKE) diff-init

format:
	clang-format-11 -i -style=file $(C_FILES)

tidy:
	clang-tidy-11 -p . --fix --fix-errors $(filter-out %libgcc2.c, $(C_FILES)) -- $(CC_CHECK_FLAGS) $(IINC) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS)

.PHONY: all compressed uncompressed clean distclean setup extract lib diff-init init format tidy
.DEFAULT_GOAL := all
# Prevent removing intermediate files
.SECONDARY:


#### Various Recipes ####

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $(@:.z64=.bin)
	$(CHECKSUMMER) $(@:.z64=.bin) $@

$(ROMC): $(ROM) tools/compressor/compress_segments.$(VERSION).csv
	$(ROM_COMPRESSOR) $(ROM) $(ROMC:.z64=.bin) $(ELF) tools/compressor/compress_segments.$(VERSION).csv $(VERSION)
	$(CHECKSUMMER) $(ROMC:.z64=.bin) $@

$(ELF): $(LINKER_SCRIPTS)
	$(LD) $(ENDIAN) $(LDFLAGS) -Map $(LD_MAP) $(foreach ld, $(LINKER_SCRIPTS), -T $(ld)) -o $@ $(filter %.o, $^)

## Order-only prerequisites
# These ensure e.g. the PNG_INC_FILES are built before the O_FILES.
# The intermediate phony targets avoid quadratically-many dependencies between the targets and prerequisites.

asset_files: $(PNG_INC_FILES)
$(O_FILES): | asset_files
text_files: $(TEXT_INC_FILES)
$(O_FILES): | text_files
o_files: $(O_FILES)
$(SEGMENTS_O): | o_files

asset_files_clean:
	$(RM) -r $(TEXT_INC_FILES)
text_files_clean:
	$(RM) -r $(TEXT_INC_FILES)

.PHONY: asset_files asset_files_clean text_files text_files_clean o_files

$(BUILD_DIR)/%.ld: %.ld
	$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) $(COMP_VERBOSE_FLAG) $< > $@

$(BUILD_DIR)/%.o: %.s
	$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) -I $(dir $*) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $(COMP_VERBOSE_FLAG) $< | $(ICONV) $(ICONV_FLAGS) | $(AS) $(ASFLAGS) $(ENDIAN) $(IINC) -I $(dir $*) $(COMP_VERBOSE_FLAG) -o $@
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
ifeq ($(MULTISTEP_BUILD), 0)
	$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) $(COMP_VERBOSE_FLAG) -E $< | $(ICONV) $(ICONV_FLAGS) | $(CC) -x c $(C_COMPILER_FLAGS) -I $(dir $*) $(COMP_VERBOSE_FLAG) -c -o $@ -
else
	$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) $(COMP_VERBOSE_FLAG) -E $< | $(ICONV) $(ICONV_FLAGS) -o $(@:.o=.i)
	$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) $(COMP_VERBOSE_FLAG) -S -o $(@:.o=.s) $(@:.o=.i)
	$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) $(COMP_VERBOSE_FLAG) -c -o $@ $(@:.o=.s)
endif
	$(OBJDUMP_CMD)

$(BUILD_DIR)/lib/%.o: lib/%.c
ifneq ($(PERMUTER), 1)
	$(error Library files has not been built, please run `$(MAKE) lib VERSION=$(VERSION)` first)
endif
	$(MAKE) -C lib VERSION=$(VERSION) ../$@

$(BUILD_DIR)/segments/$(VERSION)/%.o: linker_scripts/$(VERSION)/partial/%.ld
	$(LD) $(LDFLAGS) --relocatable -T $< -Map $(@:.o=.map) -o $@

# Make inc files from assets

build/%.inc: %.png
	$(PIGMENT64) to-bin --c-array --format $(subst .,,$(suffix $*)) -o $@ $<

build/%.msg.inc: %.msg
	$(CC) -x c $(C_COMPILER_FLAGS) -I $(dir $*) $(COMP_VERBOSE_FLAG) -E $< -o $(@:.inc=.i)
	$(MSG_REENCODER) $(@:.inc=.i) $@ $(OUT_ENCODING)

-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

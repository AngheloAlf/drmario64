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
# Use LLVM linker lld instead of GNU LD
USE_LLD ?= 0
# If non zero then compilation commands won't be printed to the terminal
QUIET ?= 0
# If non-zero, partially links each segment, making the first build slower but improving build times afterwards
PARTIAL_LINKING ?= 0
# TODO. Options: original, gcc
COMPILER ?= original

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
CROSS ?= mips-linux-gnu-


VERSION ?= us

BASEROM              := config/$(VERSION)/baserom.$(VERSION).z64
BASEROM_UNCOMPRESSED := config/$(VERSION)/baserom_uncompressed.$(VERSION).z64
TARGET               := drmario64


### Output ###

BUILD_DIR := build/$(VERSION)
ROM       := $(BUILD_DIR)/$(TARGET)_uncompressed.$(VERSION).z64
ELF       := $(BUILD_DIR)/$(TARGET).$(VERSION).elf
LD_MAP    := $(BUILD_DIR)/$(TARGET).$(VERSION).map
LD_SCRIPT := $(BUILD_DIR)/$(TARGET).$(VERSION).ld
D_FILE    := $(BUILD_DIR)/$(TARGET).$(VERSION).d
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

ifeq ($(COMPILER), original)
# Empty on purpose
else ifeq ($(COMPILER), gcc)
    COMPARE       := 0
    RUN_CC_CHECK  := 0
    BUILD_DEFINES += -DMODERN_GCC=1 -DPRESERVE_UB
else
$(error Invalid COMPILER variable detected. Please use either 'original', 'gcc')
endif

ifeq ($(NON_MATCHING),1)
    BUILD_DEFINES   += -DNON_MATCHING -DPRESERVE_UB
    COMPARE  := 0
endif

MAKE = make
CPPFLAGS += -fno-dollars-in-identifiers -P

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

ifneq ($(QUIET), 0)
    QUIET_CMD := @
else
    QUIET_CMD :=
endif

#### Tools ####
ifneq ($(shell type $(CROSS)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Please install or build $(CROSS))
endif

AS              := $(CROSS)as
GNULD           := $(CROSS)ld
OBJCOPY         := $(CROSS)objcopy
OBJDUMP         := $(CROSS)objdump
GCC             := $(CROSS)gcc
CPP             := $(CROSS)cpp
STRIP           := $(CROSS)strip
ICONV           := iconv

ifeq ($(COMPILER), original)
    ifeq ($(VERSION),$(filter $(VERSION), us gw))
    COMPILER_DIR    := tools/gcc_kmc/$(DETECTED_OS)/2.7.2
    else ifeq ($(VERSION),cn)
    COMPILER_DIR    := tools/gcc_egcs/$(DETECTED_OS)/1.1.2-4
    endif

    CC              := COMPILER_PATH=$(COMPILER_DIR) $(COMPILER_DIR)/gcc
else ifeq ($(COMPILER), gcc)
    CC              := $(GCC)
endif

ifneq ($(USE_LLD),0)
    LD              := ld.lld
else
    LD              := $(GNULD)
endif

SPLAT             ?= python3 -m splat split
SPLAT_YAML        ?= config/$(VERSION)/$(TARGET).$(VERSION).yaml

SPLAT_FLAGS       ?=
ifneq ($(FULL_DISASM),0)
    SPLAT_FLAGS       += --disassemble-all
endif

SLINKY            ?= tools/slinky/slinky-cli
SLINKY_YAML       ?= config/slinky.yaml

SLINKY_FLAGS      ?=
ifneq ($(PARTIAL_LINKING),0)
    SLINKY_FLAGS    += --partial-linking
endif

ROM_COMPRESSOR    ?= tools/compressor/rom_compressor.py
ROM_DECOMPRESSOR  ?= tools/compressor/rom_decompressor.py
SEGMENT_EXTRACTOR ?= tools/compressor/extract_compressed_segments.py
CHECKSUMMER       ?= tools/checksummer.py
MSG_REENCODER     ?= tools/buildtools/msg_reencoder.py
INC_FROM_BIN      ?= tools/buildtools/inc_from_bin.py
PIGMENT64         ?= pigment64

export SPIMDISASM_PANIC_RANGE_CHECK="True"


IINC       += -Ilib/ultralib/include -Ilib/ultralib/include/PR -Ilib/libmus/include -Ilib/ultralib/include/gcc
IINC       += -Iinclude -Ibin/$(VERSION) -I$(BUILD_DIR)/bin/$(VERSION) -I $(BUILD_DIR) -I.

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wimplicit-fallthrough -Wno-unknown-pragmas -Wno-sign-compare -Wno-uninitialized -Wno-char-subscripts -Wno-pointer-sign
ifeq ($(COMPILER), original)
    CHECK_WARNINGS += -Wno-invalid-source-encoding
else
    CHECK_WARNINGS += -Wno-builtin-declaration-mismatch
endif

ifneq ($(WERROR), 0)
    CHECK_WARNINGS += -Werror
endif

# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
ifneq ($(RUN_CC_CHECK),0)
#   The -MMD flags additionaly creates a .d file with the same name as the .o file.
    CC_CHECK          := $(CC_CHECK_COMP)
    CC_CHECK_FLAGS    := -MMD -MP -fno-builtin -funsigned-char -fsyntax-only -fdiagnostics-color -std=gnu89 -m32 -DNON_MATCHING -DPRESERVE_UB -DCC_CHECK=1
else
    CC_CHECK          := @:
endif

ABIFLAG         ?= -mabi=32 -mgp32 -mfp32
CFLAGS          += -nostdinc -fno-PIC -G 0
CFLAGS_EXTRA    ?=

WARNINGS        := -w
ASFLAGS         := -march=vr4300 -mabi=32 -G0 -no-pad-sections
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM
AS_DEFINES      := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
C_DEFINES       := -D_LANGUAGE_C
ENDIAN          := -EB
LDFLAGS         := --emit-relocs

ifeq ($(VERSION),$(filter $(VERSION), us gw))
CFLAGS_EXTRA    += -Wa,--force-n64align
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

ifeq ($(COMPILER), gcc)
# OPTFLAGS        := -Os -ffast-math -fno-unsafe-math-optimizations
OPTFLAGS        := -O1
DBGFLAGS        := -ggdb
MIPS_VERSION    := -mips3
WARNINGS        := $(CHECK_WARNINGS)

CFLAGS          += -march=vr4300 -mfix4300 -mno-abicalls
CFLAGS          += -mdivide-breaks -ffreestanding
CFLAGS          += -fno-toplevel-reorder
# Consider removing in the future
CFLAGS          += -fno-zero-initialized-in-bss
# LDFLAGS         += -lgcc_vr4300
CFLAGS_EXTRA    :=
endif

BUILD_DEFINES   += -DBUILD_VERSION=$(LIBULTRA_VERSION)

# Variable to simplify C compiler invocation
C_COMPILER_FLAGS = $(ABIFLAG) $(CFLAGS) $(CFLAGS_EXTRA) $(CHAR_SIGN) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS) $(DBGFLAGS)

ICONV_FLAGS      = --from-code=UTF-8 --to-code=$(OUT_ENCODING)

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32

ifneq ($(OBJDUMP_BUILD), 0)
    OBJDUMP_CMD = @$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)
else
    OBJDUMP_CMD = @:
endif

ifneq ($(COMPILER_VERBOSE), 0)
    COMP_VERBOSE_FLAG := -v
else
    COMP_VERBOSE_FLAG :=
endif


#### Files ####

$(shell mkdir -p asm bin)

SRC_DIRS      := $(shell find src -type d)
ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*" -not -path "asm/$(VERSION)/lib/*")
BIN_DIRS      := $(shell find bin/$(VERSION) -type d)

LIBULTRA_DIRS := $(shell find lib/ultralib/src -type d -not -path "lib/ultralib/src/voice")
LIBMUS_DIRS   := $(shell find lib/libmus/src -type d)

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
PNG_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.png))
MSG_FILES     := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.msg))

O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f)

PNG_INC_FILES := $(foreach f,$(PNG_FILES:.png=.inc),$(BUILD_DIR)/$f)
MSG_INC_FILES := $(foreach f,$(MSG_FILES:.msg=.msg.inc),$(BUILD_DIR)/$f)

SEGMENTS_SCRIPTS := $(wildcard $(BUILD_DIR)/linker_scripts/partial/*.ld)
SEGMENTS_D       := $(SEGMENTS_SCRIPTS:.ld=.d)
SEGMENTS         := $(foreach f, $(SEGMENTS_SCRIPTS:.ld=), $(notdir $f))
SEGMENTS_O       := $(foreach f, $(SEGMENTS), $(BUILD_DIR)/segments/$f.o)

LINKER_SCRIPTS   := $(LD_SCRIPT)


# Automatic dependency files
DEP_FILES := $(D_FILE) $(SEGMENTS_D)

ifneq ($(DEP_ASM), 0)
    DEP_FILES += $(O_FILES:.o=.asmproc.d)
endif

ifneq ($(DEP_INCLUDE), 0)
    DEP_FILES += $(O_FILES:.o=.d)
endif

# create build directories
$(shell mkdir -p $(BUILD_DIR)/linker_scripts/$(VERSION) $(BUILD_DIR)/segments)
$(shell mkdir -p $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS) $(LIBULTRA_DIRS) $(LIBMUS_DIRS),$(BUILD_DIR)/$(dir)))

# directory flags

ifeq ($(COMPILER), original)
$(BUILD_DIR)/src/libkmc/%.o:   OPTFLAGS := -O1
$(BUILD_DIR)/src/libnustd/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/buffers/%.o:  CFLAGS   += -fno-common
else ifeq ($(COMPILER), gcc)
$(BUILD_DIR)/src/libkmc/%.o:   OPTFLAGS := -Ofast
$(BUILD_DIR)/src/libnustd/%.o: OPTFLAGS := -Ofast
endif

$(BUILD_DIR)/src/assets/%.o:   CC       := $(GCC)
$(BUILD_DIR)/src/assets/%.o:   CFLAGS   := -G 0 -nostdinc -march=vr4300 -mfix4300 -mabi=32 -mno-abicalls -mdivide-breaks -fno-PIC -fno-common -fno-zero-initialized-in-bss -fno-toplevel-reorder
$(BUILD_DIR)/src/assets/%.o:   MIPS_VERSION:= -mips3
$(BUILD_DIR)/src/assets/%.o:   CFLAGS_EXTRA:= -Wa,-no-pad-sections
$(BUILD_DIR)/src/assets/%.o:   OPTFLAGS := -O0
$(BUILD_DIR)/src/assets/%.o:   DBGFLAGS := -ggdb


# per-file flags

$(BUILD_DIR)/asm/cn/data/main_segment/debug_menu.rodata.o: 		OUT_ENCODING := Shift-JIS
$(BUILD_DIR)/src/main_segment/debug_menu.o:                		OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/asm/cn/data/main_segment/msgwnd.rodata.o:     		OUT_ENCODING := Shift-JIS
$(BUILD_DIR)/src/main_segment/msgwnd.o:                    		OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/src/main_segment/record.o:                    		OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/src/main_segment/main_menu.o:                    	OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/asm/$(VERSION)/data/main_segment/066580.data.o:    OUT_ENCODING := Shift-JIS
$(BUILD_DIR)/src/main_segment/066580.o:                         OUT_ENCODING := Shift-JIS

$(BUILD_DIR)/src/main_segment/main_story.o:                     OUT_ENCODING := Shift-JIS

#### Main Targets ###

all: compressed

uncompressed: $(ROM)
ifneq ($(COMPARE),0)
	@md5sum $(ROM)
	@md5sum -c config/$(VERSION)/$(TARGET)_uncompressed.$(VERSION).md5
endif

compressed: $(ROMC)
ifneq ($(COMPARE),0)
	@md5sum $(ROMC)
	@md5sum -c config/$(VERSION)/$(TARGET).$(VERSION).md5
endif

clean:
	$(RM) -r $(BUILD_DIR)/asm $(BUILD_DIR)/bin $(BUILD_DIR)/src $(ROM) $(ROMC) $(ELF)

libclean:
	$(RM) -r $(BUILD_DIR)/lib

distclean: clean
	$(RM) -r $(BUILD_DIR) asm/ bin/ .splat/
	$(MAKE) -C tools distclean

setup:
	$(ROM_DECOMPRESSOR) $(BASEROM) $(BASEROM_UNCOMPRESSED) tools/compressor/compress_segments.$(VERSION).csv $(VERSION)
	$(MAKE) -C tools
	$(MAKE) $(LD_SCRIPT)

extract:
	$(RM) -r asm/$(VERSION) bin/$(VERSION)
	$(SPLAT) $(SPLAT_YAML) $(SPLAT_FLAGS)
	$(SEGMENT_EXTRACTOR) $(BASEROM) tools/compressor/compress_segments.$(VERSION).csv $(VERSION)

diff-init: all
	$(RM) -rf expected/$(BUILD_DIR)
	mkdir -p expected/$(BUILD_DIR)
	cp -r $(BUILD_DIR)/* expected/$(BUILD_DIR)

init:
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) extract
	$(MAKE) all
	$(MAKE) diff-init

format:
	clang-format-11 -i -style=file $(C_FILES)

tidy:
	clang-tidy-11 -p . --fix --fix-errors $(filter-out %libgcc2.c, $(C_FILES)) -- $(CC_CHECK_FLAGS) $(IINC) -I build/$(VERSION)/src/main_segment $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS)

.PHONY: all compressed uncompressed clean distclean setup extract diff-init init format tidy
.DEFAULT_GOAL := all
# Prevent removing intermediate files
.SECONDARY:


#### Various Recipes ####

$(ROM): $(ELF)
	$(QUIET_CMD)$(OBJCOPY) -O binary $< $(@:.z64=.bin)
	$(QUIET_CMD)$(CHECKSUMMER) $(@:.z64=.bin) $@

$(ROMC): $(ROM) tools/compressor/compress_segments.$(VERSION).csv
	$(QUIET_CMD)$(ROM_COMPRESSOR) $(ROM) $(ROMC:.z64=.bin) $(ELF) tools/compressor/compress_segments.$(VERSION).csv $(VERSION)
	$(QUIET_CMD)$(CHECKSUMMER) $(ROMC:.z64=.bin) $@

$(ELF): $(LINKER_SCRIPTS)
	$(file >$(@:.elf=.o_files.txt), $(filter %.o, $^))
	$(QUIET_CMD)$(LD) $(ENDIAN) $(LDFLAGS) -Map $(LD_MAP) $(foreach ld, $(LINKER_SCRIPTS), -T $(ld)) -o $@ @$(@:.elf=.o_files.txt)

## Order-only prerequisites
# These ensure e.g. the PNG_INC_FILES are built before the O_FILES.
# The intermediate phony targets avoid quadratically-many dependencies between the targets and prerequisites.

asset_files: $(PNG_INC_FILES)
$(O_FILES): | asset_files
msg_files: $(MSG_INC_FILES)
$(O_FILES): | msg_files

asset_files_clean:
	$(RM) -r $(PNG_INC_FILES)
msg_files_clean:
	$(RM) -r $(MSG_INC_FILES)

.PHONY: asset_files asset_files_clean msg_files msg_files_clean o_files

# The main .d file is a subproduct of generating the main linker script.
# We have list both the .ld and the .d files in this rule so Make can
# automatically regenerate the dependencies file if we have touched the slinky
# yaml (via the `-include` statement), so we always only build the .c/.s files
# listed on the yaml.
$(LD_SCRIPT) $(D_FILE): $(SLINKY_YAML) $(SLINKY)
	$(SLINKY) --custom-options version=$(VERSION) $(SLINKY_FLAGS) -o $(LD_SCRIPT) $(SLINKY_YAML)

$(BUILD_DIR)/%.ld: %.ld
	$(QUIET_CMD)$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) $(COMP_VERBOSE_FLAG) $< > $@

$(BUILD_DIR)/%.o: %.s
	$(QUIET_CMD)$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $(COMP_VERBOSE_FLAG) $< | $(ICONV) $(ICONV_FLAGS) | $(AS) $(ASFLAGS) $(ENDIAN) $(IINC) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -o $@
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(QUIET_CMD)$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
ifeq ($(MULTISTEP_BUILD), 0)
	$(QUIET_CMD)$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -E $< | $(ICONV) $(ICONV_FLAGS) | $(CC) -x c $(C_COMPILER_FLAGS) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -c -o $@ -
else
	$(QUIET_CMD)$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -E $< | $(ICONV) $(ICONV_FLAGS) -o $(@:.o=.i)
	$(QUIET_CMD)$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -S -o $(@:.o=.s) $(@:.o=.i)
	$(QUIET_CMD)$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -c -o $@ $(@:.o=.s)
endif
	$(OBJDUMP_CMD)

$(BUILD_DIR)/lib/%.o: lib/%.c
	$(QUIET_CMD)$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) -w $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(QUIET_CMD)$(MAKE) -C lib VERSION=$(VERSION) CROSS=$(CROSS) QUIET=$(QUIET) COMPILER=$(COMPILER) ../$@

$(BUILD_DIR)/lib/%.o: lib/%.s
	$(QUIET_CMD)$(MAKE) -C lib VERSION=$(VERSION) CROSS=$(CROSS) QUIET=$(QUIET) ../$@

$(BUILD_DIR)/segments/%.o: $(BUILD_DIR)/linker_scripts/partial/%.ld
	$(file >$(@:.o=.o_files.txt), $(filter %.o, $^))
	$(QUIET_CMD)$(LD) $(ENDIAN) $(LDFLAGS) --relocatable -T $< -Map $(@:.o=.map) -o $@ @$(@:.o=.o_files.txt)

# Make inc files from assets

$(BUILD_DIR)/%.inc: %.png
	$(QUIET_CMD)$(PIGMENT64) to-bin --c-array --format $(subst .,,$(suffix $*)) -o $@ $<

$(BUILD_DIR)/%.ci8.inc: %.ci8.png
	$(QUIET_CMD)$(PIGMENT64) to-bin --c-array --format palette -o $(@:.ci8.inc=.palette.inc) $<
	$(QUIET_CMD)$(PIGMENT64) to-bin --c-array --format ci8 -o $@ $<

$(BUILD_DIR)/%.ci4.inc: %.ci4.png
	$(QUIET_CMD)$(PIGMENT64) to-bin --c-array --format palette -o $(@:.ci4.inc=.palette.inc) $<
	$(QUIET_CMD)$(PIGMENT64) to-bin --c-array --format ci4 -o $@ $<

$(BUILD_DIR)/%.msg.inc: %.msg
	$(QUIET_CMD)$(CC) -x c $(C_COMPILER_FLAGS) -I $(dir $*) -I $(BUILD_DIR)/$(dir $*) $(COMP_VERBOSE_FLAG) -E $< -o $(@:.inc=.i)
	$(QUIET_CMD)$(MSG_REENCODER) $(@:.inc=.i) $@ $(OUT_ENCODING)


# Setup game_etc weirdness

$(BUILD_DIR)/src/assets/game_etc/etc.o: $(BUILD_DIR)/src/assets/game_etc/etc_lws.subseg.inc

$(BUILD_DIR)/%.subseg.inc: $(BUILD_DIR)/%.subseg
	$(QUIET_CMD)$(INC_FROM_BIN) $< $@

$(BUILD_DIR)/%.subseg: $(BUILD_DIR)/%.o $(BUILD_DIR)/linker_scripts/subseg_05.ld
	$(QUIET_CMD)$(LD) $(ENDIAN) $(LDFLAGS) -Map $(@:.subseg=.map) -T  $(BUILD_DIR)/linker_scripts/subseg_05.ld -o $(@:.subseg=.subelf) $<
	$(QUIET_CMD)$(OBJCOPY) -O binary $(@:.subseg=.subelf) $@


-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

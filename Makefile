# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules

#### Defaults ####

# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Keep .mdebug section in build
KEEP_MDEBUG ?= 0
# Check code syntax with host compiler
RUN_CC_CHECK ?= 1
CC_CHECK_COMP ?= clang
# Dump build object files
OBJDUMP_BUILD ?= 0
# Number of threads to disassmble, extract, and compress with
# N_THREADS ?= $(shell nproc)

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-



BASEROM      := baserom.z64
TARGET       := drmario64

# Fail early if baserom does not exist
ifeq ($(wildcard $(BASEROM)),)
$(error Baserom `$(BASEROM)' not found.)
endif


### Output ###

BUILD_DIR := build
ROM       := $(BUILD_DIR)/$(TARGET).z64
ELF       := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := $(BUILD_DIR)/$(TARGET).ld
LD_MAP    := $(BUILD_DIR)/$(TARGET).map



#### Setup ####

ifeq ($(NON_MATCHING),1)
	CFLAGS := -DNON_MATCHING -DAVOID_UB
	CPPFLAGS := -DNON_MATCHING -DAVOID_UB
	COMPARE := 0
endif

MAKE = make
CPPFLAGS += -fno-dollars-in-identifiers -P
LDFLAGS  := --no-check-sections --accept-unknown-input-arch --emit-relocs

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

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
  $(error Please install or build $(MIPS_BINUTILS_PREFIX))
endif

# TODO: set CC

AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump
STRIP      := $(MIPS_BINUTILS_PREFIX)strip
GCC        := $(MIPS_BINUTILS_PREFIX)gcc
CPP        := $(MIPS_BINUTILS_PREFIX)cpp

PYTHON     ?= python3
SPLAT      ?=
SPLAT_YAML ?= $(TARGET).yaml


IINC       := -Iinclude

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wno-unknown-pragmas -Wno-missing-braces
ifneq ($(RUN_CC_CHECK),0)
# Have CC_CHECK pretend to be a MIPS compiler
	MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32
	CC_CHECK          := $(CC_CHECK_COMP) -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -D _LANGUAGE_C -D NON_MATCHING $(MIPS_BUILTIN_DEFS) $(IINC) $(CHECK_WARNINGS)
	CC_CHECK += -m32
	ifneq ($(WERROR), 0)
		CC_CHECK += -Werror
	endif
else
	CC_CHECK := @:
endif

# TODO: determine
OPTFLAGS := -O2 -g3
ASFLAGS := -march=vr4300 -32 $(IINC)
MIPS_VERSION := -mips2

# Surpress the warnings with -woff.
# CFLAGS += -G 0 -non_shared -fullwarn -verbose -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 624,649,838,712,516
CFLAGS += -G 0 $(IINC)

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32

ifneq ($(OBJDUMP_BUILD), 0)
	OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.s)
	OBJCOPY_BIN = $(OBJCOPY) -O binary $@ $@.bin
else
	OBJDUMP_CMD = @:
	OBJCOPY_BIN = @:
endif


#### Files ####

$(shell mkdir -p asm bin)

SRC_DIRS := $(shell find src -type d)
ASM_DIRS := $(shell find asm -type d)
BIN_DIRS := $(shell find bin -type d)

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
BIN_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$f)

# Automatic dependency files
# (Only asm_processor dependencies and reloc dependencies are handled for now)
DEP_FILES := $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(BUILD_DIR)/auto $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(BUILD_DIR)/$(dir)))


#### Main Targets ###

all: $(ROM)
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c $(TARGET).md5
endif

clean:
	$(RM) -r $(BUILD_DIR)

distclean: clean
	$(RM) -r asm/ bin/
#	$(MAKE) -C tools distclean

setup:
#	$(MAKE) -C tools
#	python3 fixbaserom.py
#	python3 extract_baserom.py
#	python3 extract_assets.py -j$(N_THREADS)

extract:
	$(RM) -r asm
	$(PYTHON) $(SPLAT) $(SPLAT_YAML)

diff-init: uncompressed
	$(RM) -rf expected/
	mkdir -p expected/
	cp -r $(BUILD_DIR) expected/$(BUILD_DIR)

init:
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) extract
	$(MAKE) all
	$(MAKE) diff-init

.PHONY: all clean distclean setup extract diff-init init
.DEFAULT_GOAL := all
# Prevent removing intermediate files
.SECONDARY:


#### Various Recipes ####

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@
	$(OBJCOPY) -O binary --gap-fill 0xFF --pad-to 0x400000 $< $@
# TODO: update header

$(ELF): $(O_FILES) $(LD_SCRIPT) $(BUILD_DIR)/undefined_syms.ld
	$(LD) $(LDFLAGS) -T $(BUILD_DIR)/undefined_syms.ld -T $(BUILD_DIR)/auto/undefined_syms_auto.ld -T $(BUILD_DIR)/auto/undefined_funcs_auto.ld -T $(LD_SCRIPT) -Map $(LD_MAP) -o $@


$(BUILD_DIR)/undefined_syms.ld: linker_scripts/undefined_syms.ld
	$(CPP) $(CPPFLAGS) $< > $@


$(BUILD_DIR)/%.o: %.bin
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/%.o: %.s
	$(CPP) $(CPPFLAGS) $(IINC) $< | $(AS) $(ASFLAGS) -o $@
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(CC_CHECK) $<
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)


# -include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

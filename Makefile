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
OBJDUMP_BUILD ?= 1
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

CC         := COMPILER_PATH=tools/gcc_kmc/$(DETECTED_OS)/2.7.2 tools/gcc_kmc/$(DETECTED_OS)/2.7.2/gcc

AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump
STRIP      := $(MIPS_BINUTILS_PREFIX)strip
GCC        := $(MIPS_BINUTILS_PREFIX)gcc
CPP        := $(MIPS_BINUTILS_PREFIX)cpp
STRIP      := $(MIPS_BINUTILS_PREFIX)strip

PYTHON     ?= python3
SPLAT      ?= tools/splat/split.py
SPLAT_YAML ?= $(TARGET).yaml


IINC       := -Iinclude
IINC       += -Ilib/ultralib/include -Ilib/ultralib/include/gcc -Ilib/ultralib/include/PR -Ilib/ultralib/src

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wno-unknown-pragmas -Wno-missing-braces -Wno-int-conversion
# TODO: fix on ultralib side
CHECK_WARNINGS += -Wno-macro-redefined
ifneq ($(RUN_CC_CHECK),0)
# Have CC_CHECK pretend to be a MIPS compiler
	MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32
#	The -MMD flags additionaly creates a .d file with the same name as the .o file.
	CC_CHECK          := $(CC_CHECK_COMP) -MMD -Wextra -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -D_LANGUAGE_C -DNON_MATCHING $(MIPS_BUILTIN_DEFS)
	CC_CHECK          += -m32
	ifneq ($(WERROR), 0)
		CC_CHECK += -Werror
	endif
else
	CC_CHECK := @:
endif

STDERR_REDIRECTION :=


# TODO: determine
OPTFLAGS        := -O2 -g3
ASFLAGS         := -march=vr4300 -32 $(IINC)
AS_DEFINES      := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
MIPS_VERSION    := -mips3
GBIDEFINE       := -DF3DEX_GBI_2
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99 $(GBIDEFINE) -DNDEBUG -D_FINALROM

# Surpress the warnings with -woff.
# CFLAGS += -G 0 -non_shared -fullwarn -verbose -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 624,649,838,712,516
CFLAGS += -nostdinc -G 0 $(IINC) -mgp32 -mfp32 -D_LANGUAGE_C -w

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

SRC_DIRS      := $(shell find src -type d)
ASM_DIRS      := $(shell find asm -type d -not -path "asm/nonmatchings/*")
BIN_DIRS      := $(shell find bin -type d)
LIBULTRA_DIRS := $(shell find lib/ultralib/src -type d -not -path "lib/ultralib/src/voice")

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) \
                 $(foreach dir,$(LIBULTRA_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s)) \
                 $(foreach dir,$(LIBULTRA_DIRS),$(wildcard $(dir)/*.s))
BIN_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$f)

# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(BUILD_DIR)/auto $(BUILD_DIR)/linker_scripts $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS) $(LIBULTRA_DIRS),$(BUILD_DIR)/$(dir)))

# directory flags

$(BUILD_DIR)/lib/ultralib/src/%.o: CFLAGS   += -w
$(BUILD_DIR)/lib/ultralib/src/%.o: OPTFLAGS := -O3
$(BUILD_DIR)/lib/ultralib/src/%.o: CC_CHECK := @:
# Redirect warnings
$(BUILD_DIR)/lib/ultralib/src/%.o: STDERR_REDIRECTION := 2> /dev/null

# $(BUILD_DIR)/lib/ultralib/src/mgu/%.o: CFLAGS += 

#### Main Targets ###

all: $(ROM)
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c $(TARGET).md5
endif

clean:
	$(RM) -r $(BUILD_DIR)/asm $(BUILD_DIR)/bin $(BUILD_DIR)/src $(ROM) $(ELF)

libclean:
	$(RM) -r $(BUILD_DIR)/lib

distclean: clean
	$(RM) -r $(BUILD_DIR) asm/ bin/
	$(MAKE) -C tools distclean

setup:
	$(MAKE) -C tools

extract:
	$(RM) -r asm
	$(PYTHON) $(SPLAT) $(SPLAT_YAML)

diff-init: all
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

$(ELF): $(O_FILES) $(LD_SCRIPT) $(BUILD_DIR)/linker_scripts/libultra_symbols.ld $(BUILD_DIR)/linker_scripts/hardware_regs.ld $(BUILD_DIR)/linker_scripts/undefined_syms.ld
	$(LD) $(LDFLAGS) -T $(LD_SCRIPT) \
		-T $(BUILD_DIR)/auto/undefined_syms_auto.ld -T $(BUILD_DIR)/auto/undefined_funcs_auto.ld \
		-T $(BUILD_DIR)/linker_scripts/libultra_symbols.ld -T $(BUILD_DIR)/linker_scripts/hardware_regs.ld -T $(BUILD_DIR)/linker_scripts/undefined_syms.ld \
		-Map $(LD_MAP) -o $@


$(BUILD_DIR)/%.ld: %.ld
	$(CPP) $(CPPFLAGS) $< > $@


$(BUILD_DIR)/%.o: %.bin
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/%.o: %.s
	$(CPP) $(CPPFLAGS) $(COMMON_DEFINES) $(AS_DEFINES) $(IINC) -I $(dir $*) $< | $(AS) $(ASFLAGS) -o $@ $(STDERR_REDIRECTION)
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(CC_CHECK) $(IINC) $(CHECK_WARNINGS) $(COMMON_DEFINES) -o $@ $<
	$(CC) -c $(CFLAGS) -I $(dir $*) $(COMMON_DEFINES) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $< $(STDERR_REDIRECTION)
	$(STRIP) $@ -N dummy-symbol-name
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)


-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

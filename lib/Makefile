MAKEFLAGS += --no-builtin-rules

# Dump build object files
OBJDUMP_BUILD ?= 1
# 
COMPILER ?= original

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-

### Output ###

BUILD_DIR := ../build/lib


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

MAKE = make

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := windows
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := macos
	MAKE := gmake
endif

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
	$(error Please install or build $(MIPS_BINUTILS_PREFIX))
endif


OBJDUMP         := $(MIPS_BINUTILS_PREFIX)objdump
GCC             := $(MIPS_BINUTILS_PREFIX)gcc

ifeq ($(VERSION),$(filter $(VERSION), us gw))
COMPILER_DIR    := ../tools/gcc_kmc/$(DETECTED_OS)/2.7.2
else ifeq ($(VERSION),cn)
COMPILER_DIR    := ../tools/gcc_egcs/$(DETECTED_OS)/1.1.2-4
endif

ORIGINAL_CC     := COMPILER_PATH=$(COMPILER_DIR) $(COMPILER_DIR)/gcc

ifeq ($(COMPILER), original)
    CC              := $(ORIGINAL_CC)
else ifeq ($(COMPILER), gcc)
    CC              := $(GCC)
endif


IINC       := -Iultralib/include -Iultralib/include/gcc -Iultralib/include/PR -Iultralib/src -Ilibmus/src

CFLAGS          := -nostdinc -fno-PIC -G 0 -mgp32 -mfp32
MIPS_VERSION    := -mips3
WARNINGS        := -w
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM
AS_DEFINES      := -D_LANGUAGE_ASSEMBLY -DMIPSEB -D_ULTRA64
C_DEFINES       := -D_LANGUAGE_C

ifeq ($(VERSION),$(filter $(VERSION), us gw))
OPTFLAGS        := -O3
DBGFLAGS        :=
# libultra 2.0K
LIBULTRA_VERSION:= 8
else ifeq ($(VERSION),cn)
CFLAGS          += -mcpu=4300 -mno-abicalls
OPTFLAGS        := -O2
DBGFLAGS        := -ggdb
# libultra 2.0L
LIBULTRA_VERSION:= 9
endif

ifeq ($(COMPILER), original)
    AS_DEFINES      += -D_MIPS_SIM=1
else ifeq ($(COMPILER), gcc)
    ABIFLAG         := -mabi=32
#    OPTFLAGS        := -Os -ffast-math -fno-unsafe-math-optimizations
    OPTFLAGS        := -O0
    DBGFLAGS        := -ggdb
    MIPS_VERSION    := -mips3
	WARNINGS        := $(CHECK_WARNINGS)

    CFLAGS          += -march=vr4300 -mfix4300 -mno-abicalls
    CFLAGS          += -mdivide-breaks -ffreestanding
    CFLAGS          += -fno-toplevel-reorder
# Consider removing in the future
    CFLAGS          += -fno-zero-initialized-in-bss
    CFLAGS          += -fcommon
endif

BUILD_DEFINES   += -DBUILD_VERSION=$(LIBULTRA_VERSION)

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32

ifneq ($(OBJDUMP_BUILD), 0)
	OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)
else
	OBJDUMP_CMD = @:
endif

#### Files ####

SRC_DIRS      := $(shell find ultralib/src -type d -not -path "ultralib/src/voice")
LIBMUS_DIRS   += $(shell find libmus/src -type d )

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f)

O_FILES       += $(BUILD_DIR)/libmus/src/aud_dma.o \
                 $(BUILD_DIR)/libmus/src/aud_sched.o \
                 $(BUILD_DIR)/libmus/src/lib_memory.o \
                 $(BUILD_DIR)/libmus/src/player.o \
                 $(BUILD_DIR)/libmus/src/aud_samples.o \
                 $(BUILD_DIR)/libmus/src/aud_thread.o \
                 $(BUILD_DIR)/libmus/src/player_fx.o

# create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS) $(LIBMUS_DIRS),$(BUILD_DIR)/$(dir)))


# directory flags

ifeq ($(COMPILER), original)
ifeq ($(VERSION),$(filter $(VERSION), us gw))
$(BUILD_DIR)/libmus/src/%.o:   MIPS_VERSION := -mips3
$(BUILD_DIR)/libmus/src/%.o:   CFLAGS += -Wa,--force-n64align
else ifeq ($(VERSION),cn)
$(BUILD_DIR)/libmus/src/%.o:   MIPS_VERSION := -mips2
endif
$(BUILD_DIR)/libmus/src/%.o:   RELEASE_DEFINES :=
endif

# per-file flags

ifeq ($(COMPILER), original)
$(BUILD_DIR)/libmus/src/player.o:      DBGFLAGS :=
$(BUILD_DIR)/libmus/src/player_fx.o:   DBGFLAGS :=
else ifeq ($(COMPILER), gcc)
$(BUILD_DIR)/ultralib/src/os/getfpccsr.o: CFLAGS += -D__osGetSR=__osGetFpcCsr
$(BUILD_DIR)/ultralib/src/os/setfpccsr.o: CFLAGS += -D__osSetSR=__osSetFpcCsr
$(BUILD_DIR)/ultralib/src/os/exceptasm.o: CC := $(ORIGINAL_CC)
$(BUILD_DIR)/ultralib/src/os/exceptasm.o: AS_DEFINES      += -D_MIPS_SIM=1
endif


#### Main Targets ###

all: $(O_FILES)

clean:
	$(RM) -r $(BUILD_DIR)/lib

distclean: clean

.PHONY: all clean distclean
.DEFAULT_GOAL := all
# Prevent removing intermediate files
.SECONDARY:

$(BUILD_DIR)/%.o: %.s
	$(CC) -c $(IINC) -I $(dir $*) $(WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $(CFLAGS) $(MIPS_VERSION) -x assembler-with-cpp -o $@ $<
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(IINC) -I $(dir $*) $(WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) $(DBGFLAGS) -o $@ $<
	$(OBJDUMP_CMD)

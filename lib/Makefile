MAKEFLAGS += --no-builtin-rules


# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-

### Output ###

BUILD_DIR := ../build/lib


#### Setup ####

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


CC         := COMPILER_PATH=../tools/gcc_kmc/$(DETECTED_OS)/2.7.2 ../tools/gcc_kmc/$(DETECTED_OS)/2.7.2/gcc

STRIP      := $(MIPS_BINUTILS_PREFIX)strip


IINC       := -Iultralib/include -Iultralib/include/gcc -Iultralib/include/PR -Iultralib/src -Ilibmus/src

OPTFLAGS        := -O3
MIPS_VERSION    := -mips3
CFLAGS          := -nostdinc -G 0 -mgp32 -mfp32
WARNINGS        := -w
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM
AS_DEFINES      := -D_LANGUAGE_ASSEMBLY -DMIPSEB -D_ULTRA64 -D_MIPS_SIM=1
C_DEFINES       := -D_LANGUAGE_C

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
	$(CC) -c $(CFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) -x assembler-with-cpp -o $@ $<
	$(STRIP) $@ -N dummy-symbol-name

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS) -o $@ $<
	$(STRIP) $@ -N dummy-symbol-name

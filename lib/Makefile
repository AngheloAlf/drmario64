MAKEFLAGS += --no-builtin-rules


# If non zero then compilation commands won't be printed to the terminal
QUIET ?= 0

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
CROSS ?= mips-linux-gnu-

### Output ###

BUILD_DIR := ../build/$(VERSION)/lib


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

ifneq ($(QUIET), 0)
    QUIET_CMD := @
else
    QUIET_CMD :=
endif

#### Tools ####
ifneq ($(shell type $(CROSS)ld >/dev/null 2>/dev/null; echo $$?), 0)
	$(error Please install or build $(CROSS))
endif


ifeq ($(VERSION),$(filter $(VERSION), us gw))
COMPILER_DIR    := ../tools/gcc_kmc/$(DETECTED_OS)/2.7.2
else ifeq ($(VERSION),cn)
COMPILER_DIR    := ../tools/gcc_egcs/$(DETECTED_OS)/1.1.2-4
endif
CC              := COMPILER_PATH=$(COMPILER_DIR) $(COMPILER_DIR)/gcc

STRIP      := $(CROSS)strip


IINC       := -Iultralib/include -Iultralib/include/gcc -Iultralib/include/PR -Iultralib/src -Ilibmus/src

CFLAGS          := -nostdinc -fno-PIC -G 0 -mgp32 -mfp32 -mabi=32
MIPS_VERSION    := -mips3
WARNINGS        := -w
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM
AS_DEFINES      := -D_LANGUAGE_ASSEMBLY -DMIPSEB -D_ULTRA64 -D_MIPS_SIM=1
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

BUILD_DEFINES   += -DBUILD_VERSION=$(LIBULTRA_VERSION)

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

ifeq ($(VERSION),$(filter $(VERSION), us gw))
$(BUILD_DIR)/libmus/src/%.o:   MIPS_VERSION := -mips3
$(BUILD_DIR)/libmus/src/%.o:   CFLAGS += -Wa,--force-n64align
else ifeq ($(VERSION),cn)
$(BUILD_DIR)/libmus/src/%.o:   MIPS_VERSION := -mips2
endif
$(BUILD_DIR)/libmus/src/%.o:   RELEASE_DEFINES :=

# per-file flags

$(BUILD_DIR)/libmus/src/player.o:      DBGFLAGS :=
$(BUILD_DIR)/libmus/src/player_fx.o:   DBGFLAGS :=


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
	$(QUIET_CMD)$(CC) -c $(IINC) -I $(dir $*) $(WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $(CFLAGS) $(MIPS_VERSION) -x assembler-with-cpp -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(QUIET_CMD)$(CC) -c $(IINC) -I $(dir $*) $(WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) $(DBGFLAGS) -o $@ $<

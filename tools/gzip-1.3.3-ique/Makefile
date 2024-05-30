TARGET := gzip
BUILD_DIR := build

DEBUG ?= 0

AR := ar
CC := gcc

CFLAGS := -O2 -g -ffunction-sections -fdata-sections -Wall -Wextra
LDFLAGS := -Wl,--gc-sections #-Wl,--print-gc-sections

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif

SRC_DIRS := $(shell find src -type d)
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
O_FILES := $(foreach f,$(C_FILES),$(BUILD_DIR)/$(f:.c=.o))
DEP_FILES := $(foreach f,$(O_FILES),$(f:.o=.d))

$(shell mkdir -p $(foreach dir,$(SRC_DIRS),$(BUILD_DIR)/$(dir)))

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) -rf $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c -MD -MMD $(CFLAGS) $< -o $@

$(TARGET): $(O_FILES)
	$(CC) $(LDFLAGS) $^ -o $@
#	$(AR) rcs $@ $^

-include $(DEP_FILES)

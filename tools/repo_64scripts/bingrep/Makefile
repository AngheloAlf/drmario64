PROGRAMS := bingrep.elf bytestostr.elf strtobytes.elf

CC       := clang
INC      :=

WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Werror=implicit-function-declaration -Wvla -Wno-unused-function
CFLAGS   := -std=c11 -funsigned-char
OPTFLAGS := -Os -g

# Main targets

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)

.PHONY: all clean

%.elf: %.c
	$(CC) $(CFLAGS) $(OPTFLAGS) $(WARNINGS) -o $@ $^

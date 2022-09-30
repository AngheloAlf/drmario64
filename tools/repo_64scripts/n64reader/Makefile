
ELF := n64reader.elf

CC       := clang
INC      := -Icrc32

WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Werror=implicit-function-declaration -Wvla -Wno-unused-function
CFLAGS   := -std=c11
OPTFLAGS := -O2

# Main targets

all: $(ELF)

clean:
	$(RM) $(ELF)

.PHONY: all clean

$(ELF): n64reader.c crc32/crc32.c
	$(CC) $(CFLAGS) $(OPTFLAGS) $(WARNINGS) -o $@ $^

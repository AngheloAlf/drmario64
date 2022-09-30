#include <stdio.h>

int main(int argc, char** argv) {
    char* string;
    if (argc < 2) {
        printf("Usage: %s STRING", argv[0]);
        return 1;
    }

    string = argv[1];
    while (*string != '\0') {
        printf("%c  ", *string);
        string++;
    }
    puts("\\0");

    string = argv[1];
    while (*string != '\0') {
        printf("%02X ", *string);
        string++;
    }
    puts("00");

    return 0;
}

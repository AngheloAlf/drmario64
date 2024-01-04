#include "gcc/string.h"

char *strcpy(char *dest, const char *src) {
    char *d = dest;

    while (*src != '\0') {
        *d++ = *src++;
    }
    *d = '\0';

    return dest;
}

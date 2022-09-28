/**
 * @file bytestostr.c
 * @author Elliptic Ellipsis (elliptic.ellipsis@google.com)
 * @brief Convert bytes to a characters with a certain encoding.
 *
 * @copyright Copyright (c) 2021--2, Elliptic Ellipsis
 * SPDX-identifier: MIT
 */
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))

int8_t DigitFromChar(char ch) {
    switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return ch - '0';

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return ch - 'A' + 0xA;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return ch - 'a' + 0xA;

        default:
            return -1;
    }
}

/**
 * Converts the hex digits in a string into a preallocated byte array.
 *
 * Returns number of bytes written.
 */
int BytesFromString(uint8_t* byteArray, const char* string) {

    if (string != NULL) {
        int len = 0;
        int parity = 0;
        int inIndex;
        int outIndex = 0;

        for (inIndex = 0; string[inIndex] != '\0'; inIndex++) {
            len++;
            if (isxdigit(string[inIndex])) {
                parity++;
                parity &= 1;
            } else {
                fprintf(stderr, "Found nonhexadecimal character '%c', skipping.\n", string[inIndex]);
            }
        }
        if (parity & 1) {
            printf("Input \"%s\" has an odd number of nybbles, padding with a leading zero.", string);
        }
        for (inIndex = 0; inIndex < len; inIndex++) {
            if (isxdigit(string[inIndex])) {
                uint8_t digit = DigitFromChar(string[inIndex]);

                if ((outIndex + parity) & 1) {
                    byteArray[(outIndex + parity) / 2] += digit;
                } else {
                    byteArray[(outIndex + parity) / 2] = digit << 4;
                }
                outIndex++;
            }
        }
        byteArray[(outIndex + parity) / 2] = '\0';
        return (outIndex + parity) / 2;
    }

    return -1;
}

typedef enum {
    ENCODING_INVALID = -1,
    ENCODING_ASCII,
    ENCODING_UTF8,
    ENCODING_SHIFT_JIS,
    ENCODING_EUC_JP,
} Encoding;

int EncodeBytes(char* outString, uint8_t* byteArray, Encoding inEncoding) {
    if (byteArray != NULL) {
        iconv_t conv;

        switch (inEncoding) {
            case ENCODING_ASCII:
            case ENCODING_UTF8:
                strcpy(outString, (char*)byteArray);
                // printf("%s\n", outString);
                // printf("%ld\n", strlen(outString));
                return strlen(outString);
            case ENCODING_SHIFT_JIS:
                conv = iconv_open("UTF-8//TRANSLIT", "SHIFT-JIS");
                break;
            case ENCODING_EUC_JP:
                conv = iconv_open("UTF-8//TRANSLIT", "EUC-JP");
                break;
            default:
                fprintf(stderr, "Unknown encoding\n");
                return -1;
        }

        {
            size_t inBytes = strlen((char*)byteArray);
            size_t outBytes = 3 * inBytes; /* Because UTF-8 can be 3 bytes for a 1-byte Shift-JIS character... */
            char* inPtr = (char*)byteArray;
            char* outPtr = outString;

            if (conv == (iconv_t)-1) {
                fprintf(stderr, "Conversion invalid\n");
                return -1;
            }

            if (iconv(conv, &inPtr, &inBytes, &outPtr, &outBytes) == (size_t)-1) {
                fprintf(stderr, "Conversion failed.\n");
                return -1;
            }
        }

        iconv_close(conv);
        return strlen(outString);
    }
    return -1;
}

// clang-format off
struct {
    const char* name;
    const Encoding num;
} encodingNames[] = {
    { "SJIS", ENCODING_SHIFT_JIS },
    { "SHIFTJIS", ENCODING_SHIFT_JIS },
    { "SHIFT_JIS", ENCODING_SHIFT_JIS },
    { "SHIFT-JIS", ENCODING_SHIFT_JIS },
    { "EUCJP", ENCODING_EUC_JP },
    { "EUC-JP", ENCODING_EUC_JP },
    { "EUC_JP", ENCODING_EUC_JP },
    { "ASCII", ENCODING_ASCII },
    { "UTF-8", ENCODING_UTF8 },
    { "UTF8", ENCODING_UTF8 },
    { "UTF_8", ENCODING_UTF8 },
    { "", ENCODING_INVALID },
};
// clang-format on

Encoding GetEncodingFromString(const char* str) {
    char* upper = malloc(strlen(str) + 1);
    char* ptr;
    size_t i;
    Encoding ret = ENCODING_INVALID;

    strcpy(upper, str);

    for (ptr = upper; *ptr != '\0'; ptr++) {
        *ptr = toupper(*ptr);
    }

    for (i = 0; i < ARRAY_COUNT(encodingNames); i++) {
        if (strcmp(upper, encodingNames[i].name) == 0) {
            ret = encodingNames[i].num;
            break;
        }
    }

    free(upper);
    return ret;
}

int main(int argc, char** argv) {
    char* bytes;
    size_t length;
    char* outString;
    uint8_t* byteArray;
    Encoding inEncoding = ENCODING_ASCII;

    if (argc < 2) {
        printf("Usage: %s BYTES [ENCODING]\n", argv[0]);
        return 1;
    }

    if (argc == 3) {
        inEncoding = GetEncodingFromString(argv[2]);
        if (inEncoding == ENCODING_INVALID) {
            fprintf(stderr, "Unknown encoding \"%s\"\n", argv[2]);
            return 1;
        }
    }

    bytes = argv[1];
    length = strlen(bytes);
    byteArray = malloc(length + 1);

    BytesFromString(byteArray, bytes);
    outString = calloc(3 * (length + 1), sizeof(char));

    if (EncodeBytes(outString, byteArray, inEncoding) == -1) {
        free(byteArray);
        free(outString);
        return 1;
    }

    printf("%s\n", outString);

    free(byteArray);
    free(outString);

    return 0;
}

#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Size of bad character table, needs a value for every character */
#define ASIZE (UINT8_MAX + 1)

struct {
    unsigned int afterContext;
    unsigned int beforeContext;
    int maxCount;
    int width;
    bool text;
    bool untilZero;
} gOptions = { 2, 2, -1, 1, false, false };

int currentCount = 0;

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

const char* g_setaf_red = "";
const char* g_setaf_light_black = "";
const char* g_setaf_light_red = "";
const char* g_sgr0 = "";

void enableColour() {
    g_setaf_red = "\x1b[31m";
    g_setaf_light_black = "\x1b[90m";
    g_setaf_light_red = "\x1b[91m";
    g_sgr0 = "\x1b[0m";
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef void (*bytePrintFunction)(uint8_t);
typedef void (*spacePrintFunction)(unsigned int);

void printChar(uint8_t ch) {
    switch (ch) {
        case '\0':
            printf("%s%c%s", g_setaf_light_black, '0', g_sgr0);
            break;
        case '\n':
            printf("%s%c%s", g_setaf_light_black, 'n', g_sgr0);
            break;
        case '\r':
            printf("%s%c%s", g_setaf_light_black, 'r', g_sgr0);
            break;
        case '\t':
            printf("%s%c%s", g_setaf_light_black, 't', g_sgr0);
            break;

        default:
            if (isprint(ch) != 0) {
                putchar(ch);
            } else {
                printf("%s%c%s", g_setaf_light_black, '.', g_sgr0);
            }
            break;
    }
}

void printByte(uint8_t ch) {
    printf("%02X", ch);
}

void printSpacing(unsigned int k) {
    if ((k + 1) % gOptions.width == 0) {
        putchar(' ');
    }
}

void printNothing(unsigned int k) {
    (void)k;
}

struct {
    bytePrintFunction bytePrint;
    spacePrintFunction spacePrint;
} gPrintInfo = {
    printByte,
    printSpacing,
};

/* Output function */
void OUTPUT(unsigned int j, unsigned int m, uint8_t* y, unsigned int n) {
    unsigned int k;
    unsigned int start = MAX(0, (int)(j - gOptions.beforeContext));
    unsigned int end = MIN(j + m + gOptions.afterContext, n);

    /* Offset */
    printf("[%06X]:  ", j);

    /* Before context */
    for (k = start; k < end; k++) {
        if ((j <= k) && gOptions.text && gOptions.untilZero && (y[k] == '\0')) {
            break;
        }
        if (j <= k && k < j + m) { /* Matched string */
            printf("%s", g_setaf_light_red);
            gPrintInfo.bytePrint(y[k]);
            gPrintInfo.spacePrint(k);
            printf("%s", g_sgr0);
        } else { /* Context */
            gPrintInfo.bytePrint(y[k]);
            gPrintInfo.spacePrint(k);
        }
    }
    // /* Before context */
    // for (k = MAX(0, (int)(j - gOptions.beforeContext)); k < j; k++) {
    //     gPrintInfo.bytePrint(y[k]);
    //     gPrintInfo.spacePrint(k);
    // }

    // /* Matched string */
    // for (k = j; k < j + m; k++) {
    // printf(g_setaf_light_red);
    //     gPrintInfo.bytePrint(y[k]);
    //     gPrintInfo.spacePrint(k);
    // printf(g_sgr0);
    // }

    // /* After context */
    // for (k = j + m; k < MIN(j + m + gOptions.afterContext, n); k++) {
    //     gPrintInfo.bytePrint(y[k]);
    //     gPrintInfo.spacePrint(k);
    // }
    if (k >= n) {
        puts("EOF");
    } else {
        putchar('\n');
    }
}

/**
 * See https://www-igm.univ-mlv.fr/~lecroq/string/node19.html
 *
 * x is search string
 * m is length of x
 * qsBc the "bad character table" to generate
 */
void preQsBc(uint8_t* x, unsigned int m, int qsBc[]) {
    unsigned int i;

    for (i = 0; i < ASIZE; ++i) {
        qsBc[i] = m + 1;
    }
    for (i = 0; i < m; ++i) {
        qsBc[x[i]] = m - i;
    }
}

/**
 * QuickSearch implementation
 *
 * x is search string
 * m is length of x
 * y is buffer to search
 * n is length of y
 */
void QS(uint8_t* x, unsigned int m, uint8_t* y, unsigned int n) {
    unsigned int j;
    int qsBc[ASIZE];

    currentCount = 0;

    /* Preprocessing */
    preQsBc(x, m, qsBc);

    /* Searching */
    j = 0;
    while (j <= n - m) {
        // printf("%d: %d\n", j, memcmp(x, y + j, m));
        if (memcmp(x, y + j, m) == 0) {
            OUTPUT(j, m, y, n);

            if (gOptions.maxCount > -1) {
                currentCount++;
                if (currentCount >= gOptions.maxCount) {
                    break;
                }
            }
        }
        j += qsBc[y[j + m]]; /* shift */
    }
}

/* The slow but reliable way: check every byte */
void BruteForceSearch(uint8_t* x, unsigned int m, uint8_t* y, unsigned int n) {
    unsigned int j = 0;

    currentCount = 0;

    while (j <= n - m) {
        if (memcmp(x, y + j, m) == 0) {
            OUTPUT(j, m, y, n);

            if (gOptions.maxCount > -1) {
                currentCount++;
                if (currentCount >= gOptions.maxCount) {
                    break;
                }
            }
        }
        j += gOptions.width;
    }
}

struct option longOpts[] = {
    { "after-context", required_argument, NULL, 'A' },
    { "before-context", required_argument, NULL, 'B' },
    { "max-count", required_argument, NULL, 'm' },
    { "text", no_argument, NULL, 'a' },
    // Non-grep args:
    { "until-zero", no_argument, NULL, 'z' },
    { "help", no_argument, NULL, 'h' },
    { "width", no_argument, NULL, 'W' },
    { 0 },
};

int main(int argc, char** argv) {
    int opt;
    FILE* inputFile;
    uint8_t* fileBuffer;
    size_t fileLength;
    uint8_t* search;
    int searchLength;

    /* Parse options */
    if (argc < 3) {
        printf("Usage: %s PATTERN FILE", argv[0]);
    }

    while (true) {
        int optionIndex = 0;
        if ((opt = getopt_long(argc, argv, "A:B:m:W:ahz", longOpts, &optionIndex)) == EOF) {
            break;
        }

        switch (opt) {
            case 'A':
                if (sscanf(optarg, "%d", &gOptions.afterContext) == 0) {
                    fprintf(stderr, "-A expects a dec number, found %s", optarg);
                    return 1;
                }
                break;

            case 'B':
                if (sscanf(optarg, "%d", &gOptions.beforeContext) == 0) {
                    fprintf(stderr, "-B expects a dec number, found %s", optarg);
                    return 1;
                }
                break;

            case 'm':
                if (sscanf(optarg, "%d", &gOptions.maxCount) == 0) {
                    fprintf(stderr, "-m expects a dec number, found %s", optarg);
                    return 1;
                }
                break;

            case 'W':
                if (sscanf(optarg, "%d", &gOptions.width) == 0) {
                    fprintf(stderr, "-W expects a dec number, found %s", optarg);
                    return 1;
                }
                break;

            case 'a':
                gOptions.text = true;
                break;

            case 'z':
                gOptions.untilZero = true;
                break;

            case 'h': // Not consistent with grep! Will fix when multi

                printf("Usage: %s PATTERN FILE", argv[0]);
                puts("\"grep, but for binary files\".\n"
                     "By default searches in a binary file for a given string of bytes and prints the\n"
                     "address and a small amount of context. Most options are taken from grep.\n"
                     "\n"
                     "Positional arguments\n"
                     "  PATTERN                   pattern of bytes to search for. Currently no wildcards\n"
                     "  FILE                      file to search for pattern\n"
                     "\n"
                     "Options\n"
                     "  -a, --text                treat string/file as ASCII instead of bytes\n"
                     "  -m, --max-count=NUM       stop after NUM selected lines\n"
                     "  -B, --before-context=NUM  print NUM lines of leading context\n"
                     "  -A, --after-context=NUM   print NUM lines of trailing context\n"
                     "  -h, --help                print this message and exit\n"
                     "\n"
                     "Non-grep options\n"
                     "  -z, --until-zero          print text until next string terminator (\\0),"
                     "                            requires --text\n"
                     "  -W, --width=NUM           only look for results whose offset is a multiple of\n"
                     "                            NUM, e.g. a whole number of words\n"
                     "\n");

                return 1;

            default:
                break;
        }
    }

    /* Check options */
    if (gOptions.untilZero && !gOptions.text) {
        fprintf(stderr, "--until-zero specified without --text\n");
        return 1;
    }

    /* Process options and input */

    // This makes the search a char array rather than a string, always, but is needed to avoid using the final '\0'
    searchLength = strlen(argv[optind]);
    search = malloc(searchLength);
    // memcpy(search, argv[1], searchLength);
    if (gOptions.text) {
        memcpy(search, argv[optind], searchLength);
    } else {
        searchLength = BytesFromString(search, argv[optind]);
    }

    if ((inputFile = fopen(argv[optind + 1], "rb")) == NULL) {
        fprintf(stderr, "Failed to open file %s\n", argv[optind + 1]);
        free(search);
        return 1;
    }

    if (gOptions.text) {
        gPrintInfo.bytePrint = printChar;
        gPrintInfo.spacePrint = printNothing;
    }

    // If output is piped, do not use colour
    if (isatty(STDOUT_FILENO)) {
        enableColour();
    }

    // {
    //     int i;
    //     printf("%s\n", argv[optind]);
    //     for (i = 0; i < searchLength; i++) {
    //         printf("%02X ", search[i]);
    //     }
    //     putchar('\n');
    // }

    fseek(inputFile, 0, SEEK_END);
    fileLength = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    fileBuffer = malloc(fileLength);
    fread(fileBuffer, fileLength, 1, inputFile);

    if (gOptions.width > 1) {
        // fprintf(stderr, "Using BFS\n");
        /* Use brute force for more complex searches for simplicity. */
        BruteForceSearch(search, searchLength, fileBuffer, fileLength);
    } else {
        // fprintf(stderr, "Using QS\n");
        QS(search, searchLength, fileBuffer, fileLength);
    }

    fclose(inputFile);
    free(search);
    free(fileBuffer);
    return 0;
}

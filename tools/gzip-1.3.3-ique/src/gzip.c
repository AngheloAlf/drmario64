#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gzip.h"

// Originally from revision.h
#define VERSION "1.3.3-iQue"
#define PATCHLEVEL 1
#define REVDATE "2024-05-27"

static void
version(const char *progname)
{
    static const char *license_msg[] = {
        "Copyright 2002 Free Software Foundation",
        "Copyright 1992-1993 Jean-loup Gailly",
        "This program comes with ABSOLUTELY NO WARRANTY.",
        "You may redistribute copies of this program",
        "under the terms of the GNU General Public License.",
        "For more information about these matters, see the file named COPYING.",
        NULL,
    };
    const char **p = license_msg;

    printf("%s %s\n(%s)\n", progname, VERSION, REVDATE);

    while (*p != NULL)
        printf("%s\n", *p++);
    printf("Written by Jean-loup Gailly."       "\n"
           "iQue matching by cadmic and Tharo"  "\n");
}

static void
usage(const char *progname)
{
    fprintf(stderr, 
           "Usage: %s [-V] [-v] [-[0-9]] <ifilename> <ofilename>"   "\n"
           "        -V: Display version information and exit"       "\n"
           "        -v: Verbose toggle, debug mode only"            "\n"
           "        -[0-9]: Compression level, 0=fastest 9=best"    "\n"
           "        ifilename: Input decompressed file"             "\n"
           "        ofilename: Output compressed file"              "\n",
        progname);
    exit(EXIT_FAILURE);
}

static void
myerror(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "\x1b[91m"
                    "Error: "
                    "\x1b[97m");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\x1b[0m"
                    "\n");
    va_end(ap);

    exit(EXIT_FAILURE);
}

void *
util_read_whole_file(const char *filename, size_t *size_out)
{
    FILE *file = fopen(filename, "rb");
    void *buffer = NULL;
    size_t size;

    if (file == NULL)
        myerror("failed to open file '%s' for reading: %s", filename, strerror(errno));

    // get size
    fseek(file, 0, SEEK_END);
    size = ftell(file);

    // if the file is empty, return NULL buffer and 0 size
    if (size != 0) {
        // allocate buffer
        buffer = malloc(size + 1);
        if (buffer == NULL)
            myerror("could not allocate buffer for file '%s'", filename);

        // read file
        fseek(file, 0, SEEK_SET);
        if (fread(buffer, size, 1, file) != 1)
            myerror("error reading from file '%s': %s", filename, strerror(errno));

        // null-terminate the buffer (in case of text files)
        ((char *)buffer)[size] = '\0';
    }

    fclose(file);

    if (size_out != NULL)
        *size_out = size;
    return buffer;
}

void
util_write_whole_file(const char *filename, const void *data, size_t size)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
        myerror("failed to open file '%s' for writing: %s", filename, strerror(errno));

    if (fwrite(data, size, 1, file) != 1)
        myerror("error writing to file '%s': %s", filename, strerror(errno));

    fclose(file);
}

local void do_exit(s, exitcode)
    gzip_state_t *s __attribute__((unused));
    int exitcode;
{
    static int in_exit = 0;

    if (in_exit) exit(exitcode);
    in_exit = 1;
    FREE(s);
    exit(exitcode);
}

void *signal_udata = NULL;

typedef RETSIGTYPE (*sig_type) OF((int));
RETSIGTYPE abort_gzip()
{
    gzip_state_t *s = signal_udata;
    if (s->remove_ofname) {
        fclose(s->ofd);
        xunlink(s->ofname);
    }
    do_exit(s, EXIT_FAILURE);
}

int do_compression(gzip_state_t *s);

int
main(int argc, char **argv)
{
    const char *ifilename = NULL;
    const char *ofilename = NULL;
    int level = 0;
    int verbose = 0;

    // parse args

#define arg_error(fmt, ...)                       \
    do {                                          \
        fprintf(stderr, fmt "\n", ##__VA_ARGS__); \
        usage(argv[0]);                           \
    } while (0)

    int argn = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // Optional args
            if ('0' <= argv[i][1] && argv[i][1] <= '9') {
                level = argv[i][1] - '0';
                continue;
            }

            if (argv[i][1] == 'n') {
                // Ignored, always TRUE
                continue;
            }

            if (argv[i][1] == 'v') {
                verbose = 1;
                continue;
            }

            if (argv[i][1] == 'V') {
                version(argv[0]);
                do_exit(OK);
                break;
            }

            arg_error("Unknown option \"%s\"", argv[i]);
        } else {
            // Required args

            switch (argn) {
                case 0:
                    ifilename = argv[i];
                    break;
                case 1:
                    ofilename = argv[i];
                    break;
                default:
                    arg_error("Unknown positional argument \"%s\"", argv[i]);
                    break;
            }
            argn++;
        }
    }
    if (argn != 2)
        arg_error("Not enough positional arguments");

#undef arg_error

    if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
        (void) signal(SIGINT, (sig_type)abort_gzip);
    }
#ifdef SIGTERM
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN) {
        (void) signal(SIGTERM, (sig_type)abort_gzip);
    }
#endif
#ifdef SIGHUP
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN) {
        (void) signal(SIGHUP,  (sig_type)abort_gzip);
    }
#endif


    FILE *ifile = fopen(ifilename, "rb");
    if (ifile == NULL)
        myerror("Could not open input file \"%s\" for reading", ifilename);

    FILE *ofile = fopen(ofilename, "wb");
    if (ofile == NULL)
        myerror("Could not open output file \"%s\" for writing", ofilename);

    gzip_state_t *s = calloc(1, sizeof(gzip_state_t));
    signal_udata = s;
    s->level = level;
    s->verbose = verbose;
    s->progname = argv[0];
    s->ifname = (char *)ifilename;
    s->ofname = (char *)ofilename;
    s->ifd = ifile;
    s->ofd = ofile;

    // Hack: make oob window reads consistent with original 32-bit gzip binary
    s->ifd_ = 3;
    s->z_suffix = 0x08052FB5;
    s->file_type_ = 0xFFFFD052;
    s->file_method_ = 0x08054AD0;

    size_t fsize;
    __attribute__((unused)) void *idata = util_read_whole_file(ifilename, &fsize);
    s->ifile_size = fsize;

    // Go
    if (do_compression(s) != OK) {
        myerror("gzip fail");
    }

    // Done
    fclose(ifile);
    fclose(ofile);

    do_exit(s, EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

int do_compression(gzip_state_t *s) {
    local const int extra_lbits[LENGTH_CODES] /* extra bits for each length code */
        = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};

    local const int extra_dbits[D_CODES] /* extra bits for each distance code */
        = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

    local const int extra_blbits[BL_CODES]/* extra bits for each bit length code */
        = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

    s->remove_ofname = 1;
    s->time_stamp = 0;
    clear_bufs(s);
    s->save_orig_name = 0;
    s->window_size = 2L*WSIZE;
    s->l_desc  = (tree_desc){ s->dyn_ltree, s->static_ltree, extra_lbits,  LITERALS+1, L_CODES,  MAX_BITS,    0 };
    s->d_desc  = (tree_desc){ s->dyn_dtree, s->static_dtree, extra_dbits,  0,          D_CODES,  MAX_BITS,    0 };
    s->bl_desc = (tree_desc){ s->bl_tree,   (ct_data*)NULL,  extra_blbits, 0,          BL_CODES, MAX_BL_BITS, 0 };

    int ret = zip(s);
    if (ret != OK)
        return ret;
    
    if (s->verbose) {
        display_ratio(s->bytes_in - (s->bytes_out - s->header_bytes), s->bytes_in, stderr);
        fprintf(stderr, "\n");
    }

    return ret;
}

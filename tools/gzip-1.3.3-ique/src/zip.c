/* zip.c -- compress files to the gzip or pkzip format
 * Copyright (C) 1992-1993 Jean-loup Gailly
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License, see the file COPYING.
 */

#ifdef RCSID
static char rcsid[] = "$Id: zip.c,v 0.17 1993/06/10 13:29:25 jloup Exp $";
#endif

#include "config.h"
#include <ctype.h>

#include "tailor.h"
#include "gzip.h"

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#ifdef HAVE_FCNTL_H
#  include <fcntl.h>
#endif

/* ===========================================================================
 * Deflate in to out.
 * IN assertions: the input and output buffers are cleared.
 *   The variables time_stamp and save_orig_name are initialized.
 */
int zip(s)
    gzip_state_t *s;
{
    uch  flags = 0;         /* general purpose bit flags */
    ush  attr = 0;          /* ascii/binary flag */
    ush  deflate_flags = 0; /* pkzip -es, -en or -ex equivalent */

    s->outcnt = 0;

    /* Write the header to the gzip file. See algorithm.doc for the format */

    s->method = DEFLATED;
    put_byte(s, GZIP_MAGIC[0]); /* magic header */
    put_byte(s, GZIP_MAGIC[1]);
    put_byte(s, DEFLATED);      /* compression method */

    if (s->save_orig_name) {
	flags |= ORIG_NAME;
    }
    put_byte(s, flags);         /* general flags */
    put_long(s, s->time_stamp == (s->time_stamp & 0xffffffff)
	     ? (ulg)s->time_stamp : (ulg)0);

    /* Write deflated file to zip file */
    s->crc = updcrc(0, 0);

    bi_init(s, s->ofd);
    ct_init(s, &attr, &s->method);
    lm_init(s, s->level, &deflate_flags);

    put_byte(s, (uch)deflate_flags); /* extra flags */
    put_byte(s, OS_CODE);            /* OS identifier */

    if (s->save_orig_name) {
	char *p = base_name(s->ifname); /* Don't save the directory part. */
	do {
	    put_char(s, *p);
	} while (*p++);
    }
    s->header_bytes = (off_t)s->outcnt;

    (void)deflate(s);

    if (s->ifile_size != -1L && s->bytes_in != s->ifile_size) {
	fprintf(stderr, "%s: %s: file size changed while zipping\n",
		s->progname, s->ifname);
    }

    /* Write the crc and uncompressed size */
    put_long(s, s->crc);
    put_long(s, (ulg)s->bytes_in);
    s->header_bytes += 2*sizeof(long);

    flush_outbuf(s);
    return OK;
}


/* ===========================================================================
 * Read a new buffer from the current input file, perform end-of-line
 * translation, and update the crc and input file size.
 * IN assertion: size >= 2 (for end-of-line translation)
 */
int file_read(s, buf, size)
    gzip_state_t *s;
    char *buf;
    unsigned size;
{
    unsigned len;

    Assert(s->insize == 0, "inbuf not empty");

    len = fread(buf, 1, size, s->ifd);
    if (len == 0) return (int)len;
    if (len == (unsigned)-1) {
	read_error(s);
	return EOF;
    }

    s->crc = updcrc((uch*)buf, len);
    s->bytes_in += (off_t)len;
    return (int)len;
}

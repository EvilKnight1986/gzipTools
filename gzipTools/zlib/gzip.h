#include "zlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef _ZSTREAM_H
#define _ZSTREAM_H
#define  Z_HEADER_SIZE 12

/* Compress gzip data */
int gzcompress(Byte *data, uLong ndata, 
	Byte *zdata, uLong *nzdata);

/* http gzip Uncompress data */
int httpgzdecompress(Byte *zdata, uLong nzdata,
	Byte *data, uLong *ndata);
#endif
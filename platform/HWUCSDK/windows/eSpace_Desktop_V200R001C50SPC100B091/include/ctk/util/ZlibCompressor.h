#ifndef ZLIB_COMPRESSOR_H
#define ZLIB_COMPRESSOR_H

#include "ctk/ctk_config.h"

#include <string>

class GZlibCompressor
{
public:
    // This is called when the compressor is on the
    // downstream side. We'll take the message, compress it
    // and move it along to the next module.
    CTK_API static int comp(const char *msg, unsigned char *&compressed, int &len);

    // This one is called on the upstream side.  No surprise: we
    // decompress the data and send it on up the stream.
    CTK_API static int uncomp(const char *msg, char *&decompressed, int &len);
};

#endif /* ZLIB_COMPRESSOR_H */


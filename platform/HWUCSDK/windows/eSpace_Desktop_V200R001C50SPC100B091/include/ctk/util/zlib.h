/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_ZLIB_H_
#define _Z_CTK_UTIL_ZLIB_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

namespace ctk {

    class zlib
    {
    public:
        CTK_API static bool compress(rcistr _in, Bytes& _out);
        CTK_API static bool uncompress(rcistr _in, Bytes& _out, size_type _originSize=0);
    };

    class gzlib
    {
    public:
        // This is called when the compressor is on the
        // downstream side. We'll take the message, compress it
        // and move it along to the next module.
        CTK_API static bool comp(const char *msg, unsigned char *&compressed, int &len);

        // This one is called on the upstream side.  No surprise: we
        // decompress the data and send it on up the stream.
        CTK_API static bool uncomp(const char *msg, char *&decompressed, int &len);
    };

} // namespace ctk

#endif //_Z_CTK_UTIL_ZLIB_H_


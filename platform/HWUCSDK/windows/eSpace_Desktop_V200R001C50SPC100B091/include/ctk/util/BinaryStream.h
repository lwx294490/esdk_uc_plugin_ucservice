/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_BINARYSTREAM_H_
#define _Z_CTK_UTIL_BINARYSTREAM_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

namespace ctk
{

    struct CTK_API BinaryDecodeException : public Exception
    {
        typedef Exception _Super;

        BinaryDecodeException(CTK_CURRENT_ARGS, pcstr _msg);
    };

    /*
        [0]: size of data length
        [1:<size of data length>]: data length
        [<1+<size of data length>>:<data length>]: data
    */

    class CTK_API BinaryStream
    {
    public:
        CTK_STATIC_FUN ctk::int64 readInt(ctk::pcstr _buf, char _size, ctk::size_type _maxBytes);
        CTK_STATIC_FUN ctk::uint64 readUint(ctk::pcstr _buf, char _size, ctk::size_type _maxBytes);

        CTK_STATIC_FUN ctk::int64 readInt(ctk::istr _v, ctk::size_type _maxBytes);
        CTK_STATIC_FUN ctk::uint64 readUint(ctk::istr _v, ctk::size_type _maxBytes);

        CTK_STATIC_FUN char writeInt(ctk::pstr _buf, ctk::int64 _val, ctk::size_type _maxBytes);
        CTK_STATIC_FUN char writeInt(ctk::pstr _buf, ctk::uint64 _val, ctk::size_type _maxBytes);

        CTK_STATIC_FUN ctk::byte encrypt(ctk::byte _v);
        CTK_STATIC_FUN ctk::byte decrypt(ctk::byte _v);

        CTK_STATIC_FUN void encrypt(ctk::ostr _v);
        CTK_STATIC_FUN void decrypt(ctk::ostr _v);
    };

} // end of namespace ctk

#endif //_Z_CTK_UTIL_BINARYSTREAM_H_


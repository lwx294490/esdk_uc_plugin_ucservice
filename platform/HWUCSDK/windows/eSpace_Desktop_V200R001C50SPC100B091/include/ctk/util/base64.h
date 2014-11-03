/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_BASE64_H_
#define _Z_CTK_UTIL_BASE64_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{

    class CTK_API Base64
    {
    public:
        typedef std::vector<byte> ByteVector;

        CTK_STATIC_FUN void encode(istr _bin, String& _txt, bool _insertNewLines=false);
        CTK_STATIC_FUN void encode(const ByteVector& _bin, String& _txt, bool _insertNewLines=false);

        CTK_STATIC_FUN void decode(istr _txt, Bytes& _bin);
        CTK_STATIC_FUN void decode(istr _txt, ByteVector& _bin);

        CTK_STATIC_FUN bool isBase64(char);

    private:
        CTK_STATIC_FUN char encode(byte);
        CTK_STATIC_FUN byte decode(char);
    };

} // namespace ctk

#endif //_Z_CTK_UTIL_BASE64_H_


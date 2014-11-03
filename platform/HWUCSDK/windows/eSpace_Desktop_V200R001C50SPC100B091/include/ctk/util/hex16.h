/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_HEX16_H_
#define _Z_CTK_UTIL_HEX16_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{

    class CTK_API Hex16
    {
    public:
        static void encode(rcistr _inBin, String& _outTxt);
        static void decode(rcistr _inTxt, Bytes& _outBin);

        static char encode(byte);
        static byte decode(char);

        static bool isHexChar(char _c);

    };

} // namespace ctk

#endif //_Z_CTK_UTIL_HEX16_H_


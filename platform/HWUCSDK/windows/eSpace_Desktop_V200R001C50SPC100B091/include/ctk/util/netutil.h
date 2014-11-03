/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_NETUTIL_H_
#define _Z_CTK_UTIL_NETUTIL_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_octets.h"

namespace ctk
{
    CTK_API octets<2> hton(uint16 _i);
    CTK_API octets<4> hton(uint32 _i);
    CTK_API octets<8> hton(uint64 _i);

    CTK_API uint16 ntoh(octets<2> _s);
    CTK_API uint32 ntoh(octets<4> _s);
    CTK_API uint64 ntoh(octets<8> _s);

    CTK_API uint32 ip_aton(rcistr _ip);
    CTK_API String ip_ntoa(uint32 _naddr);
}

#endif //_Z_CTK_UTIL_NETUTIL_H_


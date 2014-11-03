/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_UTIL_H_
#define _Z_CTK_LOG_UTIL_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_enum.h"

#include <ace/INET_Addr.h>

namespace ctk
{
    struct CTK_API rawstring
    {
        istr buf_;

        rawstring(istr _buf);

        ctk::dumper& operator()(ctk::dumper& os) const;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::rawstring& v)
    {
        return v(os);
    }

    struct CTK_API namestring
    {
        istr buf_;
        pcstr sep_;

        namestring(rcistr _buf, pcstr _sep);

        ctk::dumper& operator()(ctk::dumper& os) const;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::namestring& v)
    {
        return v(os);
    }

    CTK_API dumper& operator<<(dumper& _d, const ACE_INET_Addr& _v);

} // namespace ctk

namespace std
{
    CTK_API ostream& operator<<(ostream& _os, const ACE_INET_Addr& _v);
} // end of namespace std

#endif//_Z_CTK_LOG_UTIL_H_


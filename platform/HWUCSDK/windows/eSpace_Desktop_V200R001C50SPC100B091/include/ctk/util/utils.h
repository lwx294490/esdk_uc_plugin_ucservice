/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_UTILS_H_
#define _Z_CTK_UTIL_UTILS_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{
    class CTK_API Util
    {
    public:

        CTK_STATIC_FUN void split(const ctk::String& _in, ctk::String& _out1, ctk::String& _out2);

        CTK_STATIC_FUN void split(const ctk::String& _in, std::vector<ctk::String>& _out, char _delim=' ', bool _noTrim=false);

    };

} // namespace ctk

#endif //_Z_CTK_UTIL_UTILS_H_


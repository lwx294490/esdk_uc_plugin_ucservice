/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_MISC_H_
#define _Z_CTK_BASE_TYPE_MISC_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    struct CTK_API null_type
    {
    };
    inline std::ostream& operator<<(std::ostream& _os, null_type)
    {
        return _os << "<null>";
    }

    struct CTK_API empty_type
    {
    };
    inline std::ostream& operator<<(std::ostream& _os, empty_type)
    {
        return _os << "<empty>";
    }

    struct CTK_API true_type
    {
    };
    inline std::ostream& operator<<(std::ostream& _os, true_type)
    {
        return _os << "<true>";
    }

    struct CTK_API false_type
    {
    };
    inline std::ostream& operator<<(std::ostream& _os, false_type)
    {
        return _os << "<false>";
    }

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_MISC_H_


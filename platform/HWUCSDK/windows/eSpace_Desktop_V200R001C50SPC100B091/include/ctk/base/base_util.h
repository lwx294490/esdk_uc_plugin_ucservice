/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_UTIL_H_
#define _Z_CTK_BASE_UTIL_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_stl.h"
#include "ctk/base/base_type_string.h"

namespace ctk
{

    typedef ctk::list<ctk::String> StringList;
    typedef ctk::list<ctk::Wstring> WstringList;

    typedef ctk::vector<ctk::String> StringArray;
    typedef ctk::vector<ctk::Wstring> WstringArray;

} // namespace ctk

#endif //_Z_CTK_BASE_UTIL_H_


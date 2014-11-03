/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_ASSERT_H_
#define _Z_CTK_BASE_ASSERT_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_current.h"

#include "ctk/log/macros.h"

#include <cassert>

namespace ctk
{
    class CTK_API logger;
    CTK_API void assertFailure(logger&, pcstr cond, CTK_CURRENT_ARGS, pcstr action);
    CTK_API void ensureFailure(logger&, pcstr cond, CTK_CURRENT_ARGS, pcstr action);
}

#endif //_Z_CTK_BASE_ASSERT_H_


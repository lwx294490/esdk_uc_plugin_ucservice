/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_SYSTEM_H_
#define _Z_CTK_BASE_SYSTEM_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    class CTK_API System
    {
    public:
        static bool closing();
        static void close();
    private:
        static volatile bool closing_;
    };

} // namespace ctk

#endif //_Z_CTK_BASE_SYSTEM_H_


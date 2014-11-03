/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MLC_HELPER_H_
#define _Z_CTK_MLC_HELPER_H_

#include "ctk/ctk_config.h"

namespace ctk {

    struct CTK_API MLC_Entry
    {
        MLC_Entry();
        ~MLC_Entry();

        static void enter();
        static void leave();

        static void startup();
        static void shutdown();
        static void logExceptionOnly();
    };

}

#endif


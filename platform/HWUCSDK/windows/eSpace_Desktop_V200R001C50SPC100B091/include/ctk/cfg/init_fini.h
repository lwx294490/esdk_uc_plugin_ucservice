/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_CFG_INIT_FINI_H_
#define _Z_CTK_CFG_INIT_FINI_H_

#include "ctk/ctk_config.h"

#ifdef _DEBUG
#define _CTK_CONSOLE_ON true
#else
#define _CTK_CONSOLE_ON false
#endif

namespace ctk
{
    struct CTK_API InitFini
    {
        InitFini(pcstr _logFile=0, bool _consoleOn=_CTK_CONSOLE_ON, int _numofTimers=0);
        ~InitFini();
    };

    CTK_API void init(pcstr _logFile=0, bool _consoleOn=_CTK_CONSOLE_ON, int _numofTimers=0);

    CTK_API void fini();

    CTK_API void startup(pcstr _logFile=0, bool _consoleOn=_CTK_CONSOLE_ON, int _numofTimers=0);

    CTK_API void shutdown();

}

#endif//_Z_CTK_CFG_INIT_FINI_H_


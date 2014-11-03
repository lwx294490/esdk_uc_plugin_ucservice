/* CTK(Mini Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_CTRLCHANDLER_H_
#define _Z_CTK_UTIL_CTRLCHANDLER_H_

#include "ctk/ctk_config.h"

#include <ctk/base/exception.h>

namespace ctk
{

    typedef void (*QuitHandlerCallback)(int);

    class CTK_API QuitHandler
    {
    public:
        QuitHandler(QuitHandlerCallback = 0);
        ~QuitHandler();

        void setCallback(QuitHandlerCallback);
        QuitHandlerCallback getCallback() const;

    };

    class CTK_API QuitHandlerException : public Exception
    {
        typedef Exception _Super;

    public:
        QuitHandlerException(CTK_CURRENT_ARGS);

    };

} // ctk

#endif // _Z_CTK_UTIL_CTRLCHANDLER_H_


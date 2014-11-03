/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_DEBUG_H_
#define _Z_CTK_LOG_DEBUG_H_

#include "ctk/ctk_config.h"

#include "ctk/log/macros.h"

namespace ctk {

    class logger;

    CTK_API void writeDataLog (logger&, CTK_CURRENT_ARGS, pcstr _msg);

    CTK_API void writeDebugLog(logger&, CTK_CURRENT_ARGS, pcstr _msg, pcstr _errLevel);
    
    CTK_API void writeInfoLog (logger&, CTK_CURRENT_ARGS, pcstr _msg, pcstr _errLevel);

    CTK_API void writeErrorLog(logger&, CTK_CURRENT_ARGS, pcstr _msg, pcstr _errLevel);

    CTK_API void writeExcptLog(logger&, CTK_CURRENT_ARGS, pcstr _msg);

    CTK_API void exceptionThrown(logger&, CTK_CURRENT_ARGS, pcstr _msg);

    CTK_API void writeLog(logger&, pcstr _title, pcstr _head, pcstr _body, pcstr _tail="", pcstr _foot="");

    CTK_API void writeEntryLog(logger&, pcstr _time, pcstr _left, pcstr _right, char _fill=' ');

}

#endif//_Z_CTK_LOG_DEBUG_H_


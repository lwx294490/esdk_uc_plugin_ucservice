/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TRACEENTRY_H_
#define _Z_CTK_BASE_TRACEENTRY_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    class CTK_API logger;
    
    struct CTK_API TraceEntry
    {
        enum LogType
        {
            LOG_NONE = 0,
            LOG_BEGIN = 0x1,
            LOG_END = 0x2,
            LOG_ALL = LOG_BEGIN | LOG_END
        };

        TraceEntry(logger& _logger, CTK_CURRENT_ARGS, LogType _logType=LOG_NONE, pcstr _info=0);
        ~TraceEntry();

        LogType& logType();
        LogType logType() const;
        void addType(LogType _t);

        std::string& info();
        const std::string& info() const;

        static void indentString(std::string& _s, ctk::size_type _depth, char _fill);

    private:
        void writeLog(bool _begin, pcstr _func, char _fill, size_type _depth);

    private:
        logger& logger_;
        LogType logType_;
        std::string info_;
    };
}

#endif // _Z_CTK_BASE_TRACEENTRY_H_


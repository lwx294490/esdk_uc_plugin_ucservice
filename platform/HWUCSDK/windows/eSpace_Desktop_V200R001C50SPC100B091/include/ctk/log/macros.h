/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_MACROS_H_
#define _Z_CTK_LOG_MACROS_H_

#include "ctk/ctk_config.h"

#include "ctk/log/log_factory.h"

#include "ctk/base/user_log_macros.h"

// define self logger
#define CTK_LOGGER()                    CTK_USER_LOGGER(ctk::LOGGER_ID)

#define CTK_LOG(x)                      CTK_USER_LOG(CTK_LOGGER(), x)
#define CTK_LOG_NL()                    CTK_USER_LOG_NL(CTK_LOGGER())
#define CTK_LOGL(x)                     CTK_USER_LOGL(CTK_LOGGER(), x)

#define CTK_LOG2(x)                     CTK_USER_LOG2(CTK_LOGGER(), x)
#define CTK_LOG2_NL()                   CTK_USER_LOG2_NL(CTK_LOGGER())
#define CTK_LOGL2(x)                    CTK_USER_LOGL2(CTK_LOGGER(), x)

#define CTK_TIME_LOG(x)                 CTK_USER_TIME_LOG(CTK_LOGGER(), x)
#define CTK_TIME_LOG_X(type, x)         CTK_USER_TIME_LOG_X(CTK_LOGGER(), type, x)

//////////////////////////////////////////////////////////////////////////////

// 跟踪日志 //
// should #include "ctk/log/log_tracer.h" before use these macros
#define CTK_TRACE()                     CTK_USER_TRACE(CTK_LOGGER())
#define CTK_TRACE0()                    CTK_USER_TRACE0(CTK_LOGGER())
#define CTK_TRACE1(info)                CTK_USER_TRACE1(CTK_LOGGER(), info)
#define CTK_TRACE_0()                   CTK_USER_TRACE_0(CTK_LOGGER())
#define CTK_TRACE_1(info)               CTK_USER_TRACE_1(CTK_LOGGER(), info)
#define CTK_TRACE_0E()                  CTK_USER_TRACE_0E(CTK_LOGGER())
#define CTK_TRACE_1E(info)              CTK_USER_TRACE_1E(CTK_LOGGER(), info)
#define CTK_TRACE_X(info)               CTK_USER_TRACE_X(CTK_LOGGER(), info)

//////////////////////////////////////////////////////////////////////////////

// 断言日志 //
// should #include "ctk/base/assert.h" before use following macros
#define CTK_ASSERT_CURR(cond, CURR)     CTK_USER_ASSERT_CURR(CTK_LOGGER(), cond, CURR)
#define CTK_ASSERT(cond)                CTK_USER_ASSERT(CTK_LOGGER(), cond)
#define CTK_ASSERT_MSG(cond, msg)       CTK_USER_ASSERT_MSG(CTK_LOGGER(), cond, msg)
#define CTK_ASSERT_ACT(cond, action)    CTK_USER_ASSERT_ACT(CTK_LOGGER(), cond, action)
#define CTK_ASSERT_RET(cond, val)       CTK_USER_ASSERT_RET(CTK_LOGGER(), cond, val)
#define CTK_ENSURE(cond)                CTK_USER_ENSURE(CTK_LOGGER(), cond)
#define CTK_ENSURE_MSG(cond, msg)       CTK_USER_ENSURE_MSG(CTK_LOGGER(), cond, msg)
#define CTK_ENSURE_ACT(cond, action)    CTK_USER_ENSURE_ACT(CTK_LOGGER(), cond, action)
#define CTK_ENSURE_RET(cond, val)       CTK_USER_ENSURE_RET(CTK_LOGGER(), cond, val)

//////////////////////////////////////////////////////////////////////////////

// should #include "ctk/log/log_debug.h" before use these macros

// 数据日志 //
#define CTK_DATA_LOG(x)                 CTK_USER_DATA_LOG(CTK_LOGGER(), x)

// 调试日志 //
#define CTK_DEBUG_LOG_X(type, x)        CTK_USER_DEBUG_LOG_X(CTK_LOGGER(), type, x)
#define CTK_DEBUG_LOG(x)                CTK_USER_DEBUG_LOG(CTK_LOGGER(), x)
#define CTK_TRACE_LOG(x)                CTK_USER_TRACE_LOG(CTK_LOGGER(), x)
#define CTK_DIAG_LOG(x)                 CTK_USER_DIAG_LOG(CTK_LOGGER(), x)
#define CTK_CMD_LOG(x)                  CTK_USER_CMD_LOG(CTK_LOGGER(), x)
#define CTK_COMM_LOG(x)                 CTK_USER_COMM_LOG(CTK_LOGGER(), x)
#define CTK_HB_LOG(x)                   CTK_USER_HB_LOG(CTK_LOGGER(), x)
#define CTK_HB_COMM_LOG(isHB, x)        do { if (isHB) CTK_HB_LOG(x); else CTK_COMM_LOG(x); } while(0)

// 信息日志 //
#define CTK_INFO_LOG_X(type, x)         CTK_USER_INFO_LOG_X(CTK_LOGGER(), type, x)
#define CTK_INFO_LOG(x)                 CTK_USER_INFO_LOG(CTK_LOGGER(), x)
#define CTK_NOTICE_LOG_X(type, x)       CTK_USER_NOTICE_LOG_X(CTK_LOGGER(), type, x)
#define CTK_NOTICE_LOG(x)               CTK_USER_NOTICE_LOG(CTK_LOGGER(), x)

// 错误日志 //
#define CTK_ERROR_LOG_X(type, x)        CTK_USER_ERROR_LOG_X(CTK_LOGGER(), type, x)
#define CTK_WARN_LOG(x)                 CTK_USER_WARN_LOG(CTK_LOGGER(), x)
#define CTK_ERROR_LOG(x)                CTK_USER_ERROR_LOG(CTK_LOGGER(), x)
#define CTK_FATAL_LOG(x)                CTK_USER_FATAL_LOG(CTK_LOGGER(), x)
#define CTK_EXCPT_LOG(ex)               CTK_USER_EXCPT_LOG(CTK_LOGGER(), ex)

// 异常日志 //
#define CTK_THROW_MSG(ex, msg)              CTK_USER_THROW_MSG(CTK_LOGGER(), ex, msg)
#define CTK_THROW_MSG_STD(ex, msg)          CTK_USER_THROW_MSG_STD(CTK_LOGGER(), ex, msg)
#define CTK_THROW_MSG_RET(ex, msg, ret)     CTK_USER_THROW_MSG_RET(CTK_LOGGER(), ex, msg, ret)
#define CTK_THROW_MSG_STD_RET(ex, msg, ret) CTK_USER_THROW_MSG_STD_RET(CTK_LOGGER(), ex, msg, ret)
#define CTK_THROW(ex)                       CTK_USER_THROW(CTK_LOGGER(), ex)
#define CTK_THROW_STD(ex)                   CTK_USER_THROW_STD(CTK_LOGGER(), ex)
#define CTK_THROW_RET(ex, ret)              CTK_USER_THROW_RET(CTK_LOGGER(), ex, ret)
#define CTK_THROW_STD_RET(ex, ret)          CTK_USER_THROW_STD_RET(CTK_LOGGER(), ex, ret)

#define CTK_ASSERT_THROW_MSG(c, e, m)   CTK_USER_ASSERT_THROW_MSG(CTK_LOGGER(), c, e, m)
#define CTK_ASSERT_THROW(cond, ex)      CTK_USER_ASSERT_THROW(CTK_LOGGER(), cond, ex)
#define CTK_ASSERT_NOTNULL(ptr)         CTK_USER_ASSERT_NOTNULL(CTK_LOGGER(), ptr)

#define CTK_TODO()                      CTK_USER_TODO(CTK_LOGGER())

namespace ctk
{
    // default log filename will be $(CWD)/log/$(LOGGER_ID).default.log
    const pcstr LOGGER_ID = ("CTK");
}

#endif//_Z_CTK_LOG_MACROS_H_


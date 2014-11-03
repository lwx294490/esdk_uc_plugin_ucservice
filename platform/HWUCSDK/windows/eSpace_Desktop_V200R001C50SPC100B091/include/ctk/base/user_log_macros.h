/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_USER_LOG_MACROS_H_
#define _Z_CTK_BASE_USER_LOG_MACROS_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/traceentry.h"

#define CTK_USER_LOGGER(x)      ctk::logger_factory::instance(x)

#define CTK_LOG_OR_OUTPUT(l,s)  do { std::ostringstream __oss__; __oss__ << s; l.writeOrPrint (__oss__.str()); } while(0)
#define CTK_LOG_AND_OUTPUT(l,s) do { std::ostringstream __oss__; __oss__ << s; l.writeAndPrint(__oss__.str()); } while(0)

#define CTK_USER_LOG(l, x)      CTK_LOG_OR_OUTPUT(l, x)
#define CTK_USER_LOG_NL(l)      CTK_LOG_OR_OUTPUT(l, std::endl)
#define CTK_USER_LOGL(l, x)     CTK_LOG_OR_OUTPUT(l, x << std::endl)
#define CTK_USER_LOG2(l, x)     CTK_LOG_AND_OUTPUT(l, x)
#define CTK_USER_LOG2_NL(l)     CTK_LOG_AND_OUTPUT(l, std::endl)
#define CTK_USER_LOGL2(l, x)    CTK_LOG_AND_OUTPUT(l, x << std::endl)

#define CTK_USER_CURRENT_LOG(l, x) CTK_USER_LOGL2(l, ctk::SimpleThread::current() << '[' << (l).id() << ']' << x)
#define CTK_USER_TIME_LOG(l, x) CTK_USER_CURRENT_LOG(l, ' ' << x)

#define CTK_VAR(v) #v << '(' << v << ')'

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//              跟踪日志宏                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// CTK_USER_TRACE(_log_)
// CTK_USER_TRACE0(_log_)
// CTK_USER_TRACE1(_log_, name)
// CTK_USER_TRACE_THREAD_ONWORK(_log_)

// 跟踪记录函数调用栈 //
#define CTK_USER_TRACE(_log_)           ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, ctk::TraceEntry::LOG_NONE)
#define CTK_USER_TRACE0(_log_)          ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
                                             !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_ALL)
#define CTK_USER_TRACE1(_log_, _x_)     std::ostringstream __trace_info__; if (_log_.traceOn()) __trace_info__ << _x_; \
                                        ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
                                             !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_ALL, \
                                             __trace_info__.str().c_str())
#define CTK_USER_TRACE_0(_log_)         ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
                                             !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_BEGIN)
#define CTK_USER_TRACE_1(_log_, _x_)    std::ostringstream __trace_info__; if (_log_.traceOn()) __trace_info__ << _x_; \
                                        ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
                                             !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_BEGIN, \
                                             __trace_info__.str().c_str())
#define CTK_USER_TRACE_0E(_log_)        ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
                                            !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_END)
#define CTK_USER_TRACE_1E(_log_, _x_)   std::ostringstream __trace_info__; if (_log_.traceOn()) __trace_info__ << _x_; \
                                        ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
                                             !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_END, \
                                             __trace_info__.str().c_str())
#define CTK_USER_TRACE_X(_log_, _x_)    do { if (_log_.traceOn()) { \
                                            std::ostringstream __trace_info__x; \
                                            __trace_info__x << _x_; \
                                            if (!__trace_entry__.info().empty()) __trace_entry__.info() += ' '; \
                                            __trace_entry__.info() += __trace_info__x.str(); \
                                            __trace_entry__.addType(ctk::TraceEntry::LOG_END); \
                                        } } while(0)

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//              断言日志宏                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// CTK_USER_ASSERT(_log_, cond)
// CTK_USER_ASSERT_ACT(_log_, cond, action)
// CTK_USER_ASSERT_RET(_log_, cond, val)
// CTK_USER_ENSURE(_log_, cond)
// CTK_USER_ENSURE_ACT(_log_, cond, action)
// CTK_USER_ENSURE_RET(_log_, cond, val)

///////////////////////////////////////////////////////////////////////////////

#ifdef _CTK_ASSERT_ABORT_ON
#define CTK_ASSERT__(x) assert(x)
#else
#define CTK_ASSERT__(x)
#endif

#define CTK_USER_ASSERT_FAIL__(_log_, cond, act) ctk::assertFailure(_log_, cond, CTK_CURRENT, act)
#define CTK_USER_ENSURE_FAIL__(_log_, cond, act) ctk::ensureFailure(_log_, cond, CTK_CURRENT, act)

#ifdef _CTK_ASSERT_ON

#define CTK_USER_ASSERT_CURR(_log_, cond, CURR) do { \
            if (!(cond)) ctk::assertFailure(_log_, #cond, CURR, ""); \
            CTK_ASSERT__(cond); \
        } while(0)

// 调试版本，条件为false时会退出程序(core dump) //
#define CTK_USER_ASSERT(_log_, cond) do { \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, #cond, ""); \
            CTK_ASSERT__(cond); \
        } while(0)

#define CTK_USER_ASSERT_MSG(_log_, cond, msg) do { \
            std::ostringstream oss_; oss_ << #cond << ", " << msg; \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, oss_.str().c_str(), ""); \
            CTK_ASSERT__(cond); \
        } while(0)

// 断言不成立时，调试版退出，发布版执行action //
#define CTK_USER_ASSERT_ACT(_log_, cond, action) do { \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, #cond, #action); \
            CTK_ASSERT__(cond); \
            if (!(cond)) { action; } \
        } while(0)

// 断言不成立时，调试版退出，发布版返回一个值 //
#define CTK_USER_ASSERT_RET(_log_, cond, val) do { \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, #cond, "return " #val); \
            CTK_ASSERT__(cond); \
            if (!(cond)) { return(val); } \
        } while(0)

// 用户有容错处理，条件为false时可以继续运行，只是起个提示作用 //
#define CTK_USER_ENSURE(_log_, cond) do { \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, #cond, ""); \
        } while(0)

#define CTK_USER_ENSURE_MSG(_log_, cond, msg) do { \
            std::ostringstream oss_; oss_ << #cond << ", " << msg; \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, oss_.str().c_str(), ""); \
        } while(0)

// 条件为false时执行用户提供的action，可能继续运行 //
#define CTK_USER_ENSURE_ACT(_log_, cond, action) do { \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, #cond, #action); \
            if (!(cond)) { action; } \
        } while(0)

// 条件为false时返回 //
#define CTK_USER_ENSURE_RET(_log_, cond, val) do { \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, #cond, "return " #val); \
            if (!(cond)) { return(val); } \
        } while(0)

#else

#define CTK_USER_ASSERT_CURR(_log_, cond, CURR) do; while(0)
#define CTK_USER_ASSERT(_log_, cond) do; while(0)
#define CTK_USER_ASSERT_MSG(_log_, cond, msg) do; while(0)
#define CTK_USER_ASSERT_ACT(_log_, cond, action) do { if (!(cond)) { action; } } while(0)
#define CTK_USER_ASSERT_RET(_log_, cond, val) do { if (!(cond)) { return val; } } while(0)
#define CTK_USER_ENSURE(_log_, cond) do ; while(0)
#define CTK_USER_ENSURE_MSG(_log_, cond, msg) do ; while(0)
#define CTK_USER_ENSURE_ACT(_log_, cond, action) do { if (!(cond)) { action; } } while(0)
#define CTK_USER_ENSURE_RET(_log_, cond, val) do { if (!(cond)) { return val; } } while(0)

#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//              调试日志宏                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// CTK_USER_DEBUG_LOG(log, x)
// CTK_USER_TRACE_LOG(log, x)
// CTK_USER_DATA_LOG(log, x)
// CTK_USER_CMD_LOG(log, x)
// CTK_USER_COMM_LOG(log, x)

// CTK_USER_INFO_LOG(log, x)
// CTK_USER_NOTICE_LOG(log, x)
// CTK_USER_WARN_LOG(log, x)
// CTK_USER_ERROR_LOG(log, x)
// CTK_USER_FATAL_LOG(log, x)
// CTK_USER_EXCPT_LOG(log, x)

// CTK_USER_THROW(log, ex)
// CTK_USER_THROW_STD(log, ex)
// CTK_USER_THROW_RET(log, ex, ret)
// CTK_USER_THROW_STD_RET(log, ex, ret)
// CTK_USER_TODO(_log_)
// CTK_USER_ASSERT_THROW(_log_, cond, ex)
// CTK_USER_ASSERT_NOTNULL(_log_, ptr)

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_DATA_LOG(l, x) \
        do { \
            if (l.debugOn() && l.dataLogOn()) { \
                std::ostringstream _oss_; _oss_ << x; \
                ctk::writeDataLog(l, CTK_CURRENT, _oss_.str().c_str()); \
            } \
        } while(0)

#define CTK_USER_DEBUG_LOG_ON_X__(l, t, on, x) \
        do { \
            if (l.debugOn() && on) { \
                std::ostringstream _oss_; _oss_ << x; \
                ctk::writeDebugLog(l, CTK_CURRENT, _oss_.str().c_str(), t); \
            } \
        } while(0)
#define CTK_USER_DEBUG_LOG_X(l, t, x)   CTK_USER_DEBUG_LOG_ON_X__(l, t,                    l.logOn(t),     x)
#define CTK_USER_DEBUG_LOG(l, x)        CTK_USER_DEBUG_LOG_ON_X__(l, ctk::log::TYPE_DEBUG, l.debugLogOn(), x)
#define CTK_USER_TRACE_LOG(l, x)        CTK_USER_DEBUG_LOG_ON_X__(l, ctk::log::TYPE_TRACE, l.traceLogOn(), x)
#define CTK_USER_DIAG_LOG(l, x)         CTK_USER_DEBUG_LOG_ON_X__(l, ctk::log::TYPE_DIAG,  l.diagLogOn(),  x)
#define CTK_USER_CMD_LOG(l, x)          CTK_USER_DEBUG_LOG_ON_X__(l, ctk::log::TYPE_CMD,   l.cmdLogOn(),   x)
#define CTK_USER_COMM_LOG(l, x)         CTK_USER_DEBUG_LOG_ON_X__(l, ctk::log::TYPE_COMM,  l.commLogOn(),  x)
#define CTK_USER_HB_LOG(l, x)           CTK_USER_DEBUG_LOG_ON_X__(l, ctk::log::TYPE_HB,    l.hbLogOn(),    x)

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_INFO_LOG_X__(l, t, on, x) do { \
            if (on) { \
                std::ostringstream _oss_; _oss_ << x; \
                ctk::writeInfoLog(l, CTK_CURRENT, _oss_.str().c_str(), t); \
            } \
        } while(0)
#define CTK_USER_INFO_LOG_X(l, t, x)    CTK_USER_INFO_LOG_X__(l, t,                     l.logOn(t), x)
#define CTK_USER_INFO_LOG(l, x)         CTK_USER_INFO_LOG_X__(l, ctk::log::TYPE_INFO,   l.infoOn(),   x)

#define CTK_USER_NOTICE_LOG_X(l, t, x)  CTK_USER_INFO_LOG_X__(l, t,                     true,         x)
#define CTK_USER_NOTICE_LOG(l, x)       CTK_USER_INFO_LOG_X__(l, ctk::log::TYPE_NOTICE, true,         x)

#define CTK_USER_TIME_LOG_X__(l, t, on, x) do { \
            if (l.debugOn() && on) { \
                std::ostringstream _oss_; _oss_ << x; \
                ctk::writeInfoLog(l, CTK_CURRENT, _oss_.str().c_str(), t); \
            } \
        } while(0)
#define CTK_USER_TIME_LOG_X(l, t, x)    CTK_USER_TIME_LOG_X__(l, t,                     l.logOn(t), x)

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_ERROR_LOG_X(_log_, type, x) do { \
            std::ostringstream oss_info; oss_info << x; \
            ctk::writeErrorLog(_log_, CTK_CURRENT, oss_info.str().c_str(), type); \
        } while(0)
#define CTK_USER_WARN_LOG(_log_, x)     CTK_USER_ERROR_LOG_X(_log_, ctk::log::TYPE_WARN, x)
#define CTK_USER_ERROR_LOG(_log_, x)    CTK_USER_ERROR_LOG_X(_log_, ctk::log::TYPE_ERROR, x)
#define CTK_USER_FATAL_LOG(_log_, x)    CTK_USER_ERROR_LOG_X(_log_, ctk::log::TYPE_FATAL, x)

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_EXCPT_LOG(_log_, ex) do { \
            std::ostringstream oss_info; oss_info << ex; \
            ctk::writeExcptLog(_log_, CTK_CURRENT, oss_info.str().c_str()); \
        } while(0)

///////////////////////////////////////////////////////////////////////////////

#define CTK_THROW_ANYWAY(ex) throw ex(CTK_CURRENT, #ex)

#define CTK_RETHROW throw
#ifdef _DEBUG
#define CTK_RETHROW_AT_DEBUG throw
#else
#define CTK_RETHROW_AT_DEBUG
#endif

#if defined(_CTK_THROW_REALLY) && _CTK_THROW_REALLY
#define CTK_USER_THROW__(_log_, ex, msg) do { \
            ctk::String __s__; __s__ << #ex << ": " << msg; \
            ctk::exceptionThrown(_log_, CTK_CURRENT, __s__.c_str()); \
            throw ex(CTK_CURRENT, __s__.c_str()); \
        } while(0)
#define CTK_USER_THROW_STD__(_log_, ex, msg) do { \
            ctk::String __s__; __s__ << #ex << ": " << msg; \
            ctk::exceptionThrown(_log_, CTK_CURRENT, __s__.c_str()); \
            throw ex(__s__.c_str()); \
        } while(0)
#define CTK_USER_THROW_MSG(_log_, ex, msg)              CTK_USER_THROW__(_log_, ex, msg)
#define CTK_USER_THROW_MSG_STD(_log_, ex, msg)          CTK_USER_THROW_STD__(_log_, ex, msg)
#define CTK_USER_THROW_MSG_RET(_log_, ex, msg, ret)     CTK_USER_THROW_MSG(_log_, ex, msg)
#define CTK_USER_THROW_MSG_STD_RET(_log_, ex, msg, ret) CTK_USER_THROW_MSG_STD(_log_, ex, msg)
#else
#define CTK_USER_THROW_ACT__(_log_, ex, msg, act) do { \
            CTK_USER_INFO_LOG(_log_, "Following exception will be thrown in real world."); \
            ctk::String __s__; __s__ << #ex << ": " << msg; \
            ctk::exceptionThrown(_log_, CTK_CURRENT, __s__.c_str()); \
            act; \
        } while(0)
#define CTK_USER_THROW_MSG(_log_, ex, msg)              CTK_USER_THROW_ACT__(_log_, ex, msg, )
#define CTK_USER_THROW_MSG_STD(_log_, ex, msg)          CTK_USER_THROW_ACT__(_log_, ex, msg)
#define CTK_USER_THROW_MSG_RET(_log_, ex, msg, ret)     CTK_USER_THROW_ACT__(_log_, ex, msg, return ret)
#define CTK_USER_THROW_MSG_STD_RET(_log_, ex, msg, ret) CTK_USER_THROW_RET(_log_, ex, msg, ret)
#endif
#define CTK_USER_THROW(_log_, ex)                       CTK_USER_THROW_MSG(_log_, ex, #ex)
#define CTK_USER_THROW_STD(_log_, ex)                   CTK_USER_THROW_MSG_STD(_log_, ex, #ex)
#define CTK_USER_THROW_RET(_log_, ex, ret)              CTK_USER_THROW_MSG_RET(_log_, ex, #ex, ret)
#define CTK_USER_THROW_STD_RET(_log_, ex, ret)          CTK_USER_THROW_MSG_STD_RET(_log_, ex, #ex, ret)

#define CTK_USER_ASSERT_THROW_MSG(_log_, cond, ex, msg) CTK_USER_ASSERT_ACT(_log_, cond, CTK_USER_THROW_MSG(_log_, ex, msg))
#define CTK_USER_ASSERT_THROW(_log_, cond, ex)          CTK_USER_ASSERT_THROW_MSG(_log_, cond, ex, #ex)
#define CTK_USER_ASSERT_NOTNULL(_log_, ptr)             CTK_USER_ASSERT_THROW(_log_, ptr!=0, ctk::NullPointerException)

#define CTK_USER_TODO(_log_)                            CTK_USER_THROW(_log_, ctk::ToBeDoneException)

namespace ctk
{
    namespace log {
        
        const pcstr TYPE_DEBUG = "DEBUG";
        const pcstr TYPE_TRACE = "TRACE";
        const pcstr TYPE_DATA = "DATA";
        const pcstr TYPE_DIAG = "DIAG";
        const pcstr TYPE_COMM = "COMM";
        const pcstr TYPE_CMD = "CMD";
        const pcstr TYPE_HB = "HB";

        const pcstr TYPE_INFO = "INFO";
        const pcstr TYPE_NOTICE = "NOTICE";

        const pcstr TYPE_WARN = "<WARNING>";
        const pcstr TYPE_ERROR = "<ERROR>";
        const pcstr TYPE_FATAL = "<FATALERROR>";

    }
}

#endif // _Z_CTK_BASE_USER_LOG_MACROS_H_


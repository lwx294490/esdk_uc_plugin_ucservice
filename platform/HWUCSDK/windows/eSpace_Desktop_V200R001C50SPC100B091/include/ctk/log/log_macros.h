/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_BASE_MACROS_H_
#define _Z_CTK_LOG_BASE_MACROS_H_

#include "ctk/ctk_config.h"

#define CTK_DUMP_MAX_SIZE CTK_LOGGER().getMaxStringSize()

// 用于辅助日志记载 //

#define CTK_DUMP(_os_, _type_) \
            std::ostringstream __oss__; \
            __oss__ << _type_; \
            ctk::dumper::_Entry __dump_entry__(_os_, __oss__.str())

#define DUMP_SUP(_d, _Super) \
            do { \
                _d << ctk::indent; \
                if (!_d.compact()) { \
                    DUMP_RAW(_d, #_Super " = "); \
                } \
                _Super::dump(_d); \
            } while(0)

#define DUMP_ONE(_os_, _name_, _var_, _sep_) \
            do { \
                _os_ << ctk::indent; \
                _os_ << ctk::namestring(_name_, _sep_); \
                _os_ << _var_;\
                _os_ << ctk::endline;\
            } while (0)

#define DUMP_VAL(_os_, _val_) \
            do { \
                _os_ << ctk::indent; \
                _os_ << _val_;\
                _os_ << ctk::endline;\
            } while (0)

#define DUMP_ARR(_os_, _var_, _size_) \
            do { \
                _os_ << ctk::indent; \
                _os_ << ctk::namestring(#_var_, 0); \
                _os_ << ctk::make_array_ref(&_var_[0], _size_); \
                _os_ << ctk::endline; \
            } while(0)

#define DUMP_RAW(_os_, _msg_) _os_ << ctk::rawstring(_msg_)

#define DUMP_VAR(_os_, _var_)            DUMP_ONE(_os_, #_var_, _var_, 0)

#define DUMP_NVL(_os_, _name_, _val_)    DUMP_ONE(_os_, #_name_, _val_, 0)

#define DUMP_INT(_os_, _var_)            DUMP_ONE(_os_, #_var_, (int)_var_, 0)

#define DUMP_HEX(_os_, _var_, _maxsize_) DUMP_ONE(_os_, #_var_, ctk::hexdata(_var_, _maxsize_), 0)

#define DUMP_BUF(_os_, _var_, _maxsize_) DUMP_ONE(_os_, #_var_, ctk::istr(_var_, _maxsize_), 0)

#define DUMP_STR(_os_, _var_, _maxsize_) DUMP_BUF(_os_, _var_, _maxsize_)

#define DUMP_PTR(_os_, _ptr_) do { if (_ptr_) DUMP_NVL(_os_, _ptr_, *_ptr_); else DUMP_NVL(_os_, _ptr_, ctk::rawstring("null")); } while(0)

#define DUMP_VAR_(d, v) DUMP_NVL(d, v, v##_)

//////////////////////////////////////////////////////////////////////////////

#define CTK_TIME ctk::Time::now().toDateTime().c_str()

#define CTK_COMPILE_TIME __DATE__ " " __TIME__

#define COUT(x)     CTK_OUT(x)
#define COUTL(x)    CTK_OUT(x<<std::endl)
#define COUT_NL()   CTK_OUT(std::endl)

#define CLOG(x)     CTK_LOG(x)
#define CLOGL(x)    CTK_LOG(x<<std::endl)
#define CLOG_NL(x)  CTK_LOG(std::endl)

#define CLOG2(x)    CTK_LOG2(x)
#define CLOGL2(x)   CTK_LOG2(x<<std::endl)
#define CLOG_NL2(x) CTK_LOG2(std::endl)

#define OSOUT(os, x)    do { os << x; } while(0)
#define OSOUTL(os, x)   OSOUT(os, x << std::endl)
#define OS_NL(os)       OSOUT(os, std::endl)

#define OSNV(os, n, v)  OSOUTL(os, "    " << n << "(" << v << ")")
#define OSVARL(os, x)   OSNV(os, #x, x)
#define OSEXPR(os, x)   OSVARL(os, (x))

#define CNVL(n, v)      OSNV(ctk::std_log(), n, v)
#define CVARL(x)        OSVARL(ctk::std_log(), x)
#define CEXPR(x)        CVARL((x))

#define OUT_HEX(_i_, _f_, _w_) std::hex << std::setfill(_f_) \
                            << std::setw(_w_) << _i_ \
                            << std::setfill(ctk::C_space) << std::dec

#ifndef CTK_MAX_DEBUG_LINE_LEN
#define CTK_MAX_DEBUG_LINE_LEN 118
#endif

namespace ctk {

    typedef ctk::dumper& (*__dumper_fn)(ctk::dumper&);
    inline ctk::dumper& operator<<(ctk::dumper& _os, __dumper_fn _fn)
    {
        return _fn(_os);
    }

    CTK_API ctk::dumper& indent(ctk::dumper& _os);
    CTK_API ctk::dumper& endline(ctk::dumper& _os);
    CTK_API ctk::dumper& nl(ctk::dumper& _os);

}

#endif//_Z_CTK_LOG_BASE_MACROS_H_


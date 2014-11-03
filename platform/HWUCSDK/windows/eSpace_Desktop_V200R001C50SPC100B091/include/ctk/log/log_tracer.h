/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_TRACER_H_
#define _Z_CTK_LOG_TRACER_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

#include "ctk/log/macros.h"

// 跟踪记录函数调用栈 //

#define CTK_TRACER() (*ctk::tracer::instance())

namespace ctk
{
    // trace helper

    class CTK_API tracer
    {
    public:
        typedef tracer _Self;
        typedef Current Item;
        typedef CallStack::_Stack stack_type;
        typedef stack_type::container_type seq_type;
        typedef seq_type::const_reverse_iterator const_reverse_iterator;

    public:
        void push(CTK_CURRENT_ARGS);
        void pop();

        const _Self& separator(pcstr _sep) const;
        istr separator() const;

        stack_type& container();
        const stack_type& container() const;

        CallStack& callStack();
        const CallStack& callStack() const;

        void destroy_current_stack();

        CTK_STATIC_FUN tracer*& instance();
        CTK_STATIC_FUN void destroy();

        std::ostream& dump(std::ostream& os) const;
        ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        friend tracer* ctk::allocate_no_mlc<tracer>(CTK_CURRENT_ARGS);
        friend void ctk::destroy_no_mlc<tracer>(tracer*&, CTK_CURRENT_ARGS);
        tracer();
        ~tracer();
    };
    inline ::std::ostream& operator<<(::std::ostream& os, const ::ctk::tracer& v)
    {
        return v.dump(os);
    }
    inline ::ctk::dumper& operator<<(::ctk::dumper& os, const ::ctk::tracer& v)
    {
        return v.dump(os);
    }

    CTK_API dumper& operator<<(dumper& os, const CallStack& v);
    CTK_API dumper& operator<<(dumper& os, const Current& v);

    CTK_API void printTraceStack(std::ostream&);

} // namespace ctk

#endif//_Z_CTK_LOG_TRACER_H_


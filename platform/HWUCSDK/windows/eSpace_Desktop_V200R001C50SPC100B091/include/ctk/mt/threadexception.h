/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_THREADEXCEPTION_H_
#define _Z_CTK_THREADEXCEPTION_H_

#include "ctk/ctk_config.h"

#include "ctk/base/exception.h"

namespace ctk
{

    class CTK_API NullHandleException : public Exception
    {
        typedef Exception _Super;

    public:
        NullHandleException(CTK_CURRENT_ARGS);

    };

    class CTK_API ThreadSyscallException : public Exception
    {
        typedef Exception _Super;

    public:
        ThreadSyscallException(CTK_CURRENT_ARGS, int _err);

        virtual void dump(std::ostream&) const;

        int error() const;

    private:
        const int error_;

    };

    class CTK_API ThreadLockedException : public Exception
    {
        typedef Exception _Super;

    public:
        ThreadLockedException(CTK_CURRENT_ARGS);

    };

    class CTK_API ThreadStartedException : public Exception
    {
        typedef Exception _Super;

    public:
        ThreadStartedException(CTK_CURRENT_ARGS);

    };

    class CTK_API ThreadNotStartedException : public Exception
    {
        typedef Exception _Super;

    public:
        ThreadNotStartedException(CTK_CURRENT_ARGS);

    };

    class CTK_API DeadlockException : public Exception
    {
        typedef Exception _Super;

    public:
        DeadlockException(CTK_CURRENT_ARGS);

    };

} // end of namespace ctk

#endif //_Z_CTK_THREADEXCEPTION_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_EXCEPTION_H_
#define _Z_CTK_EXCEPTION_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_current.h"

#include <stdexcept>

#ifdef _STLP_NOTHROW_INHERENTLY
#define CTK_NOTHROW _STLP_NOTHROW_INHERENTLY
#else
#ifdef _THROW0
#define CTK_NOTHROW _THROW0()
#else
#define CTK_NOTHROW throw ()
#endif
#endif

namespace std
{
    CTK_API ostream& operator<<(ostream& os, const exception& e);
}

namespace ctk
{
    // Exceptions

    struct CTK_API Exception : public std::exception
    {
        typedef std::exception _Super;

        Exception(CTK_CURRENT_ARGS, pcstr _name, pcstr _msg);
        virtual ~Exception() CTK_NOTHROW;

        const Current& info() const;
        pcstr file() const;
        uint  line() const;
        pcstr func() const;

        const CallStack& stack() const;

        pcstr name() const;
        pcstr msg() const;

        virtual pcstr what() const CTK_NOTHROW;

        virtual void dump(std::ostream& _os) const;
        
    private:
        std::string name_;

        Current info_;

        CallStack stack_;

        std::string msg_;

        mutable std::string str_;

    };

    struct CTK_API OutOfRangeException : public Exception
    {
        typedef Exception _Super;

        OutOfRangeException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    struct CTK_API EmptyDataException : public Exception
    {
        typedef Exception _Super;

        EmptyDataException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    struct CTK_API InvalidDataException : public Exception
    {
        typedef Exception _Super;

        InvalidDataException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    struct CTK_API UnsupportedFunctionException : public Exception
    {
        typedef Exception _Super;

        UnsupportedFunctionException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    struct CTK_API ToBeDoneException : public Exception
    {
        typedef Exception _Super;

        ToBeDoneException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    struct CTK_API NullPointerException : public Exception
    {
        typedef Exception _Super;

        NullPointerException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    struct CTK_API DuplicatedUnitException: public Exception
    {
        typedef Exception _Super;

        DuplicatedUnitException(CTK_CURRENT_ARGS, pcstr _msg=ctk::S_empty);

    };

    typedef Exception ExceptionBase;

}

#endif //_Z_CTK_EXCEPTION_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_WCHAR_H_
#define _Z_CTK_UTIL_TYPE_WCHAR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"

#include "ctk/util/util_func.h"

namespace ctk
{
    class CTK_API Wchar
    {
    public:
        typedef Wchar _Self;
        typedef wchar value_type;

    private:
        value_type value_;

    public:
        Wchar()
            : value_(0)
        {
        }
        Wchar(value_type _v)
            : value_(_v)
        {
        }
        explicit Wchar(rcstr _s)
        {
            fromString(_s);
        }
        explicit Wchar(rcwstr _s)
        {
            fromString(ctk::to_ansi(_s));
        }

        _Self& fromString(rcstr _s)
        {
            int32 v = 0;
            _s >> v;
            value_ = static_cast<value_type>(v);
            return *this;
        }

        String toString() const
        {
            String ret;
            ret << (int32)value_;
            return ret;
        }

        _Self& operator=(value_type _v)
        {
            value_ = _v;
            return *this;
        }

        operator value_type& ()
        {
            return value_;
        }

        operator value_type () const
        {
            return value_;
        }

        value_type& value()
        {
            return value_;
        }

        value_type value() const
        {
            return value_;
        }

    public:
        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    }; // Wchar
    inline std::ostream& operator<<(std::ostream& os, const Wchar& v)
    {
        return v.dump(os);
    }

}

#endif //_Z_CTK_UTIL_WCHAR_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_BIT_H_
#define _Z_CTK_UTIL_TYPE_BIT_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"

#include "ctk/util/util_func.h"

namespace ctk
{
    class CTK_API Bit
    {
    public:
        typedef Bit _Self;
        typedef bool value_type;

    private:
        value_type value_;

    public:
        CTK_STATIC_CONST value_type MAX_VAL = true;
        CTK_STATIC_CONST value_type MIN_VAL = false;

    public:
        Bit()
            : value_(0)
        {
        }
        Bit(value_type _v)
            : value_(_v)
        {
        }
        explicit Bit(rcstr _s)
        {
            fromString(_s);
        }
        explicit Bit(rcwstr _s)
        {
            fromString(ctk::to_ansi(_s));
        }

        _Self& fromString(rcstr _s)
        {
            int16 v = 0;
            _s >> v;
            value_ = static_cast<value_type>(v);
            return *this;
        }

        String toString() const
        {
            String ret;
            ret << (int16)value_;
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
        std::ostream& dump(std::ostream& _os) const
        {
            return _os << (value_?"true":"false");
        }

    }; // Ulonglong
    inline std::ostream& operator<<(std::ostream& os, const Bit& v)
    {
        return os << v.value();
    }

}

#endif //_Z_CTK_UTIL_BIT_H_


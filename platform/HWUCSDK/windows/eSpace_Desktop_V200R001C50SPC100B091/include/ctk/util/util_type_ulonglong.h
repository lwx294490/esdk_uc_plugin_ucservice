/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_ULONGLONG_H_
#define _Z_CTK_UTIL_TYPE_ULONGLONG_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"

#include "ctk/util/util_func.h"

namespace ctk
{
    class CTK_API Ulonglong
    {
    public:
        typedef Ulonglong _Self;
        typedef uint64 value_type;
        typedef uint32 half_type;

    private:
        value_type value_;

    public:
        CTK_STATIC_CONST value_type MAX_VAL = 18446744073709551615ULL;
        CTK_STATIC_CONST value_type MIN_VAL = 0ULL;
        CTK_STATIC_CONST half_type HALF_MASK = 0xFFFFFFFF;
        CTK_STATIC_CONST half_type HALF_BITS = 32;
        CTK_STATIC_CONST value_type LOW_MASK = value_type(HALF_MASK);
        CTK_STATIC_CONST value_type HIGH_MASK = value_type(~LOW_MASK);

    public:
        Ulonglong()
            : value_(0)
        {
        }
        Ulonglong(value_type _v)
            : value_(_v)
        {
        }
        Ulonglong(half_type _low, half_type _high)
            : value_((_low&HALF_MASK) | (value_type(_high&HALF_MASK)<<HALF_BITS))
        {
        }
        explicit Ulonglong(rcstr _s)
        {
            fromString(_s);
        }
        explicit Ulonglong(rcwstr _s)
        {
            fromString(ctk::to_ansi(_s));
        }

        _Self& fromString(rcstr _s)
        {
            _s >> value_;
            return *this;
        }

        String toString() const
        {
            String ret;
            ret << value_;
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

        _Self& low(half_type c)
        {
            value_ &= ~ LOW_MASK;
            value_ |= c & LOW_MASK;
            return *this;
        }

        _Self& high(half_type c)
        {
            value_ &= ~ HIGH_MASK;
            value_ |= (value_type(c) << HALF_BITS) & HIGH_MASK;
            return *this;
        }

        half_type low() const
        {
            return half_type(value_ & LOW_MASK);
        }

        half_type high() const
        {
            return half_type((value_ >> HALF_BITS) & HALF_MASK);
        }

    public:
        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const
        {
            return _os << print(value_);
        }

    }; // Ulonglong
    inline std::ostream& operator<<(std::ostream& os, const Ulonglong& v)
    {
        return os << v.value();
    }

}

#endif //_Z_CTK_UTIL_ULONGLONG_H_


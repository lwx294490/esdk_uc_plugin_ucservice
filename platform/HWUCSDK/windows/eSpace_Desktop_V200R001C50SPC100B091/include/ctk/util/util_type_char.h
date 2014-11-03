/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_CHAR_H_
#define _Z_CTK_UTIL_TYPE_CHAR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"

#include "ctk/util/util_func.h"

namespace ctk
{
    class CTK_API Char
    {
    public:
        typedef Char _Self;
        typedef char value_type;
        typedef byte half_type;

    private:
        value_type value_;

    public:
        CTK_STATIC_CONST value_type MAX_VAL = 127;
        CTK_STATIC_CONST value_type MIN_VAL = -MAX_VAL-1;
        CTK_STATIC_CONST half_type HALF_MASK = 0x0F;
        CTK_STATIC_CONST half_type HALF_BITS = 4;
        CTK_STATIC_CONST value_type LOW_MASK = value_type(HALF_MASK);
        CTK_STATIC_CONST value_type HIGH_MASK = value_type(~LOW_MASK);

    public:
        Char()
            : value_(0)
        {
        }
        Char(value_type _v)
            : value_(_v)
        {
        }
        Char(half_type _low, half_type _high)
            : value_((_low&HALF_MASK) | (value_type(_high&HALF_MASK)<<HALF_BITS))
        {
        }
        explicit Char(rcstr _s)
        {
            fromString(_s);
        }
        explicit Char(rcwstr _s)
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

        _Self operator-() const
        {
            return _Self(-value_);
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
        _Self& fromHex(byte _v)
        {
            value() = ctk::HexToChar(_v);
            return *this;
        }

        byte toHex() const
        {
            return ctk::HexFromChar(value());
        }

        bool isSpace() const
        {
            return ctk::CharIsSpace(value());
        }

        bool isPrint() const
        {
            return ctk::CharIsPrint(value());
        }

        bool isCntrl() const
        {
            return ctk::CharIsCntrl(value());
        }

        bool isUpper() const
        {
            return ctk::CharIsUpper(value());
        }

        bool isLower() const
        {
            return ctk::CharIsLower(value());
        }

        bool isAlpha() const
        {
            return ctk::CharIsAlpha(value());
        }

        bool isDigit() const
        {
            return ctk::CharIsDigit(value());
        }

        bool isPunct() const
        {
            return ctk::CharIsPunct(value());
        }

        bool isXdigit() const
        {
            return ctk::CharIsXdigit(value());
        }

        bool isAlnum() const
        {
            return ctk::CharIsAlnum(value());
        }

        bool isGraph() const
        {
            return ctk::CharIsGraph(value());
        }

        _Self toLower() const
        {
            return _Self(CharToLower(value()));
        }

        _Self toUpper() const
        {
            return _Self(CharToUpper(value()));
        }

        bool in(istr _s) const
        {
            value_type c = value();
            if (!c)
                return true;
            pcstr p = _s.data();
            while (*p && c!=*p)
                ++p;
            return *p!=0;
        }

    public:
        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const
        {
            return _os << print(value_);
        }

    }; // Char
    inline std::ostream& operator<<(std::ostream& os, const Char& v)
    {
        return os << v.value();
    }

}

#endif //_Z_CTK_UTIL_CHAR_H_


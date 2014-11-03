/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_BYTE_H_
#define _Z_CTK_UTIL_TYPE_BYTE_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"

#include "ctk/util/util_func.h"

namespace ctk
{
    class CTK_API Byte
    {
    public:
        typedef Byte _Self;
        typedef byte value_type;
        typedef byte half_type;

    private:
        value_type value_;

    public:
        CTK_STATIC_CONST value_type MAX_VAL = 255;
        CTK_STATIC_CONST value_type MIN_VAL = 0;
        CTK_STATIC_CONST half_type HALF_MASK = 0x0F;
        CTK_STATIC_CONST half_type HALF_BITS = 4;
        CTK_STATIC_CONST value_type LOW_MASK = value_type(HALF_MASK);
        CTK_STATIC_CONST value_type HIGH_MASK = value_type(~LOW_MASK);

        enum BitNo
        {
            BIT_A = 0,
            BIT_B = 1,
            BIT_C = 2,
            BIT_D = 3,
            BIT_E = 4,
            BIT_F = 5,
            BIT_G = 6,
            BIT_H = 7
        };
        enum BitMask
        {
            MASK_A = 1<<BIT_A,
            MASK_B = 1<<BIT_B,
            MASK_C = 1<<BIT_C,
            MASK_D = 1<<BIT_D,
            MASK_E = 1<<BIT_E,
            MASK_F = 1<<BIT_F,
            MASK_G = 1<<BIT_G,
            MASK_H = 1<<BIT_H
        };

    public:
        Byte()
            : value_(0)
        {
        }
        Byte(value_type _v)
            : value_(_v)
        {
        }
        Byte(half_type _low, half_type _high)
            : value_((_low&HALF_MASK) | (value_type(_high&HALF_MASK)<<HALF_BITS))
        {
        }
        explicit Byte(rcstr _s)
        {
            fromString(_s);
        }
        explicit Byte(rcwstr _s)
        {
            fromString(ctk::to_ansi(_s));
        }

        _Self& fromString(rcstr _s)
        {
            uint16 v = 0;
            _s >> v;
            value_ = static_cast<value_type>(v);
            return *this;
        }

        String toString() const
        {
            String ret;
            ret << (uint16)value_;
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
        struct BitHelper
        {
            typedef BitHelper _Self;

            BitHelper(byte& _v, byte _n):v_(_v), n_(_n){}
            BitHelper(const byte& _v, byte _n):v_(const_cast<byte&>(_v)), n_(_n){}

            operator bool() const
            {
                return ((v_ >> n_) & 0x1) == 1;
            }

            _Self& operator=(bool _v)
            {
                byte mask = byte(1) << n_;
                v_ &= ~mask;
                if (_v)
                    v_ |= mask;
                return *this;
            }

            byte& v_;
            byte n_;

        private:
            _Self& operator=(const _Self&);
        };

        BitHelper operator[](byte _bit_no)
        {
            return BitHelper(value_, _bit_no);
        }

        bool operator[](byte _bit_no) const
        {
            return BitHelper(value_, _bit_no);
        }

        _Self& set(byte _bit_no, bool _v=true)
        {
            (*this)[_bit_no] = _v;
            return *this;
        }

        _Self& reset(byte _bit_no)
        {
            (*this)[_bit_no] = false;
            return *this;
        }

        bool get(byte _bit_no) const
        {
            return (*this)[_bit_no];
        }

    public:
        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const
        {
            return _os << print(value_);
        }

    }; // Byte
    inline std::ostream& operator<<(std::ostream& os, const Byte& v)
    {
        return os << (int)v.value();
    }

}

#endif //_Z_CTK_UTIL_BYTE_H_


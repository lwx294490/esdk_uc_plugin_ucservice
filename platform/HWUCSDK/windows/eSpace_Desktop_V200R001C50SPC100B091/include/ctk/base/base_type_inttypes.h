/*
 *  ctk_base_types.h
 *  espace
 *
 *  Created by luyunhai 117629 on 11-6-3.
 *  Copyright 2011 Huawei Technologies Co., Ltd. All rights reserved.
 *
 */
#ifndef _CTK_BASE_TYPES_H_
#define _CTK_BASE_TYPES_H_

#include "ctk/ctk_config.h"

namespace ctk
{
    template<class T, int _DEFAULT_VALUE=0>
    class NumberValue
    {
        typedef T type;
        typedef type & reference;
        typedef type const& const_reference;
        
        type value_;
        
    public:
        NumberValue() : value_((type)_DEFAULT_VALUE) { }
        NumberValue(const_reference _v) : value_(_v) { }
        
        NumberValue& operator=(const_reference _v) { value_ = _v; return *this; }
        
        operator reference() { return value_; }
        operator const_reference() const { return value_; }
        
        reference value() { return value_; }
        const_reference value() const { return value_; }
        
        bool equal(const_reference _v) const { return value_ == _v; }

        ctk::dumper& dump(ctk::dumper& _d) const { _d.internal_stream() << *this; return _d; }
        
    }; // end of class NumberValue<T>
    
    template<class T, int _DEFAULT_VALUE>
    inline std::ostream&
    operator<< (std::ostream& os, const NumberValue<T,_DEFAULT_VALUE>& v)
    {
        return os << v.value();
    }
    template<int _DEFAULT_VALUE>
    inline std::ostream&
    operator<< (std::ostream& os, const NumberValue<int8,_DEFAULT_VALUE>& v)
    {
        return os << (int16)v.value();
    }
    template<int _DEFAULT_VALUE>
    inline std::ostream&
    operator<< (std::ostream& os, const NumberValue<uint8,_DEFAULT_VALUE>& v)
    {
        return os << (uint16)v.value();
    }
    
    template<class T, int _DEFAULT_VALUE>
    inline std::istream&
    operator>> (std::istream& is, NumberValue<T,_DEFAULT_VALUE>& v)
    {
        return is >> v.value();
    }
    template<int _DEFAULT_VALUE>
    inline std::istream&
    operator>> (std::istream& is, NumberValue<int8,_DEFAULT_VALUE>& v)
    {
        int16 i16=0;
        is >> i16;
        v = (int8)i16;
        return is;
    }
    template<int _DEFAULT_VALUE>
    inline std::istream&
    operator>> (std::istream& is, NumberValue<uint8,_DEFAULT_VALUE>& v)
    {
        uint16 i16=0;
        is >> i16;
        v = (uint8)i16;
        return is;
    }

    template<class T>
    inline
    NumberValue<T, 0>
    number(T _value)
    {
        return NumberValue<T, 0>(_value);
    }

    typedef NumberValue<int1>   Int1;
    typedef NumberValue<int8>   Int8;
    typedef NumberValue<uint8>  Uint8;
    typedef NumberValue<int16>  Int16;
    typedef NumberValue<uint16> Uint16;
    typedef NumberValue<int32>  Int32;
    typedef NumberValue<uint32> Uint32;
    typedef NumberValue<int64>  Int64;
    typedef NumberValue<uint64> Uint64;
    typedef NumberValue<float>  Float;
    typedef NumberValue<double> Double;
    
    typedef Int1   Bool;
    typedef Int1   Boolean;
    typedef Int1   Bit;
    typedef Uint8  Uint4;
    typedef Uint8  Byte;
    typedef Int16  Short;
    typedef Uint16 Ushort;
    typedef Int32  Long;
    typedef Uint32 Ulong;
    typedef Int64  Longlong;
    typedef Uint64 Ulonglong;

    typedef Float  Real32;
    typedef Double Real64;
    
} // end of namespace ctk

#endif // _CTK_BASE_TYPES_H_


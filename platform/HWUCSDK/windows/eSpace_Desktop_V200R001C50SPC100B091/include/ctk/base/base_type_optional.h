/*
 *  ctk_base_optional.h
 *  espace
 *
 *  Created by luyunhai 117629 on 11-7-7.
 *  Copyright 2011 Huawei Technologies Co., Ltd. All rights reserved.
 *
 */
#ifndef _CTK_BASE_OPTIONAL_H_
#define _CTK_BASE_OPTIONAL_H_

#include "ctk/ctk_config.h"

namespace ctk
{
    template<class T>
    class Optional
    {
        typedef T type;
        typedef type & reference;
        typedef type const& const_reference;
        
        type value_;
        bool valid_;
        
    public:
        Optional() : valid_(false) { }
        Optional(const_reference _v) : value_(_v), valid_(true) { }
        
        Optional& operator=(const_reference _v) { value_ = _v; valid_ = true; return *this; }
        
        operator reference()             { valid_ = true; return value_; }
        operator const_reference() const { return value_; }
        
        reference       value()       { valid_ = true; return value_; }
        const_reference value() const { return value_; }
        
        bool& valid()       { return valid_; }
        bool  valid() const { return valid_; }
        
    }; // end of class Optional<T>
    
    template<class T>
    inline std::ostream&
    operator<< (std::ostream& os, const Optional<T>& v)
    {
        return os << v.value();
    }
    
    template<class T>
    inline std::string&
    operator<< (std::string& os, const Optional<T>& v)
    {
        return os << v.value();
    }
    
    template<class T>
    inline void
    operator>> (const std::string& is, Optional<T>& v)
    {
        is >> v.value();
    }
    
} // end of namespace ctk

#endif // _CTK_BASE_OPTIONAL_H_


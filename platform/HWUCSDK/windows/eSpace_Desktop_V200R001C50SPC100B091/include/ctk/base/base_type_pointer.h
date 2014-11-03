/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_POINTER_H_
#define _Z_CTK_BASE_TYPE_POINTER_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    template<class T>
    struct Pointer
    {
        typedef Pointer<T> _Self;
        
        Pointer(T* _p=0) : p_(_p) { }
        Pointer(const _Self& _v) : p_(_v.p_) { }
        ~Pointer() { }

        Pointer& operator=(T* _p) { return set(_p); }

        Pointer& operator=(const _Self& _v) { return set(_v.p_); }

        Pointer& set(T* _p) { p_ = _p; return *this; }

        T* operator->() const { return get(); }

        T& operator*() const { return *get(); }

        operator T*() const { return get(); }

        bool operator !() const { return !get(); }

        T* get() const { return p_; }

        T*& ref() { return p_; }

        T* release() { T* p = p_; p_ = 0; return p; }

        void destroy() { delete p_; p_ = 0; }

    private:
        T* p_;
    };

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_POINTER_H_


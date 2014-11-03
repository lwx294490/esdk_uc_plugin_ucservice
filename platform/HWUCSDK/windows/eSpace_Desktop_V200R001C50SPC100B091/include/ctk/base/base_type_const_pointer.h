/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_CONST_POINTER_H_
#define _Z_CTK_BASE_TYPE_CONST_POINTER_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    template<class T>
    struct ConstPointer
    {
        typedef ConstPointer<T> _Self;
        typedef const T* _ConstPtr;
        typedef const T& _ConstRef;
        
        ConstPointer(_ConstPtr _p=0) : p_(_p) { }
        ConstPointer(const _Self& _v) : p_(_v.p_) { }
        ~ConstPointer() { }

        ConstPointer& operator=(_ConstPtr _p) { return set(_p); }

        ConstPointer& operator=(const _Self& _v) { return set(_v.p_); }

        ConstPointer& set(_ConstPtr _p) { p_ = _p; return *this; }

        _ConstPtr operator->() const { return get(); }

        _ConstRef operator*() const { return *get(); }

        operator _ConstPtr () const { return get(); }

        bool operator !() const { return !get(); }

        _ConstPtr get() const { return p_; }

        void destroy() { delete (T*)p_; p_ = 0; }

    private:
        _ConstPtr p_;
    };

} // namespace ctk

#endif // _Z_CTK_BASE_TYPE_CONST_POINTER_H_


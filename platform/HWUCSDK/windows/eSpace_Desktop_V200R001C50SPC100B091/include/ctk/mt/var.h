/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_VAR_H_
#define _Z_CTK_MT_VAR_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/mutex.h"

namespace ctk {
namespace mt {

    template<class T>
    class Var
    {
        typedef Var<T> _Self;
        typedef ctk::Mutex _Mutex;

    private:
        T var_;
        _Mutex mtx_;

    public:
        Var()
            : var_(T())
        {
        }
        Var(const T& _v)
            : var_(_v)
        {
        }
        Var(const _Self& _v)
        {
            _v.get(var_);
        }
        ~Var()
        {
        }

        _Self& operator=(const T& _v)
        {
            set(_v);
            return *this;
        }
        _Self& operator=(const _Self& _v)
        {
            if (this==&_v)
                return *this;
            set(_v);
            return *this;
        }

        void set(const T& _v)
        {
            _Mutex::Lock __lck(mtx_);
            var_ = _v;
        }

        void set(const _Self& _v)
        {
            _Mutex::Lock __lck(mtx_);
            _v.get(var_);
        }

        void get(T& _v) const
        {
            _Mutex::Lock __lck(mtx_);
            _v = var_;
        }

        T get() const
        {
            _Mutex::Lock __lck(mtx_);
            return var_;
        }

        void swap(T& _v)
        {
            _Mutex::Lock __lck(mtx_);
            ctk::swap(var_, _v);
        }

        void swap(_Self& _v)
        {
            _Mutex::Lock __lck(mtx_);
            _v.swap(var_);
        }

        template <class _Function>
        void
        for_all(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            _f(var_);
        }

        template <class _Function>
        void
        for_all(_Function __f) const
        {
            _Mutex::Lock __lck(mtx_);
            _f(var_);
        }

    };

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_VAR_H_


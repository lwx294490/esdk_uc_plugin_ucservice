/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_SINGLETON_T_H_
#define _Z_CTK_SINGLETON_T_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_system.h"
#include "ctk/base/mlcheck.h"

#include "ctk/mt/mutex.h"
#include "ctk/mt/nullmutex.h"

#define CTK_SINGLETON_INSTANCE(x) (*ctk::Singleton_T<x>::instance(CTK_CURRENT))

#define CTK_DESTROY_SINGLETON(x)  ctk::Singleton_T<x>::destroy()

#define CTK_DECLARE_SINGLETON(x) friend x* ctk::allocate_no_mlc<x>(CTK_CURRENT_ARGS); friend void ctk::destroy_no_mlc<x>(x*&, CTK_CURRENT_ARGS)

namespace ctk
{
    template<class T>
    struct CreateByAllocate
    {
        static T* allocate(CTK_CURRENT_ARGS)
        {
            return ctk::allocate<T>(CTK_CURRENT_VARS);
        }

        static void destroy(T*& _p)
        {
            ctk::destroy(_p, CTK_CURRENT);
        }
    };

    template<class T>
    struct CreateByNew
    {
        static T* allocate(CTK_CURRENT_ARGS)
        {
            return ctk_new T();
        }

        static void destroy(T*& _p)
        {
            delete _p;
            _p = 0;
        }
    };

    template<class T, class _Mutex=ctk::Mutex, template <class> class _CreatePolicy=CreateByAllocate >
        class Singleton_T
        {
        public:
            CTK_STATIC_FUN T*& instance(CTK_CURRENT_ARGS_DEFAULT)
            {
                if (!ptr())
                {
                    typename _Mutex::Lock __lck(mtx());
                    if (!ptr())
                    {
                        ptr() = _CreatePolicy<T>::allocate(CTK_CURRENT_VARS);
                    }
                }
                return ptr();
            }

            CTK_STATIC_FUN void destroy()
            {
                typename _Mutex::Lock __lck(mtx());
                _CreatePolicy<T>::destroy(ptr());
            }

        private:
            CTK_STATIC_FUN _Mutex& mtx()
            {
                CTK_STATIC_VAR _Mutex g__mtx;
                return g__mtx;
            }

            CTK_STATIC_FUN T*& ptr()
            {
                CTK_STATIC_VAR T* g__inst = 0;
                return g__inst;
            }

        private:
            Singleton_T();
            Singleton_T(const Singleton_T&);
            Singleton_T& operator=(const Singleton_T&);
        };

} // end of namespace ctk

#endif //_Z_CTK_SINGLETON_T_H_


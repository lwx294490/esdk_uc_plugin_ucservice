/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_SINGLETON_H_
#define _Z_CTK_SINGLETON_H_

#include "ctk/ctk_config.h"

#include "ctk/util/singleton_T.h"

#define ECS_SINGLETON_INSTANCE(x) (*ctk::Singleton<x>::instance())

#define ECS_DESTROY_SINGLETON(x)  ctk::Singleton<x>::destroy()

#define ECS_DECLARE_SINGLETON(x) friend struct ctk::CreateByNew<x>

namespace ctk
{
    template<class T, class _Mutex=ctk::Mutex>
        class Singleton
        {
        public:
            CTK_STATIC_FUN T*& instance()
            {
                return Singleton_T<T, _Mutex, CreateByNew>::instance();
            }

            CTK_STATIC_FUN void destroy()
            {
                Singleton_T<T, _Mutex, CreateByNew>::destroy();
            }

        private:
            Singleton();
            Singleton(const Singleton&);
            Singleton& operator=(const Singleton&);
        };

} // end of namespace ctk

#endif //_Z_CTK_SINGLETON_H_


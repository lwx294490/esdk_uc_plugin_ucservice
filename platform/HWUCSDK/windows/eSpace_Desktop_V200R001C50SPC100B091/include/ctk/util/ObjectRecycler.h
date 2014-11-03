/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_ObjectRecycler_H_
#define _Z_CTK_ObjectRecycler_H_

#include "ctk/ctk_config.h"

#include "ctk/base/noncopyable.h"
#include "ctk/base/base_type_time.h"
#include "ctk/mt/queue.h"

namespace ctk
{
    template<class T>
    class ObjectRecycler : private ctk::noncopyable
    {
        typedef ctk::mt::queue<T*> _Queue;
        _Queue q_;

        struct fnDeletePtr
        {
            void operator()(T* _p)
            {
                delete _p;
            }
        };

        T emptyObject_;

    public:
        ~ObjectRecycler()
        {
            q_.for_each(fnDeletePtr());
        }

        T* newObj()
        {
            T* p = 0;
            if (q_.get(p, ctk::Time::microSeconds(0)))
            {
                *p = emptyObject_;
                return p;
            }

            return ctk_new T();
        }

        void deleteObj(T*& _p)
        {
            q_.put(_p);
            _p = 0;
        }

    };

} // end of namespace ctk

#endif //_Z_CTK_ObjectRecycler_H_


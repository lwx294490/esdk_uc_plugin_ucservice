/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_MUTEX_H_
#define _Z_CTK_MT_MUTEX_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/lock.h"

#include <ace/Thread_Mutex.h>

namespace ctk
{
    class Mutex
    {
    public:
        typedef Guard_T<Mutex> Lock;
        typedef TryGuard_T<Mutex> TryLock;

        typedef ACE_Thread_Mutex _MutexImpl;

    public:
        Mutex()
        {
        }

        ~Mutex()
        {
        }

        void lock() const
        {
            impl().acquire();
        }

        bool tryLock() const
        {
            return 0 == impl().tryacquire();
        }

        void unlock() const
        {
            impl().release();
        }

        bool willUnlock() const
        {
            return true;
        }

        _MutexImpl& impl() const
        {
            return mtx_;
        }

    private:
        Mutex(const Mutex&);
        Mutex& operator=(const Mutex&);

        mutable _MutexImpl mtx_;

    };

} // end of namespace ctk

#endif //_Z_CTK_MT_MUTEX_H_


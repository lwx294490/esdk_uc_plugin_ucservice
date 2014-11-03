/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_RECMUTEX_H_
#define _Z_CTK_MT_RECMUTEX_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/lock.h"

#include <ace/Recursive_Thread_Mutex.h>

namespace ctk
{
    class RecMutex
    {
    public:
        typedef Guard_T<RecMutex> Lock;
        typedef TryGuard_T<RecMutex> TryLock;

        typedef ACE_Recursive_Thread_Mutex _MutexImpl;

    public:
        RecMutex()
        {
        }

        ~RecMutex()
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
            return impl().get_nesting_level() == 1;
        }

        _MutexImpl& impl() const
        {
            return mtx_;
        }

    private:
        RecMutex(const RecMutex&);
        RecMutex& operator=(const RecMutex&);

        mutable _MutexImpl mtx_;
    };

} // end of namespace ctk

#endif //_Z_CTK_MT_RECMUTEX_H_


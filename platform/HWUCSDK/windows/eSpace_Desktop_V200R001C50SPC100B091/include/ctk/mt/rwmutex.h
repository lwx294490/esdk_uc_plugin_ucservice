/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_RWMUTEX_H_
#define _Z_CTK_MT_RWMUTEX_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/rwlock.h"

#include <ace/RW_Thread_Mutex.h>

namespace ctk
{

    class RWMutex
    {
    public:
        typedef ReadGuard_T<RWMutex> RLock;
        typedef TryReadGuard_T<RWMutex> TryRLock;
        typedef WriteGuard_T<RWMutex> WLock;
        typedef TryWriteGuard_T<RWMutex> TryWLock;

        typedef ACE_RW_Thread_Mutex _MutexImpl;

    public:
        RWMutex()
        {
        }

        ~RWMutex()
        {
        }

        void readLock() const
        {
            impl().acquire_read();
        }

        bool tryReadLock() const
        {
            return 0 == impl().tryacquire_read();
        }

        void writeLock() const
        {
            impl().acquire_write();
        }

        bool tryWriteLock() const
        {
            return 0 == impl().tryacquire_write();
        }

        void unlock() const
        {
            impl().release();
        }

        bool tryUpgrade() const
        {
            return 0 == impl().tryacquire_write_upgrade();
        }

        _MutexImpl& impl() const
        {
            return mtx_;
        }

    private:
        RWMutex(const RWMutex&);
        RWMutex& operator=(const RWMutex&);

        mutable _MutexImpl mtx_;

    };

} // end of namespace ctk

#endif //_Z_CTK_MT_RWMUTEX_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_RWLOCK_H_
#define _Z_CTK_MT_RWLOCK_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/threadexception.h"

namespace ctk
{

    template <typename T>
    class ReadGuard_T
    {
    protected:
        // TryReadGuard_T's constructors
        ReadGuard_T(const T& _mtx, bool)
            : mtx_(_mtx)
        {
            locked_ = mtx_.tryReadLock();
        }

    public:
        ReadGuard_T(const T& _mtx)
            : mtx_(_mtx)
        {
            mtx_.readLock();

            locked_ = true;
        }

        ~ReadGuard_T()
        {
            if (locked_)
            {
                mtx_.unlock();
            }
        }

        void acquire() const
        {
            if (locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }
            
            mtx_.readLock();
            
            locked_ = true;
        }

        bool tryAcquire() const
        {
            if (locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }
            
            locked_ = mtx_.tryReadLock();
            
            return locked_;
        }

        void release() const
        {
            if (!locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }

            mtx_.unlock();

            locked_ = false;
        }

        bool acquired() const
        {
            return locked_;
        }

        bool tryUpgrade() const
        {
            return mtx_.tryUpgrade();
        }

    private:
        ReadGuard_T(const ReadGuard_T&);
        ReadGuard_T& operator=(const ReadGuard_T&);

        const T& mtx_;
        mutable bool locked_;

    };

    template <typename T>
    class TryReadGuard_T : public ReadGuard_T<T>
    {
    public:
        TryReadGuard_T(const T& _mutex)
            : ReadGuard_T<T>(_mutex, true)
        {
        }
    };

    template <typename T>
    class WriteGuard_T
    {
    protected:
        // TryWriteGuard_T's constructor
        WriteGuard_T(const T& mutex, bool)
            : mtx_(mutex)
        {
            locked_ = mtx_.tryWriteLock();
        }

    public:
        WriteGuard_T(const T& _mutex)
            : mtx_(_mutex)
        {
            mtx_.writeLock();

            locked_ = true;
        }

        ~WriteGuard_T()
        {
            if (locked_)
            {
                mtx_.unlock();
            }
        }

        void acquire() const
        {
            if (locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }

            mtx_.writeLock();
            
            locked_ = true;
        }

        bool tryAcquire() const
        {
            if (locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }
            
            locked_ = mtx_.tryWriteLock();
            
            return locked_;
        }

        void release() const
        {
            if (!locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }

            mtx_.unlock();
            
            locked_ = false;
        }

        bool acquired() const
        {
            return locked_;
        }

    private:
        WriteGuard_T(const WriteGuard_T&);
        WriteGuard_T& operator=(const WriteGuard_T&);

        const T& mtx_;
        mutable bool locked_;

    };

    template <typename T>
    class TryWriteGuard_T : public WriteGuard_T<T>
    {
    public:
        TryWriteGuard_T(const T& mutex)
            : WriteGuard_T<T>(mutex, true)
        {
        }
    };

} // end of namespace ctk

#endif //_Z_CTK_MT_RWLOCK_H_


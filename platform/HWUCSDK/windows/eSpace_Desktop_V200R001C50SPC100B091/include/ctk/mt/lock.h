/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_LOCK_H_
#define _Z_CTK_MT_LOCK_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/threadexception.h"

namespace ctk
{
    template <typename T>
    class Guard_T
    {
    protected:
        // TryGuard_T's contructor
        Guard_T(const T& _mtx, bool)
            : mtx_(_mtx)
        {
            locked_ = mtx_.tryLock();
        }

    public:
        Guard_T(const T& _mtx)
            : mtx_(_mtx)
        {
            mtx_.lock();

            locked_ = true;
        }

        ~Guard_T()
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

            mtx_.lock();
            
            locked_ = true;
        }

        bool tryAcquire() const
        {
            if (locked_)
            {
                throw ThreadLockedException(CTK_CURRENT);
            }

            locked_ = mtx_.tryLock();
            
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
        Guard_T(const Guard_T&);
        Guard_T& operator=(const Guard_T&);

        const T& mtx_;
        mutable bool locked_;

    };

    template <typename T>
    class TryGuard_T : public Guard_T<T>
    {
    public:
        TryGuard_T(const T& _mtx)
            : Guard_T<T>(_mtx, true)
        {
        }
    };

} // end of namespace ctk

#endif //_Z_CTK_MT_LOCK_H_


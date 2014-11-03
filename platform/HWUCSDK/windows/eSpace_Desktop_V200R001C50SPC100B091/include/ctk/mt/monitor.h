/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_MONITOR_H_
#define _Z_CTK_MT_MONITOR_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/lock.h"
#include "ctk/mt/cond.h"

namespace ctk
{

    template <class MUTEX>
    class Monitor
    {
    public:
        typedef Guard_T<Monitor<MUTEX> > Lock;
        typedef TryGuard_T<Monitor<MUTEX> > TryLock;

        Monitor()
            : cond_(mtx_), numofNotified_(0)
        {
        }

        ~Monitor()
        {
        }

        void lock() const
        {
            mtx_.lock();

            if(mtx_.willUnlock())
            {
                numofNotified_ = 0;
            }
        }
        
        void unlock() const
        {
            if(mtx_.willUnlock())
            {
                notifyImpl(numofNotified_);
            }

            mtx_.unlock();
        }

        bool tryLock() const
        {
            bool locked = mtx_.tryLock();

            if (locked && mtx_.willUnlock())
            {
                numofNotified_ = 0;
            }

            return locked;
        }

        void wait() const
        {
            notifyImpl(numofNotified_);

            try
            {
                cond_.wait();
            }
            catch(...)
            {
                numofNotified_ = 0;
                throw;
            }

            numofNotified_ = 0;
        }
        
        bool timedWait(const Time& _waitTime) const
        {
            notifyImpl(numofNotified_);

            bool retval;

            try
            {
                retval = cond_.timedWait(_waitTime);
            }
            catch(...)
            {
                numofNotified_ = 0;
                throw;
            }

            numofNotified_ = 0;
            return retval;
        }
        
        void notify()
        {
            if (numofNotified_ != -1)
            {
                ++numofNotified_;
            }
        }

        void notifyAll()
        {
            numofNotified_ = -1;
        }

    private:
        Monitor(const Monitor&);
        Monitor& operator=(const Monitor&);

        void notifyImpl(int _numofNotify) const
        {
            if (_numofNotify != 0)
            {
                if(_numofNotify == -1)
                {
                    cond_.broadcast();
                }
                else
                {
                    while (_numofNotify > 0)
                    {
                        cond_.signal();

                        --_numofNotify;
                    }
                }
            }
        }

        mutable MUTEX mtx_;
        mutable ConditionVariable<MUTEX> cond_;
        mutable int numofNotified_;

    };

} // end of namespace ctk

#endif //_Z_CTK_MT_MONITOR_H_


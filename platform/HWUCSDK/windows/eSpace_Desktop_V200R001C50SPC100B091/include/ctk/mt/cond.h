/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_COND_H_
#define _Z_CTK_MT_COND_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_time.h"

#include "ctk/mt/threadexception.h"

#include <ace/Condition_T.h>

namespace ctk
{

    // MUTEX must be one of Mutex,RecMutex
    template <typename MUTEX>
    class ConditionVariable
    {
    public:
        ConditionVariable(const MUTEX& _mtx)
            : cond_(_mtx.impl())
        {
        }

        ~ConditionVariable()
        {
        }

        void signal() const
        {
            cond_.signal();
        }

        void broadcast() const
        {
            cond_.broadcast();
        }

        void wait() const
        {
            cond_.wait();
        }

        bool timedWait(const Time& _timeout) const
        {
            ACE_Time_Value tv(ctk::Time::now() + _timeout);

            return 0 == cond_.wait(&tv);
        }

    private:
        ConditionVariable(const ConditionVariable&);
        ConditionVariable& operator=(const ConditionVariable&);

        mutable ACE_Condition<typename MUTEX::_MutexImpl> cond_;

    };

} // end of namespace ctk

#endif //_Z_CTK_MT_COND_H_


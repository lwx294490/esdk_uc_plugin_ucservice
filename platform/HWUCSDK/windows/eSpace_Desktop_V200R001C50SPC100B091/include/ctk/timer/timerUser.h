/* CTK(Mini Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_USER_H_
#define _Z_CTK_TIMER_USER_H_

#include "ctk/ctk_config.h"

#define _CTK_TIMER_USER_USE_SEPARATE_THREAD

#ifdef _CTK_TIMER_USER_USE_SEPARATE_THREAD
#include "ctk/timer/timerUserThread.h"
#include "ctk/mt/threadUtil.h"
#else
#include "ctk/timer/timerManager.h"
#endif

namespace ctk {

    class TimerUser
    {
#ifdef _CTK_TIMER_USER_USE_SEPARATE_THREAD
        ctk::Handle<TimerUserThread> thr_;
#else
        TimerId timerId_;
#endif

    public:
        TimerUser()
        {
        }
        ~TimerUser()
        {
            stop();
        }

        bool start(
            ITimerObject* _this
            , rcistr _name
            , uint32 _timeoutMilliSeconds
            , uint32 _times = 0 // 0 as unlimited times
            , uint32 _userId = 0
            , void* _param = 0
            )
        {
#ifdef _CTK_TIMER_USER_USE_SEPARATE_THREAD
            thr_ = ctk::allocate<TimerUserThread>(CTK_CURRENT, _this, _name, _timeoutMilliSeconds, _times, _userId, _param);
            thr_->start();
            return true;
#else
            return CTK_TIMER_MANAGER().setTimer(timerId_, _name, _userId, _timeoutMilliSeconds, _this, _times, _param);
#endif
        }

        void stop()
        {
#ifdef _CTK_TIMER_USER_USE_SEPARATE_THREAD
            ctk::stopThread(thr_);
#else
            if (!timerId_.empty())
                CTK_TIMER_MANAGER().killTimer(timerId_);
#endif
        }

    };

} // end of namespace ctk

#endif // _Z_CTK_TIMER_USER_H_


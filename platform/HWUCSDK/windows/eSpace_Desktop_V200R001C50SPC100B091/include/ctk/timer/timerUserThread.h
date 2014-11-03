/* CTK(Mini Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_USER_THREAD_H_
#define _Z_CTK_TIMER_USER_THREAD_H_

#include "ctk/ctk_config.h"

#include "ctk/timer/timerObject.h"
#include "ctk/timer/timerId.h"

#include "ctk/mt/thread.h"

#include "ctk/util/util_type.h"

namespace ctk {

    class CTK_API TimerUserThread : public ctk::SimpleThread
    {
        typedef ctk::SimpleThread _Super;

        ctk::Pointer<ITimerObject> this_;
        ctk::Uint32 timeoutMilliSeconds_;
        ctk::Uint32 times_;
        ctk::Uint32 userId_;
        void* param_;

        TimerId timerId_;

        ctk::Time stepTime_;
        ctk::Time nextTime_;

        ctk::Uint32 currNo_;

    public:
        TimerUserThread(
            ITimerObject* _this
            , rcistr _name
            , uint32 _timeoutMilliSeconds
            , uint32 _times = 0 // 0 as unlimited times
            , uint32 _userId = 0
            , void* _param = 0
            );
        ~TimerUserThread();

        bool onBirth();

        bool onLoop();

        void onDeath();

    };

} // end of namespace ctk

#endif // _Z_CTK_TIMER_USER_THREAD_H_


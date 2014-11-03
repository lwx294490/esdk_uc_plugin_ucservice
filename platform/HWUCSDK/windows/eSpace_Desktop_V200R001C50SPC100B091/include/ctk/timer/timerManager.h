/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_MANAGER_H_
#define _Z_CTK_TIMER_MANAGER_H_

#include "ctk/ctk_config.h"

#include "ctk/timer/timerObject.h"

#include "ctk/mt/thread.h"
#include "ctk/mt/recmutex.h"

#define CTK_TIMER_MANAGER() (*ctk::TimerManager::instance())

namespace ctk {

    class TimerQueue;
    class TimerManager;

    class TimeoutThread : public OwnedThread<TimerManager>
    {
        typedef OwnedThread<TimerManager> _Super;

    public:
        TimeoutThread(TimerManager* _o, pcstr _name);

        void onWork();
        bool onWait();
        void onStop();

        ctk::dumper& dump(ctk::dumper& _d) const;
    };

    class CTK_API TimerManager : public noncopyable, public ThreadOwner
    {
    public:
        void open();
        void reopen(ctk::uint32 _numofTimers);
        void close();

        void start();
        void stop();

        bool setTimer(ctk::TimerId& unTimerID,
                      ctk::rcistr _name,
                      ctk::uint32 unUserTimerID,
                      ctk::uint32 unInterval,  // milliseconds
                      ITimerObject* pCallBackObject,
                      ctk::uint32 unTimes = 1,
                      void* pParam = 0);
        bool resetTimer(ctk::TimerId unTimerID, ctk::uint32 unInterval, ctk::uint32 unTimes = 1);
        void killTimer(ctk::TimerId unTimerID);

        void onThreadExit(ctk::Thread* _thr);

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        friend class TimeoutThread;
        void onWork();
        bool onWait();
        void onStop();

    public:
        CTK_STATIC_FUN TimerManager*& instance();
        CTK_STATIC_FUN void destroy();

    private:
        friend TimerManager* ctk::allocate_no_mlc<TimerManager>(CTK_CURRENT_ARGS);
        friend void ctk::destroy_no_mlc<TimerManager>(TimerManager*&, CTK_CURRENT_ARGS);
        TimerManager();
        ~TimerManager();

    private:
        TimerQueue* volatile m_timerQueue;

        ctk::Handle<TimeoutThread> m_pTimeoutThread;
    };
    inline std::ostream& operator<<(std::ostream& os, const TimerManager& v)
    {
        return v.dump(os);
    }
    inline ctk::dumper& operator<<(ctk::dumper& os, const TimerManager& v)
    {
        return v.dump(os);
    }

} // end of namespace ctk

#endif // _Z_CTK_TIMER_MANAGER_H_


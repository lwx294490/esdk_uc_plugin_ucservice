/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_T_H_
#define _Z_CTK_TIMER_T_H_

#include "ctk/ctk_config.h"

#include "ctk/timer/timerManager.h"

namespace ctk {

    template <class T>
    class Timer_T : public ITimerObject
    {
        typedef ctk::Mutex _Mutex;
        _Mutex mtx_;
        struct DATA
        {
            Pointer<T> this_;
            TimerId timerId_;
            void clear()
            {
                this_ = 0;
                timerId_.reset();
            }
        } data_;
        
        uint32 userId_;
        String name_;
        uint32 timeoutMilliSeconds_;
        ctk::OnTimerResult (T::*onTimerFunc_)(void*);
        uint32 times_;
        void (T::*onCancelFunc_)(void*);

        static const uint32 INVALID_VAL = 0xffffffff;

    public:
        Timer_T()
            : userId_(INVALID_VAL)
            , timeoutMilliSeconds_(INVALID_VAL)
            , onTimerFunc_(0)
            , times_(INVALID_VAL)
            , onCancelFunc_(0)
        {
        }
        Timer_T(uint32 _userId
            , rcistr _name
            , uint32 _timeoutMilliSeconds
            , ctk::OnTimerResult (T::*_onTimerFunc)(void*)
            , uint32 _times = 0 // default unlimited times
            , void (T::*_onCancelFunc)(void*) = 0
            )
            : userId_(_userId)
            , name_(_name)
            , timeoutMilliSeconds_(_timeoutMilliSeconds)
            , onTimerFunc_(_onTimerFunc)
            , times_(_times)
            , onCancelFunc_(_onCancelFunc)
        {
        }
        Timer_T(const Timer_T& _v)
        {
            _v.get(*this);
        }
        ~Timer_T()
        {
        }

        void init(uint32 _userId
            , rcistr _name
            , uint32 _timeoutMilliSeconds
            , ctk::OnTimerResult (T::*_onTimerFunc)(void*)
            , uint32 _times = 0 // default unlimited times
            , void (T::*_onCancelFunc)(void*) = 0
            )
        {
            userId_ = _userId;
            name_ = _name;
            timeoutMilliSeconds_ = _timeoutMilliSeconds;
            onTimerFunc_ = _onTimerFunc;
            times_ = _times;
            onCancelFunc_ = _onCancelFunc;
        }

        Timer_T& operator=(const Timer_T& _v)
        {
            _Mutex::Lock lck(mtx_);
            _v.get(*this);
            return *this;
        }

        void get(Timer_T& _v) const
        {
            _Mutex::Lock lck(mtx_);
            _v.data_ = data_;
            _v.userId_ = userId_;
            _v.name_ = name_;
            _v.timeoutMilliSeconds_ = timeoutMilliSeconds_;
            _v.onTimerFunc_ = onTimerFunc_;
            _v.times_ = times_;
            _v.onCancelFunc_ = onCancelFunc_;
        }

        void set(const DATA& _v)
        {
            _Mutex::Lock lck(mtx_);
            data_ = _v;
        }

        DATA get() const
        {
            _Mutex::Lock lck(mtx_);
            return data_;
        }

        DATA getAndClear()
        {
            _Mutex::Lock lck(mtx_);
            DATA ret = data_;
            data_.clear();
            return ret;
        }

        virtual ctk::OnTimerResult onTimer(TimerId _timerId, uint32 _userTimerId, void* _param)
        {
            DATA data = get();
            if (data.this_ && onTimerFunc_ && data.timerId_==_timerId && userId_==_userTimerId)
            {
                return (data.this_.get()->*onTimerFunc_)(_param);
            }
            return ctk::OnTimerResult();
        }

        virtual void onCancel(TimerId _timerId, uint32 _userTimerId, void* _param)
        {
            DATA data = get();
            if (data.this_ && onCancelFunc_ && data.timerId_==_timerId && userId_==_userTimerId)
            {
                (data.this_.get()->*onCancelFunc_)(_param);
            }
        }

        void start(T* _this, void* _param=0)
        {
            DATA data = get();
            if (data.this_ == _this && !data.timerId_.empty())
                return;
            if (CTK_TIMER_MANAGER().setTimer(data.timerId_, name_, userId_, timeoutMilliSeconds_, this, times_, _param))
            {
                data.this_ = _this;
            }
            set(data);
        }

        void stop()
        {
            DATA data = getAndClear();
            if (data.this_)
            {
                CTK_TIMER_MANAGER().killTimer(data.timerId_);
            }
        }

        void reset(uint32 _timeoutMilliSeconds = 0, uint32 _times = INVALID_VAL)
        {
            DATA data;
            {
                _Mutex::Lock lck(mtx_);
                if (_timeoutMilliSeconds)
                    timeoutMilliSeconds_ = _timeoutMilliSeconds;
                if (_times != INVALID_VAL)
                    times_ = _times;
                data = data_;
            }
            if (data.this_)
            {
                CTK_TIMER_MANAGER().resetTimer(data.timerId_, timeoutMilliSeconds_, times_);
            }
            set(data);
        }

        void restart(T* _this, ctk::Time _timeout, uint32 _times = 1, void* _param=0)
        {
            DATA data = getAndClear();
            if (data.this_)
            {
                CTK_TIMER_MANAGER().killTimer(data.timerId_);
            }
            {
                _Mutex::Lock lck(mtx_);
                timeoutMilliSeconds_ = (ctk::uint32)_timeout.toMilliSeconds();
                times_ = _times;
            }
            if (CTK_TIMER_MANAGER().setTimer(data.timerId_, name_, userId_, timeoutMilliSeconds_, this, times_, _param))
            {
                data.this_ = _this;
            }
            set(data);
        }

        bool started() const
        {
            _Mutex::Lock lck(mtx_);
            return data_.this_ != 0;
        }

    };

} // end of namespace ctk

#endif // _Z_CTK_TIMER_T_H_


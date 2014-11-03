/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_THREAD_UTIL_H_
#define _Z_CTK_THREAD_UTIL_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/thread.h"

#include "ctk/util/memfun.h"

#include "ctk/mt/set.h"

namespace ctk
{
    template<class T>
    class RunOnceThread : public SimpleThread
    {
        typedef SimpleThread _Super;
     
        typedef void (T::*_F_void)();

        T* this_;
        _F_void fn_on_run_once_;
        _F_void fn_on_stop_;

    public:
        RunOnceThread(T* _this,
                      _F_void _fn_on_run_once, 
                      _F_void _fn_on_stop, 
                      istr _name)
            : _Super(0, _name.data())
            , this_(_this)
            , fn_on_run_once_(_fn_on_run_once)
            , fn_on_stop_(_fn_on_stop)
        {
        }

    protected:
        virtual void run()
        {
            if (this_ && fn_on_run_once_)
                (this_->*fn_on_run_once_)();
        }

        virtual void onStop()
        {
            if (this_ && fn_on_stop_)
                (this_->*fn_on_stop_)();
        }

    };

    template<class T, class C>
    void
    runInThread(ctk::Handle<T>& _thr, C* _this, void (C::*_fn_run)(), void (C::*_fn_on_stop)(), istr _name, bool _createNewThread=true)
    {
        if (_createNewThread)
        {
            _thr = ctk::allocate<RunOnceThread<C> >(CTK_CURRENT, _this, _fn_run, _fn_on_stop, _name);
            _thr->startAndWait();
        }
        else
        {
            if (_this && _fn_run)
                (_this->*_fn_run)();
        }
    }

    template<class T>
    class RunLoopThread : public SimpleThread
    {
        typedef SimpleThread _Super;
     
        typedef bool (T::*_F_bool)();
        typedef void (T::*_F_void)();

        T* this_;
        _F_bool fn_on_loop_;
        _F_void fn_on_stop_;

    public:
        RunLoopThread(T* _this,
                      _F_bool _fn_on_loop, 
                      _F_void _fn_on_stop, 
                      istr _name)
            : _Super(0, _name.data())
            , this_(_this)
            , fn_on_loop_(_fn_on_loop)
            , fn_on_stop_(_fn_on_stop)
        {
        }

    protected:
        virtual bool onLoop()
        {
            if (this_ && fn_on_loop_)
                return (this_->*fn_on_loop_)();
            return true;
        }

        virtual void onStop()
        {
            if (this_ && fn_on_stop_)
                (this_->*fn_on_stop_)();
        }

    };

    template<class T, class C>
    void
    runLoopInThread(ctk::Handle<T>& _thr, C* _this, bool (C::*_fn_on_loop)(), void (C::*_fn_on_stop)(), istr _name)
    {
        _thr = ctk::allocate<RunLoopThread<C> >(CTK_CURRENT, _this, _fn_on_loop, _fn_on_stop, _name);
        _thr->startAndWait();
    }

    struct StopThreadFunction
    {
        ctk::Time waitTime_;
        ctk::size_type stopped_;

        StopThreadFunction()
            : stopped_(0)
        {
        }
        StopThreadFunction(ctk::Time _waitTime)
            : waitTime_(_waitTime), stopped_(0)
        {
        }
        void operator()(SimpleThreadPtr _thr)
        {
            if (_thr)
            {
                if (waitTime_!=ctk::Time())
                    stopped_ += _thr->stop(waitTime_) ? 1 : 0;
                else
                {
                    _thr->stop();
                    stopped_ += 1;
                }
            }
            else
                stopped_ += 1;
        }
    };

    template<class T>
    inline
    bool
    stopThread(ctk::Handle<T>& _thr, ctk::Time _waitTime)
    {
        bool stopped = true;
        ctk::Handle<T> tmp = _thr;
        if (tmp)
        {
            stopped = tmp->stop(_waitTime);
            tmp = 0;
        }
        _thr = 0;
        return stopped;
    }

    template<class T>
    inline
    bool
    stopThread(ctk::Handle<T>& _thr)
    {
        bool stopped = true;
        ctk::Handle<T> tmp = _thr;
        if (tmp)
        {
            tmp->stop();
            tmp = 0;
        }
        _thr = 0;
        return stopped;
    }

    template<class T>
    inline 
    void
    clearThread(ctk::Handle<T>& _thr, ctk::Thread* _ptr)
    {
        ctk::Handle<T> tmp = _thr;
        if (tmp)
        {
            if (tmp.get()==_ptr)
            {
                tmp = 0;
                _thr = 0;
            }
        }
    }

    class CTK_API AsyncThreadManager : public ThreadOwner
    {
        typedef ctk::mt::set<SimpleThreadPtr> _Threads;
        _Threads threads_;
        ctk::String name_;
        volatile bool closing_;

    public:
        AsyncThreadManager(rcistr _name);
        ~AsyncThreadManager();

        void open();

        void close();

        void put(SimpleThreadPtr _thr);

        void onThreadExit(Thread* _thr);

        size_type size() const;

        ctk::dumper& dump(ctk::dumper& _d) const;
    };

    template<typename T>
    struct IsVoid
    {
        enum { value = 0 };
        typedef T type;
    };

    template<>
    struct IsVoid<void>
    {
        enum { value = 1 };
        typedef int type;
    };

    template <int _isVoid, class Fo>
    struct FuncAdapter
    {
    };

    template <class Fo>
    struct FuncAdapter<0, Fo>
    {
        Fo fo_;

        FuncAdapter(Fo _fo)
            : fo_(_fo)
        {
        }

        typename IsVoid<typename Fo::result_type>::type operator()()
        {
            return fo_();
        }
    };

    template <class Fo>
    struct FuncAdapter<1, Fo>
    {
        Fo fo_;

        FuncAdapter(Fo _fo)
            : fo_(_fo)
        {
        }

        typename IsVoid<typename Fo::result_type>::type operator()()
        {
            fo_();
            return 0;
        }
    };

    template<typename _ResultType>
    class AsyncRunThread : public SimpleThread
    {
        typedef SimpleThread _Super;

    protected:
        typedef IsVoid<_ResultType> _IsVoidResult;
        typedef typename _IsVoidResult::type _ExitCode;

        _ExitCode exitCode_;

    public:
        AsyncRunThread(ThreadOwner* _owner, pcstr _name)
            : _Super(_owner, _name)
        {
        }

        _ExitCode exitCode() const
        {
            return exitCode_;
        }

    };

    template<class Fo>
    class AsyncRun : public AsyncRunThread<typename Fo::result_type>
    {
        typedef AsyncRunThread<typename Fo::result_type> _Super;

        Fo fo_;

        ctk::Time delay_;

        volatile bool ok_;
        
    public:
        AsyncRun(Fo _fo, pcstr _name, ThreadOwner* _owner, ctk::Time _delay)
            : fo_(_fo)
            , _Super(_owner, _name ? _name : "async.run")
            , delay_(_delay)
            , ok_(false)
        {
        }

        bool ok() const
        {
            return ok_;
        }

    protected:
        void run()
        {
            if (delay_!=ctk::Time())
            {
                _Super::wait(delay_);
            }

            ok_ = true;
            _Super::notify();

            _Super::exitCode_ = FuncAdapter<_Super::_IsVoidResult::value, Fo>(fo_)();
        }

    };

    template<class Fo>
        inline ctk::Handle<AsyncRunThread<typename Fo::result_type> >
        asyncRun(Fo _fo, pcstr _name, ThreadOwner* _owner=0, ctk::Time _delay=ctk::Time())
    {
        ctk::Handle<AsyncRunThread<typename Fo::result_type> > thr
            = ctk::allocate<AsyncRun<Fo> >(CTK_CURRENT, _fo, _name, _owner, _delay);
        thr->start();
        return thr;
    }

    template<class Fo>
        inline typename IsVoid<typename Fo::result_type>::type
        syncRun(Fo _fo, pcstr _name, ThreadOwner* _owner=0, ctk::Time _delay=ctk::Time())
    {
        ctk::Handle<AsyncRunThread<typename Fo::result_type> > thr
            = ctk::allocate<AsyncRun<Fo> >(CTK_CURRENT, _fo, _name, _owner, _delay);
        thr->start();
        thr->join();
        return thr->exitCode();
    }

} // end of namespace ctk

#endif //_Z_CTK_THREAD_UTIL_H_


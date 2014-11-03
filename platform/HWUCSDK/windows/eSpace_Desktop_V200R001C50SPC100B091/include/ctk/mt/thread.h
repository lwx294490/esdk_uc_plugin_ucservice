/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_THREAD_H_
#define _Z_CTK_THREAD_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/shared.h"
#include "ctk/mt/handle.h"
#include "ctk/mt/mutex.h"
#include "ctk/mt/recmutex.h"
#include "ctk/mt/monitor.h"

#include "ctk/base/base_type_time.h"
#include "ctk/base/base_type_pointer.h"

#include "ctk/log/log_macros.h"

#include <ace/Thread.h>

namespace ctk
{
#ifdef _WIN32
    struct WinHandleWrapper : public Shared
    {
        WinHandleWrapper(HANDLE _h, bool _r = true)
            : h_(_h), r_(_r)
        {
        }

        virtual ~WinHandleWrapper()
        {
            if(h_ && r_)
            {
                CloseHandle(h_);
            }
        }

        HANDLE h_;
        bool r_;
    };

    typedef Handle<WinHandleWrapper> AutoHandle;
#endif

    struct CTK_API ThreadId
    {
#ifdef _WIN32
        typedef unsigned int type;
#else
        typedef pthread_t type;
#endif

        type id_;

        ThreadId(type _id=0) : id_(_id) { }

        operator type() const { return id_; }
    };
    CTK_API std::ostream& operator<<(std::ostream& _os , const ctk::ThreadId& _v);
    CTK_API ctk::dumper& operator<<(ctk::dumper& _os , const ctk::ThreadId& _v);

    //
    // 线程控制 //
    //
    class CTK_API ThreadControl
    {
    public:
        ThreadControl();

    #ifdef _WIN32
        ThreadControl(const AutoHandle&, ThreadId);
    #else
        ThreadControl(ThreadId);
    #endif

        ThreadControl(const ThreadControl&);
        ThreadControl& operator=(const ThreadControl&);

        static ThreadControl current();

        bool operator==(const ThreadControl&) const;
        bool operator!=(const ThreadControl&) const;
        bool operator<(const ThreadControl&) const;

        ThreadId id() const;

        void join();

        void detach();

        bool isAlive() const; // 操作系统中线程资源是否存在且处于活动状态 //

        CTK_STATIC_FUN void sleep(const Time&);
        CTK_STATIC_FUN void yield();

    private:
        Mutex stateMutex_;
    #ifdef _WIN32
        AutoHandle handle_;
    #endif
        ThreadId id_;
    };

    //
    // 注意：线程对象必须动态分配，不能在堆栈中定义线程变量。 //
    // new 了以后，不需要delete，在线程执行结束后会自动删除该对象， //
    // 在这之前不能删除。 //
    //
    class CTK_API Thread : virtual public ctk::Shared
    {
    public:
        Thread();
        virtual ~Thread();

        virtual void run_i() = 0;

        ThreadId id() const;

        ThreadControl start(size_t _stackSize = 0);

        ThreadControl getThreadControl() const;

        bool operator==(const Thread&) const;
        bool operator!=(const Thread&) const;
        bool operator<(const Thread&) const;

        bool started() const;

    private:
        Thread(const Thread&);
        void operator=(const Thread&);

    private:
        volatile bool started_; // 线程是否已经启动 //

        Mutex stateMutex_;
    #ifdef _WIN32
        AutoHandle handle_;
    #endif
        ThreadId id_;

    protected:
        volatile bool stopped_; // 线程是否已经结束（任务完成） //

    };

    typedef Handle<Thread> ThreadPtr;

    class CTK_API ThreadOwner
    {
        friend class SimpleThread;

        ctk::String ownername_;

    public:
        ThreadOwner(ctk::pcstr _name=0);
        virtual ~ThreadOwner();

        ctk::rcstr ownername() const;

    protected:
        virtual void onThreadExit(ctk::Thread* _thr) = 0;

    };

    class CTK_API SimpleThread;

    struct CTK_API ThreadInfo
    {
        ctk::Pointer<SimpleThread> thread_;
        ctk::String sThreadId_;
        ctk::Time currDateTime_;
        ctk::String sCurrDateTime_;

        void updateDateTime();

        ctk::dumper& dump(ctk::dumper& _os) const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const ThreadInfo& _v)
    {
        return _os << _v.sCurrDateTime_ << _v.sThreadId_;
    }

    //
    // 注意看前面Thread的说明，要点是不能在堆栈中定义线程对象，不要自行delete，最好使用Handle<>. //
    //
    class CTK_API SimpleThread: public Thread
    {
    public:
        SimpleThread(ThreadOwner* _owner, pcstr _name);
        ~SimpleThread();

        void startAndWait(size_t _stackSize = 0);
        void startUntilInitialized(size_t _stackSize = 0) { startAndWait(_stackSize); }

        // return false if wait timeout
        bool startAndWait(ctk::Time _wait, size_t _stackSize = 0);

        // stop should be called by other thread
        
        // stop running and join
        void stop();

        // stop running and wait stopped in given time
        // return false if not stopped
        bool stop(ctk::Time _waitTime); 

        void stopOnly();

        void join();
        bool join(ctk::Time _waitTime);

        bool activeStopping() const;

        void detach(); // set owner_ to 0

        bool living() const;
        void living(bool _living);
        void livingEnd();

        void wait() const;
        bool wait(const Time&) const;

        void notify();

        ThreadOwner* owner() const;
        void owner(ThreadOwner* _owner);

        ctk::rcstr name() const;
        ctk::rcstr fullname() const;

        ctk::rcstr threadIdString() const;
        ctk::rcstr currDateTimeString() const;
        ctk::Time currDateTime() const;

        const ThreadInfo& info() const;

        static const ThreadInfo& current();
        static void destroyThreadFactory();

        virtual ctk::dumper& dump(ctk::dumper& _os) const;

    protected:
        // thread entry
        virtual void run();

        virtual bool onBirth();
        virtual bool onWait();
        virtual void onWork(); // if (!onLoop()) m_living = false;
        virtual bool onLoop();
        virtual void onDeath();
        virtual void onStop();

    protected:
        virtual void run_i(); // 具体子类不要重载这个函数，这是给一些特定线程类的基类用的 //

    private:
        bool onBirth_i();
        bool onWait_i();
        void onWork_i();
        void onDeath_i();
        void onStop_i();

        void on_thread_exit();

    private:
        typedef ctk::Mutex _Mutex;
        _Mutex mtxOwner_;
        ThreadOwner* owner_;

        typedef ctk::Monitor<ctk::Mutex> _Monitor;
        _Monitor monWait_;

        // thread local member
        ctk::String name_;
        ctk::String fullname_;

        volatile bool m_living; // 线程循环执行标志 // must be volatile if not use mutex to lock it //

        volatile bool activeStopping_; // 线程被主动停止 //
        
    };

    template<class T>
    class OwnedThread : public SimpleThread
    {
        typedef SimpleThread _Super;

        typedef bool (T::*_F_bool)();
        typedef void (T::*_F_void)();

        _F_bool on_birth_;
        _F_bool on_wait_;
        _F_void on_work_;
        _F_bool on_loop_;
        _F_void on_death_;
        _F_void on_stop_;

        _F_void on_run_;
     
    public:
        OwnedThread(T* _owner, rcistr _name)
            : _Super(_owner, _name.data())
            , on_birth_(0)
            , on_wait_(0)
            , on_work_(0)
            , on_loop_(0)
            , on_death_(0)
            , on_stop_(0)
            , on_run_(0)
        {
        }

        T* getOwner() const
        {
            return dynamic_cast<T*>(owner());
        }
        void setOwner(T* _owner)
        {
            owner(_owner);
        }

        void exec(_F_void _fn)
        {
            if (_fn)
            {
                T* o = getOwner();
                if (o)
                {
                    (o->*_fn)();
                }
            }
        }
        bool exec(_F_bool _fn)
        {
            if (_fn)
            {
                T* o = getOwner();
                if (o)
                {
                    return (o->*_fn)();
                }
            }
            return true;
        }

        void set_on_birth(_F_bool _fn)
        {
            on_birth_ = _fn;
        }
        void set_on_wait(_F_bool _fn)
        {
            on_wait_ = _fn;
        }
        void set_on_work(_F_void _fn)
        {
            on_work_ = _fn;
        }
        void set_on_loop(_F_bool _fn)
        {
            on_loop_ = _fn;
        }
        void set_on_death(_F_void _fn)
        {
            on_death_ = _fn;
        }
        void set_on_stop(_F_void _fn)
        {
            on_stop_ = _fn;
        }
        void set_on_run(_F_void _fn)
        {
            on_run_ = _fn;
        }

    protected:
        virtual void run()
        {
            if (on_run_)
                exec(on_run_);
            else
                _Super::run();
        }

        virtual bool onBirth()
        {
            if (on_birth_)
                return exec(on_birth_);
            else
                return _Super::onBirth();

        }
        virtual bool onWait()
        {
            if (on_wait_)
                return exec(on_wait_);
            else
                return _Super::onWait();
        }
        virtual void onWork()
        {
            if (on_work_)
                exec(on_work_);
            else
                _Super::onWork();
        }
        virtual bool onLoop()
        {
            if (on_loop_)
                return exec(on_loop_);
            else
                return _Super::onLoop();
        }
        virtual void onDeath()
        {
            if (on_death_)
                exec(on_death_);
            else
                _Super::onDeath();
        }
        virtual void onStop()
        {
            if (on_stop_)
                exec(on_stop_);
            else
                _Super::onStop();
        }

    };

    typedef Handle<SimpleThread> SimpleThreadPtr;

    struct THREAD_FACTORY { };

    CTK_API ctk::dumper& operator<<(ctk::dumper& _os , const THREAD_FACTORY& _v);

    CTK_API void sleep(uint32 _milliSeconds);

} // end of namespace ctk

#endif //_Z_CTK_THREAD_H_


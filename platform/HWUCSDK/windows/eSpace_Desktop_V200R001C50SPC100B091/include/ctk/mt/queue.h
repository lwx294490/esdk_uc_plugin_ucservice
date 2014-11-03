/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_QUEUE_H_
#define _Z_CTK_MT_QUEUE_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_stl.h"
#include "ctk/base/base_type_time.h"

#include "ctk/log/log_stl.h"

#include "ctk/mt/mutex.h"
#include "ctk/mt/monitor.h"

namespace ctk {
namespace mt {

    template<class T>
    class queue
    {
        typedef queue<T>                 _Self;
        typedef ctk::queue<T>            _Queue;
        typedef ctk::Monitor<ctk::Mutex> _Mutex;

        _Queue c_;
        _Mutex mtx_;

    public:
        typedef typename _Queue::container_type      _Container;
        typedef typename _Container::iterator        _Iterator;
        typedef typename _Container::const_iterator  _ConstItr;

    public:
        queue()
        {
        }
        queue(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        queue(const _Container& _v)
            : c_(_v)
        {
        }

        _Self& operator=(const _Self& _v)
        {
            if (this==&_v)
                return *this;
            _Mutex::Lock __lck(mtx_);
            _v.copyTo(c_);
            return *this;
        }

        void copyTo(_Queue& _v) const
        {
            _Mutex::Lock __lck(mtx_);
            _v = c_;
        }

        void takeOut(_Container& _v)
        {
            _v.clear();
            _Mutex::Lock __lck(mtx_);
            ctk::swap(_v, c_._Get_c());
        }

        void put(const T& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_.push(_v);

            mtx_.notify();
        }

        void push(T& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_.push(T());
            ctk::swap(_v, c_.back());

            mtx_.notify();
        }

        bool get(T& _v)
        {
            return get(_v, Time::forever());
        }

        bool get(T& _v, const ctk::Time& _waitTime)
        {
            _Mutex::Lock __lck(mtx_);
            if (c_.empty())
            {
                if (_waitTime==Time::forever())
                    mtx_.wait();
                else if (!mtx_.timedWait(_waitTime))
                    return false;
                if (c_.empty())
                    return false;
            }
            ctk::swap(_v, c_.front());
            c_.pop();
            return true;
        }

        bool pop(T& _v)
        {
            return pop(_v, Time::forever());
        }

        bool pop(T& _v, const ctk::Time& _waitTime)
        {
            _Mutex::Lock __lck(mtx_);
            if (c_.empty())
            {
                if (_waitTime==Time::forever())
                    mtx_.wait();
                else if (!mtx_.timedWait(_waitTime))
                    return false;
                if (c_.empty())
                    return false;
            }
            _v = c_.front();
            c_.pop();
            return true;
        }

        void notify()
        {
            _Mutex::Lock __lck(mtx_);
            mtx_.notify();
        }

        void notifyAll()
        {
            _Mutex::Lock __lck(mtx_);
            mtx_.notifyAll();
        }

        bool empty() const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.empty();
        }

        ctk::size_type size() const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.size();
        }

        void clear()
        {
            _Mutex::Lock __lck(mtx_);
            c_.clear();
            mtx_.notifyAll();
        }

        template <class _Function>
        _Function
        for_each(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            for (_Iterator it = c_._Get_c().begin(); it != c_._Get_c().end(); ++it)
            {
                _f(*it);
            }
            return _f;
        }

        template <class _Function>
        _Function
        for_each(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_ConstItr it = c_._Get_c().begin(); it != c_._Get_c().end(); ++it)
            {
                _f(*it);
            }
            return _f;
        }

        template <class _Function>
        _Function
        for_all(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            _f(c_._Get_c());
            return _f;
        }

        template <class _Function>
        _Function
        for_all(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            _f(c_._Get_c());
            return _f;
        }

        ctk::dumper& dump(ctk::dumper& d) const
        {
            CTK_DUMP(d, "ctk::mt::queue");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_._Get_c());
            return d;
        }

    };
    template<class T> inline ctk::dumper& operator<<(ctk::dumper& d, const queue<T>& v)
    {
        return v.dump(d);
    }
    template<class T> inline std::ostream& operator<<(std::ostream& os, const queue<T>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_QUEUE_H_


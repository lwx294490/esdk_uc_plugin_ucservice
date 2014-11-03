/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_LIST_H_
#define _Z_CTK_MT_LIST_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_stl.h"

#include "ctk/log/log_stl.h"

#include "ctk/mt/mutex.h"

namespace ctk {
namespace mt {

    template<class T>
    class list
    {
        typedef list<T> _Self;
        typedef ctk::Mutex _Mutex;

    public:
        typedef ctk::list<T> _Container;
        typedef typename _Container::iterator _Iterator;
        typedef typename _Container::const_iterator _ConstItr;

    private:
        _Container c_;
        _Mutex mtx_;

    public:
        list()
        {
        }
        list(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        list(const _Container& _v)
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

        void copyTo(_Container& _v) const
        {
            _Mutex::Lock __lck(mtx_);
            _v = c_;
        }

        void takeOut(_Container& _v)
        {
            _v.clear();
            _Mutex::Lock __lck(mtx_);
            ctk::swap(_v, c_);
        }

        void resize(size_type _newsize)
        {	// determine new length, padding with T() elements as needed
            _Mutex::Lock __lck(mtx_);
            c_.resize(_newsize);
        }

        void resize(size_type _newsize, T _v)
        {	// determine new length, padding with _v elements as needed
            _Mutex::Lock __lck(mtx_);
            c_.resize(_newsize, _v);
        }

        size_type size() const
        {	// return length of sequence
            _Mutex::Lock __lck(mtx_);
            return c_.size();
        }

        size_type max_size() const
        {	// return maximum possible length of sequence
            _Mutex::Lock __lck(mtx_);
            return c_.max_size();
        }

        bool empty() const
        {	// test if sequence is empty
            _Mutex::Lock __lck(mtx_);
            return c_.empty();
        }

        bool front(T& _v) const
        {	// return first element of nonmutable sequence
            _Mutex::Lock __lck(mtx_);
            if (c_.empty())
                return false;
            _v = c_.front();
            return true;
        }

        bool back(T& _v) const
        {	// return last element of nonmutable sequence
            _Mutex::Lock __lck(mtx_);
            if (c_.empty())
                return false;
            _v = c_.back();
            return true;
        }

        void push_front(const T& _v)
        {	// insert element at beginning
            _Mutex::Lock __lck(mtx_);
            c_.push_front(_v);
        }

        bool pop_front(T& _v)
        {	// erase element at beginning
            _Mutex::Lock __lck(mtx_);
            if (c_.empty())
                return false;
            _v = c_.front();
            c_.pop_front();
            return true;
        }

        void push_back(const T& _v)
        {	// insert element at end
            _Mutex::Lock __lck(mtx_);
            c_.push_back(_v);
        }

        bool pop_back(T& _v)
        {	// erase element at end
            _Mutex::Lock __lck(mtx_);
            if (c_.empty())
                return false;
            _v = c_.back();
            c_.pop_back();
            return true;
        }

        void clear()
        {	// erase all
            _Mutex::Lock __lck(mtx_);
            c_.clear();
        }

        template <class _Function>
        _Function
        for_each(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            for (_Iterator it = c_.begin(); it != c_.end(); ++it)
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
            for (_ConstItr it = c_.begin(); it != c_.end(); ++it)
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
            _f(c_);
            return _f;
        }

        template <class _Function>
        _Function
        for_all(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            _f(c_);
            return _f;
        }

        ctk::dumper& dump(ctk::dumper& d) const
        {
            CTK_DUMP(d, "ctk::mt::list");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    };
    template<class T> inline ctk::dumper& operator<<(ctk::dumper& d, const list<T>& v)
    {
        return v.dump(d);
    }
    template<class T> inline std::ostream& operator<<(std::ostream& os, const list<T>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_LIST_H_


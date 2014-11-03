/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_VECTOR_H_
#define _Z_CTK_MT_VECTOR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_stl.h"

#include "ctk/log/log_stl.h"

#include "ctk/mt/mutex.h"

namespace ctk {
namespace mt {

    template<class T>
    class vector
    {
        typedef vector<T> _Self;
        typedef ctk::Mutex _Mutex;

    public:
        typedef ctk::vector<T> _Container;
        typedef typename _Container::iterator _Iterator;
        typedef typename _Container::const_iterator _ConstItr;

    private:
        _Container c_;
        _Mutex mtx_;

    public:
        vector()
        {
        }
        vector(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        vector(const _Container& _v)
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

        T get(size_type _pos) const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.at(_pos);
        }

        void set(size_type _pos, const T& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_.at(_pos) = _v;
        }

        T& unsafe_at(size_type _pos)
        {
            _Mutex::Lock __lck(mtx_);
            return c_.at(_pos);
        }

        const T& unsafe_at(size_type _pos) const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.at(_pos);
        }

    	void reserve(size_type _count)
        {	// determine new minimum length of allocated storage
            _Mutex::Lock __lck(mtx_);
            c_.reserve(_count);
        }

    	size_type capacity() const
        {	// return current length of allocated storage
            _Mutex::Lock __lck(mtx_);
            return c_.capacity();
        }

    	void resize(size_type _newsize, bool _b = false)
        {	// determine new length, padding with _Val elements as needed
            _Mutex::Lock __lck(mtx_);
            c_.resize(_newsize, _b);
        }

    	size_type max_size() const
        {	// return maximum possible length of sequence
            _Mutex::Lock __lck(mtx_);
            return c_.max_size();
        }

        bool empty() const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.empty();
        }

        size_type size() const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.size();
        }

        void clear()
        {
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
            CTK_DUMP(d, "ctk::mt::vector");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    };
    template<class T> inline ctk::dumper& operator<<(ctk::dumper& d, const vector<T>& v)
    {
        return v.dump(d);
    }
    template<class T> inline std::ostream& operator<<(std::ostream& os, const vector<T>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_VECTOR_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_SET_H_
#define _Z_CTK_MT_SET_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_stl.h"

#include "ctk/log/log_stl.h"

#include "ctk/mt/mutex.h"

namespace ctk {
namespace mt {

    template<class _K>
    class set
    {
        typedef set<_K> _Self;
        typedef ctk::Mutex _Mutex;

    public:
        typedef ctk::set<_K> _Container;
        typedef typename _Container::iterator _Iterator;
        typedef typename _Container::const_iterator _ConstItr;

    private:
        _Container c_;
        _Mutex mtx_;

    public:
        set()
        {
        }
        set(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        set(const _Container& _v)
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

        void insert(const _K& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_.insert(_v);
        }

        size_type erase(const _K& _k)
        {
            _Mutex::Lock __lck(mtx_);
            return c_.erase(_k);
        }

        bool has(const _K& _k) const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.find(_k)!=c_.end();
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
            CTK_DUMP(d, "ctk::mt::set");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    };
    template<class _K> inline ctk::dumper& operator<<(ctk::dumper& d, const set<_K>& v)
    {
        return v.dump(d);
    }
    template<class _K> inline std::ostream& operator<<(std::ostream& os, const set<_K>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

    template<class _K>
    class multiset
    {
        typedef multiset<_K> _Self;
        typedef ctk::Mutex _Mutex;

    public:
        typedef ctk::multiset<_K> _Container;
        typedef typename _Container::iterator _Iterator;
        typedef typename _Container::const_iterator _ConstItr;

    private:
        _Container c_;
        _Mutex mtx_;

    public:
        multiset()
        {
        }
        multiset(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        multiset(const _Container& _v)
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

        void insert(const _K& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_.insert(_v);
        }

        size_type erase(const _K& _k)
        {
            _Mutex::Lock __lck(mtx_);
            return c_.erase(_k);
        }

        size_type count(const _K& _k)
        {
            _Mutex::Lock __lck(mtx_);
            return c_.count(_k);
        }

        bool has(const _K& _k) const
        {
            _Mutex::Lock __lck(mtx_);
            return c_.find(_k)!=c_.end();
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
            CTK_DUMP(d, "ctk::mt::multiset");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    };
    template<class _K> inline ctk::dumper& operator<<(ctk::dumper& d, const multiset<_K>& v)
    {
        return v.dump(d);
    }
    template<class _K> inline std::ostream& operator<<(std::ostream& os, const multiset<_K>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_SET_H_


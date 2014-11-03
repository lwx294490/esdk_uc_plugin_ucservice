/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_MAP_H_
#define _Z_CTK_MT_MAP_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_stl.h"

#include "ctk/mt/mutex.h"

#include "ctk/log/log_stl.h"

namespace ctk {
namespace mt {

    template<class _K, class _V>
    class map
    {
        typedef map<_K, _V> _Self;

    public:
        typedef ctk::Mutex _Mutex;
        typedef ctk::map<_K, _V> _Container;
        typedef typename _Container::iterator _Iterator;
        typedef typename _Container::const_iterator _ConstItr;

    private:
        _Container c_;
        _Mutex mtx_;

    public:
        map()
        {
        }
        map(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        map(const _Container& _v)
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

        void put(const _K& _k, const _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_[_k] = _v;
        }

        void put(const _K& _k, const _V& _vNew, _V& _vOld)
        {
            _Mutex::Lock __lck(mtx_);
            _V& v = c_[_k];
            _vOld = v;
            v = _vNew;
        }

        void push(const _K& _k, _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            ctk::swap(c_[_k], _v);
        }

        bool checked_insert(const _K& _k, const _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            if (c_.find(_k)!=c_.end())
                return false;
            c_[_k] = _v;
            return true;
        }

        bool get(const _K& _k, _V& _v) const
        {
            _Mutex::Lock __lck(mtx_);
            _ConstItr it = c_.find(_k);
            if (it==c_.end())
                return false;
            _v = (*it).second;
            return true;
        }

        bool pop(const _K& _k, _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            _Iterator it = c_.find(_k);
            if (it==c_.end())
                return false;
            _v = (*it).second;
            c_.erase(it);
            return true;
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

        _V at(const _K& _k) const
        {
            _Mutex::Lock __lck(mtx_);
            _ConstItr it = c_.find(_k);
            if (it==c_.end())
                return _V();
            return (*it).second;
        }

        _V& unsafe_at(const _K& _k)
        {
            _Mutex::Lock __lck(mtx_);
            return c_[_k];
        }

        _V& internal_at(const _K& _k)
        {
            return c_[_k];
        }

        _Container& internal_container()
        {
            return c_;
        }

        _Mutex& internal_mtx()
        {
            return mtx_;
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

        void getKeyList(std::list<_K>& _keyList) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_ConstItr it = c_.begin(); it != c_.end(); ++it)
            {
                _keyList.push_back((*it).first);
            }
        }

        void getValueList(std::list<_V>& _valueList) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_ConstItr it = c_.begin(); it != c_.end(); ++it)
            {
                _valueList.push_back((*it).second);
            }
        }

        template <class _Function>
        _Function
        for_each(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            for (_Iterator it = c_.begin(); it != c_.end(); ++it)
            {
                _f((*it).second);
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
                _f((*it).second);
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

        template <class _Function>
        bool
        checkIf(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_ConstItr it = c_.begin(); it != c_.end(); ++it)
            {
                if (_f((*it).second))
                    return true;
            }
            return false;
        }

        template <class _Function>
        bool
        eraseIf(const _K& _k, _Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            _Iterator it = c_.find(_k);
            if (it != c_.end())
            {
                if (_f((*it).second))
                {
                    c_.erase(it);
                    return true;
                }
            }
            return false;
        }

        ctk::dumper& dump(ctk::dumper& d) const
        {
            CTK_DUMP(d, "ctk::mt::map");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    };
    template<class _K, class _V> inline ctk::dumper& operator<<(ctk::dumper& d, const map<_K, _V>& v)
    {
        return v.dump(d);
    }
    template<class _K, class _V> inline std::ostream& operator<<(std::ostream& os, const map<_K, _V>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

    template<class _K, class _V>
    class multimap
    {
        typedef multimap<_K, _V> _Self;
        typedef ctk::Mutex _Mutex;

    public:
        typedef ctk::multimap<_K, _V> _Container;
        typedef typename _Container::iterator _Iterator;
        typedef typename _Container::const_iterator _ConstItr;

    private:
        _Container c_;
        _Mutex mtx_;

    public:
        multimap()
        {
        }
        multimap(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        multimap(const _Container& _v)
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

        void insert(const _K& _k, const _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_.insert(std::make_pair(_k, _v));
        }

        bool get(const _K& _k, std::list<_V>& _v) const
        {
            _v.clear();
            _Mutex::Lock __lck(mtx_);
            std::pair<_ConstItr, _ConstItr> range = c_.equal_range(_k);
            for (_ConstItr it = range.first; it != range.second; ++it)
                _v.push_back((*it).second);
            return !_v.empty();
        }

        bool pop(const _K& _k, std::list<_V>& _v)
        {
            _v.clear();
            _Mutex::Lock __lck(mtx_);
            std::pair<_ConstItr, _ConstItr> range = c_.equal_range(_k);
            for (_ConstItr it = range.first; it != range.second; ++it)
                _v.push_back((*it).second);
            c_.erase(_k);
            return !_v.empty();
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

        void getKeyList(std::list<_K>& _keyList) const
        {
            _keyList.clear();
            _Mutex::Lock __lck(mtx_);
            for (_ConstItr it = c_.begin(); it != c_.end(); ++it)
            {
                _keyList.push_back((*it).first);
            }
        }

        template <class _Function>
        _Function
        for_each(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            for (_Iterator it = c_.begin(); it != c_.end(); ++it)
            {
                _f((*it).second);
            }
            return _f;
        }

        template <class _Function>
        _Function
        for_each(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_Iterator it = c_.begin(); it != c_.end(); ++it)
            {
                _f((*it).second);
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
            CTK_DUMP(d, "ctk::mt::multimap");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    };
    template<class _K, class _V> inline ctk::dumper& operator<<(ctk::dumper& d, const multimap<_K, _V>& v)
    {
        return v.dump(d);
    }
    template<class _K, class _V> inline std::ostream& operator<<(std::ostream& os, const multimap<_K, _V>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_MAP_H_


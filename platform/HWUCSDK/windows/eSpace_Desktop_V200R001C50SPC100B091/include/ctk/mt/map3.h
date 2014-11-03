/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_MAP3_H_
#define _Z_CTK_MT_MAP3_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_stl.h"

#include "ctk/log/log_stl.h"

#include "ctk/mt/mutex.h"

namespace ctk {
namespace mt {

    template<class _K1, class _K2, class _K3, class _V>
    class map3
    {
        typedef map3<_K1, _K2, _K3, _V> _Self;

    public:
        typedef ctk::Mutex _Mutex;
        typedef typename ctk::map<_K3, _V> _Container3;
        typedef typename ctk::map<_K2, _Container3> _Container2;
        typedef typename ctk::map<_K1, _Container2> _Container1;
        typedef typename _Container1::iterator _It1;
        typedef typename _Container1::const_iterator _CIt1;
        typedef typename _Container2::iterator _It2;
        typedef typename _Container2::const_iterator _CIt2;
        typedef typename _Container3::iterator _It3;
        typedef typename _Container3::const_iterator _CIt3;
        typedef _Container1 _Container;
        typedef _It1 _Iterator;
        typedef _CIt1 _ConstIterator;

        struct _Keys
        {
            _K1 k1_;
            _K2 k2_;
            _K3 k3_;
            _Keys(const _K1& _k1, const _K2& _k2, const _K3& _k3)
                : k1_(_k1), k2_(_k2), k3_(_k3)
            {
            }
        };

    private:
        _Mutex mtx_;
        _Container c_;

    public:
        map3()
        {
        }
        map3(const _Self& _v)
        {
            _v.copyTo(c_);
        }
        map3(const _Container& _v)
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

        void put(const _K1& _k1, const _K2& _k2, const _K3& _k3, const _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            c_[_k1][_k2][_k3] = _v;
        }

        bool checked_insert(const _K1& _k1, const _K2& _k2, const _K3& _k3, const _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            if (has_i(_k1, _k2, _k3))
                return false;
            c_[_k1][_k2][_k3] = _v;
            return true;
        }

        bool get(const _K1& _k1, const _K2& _k2, const _K3& _k3, _V& _v) const
        {
            _Mutex::Lock __lck(mtx_);
            _CIt1 i1 = c_.find(_k1);
            if (i1 != c_.end())
            {
                _CIt2 i2 = (*i1).second.find(_k2);
                if (i2 != (*i1).second.end())
                {
                    _CIt3 i3 = (*i2).second.find(_k3);
                    if (i3 != (*i2).second.end())
                    {
                        _v = (*i3).second;
                        return true;
                    }
                }
            }
            return false;
        }

        bool pop(const _K1& _k1, const _K2& _k2, const _K3& _k3, _V& _v)
        {
            _Mutex::Lock __lck(mtx_);
            _It1 i1 = c_.find(_k1);
            if (i1 != c_.end())
            {
                _It2 i2 = (*i1).second.find(_k2);
                if (i2 != (*i1).second.end())
                {
                    _CIt3 i3 = (*i2).second.find(_k3);
                    if (i3 != (*i2).second.end())
                    {
                        _v = (*i3).second;
                        (*i2).second.erase(i3);
                        return true;
                    }
                }
            }
            return false;
        }

        size_type erase(const _K1& _k1, const _K2& _k2, const _K3& _k3)
        {
            size_type ret = 0;
            _Mutex::Lock __lck(mtx_);
            _It1 i1 = c_.find(_k1);
            if (i1 != c_.end())
            {
                _It2 i2 = (*i1).second.find(_k2);
                if (i2 != (*i1).second.end())
                {
                    _CIt3 i3 = (*i2).second.find(_k3);
                    if (i3 != (*i2).second.end())
                    {
                        ret = (*i2).second.erase(_k3);
                    }
                    if ((*i2).second.empty())
                    {
                        (*i1).second.erase(_k2);
                    }
                }
                if ((*i1).second.empty())
                {
                    c_.erase(_k1);
                }
            }
            return ret;
        }

        bool has(const _K1& _k1) const
        {
            _Mutex::Lock __lck(mtx_);
            return has_i(_k1);
        }

        bool has(const _K1& _k1, const _K2& _k2) const
        {
            _Mutex::Lock __lck(mtx_);
            return has_i(_k1, _k2);
        }

        bool has(const _K1& _k1, const _K2& _k2, const _K3& _k3) const
        {
            _Mutex::Lock __lck(mtx_);
            return has_i(_k1, _k2, _k3);
        }

        _V at(const _K1& _k1, const _K2& _k2, const _K3& _k3) const
        {
            _Mutex::Lock __lck(mtx_);
            _CIt1 it1 = c_.find(_k1);
            if (it1==c_.end())
                return _V();
            const _Container2& c2 = (*it1).second;
            _CIt2 it2 = c2.find(_k2);
            if (it2==c2.end())
                return _V();
            const _Container3& c3 = (*it2).second;
            _CIt3 it3 = c3.find(_k3);
            if (it3==c3.end())
                return _V();
            return (*it3).second;
        }

        _V& unsafe_at(const _K1& _k1, const _K2& _k2, const _K3& _k3)
        {
            _Mutex::Lock __lck(mtx_);
            return c_[_k1][_k2][_k3];
        }

        _V& internal_at(const _K1& _k1, const _K2& _k2, const _K3& _k3)
        {
            return c_[_k1][_k2][_k3];
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

        bool empty(const _K1& _k1) const
        {
            _Mutex::Lock __lck(mtx_);
            _CIt1 i1 = c_.find(_k1);
            if (i1 != c_.end())
            {
                return (*i1).second.empty();
            }
            return true;
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

        void getKeyList(std::list<_Keys>& _keyList) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_CIt1 i1 = c_.begin(); i1 != c_.end(); ++i1)
            {
                for (_CIt2 i2 = (*i1).second.begin(); i2 != (*i1).second.end(); ++i2)
                {
                    for (_CIt3 i3 = (*i2).second.begin(); i3 != (*i2).second.end(); ++i3)
                    {
                        _keyList.push_back(_Keys((*i1).first, (*i2).first, (*i3).first));
                    }
                }
            }
        }

        template <class _Function>
        _Function
        for_each(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            for (_It1 i1 = c_.begin(); i1 != c_.end(); ++i1)
            {
                for (_It2 i2 = (*i1).second.begin(); i2 != (*i1).second.end(); ++i2)
                {
                    for (_It3 i3 = (*i2).second.begin(); i3 != (*i2).second.end(); ++i3)
                    {
                        _f((*i3).second);
                    }
                }
            }
            return _f;
        }

        template <class _Function>
        _Function
        for_each(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            for (_CIt1 i1 = c_.begin(); i1 != c_.end(); ++i1)
            {
                for (_CIt2 i2 = (*i1).second.begin(); i2 != (*i1).second.end(); ++i2)
                {
                    for (_CIt3 i3 = (*i2).second.begin(); i3 != (*i2).second.end(); ++i3)
                    {
                        _f((*i3).second);
                    }
                }
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
            CTK_DUMP(d, "ctk::mt::map3");
            _Mutex::Lock __lck(mtx_);
            ctk::output(d, c_);
            return d;
        }

    private:
        bool has_i(const _K1& _k1) const
        {
            return c_.find(_k1);
        }
        bool has_i(const _K1& _k1, const _K2& _k2) const
        {
            _CIt1 i1 = c_.find(_k1);
            if (i1 != c_.end())
            {
                _CIt2 i2 = (*i1).second.find(_k2);
                return (i2 != (*i1).second.end());
            }
            return false;
        }
        bool has_i(const _K1& _k1, const _K2& _k2, const _K3& _k3) const
        {
            _CIt1 i1 = c_.find(_k1);
            if (i1 != c_.end())
            {
                _CIt2 i2 = (*i1).second.find(_k2);
                if (i2 != (*i1).second.end())
                {
                    _CIt3 i3 = (*i2).second.find(_k3);
                    return (i3 != (*i2).second.end());
                }
            }
            return false;
        }

    };
    template<class _K1, class _K2, class _K3, class _V>
        inline ctk::dumper& operator<<(ctk::dumper& d, const map3<_K1, _K2, _K3, _V>& v)
    {
        return v.dump(d);
    }
    template<class _K1, class _K2, class _K3, class _V>
        inline std::ostream& operator<<(std::ostream& os, const map3<_K1, _K2, _K3, _V>& v)
    {
        ctk::dumper d(os, false);
        d << v;
        return os;
    }

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_MAP3_H_


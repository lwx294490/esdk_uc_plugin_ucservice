/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

//#ifndef _Z_PML_NTV_H_
//#error "ntv_stl.h should included by pml/ntv.h!"
//#endif

#ifndef _Z_PML_NTV_STL_H_
#define _Z_PML_NTV_STL_H_

#include "ctk/base/base_type_stl.h"

#include "ctk/base/base_type_enum.h"

#include "ctk/pml/pml_stream.h"

namespace ctk {
namespace pml {
namespace ntv {

    template<class T> inline void
        operator<<(Unit& _os, const T& _v)
    {
        ctk::pml::stream mps;
        mps.setAsOutputStream(_os.allNesessary());
        const_cast<T&>(_v).codec(mps);
        _os << mps.unit();
    }
    template<class T> inline void
        operator>>(const Unit& _is, T& _v)
    {
        ctk::pml::stream mps(_is);
        mps.setAsInputStream();
        _v.codec(mps);
    }

    template<typename E>
        inline void
        operator<<(Unit& _os, const ctk::Enum<E>& _v)
    {
        _os << (int)_v;
    }
    template<typename E>
        inline bool
        operator>>(const Unit& _is, ctk::Enum<E>& _v)
    {
        int v = -1;
        if (!(_is >> v))
            return false;
        _v = v;
        return true;
    }

    template<class T> inline void
        operator+=(Unit& _os, const T& _v)
    {
        ctk::pml::stream mps;
        mps.setAsOutputStream(_os.allNesessary());
        const_cast<T&>(_v).codec(mps);
        _os += mps.unit();
    }

    template<class T> inline void
        operator<<(Unit& _os, T* const &_v)
    {
        _os << *_v;
    }
    template<class T> inline void
        operator>>(const Unit& _is, T* &_v)
    {
        if (_v)
            _is >> *_v;
    }

    template<class T1, class T2>
        inline void
        operator<<(Unit& _os, const std::pair<T1, T2>& _v)
    {
        _os << _v.second;
        _os.name().clear() << _v.first;
    }
    template<class T1, class T2>
        inline void
        operator>>(const Unit& _is, std::pair<T1, T2>& _v)
    {
        _is >> _v.second;
        _is.name() >> _v.first;
    }
    template<class T1, class T2>
        inline void
        operator>>(const Unit& _is, std::pair<const T1, T2>& _v)
    {
        _is >> _v.second;
        _is.name() >> const_cast<T1&>(_v.first);
    }

    template<class T>
        inline Unit&
        output_(Unit& _os, T _begin, T _end)
    {
        for (T it=_begin; it!=_end; ++it)
        {
            Unit child;
            child << *it;
            _os.addChild(child);
        }
        return _os;
    }
    template<class _Inserter>
        inline const Unit&
        input_(const Unit& _is, _Inserter _inserter)
    {
        ListValue* pLV = 0;
        if (!_is.getValue(pLV))
            return _is;
        
        for (ListValue::const_iterator it=pLV->begin(); it!=pLV->end(); ++it)
        {
            typename _Inserter::container_type::value_type x;
            (*(*it)) >> x;
            *_inserter = x;
        }

        return _is;
    }

    // for STL container classes with begin(), end()
    template<class T>
        inline Unit&
        output(Unit& _os, const T& _v)
    {
        return output_(_os, _v.begin(), _v.end());
    }
    // push_back()
    template<class T>
        inline const Unit&
        input(const Unit& _is, T& _v)
    {
        return input_(_is, std::back_inserter(_v));
    }
    // insert()
    template<class T>
        inline const Unit&
        input_random(const Unit& _is, T& _v)
    {
        return input_(_is, ctk::random_inserter(_v));
    }
    // erase() + insert()
    template<class T>
        inline const Unit&
        update_random(const Unit& _is, T& _v)
    {
        return input_(_is, ctk::pair_updater(_v));
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::vector<T>& _v)
    {
        //_os.type("vector");
        return output(_os, _v);
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::vector<T>& _v)
    {
        _v.clear();
        return input(_is, _v);
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::list<T>& _v)
    {
        //_os.type("list");
        return output(_os, _v);
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::list<T>& _v)
    {
        _v.clear();
        return input(_is, _v);
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::deque<T>& _v)
    {
        //_os.type("deque");
        return output(_os, _v);
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::deque<T>& _v)
    {
        _v.clear();
        return input(_is, _v);
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::queue<T>& _v)
    {
        //_os.type("queue");
        return output(_os, _v._Get_c());
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::queue<T>& _v)
    {
        _v.clear();
        return input(_is, _v._Get_c());
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::stack<T>& _v)
    {
        //_os.type("stack");
        return output(_os, _v._Get_c());
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::stack<T>& _v)
    {
        _v.clear();
        return input(_is, _v._Get_c());
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::set<T>& _v)
    {
        //_os.type("set");
        return output(_os, _v);
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::set<T>& _v)
    {
        _v.clear();
        return input_random(_is, _v);
    }

    template<class T>
        inline Unit&
        operator<<(Unit& _os, const ctk::multiset<T>& _v)
    {
        //_os.type("multiset");
        return output(_os, _v);
    }
    template<class T>
        inline const Unit&
        operator>>(const Unit& _is, ctk::multiset<T>& _v)
    {
        _v.clear();
        return input_random(_is, _v);
    }

    template<class K, class V>
        inline Unit&
        operator<<(Unit& _os, const ctk::map<K,V>& _v)
    {
        _os.type("map");
        return output(_os, _v);
    }
    template<class K, class V>
        inline const Unit&
        operator>>(const Unit& _is, ctk::map<K,V>& _v)
    {
        _v.clear();
        return update_random(_is, _v);
    }

    template<class K, class V>
        inline Unit&
        operator<<(Unit& _os, const ctk::multimap<K,V>& _v)
    {
        _os.type("multimap");
        return output(_os, _v);
    }
    template<class K, class V>
        inline const Unit&
        operator>>(const Unit& _is, ctk::multimap<K,V>& _v)
    {
        _v.clear();
        return input_random(_is, _v);
    }

    template<class T>
        inline
        void
        operator<<(Unit& _os, const ctk::Pointer<T>& _v)
    {
        if (_v)
            _os << *_v;
    }
    template<class T>
        inline
        const Unit&
        operator>>(const Unit& _is, ctk::Pointer<T>& _v)
    {
        if (_v)
            _is >> *_v;
        return _is;
    }

    inline
    void
    operator<<(Unit& _os, const ctk::TriBool& _v)
    {
        _os << (int)_v.get();
    }
    inline
    const Unit&
    operator>>(const Unit& _is, ctk::TriBool& _v)
    {
        int v = -1;
        _is >> v;
        _v.set((ctk::TriBool::_Value)v);
        return _is;
    }

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_STL_H_


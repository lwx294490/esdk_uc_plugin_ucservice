/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// NBR(Nested Binary Representation)
// LSD(LengthOfSize Size Data)

//#ifndef _Z_CTK_NBR_STREAM_H_
//#error "nbr_stl.h should included by pml/stream.h!"
//#endif

#ifndef _Z_CTK_NBR_STL_H_
#define _Z_CTK_NBR_STL_H_

#include "ctk/base/base_type_stl.h"

namespace ctk {
namespace nbr {

    template<class T1, class T2> inline void
        operator<<(OutputStream& _os, const std::pair<T1, T2>& _v)
    {
        OutputStream::Entry __entry(_os);
        _os.write(1, _v.first);
        _os.write(2, _v.second);
    }

    template<class T1, class T2> inline void
        operator>>(InputStream& _is, std::pair<T1, T2>& _v)
    {
        _is.read(1, _v.first);
        _is.read(2, _v.second);
    }

    template<class T1, class T2> inline void
        operator>>(InputStream& _is, std::pair<const T1, T2>& _v)
    {
        _is.read(1, const_cast<T1&>(_v.first));
        _is.read(2, _v.second);
    }

    template<class T> inline void
        output_(OutputStream& _os, T _begin, T _end)
    {
        OutputStream::Entry __entry(_os);
        for (T it=_begin; it!=_end; ++it)
        {
            _os.write(TAG_DUMMY, *it);
        }
    }
    
    template<class _Inserter> inline void
        input_(InputStream& _is, _Inserter _inserter)
    {
        ValueBase* vb = _is.get();
        if (!vb || vb->simple())
            return;

        ComplexValue* cb = dynamic_cast<ComplexValue*>(vb);
        for (ComplexValue::const_iterator it=cb->begin(); it!=cb->end(); ++it)
        {
            typename _Inserter::container_type::value_type x;
            ValueBase* vbValue = (*it).value();
            InputStream isValue(vbValue);
            isValue >> x;
            *_inserter = x;
        }
    }

    // for STL container classes with begin(), end()
    template<class T> inline void
        output(OutputStream& _os, const T& _v)
    {
        return output_(_os, _v.begin(), _v.end());
    }

    // push_back()
    template<class T> inline void
        input(InputStream& _is, T& _v)
    {
        return input_(_is, std::back_inserter(_v));
    }

    // insert()
    template<class T> inline void
        input_random(InputStream& _is, T& _v)
    {
        return input_(_is, ctk::random_inserter(_v));
    }

    // insert()
    template<class T> inline void
        update_random(InputStream& _is, T& _v)
    {
        return input_(_is, ctk::pair_updater(_v));
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::vector<T>& _v)
    {
        return output(_os, _v);
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::list<T>& _v)
    {
        return output(_os, _v);
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::deque<T>& _v)
    {
        return output(_os, _v);
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::queue<T>& _v)
    {
        return output(_os, _v._Get_c());
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::stack<T>& _v)
    {
        return output(_os, _v._Get_c());
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::set<T>& _v)
    {
        return output(_os, _v);
    }

    template<class T> inline void
        operator<<(OutputStream& _os, const ctk::multiset<T>& _v)
    {
        return output(_os, _v);
    }

    template<class K, class V> inline void
        operator<<(OutputStream& _os, const ctk::map<K,V>& _v)
    {
        return output(_os, _v);
    }

    template<class K, class V> inline void
        operator<<(OutputStream& _os, const ctk::multimap<K,V>& _v)
    {
        return output(_os, _v);
    }

    template<class T> inline void
        operator>>(InputStream& _is, ctk::vector<T>& _v)
    {
        _v.clear();
        return input(_is, _v);
    }
    template<class T> inline void
        operator>>(InputStream& _is, ctk::list<T>& _v)
    {
        _v.clear();
        return input(_is, _v);
    }
    template<class T> inline void
        operator>>(InputStream& _is, ctk::deque<T>& _v)
    {
        _v.clear();
        return input(_is, _v);
    }
    template<class T> inline void
        operator>>(InputStream& _is, ctk::queue<T>& _v)
    {
        _v.clear();
        return input(_is, _v._Get_c());
    }
    template<class T> inline void
        operator>>(InputStream& _is, ctk::stack<T>& _v)
    {
        _v.clear();
        return input(_is, _v._Get_c());
    }
    template<class T> inline void
        operator>>(InputStream& _is, ctk::set<T>& _v)
    {
        _v.clear();
        return input_random(_is, _v);
    }
    template<class T> inline void
        operator>>(InputStream& _is, ctk::multiset<T>& _v)
    {
        _v.clear();
        return input_random(_is, _v);
    }
    template<class K, class V> inline void
        operator>>(InputStream& _is, ctk::map<K,V>& _v)
    {
        _v.clear();
        return update_random(_is, _v);
    }
    template<class K, class V> inline void
        operator>>(InputStream& _is, ctk::multimap<K,V>& _v)
    {
        _v.clear();
        return input_random(_is, _v);
    }

} // end of namespace nbr
} // end of namespace ctk

#endif // !_Z_CTK_NBR_STL_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_STL_H_
#define _Z_CTK_XML_STL_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLStream.h"

// map的key将放在节点的__key__属性中。 //

namespace ctk {

    template<class K, class V>
    void operator<<(XMLOutStream& _xos, const std::pair<K,V>& _v)
    {
        std::ostringstream oss;
        oss << _v.first;
        _xos.attr("__key__").value(oss.str());
        _xos << _v.second;
    }
    template<class K, class V>
    bool operator>>(const XMLInStream& _xis, std::pair<K,V>& _v)
    {
        std::istringstream iss(_xis.attr("__key__").value());
        iss  >> _v.first;
        
        return _xis >> _v.second;
    }
    template<class K, class V>
    bool operator>>(const XMLInStream& _xis, std::pair<const K,V>& _v)
    {
        std::istringstream iss(_xis.attr("__key__").value());
        iss  >> const_cast<K&>(_v.first);
        
        return _xis >> _v.second;
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const vector<T>& _v)
    {
        //_xos.type("vector");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, vector<T>& _v)
    {
        _v.clear();
        return _xis.input(std::back_inserter(_v));
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const deque<T>& _v)
    {
        _xos.type("deque");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, deque<T>& _v)
    {
        _v.clear();
        return _xis.input(std::back_inserter(_v));
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const queue<T>& _v)
    {
        _xos.type("queue");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, queue<T>& _v)
    {
        _v.clear();
        return _xis.input(std::back_inserter(_v));
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const stack<T>& _v)
    {
        _xos.type("stack");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, stack<T>& _v)
    {
        _v.clear();
        return _xis.input(std::back_inserter(_v));
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const list<T>& _v)
    {
        _xos.type("list");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, list<T>& _v)
    {
        _v.clear();
        return _xis.input(std::back_inserter(_v));
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const set<T>& _v)
    {
        _xos.type("set");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, set<T>& _v)
    {
        _v.clear();
        return _xis.input(ctk::random_inserter(_v));
    }

    template<class T>
    void operator<<(XMLOutStream& _xos, const multiset<T>& _v)
    {
        _xos.type("multiset");
        _xos.output(_v.begin(), _v.end());
    }
    template<class T>
    bool operator>>(const XMLInStream& _xis, multiset<T>& _v)
    {
        _v.clear();
        return _xis.input(ctk::random_inserter(_v));
    }

    // map的key放在xml节点的__key__属性中 //
    template<class K, class V>
    void operator<<(XMLOutStream& _xos, const map<K, V>& _v)
    {
        _xos.type("map");
        _xos.output(_v.begin(), _v.end());
    }
    // map的key从xml节点的__key__属性中取 //
    template<class K, class V>
    bool operator>>(const XMLInStream& _xis, map<K, V>& _v)
    {
        _v.clear();
        return _xis.input(ctk::random_inserter(_v));
    }

    template<class K, class V>
    void operator<<(XMLOutStream& _xos, const multimap<K, V>& _v)
    {
        _xos.type("multimap");
        _xos.output(_v.begin(), _v.end());
    }
    template<class K, class V>
    bool operator>>(const XMLInStream& _xis, multimap<K, V>& _v)
    {
        _v.clear();
        return _xis.input(ctk::random_inserter(_v));
    }

} // end of namespace ctk

#endif // _Z_CTK_XML_STL_H_


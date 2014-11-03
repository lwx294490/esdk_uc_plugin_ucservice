/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_STL_H_
#define _Z_CTK_BASE_TYPE_STL_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include <deque>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <map>

namespace ctk
{
    using std::deque;
    using std::vector;
    using std::list;
    using std::set;
    using std::multiset;
    using std::map;
    using std::multimap;

    template<class _Ty, class _Container = ctk::deque<_Ty> >
    class queue : public std::queue<_Ty, _Container>
    {
        typedef std::queue<_Ty, _Container> _Super;
        typedef queue<_Ty, _Container> _Self;

    public:
        typedef typename _Container::const_iterator const_iterator;
        typedef typename _Container::iterator iterator;
        typedef typename _Container::reference reference;
        typedef typename _Container::const_reference const_reference;

        const _Container& _Get_c() const
        {
            return _Super::c;
        }
        _Container& _Get_c()
        {
            return _Super::c;
        }

        void clear()
        {
            _Get_c().clear();
        }

        void swap(_Self& _v)
        {
            _Get_c().swap(_v._Get_c());
        }

        void push_back(const _Ty& _v)
        {
            _Get_c().push_back(_v);
        }

        const_iterator begin() const
        {
            return _Get_c().begin();
        }

        const_iterator end() const
        {
            return _Get_c().end();
        }

    };
    template<class _Ty, class _Container >
        inline void swap(queue<_Ty, _Container>& _l, queue<_Ty, _Container>& _r)
    {
        _l.swap(_r);
    }

    template<class _Ty, class _Container = ctk::deque<_Ty> >
    class stack : public std::stack<_Ty, _Container>
    {
        typedef std::stack<_Ty, _Container> _Super;
        typedef stack _Self;

    public:
        typedef typename _Container::const_iterator const_iterator;
        typedef typename _Container::iterator iterator;
        typedef typename _Container::reference reference;
        typedef typename _Container::const_reference const_reference;

        const _Container& _Get_c() const
        {
            return _Super::c;
        }
        _Container& _Get_c()
        {
            return _Super::c;
        }

        void clear()
        {
            _Get_c().clear();
        }

        void swap(_Self& _v)
        {
            _Get_c().swap(_v._Get_c());
        }

        void push_back(const _Ty& _v)
        {
            _Get_c().push_back(_v);
        }

        const_iterator begin() const
        {
            return _Get_c().begin();
        }

        const_iterator end() const
        {
            return _Get_c().end();
        }

    };
    template<class _Ty, class _Container >
        inline void swap(stack<_Ty, _Container>& _l, stack<_Ty, _Container>& _r)
    {
        _l.swap(_r);
    }

    template <class _Container>
    class random_insert_iterator : public std::iterator<std::output_iterator_tag,void,void,void,void>
    {
    protected:
        _Container* container;
    public:
        typedef _Container container_type;
        typedef std::output_iterator_tag iterator_category;

        explicit random_insert_iterator(_Container& __x)
            : container(&__x)
        {
        }
        random_insert_iterator<_Container>&
        operator=(const typename _Container::value_type& __val)
        {
            container->insert(__val);
            return *this;
        }
        random_insert_iterator<_Container>& operator*() { return *this; }
        random_insert_iterator<_Container>& operator++() { return *this; }
        random_insert_iterator<_Container>  operator++(int) { return *this; }
    };

    template <class _Container>
    inline random_insert_iterator<_Container>  CTK_CALL
    random_inserter(_Container& __x)
    {
        return random_insert_iterator<_Container>(__x);
    }

    template <class _Container>
    class pair_update_iterator : public std::iterator<std::output_iterator_tag,void,void,void,void>
    {
        typedef pair_update_iterator<_Container> _Self;
    protected:
        _Container* container;
    public:
        typedef _Container container_type;
        typedef std::output_iterator_tag iterator_category;

        explicit pair_update_iterator(_Container& __x)
            : container(&__x)
        {
        }
        _Self& operator=(const typename _Container::value_type& __val)
        {
            container->erase(__val.first);
            container->insert(__val);
            return *this;
        }
        _Self& operator*() { return *this; }
        _Self& operator++() { return *this; }
        _Self  operator++(int) { return *this; }
    };

    template <class _Container>
    inline pair_update_iterator<_Container>  CTK_CALL
    pair_updater(_Container& __x)
    {
        return pair_update_iterator<_Container>(__x);
    }

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_STL_H_


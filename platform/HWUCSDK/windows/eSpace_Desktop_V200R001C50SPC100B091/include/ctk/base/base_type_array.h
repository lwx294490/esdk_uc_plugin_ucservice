/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_ARRAY_H_
#define _Z_CTK_BASE_TYPE_ARRAY_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/noncopyable.h"

namespace ctk
{
    template<typename T>
    struct array_ref
    {
        typedef array_ref         _Self;

        typedef typename MemberType<T>::type value_type;
        typedef value_type&       reference;
        typedef value_type*       pointer;
        typedef pointer           iterator;
        typedef const value_type& const_reference;
        typedef const value_type* const_pointer;
        typedef const_pointer     const_iterator;

        array_ref()
            : size_(0), data_(0)
        {
        }
        array_ref(size_type _size, pointer _data)
            : size_(_size), data_(_data)
        {
        }
        array_ref(size_type _size, const_pointer _data)
            : size_(_size), data_(const_cast<pointer>(_data))
        {
        }

        iterator begin()
        {
            return data_;
        }

        iterator end()
        {
            return data_ + size_;
        }

        const_iterator begin() const
        {
            return data_;
        }

        const_iterator end() const
        {
            return data_ + size_;
        }

        reference operator[](size_type _i)
        {
            return data_[_i];
        }

        const_reference operator[](size_type _i) const
        {
            return data_[_i];
        }

        pointer data()
        {
            return data_;
        }

        const_pointer data() const
        {
            return data_;
        }

        size_type size() const
        {
            return size_;
        }

    private:
        size_type size_;
        pointer data_;
    };
    template<typename T>
        inline
        array_ref<T>
        make_array_ref(T* _array, size_type _size)
    {
        return array_ref<T>(_size, _array);
    }

    template<typename T, size_type N>
    struct array
    {
        typedef array<T,N>        _Self;

        typedef T                 value_type;
        typedef value_type&       reference;
        typedef value_type*       pointer;
        typedef pointer           iterator;
        typedef const value_type& const_reference;
        typedef const value_type* const_pointer;
        typedef const_pointer     const_iterator;

        array()
        {
        }
        array(const _Self& _v)
        {
            assign(_v);
        }
        template<size_type M>
        array(const array<T, M>& _v)
        {
            assign(_v);
        }
        ~array()
        {
        }

        _Self& operator=(const _Self& _v)
        {
            return assign(_v);
        }
        template<size_type M>
        _Self& operator=(const array<T, M>& _v)
        {
            return assign(_v);
        }

        _Self& assign(const _Self& _v)
        {
            for(size_type i=0; i<max_size(); ++i)
            {
                data_[i] = _v.data_[i];
            }
            return *this;
        }
        template<size_type M>
        _Self& assign(const array<T, M>& _v)
        {
            size_type n = N < M ? N : M;
            for(size_type i=0; i<n; ++i)
            {
                data_[i] = _v.data_[i];
            }
            return *this;
        }

        iterator begin()
        {
            return data_;
        }

        iterator end()
        {
            return data_ + max_size();
        }

        const_iterator begin() const
        {
            return data_;
        }

        const_iterator end() const
        {
            return data_ + max_size();
        }

        reference operator[](size_type _i)
        {
            return data_[_i];
        }

        const_reference operator[](size_type _i) const
        {
            return data_[_i];
        }

        pointer data()
        {
            return data_;
        }

        const_pointer data() const
        {
            return data_;
        }

        CTK_STATIC_FUN size_type max_size()
        {
            return N;
        }

    private:
        T data_[N];
    };
    template<typename T, size_type N>
        inline
        array_ref<T>
        make_array_ref(const array<T,N>& _array, size_type _size=0)
    {
        return array_ref<T>(_size ? _size : _array.max_size(), _array.data());
    }

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_ARRAY_H_


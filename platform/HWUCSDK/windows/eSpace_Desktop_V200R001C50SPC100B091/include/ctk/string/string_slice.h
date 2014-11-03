/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_SLICE_H_
#define _Z_CTK_STRING_SLICE_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"
#include "ctk/base/exception.h"
#include "ctk/base/base_func.h"
#include "ctk/util/util_type_byte.h"
#include "ctk/log/log_debug.h"

namespace ctk
{
    // 具有一定长度的字符串，代表字符串片段 //
    //
    // 代表源字符串。 //
    // 可代替const_pointer。 //
    // 只要是用const_pointer的地方就可以用StringSlice来限定长度。 //
    // 不能修改字符串的内容。 //
    // 析构时不删除缓冲区。 //
    //
    class CTK_API StringSlice
    {
    public:
        typedef StringSlice _Self;

        typedef uchar char_type;
        typedef const char_type & const_reference;
        typedef const char_type * const_pointer;
        typedef const_pointer const_iterator;
        typedef char_type * pointer;

    public:
        StringSlice()
            : addr_(0), size_(0), cursor_(0)
        {
        }
        StringSlice(const _Self& v)
            : addr_(v.addr_), size_(v.size_), cursor_(v.cursor_)
        {
        }
        StringSlice(pcstr v)
            : addr_((const_pointer)v), size_(ctk::StrLen(v)), cursor_(0)
        {
        }
        StringSlice(pcustr v)
            : addr_((const_pointer)v), size_(ctk::StrLen((pcstr)v)), cursor_(0)
        {
        }
        StringSlice(ctk::istr v)
            : addr_((const_pointer)v.data()), size_((size_type)v.size()), cursor_(0)
        {
        }
        StringSlice(const std::string& v)
            : addr_((const_pointer)v.data()), size_((size_type)v.size()), cursor_(0)
        {
        }
        StringSlice(const String& v)
            : addr_((const_pointer)v.data()), size_((size_type)v.size()), cursor_(0)
        {
        }
        StringSlice(pcstr _addr, size_type _size, size_type _cursor=0)
            : addr_((const_pointer)_addr), size_(_size), cursor_(_cursor)
        {
        }
        StringSlice(pcustr _addr, size_type _size, size_type _cursor=0)
            : addr_((const_pointer)_addr), size_(_size), cursor_(_cursor)
        {
        }
        ~StringSlice()
        {
        }

        // 只提供自身复制赋值运算符重载，其它类型的参数可以通过构造函数赋值。 //
        _Self& operator=(const _Self& v)
        {
            if (this == &v)
                return *this;
            return assign(v.data(), v.size(), v.cursor());
        }

        operator ctk::istr() const
        {
            return ctk::istr(data(), size());
        }

        // 下标操作 //

        // 高可靠版 //
        const_reference at(size_type i) const
        {
            return ctk::CharAt(data(), size(), i);
        }

        // 高性能版 //
        const_reference operator[](size_type i) const
        {
            return data()[i];
        }

        // 成员访问 //

        bool empty() const
        {
            return !size();
        }

        pcstr c_str() const
        {
            return (pcstr)data();
        }

        const_pointer data() const
        {
            return addr_;
        }

        size_type size() const
        {
            return size_;
        }

    public:
        // 内置前向迭代器 //
        const_reference operator*() const
        {
            return *current();
        }
        _Self& operator++() 
        {
            if (cursor_ + 1 > size())
                CTK_THROW(OutOfRangeException);
            ++cursor_;
            return *this;
        }
        _Self operator++(int)
        {
            _Self ret = *this;
            ++*this;
            return ret;
        }

        _Self& rewind(size_type _cursor=0)
        {
            if (cursor_ > size())
                CTK_THROW(OutOfRangeException);
            cursor_ = _cursor;
            return *this;
        }

        _Self& advance(size_type _step)
        {
            if (cursor_ + _step > size())
                CTK_THROW(OutOfRangeException);
            cursor_ += _step;
            return *this;
        }

        bool match(istr _v)
        {
            if (left()<_v.size())
                return false;
            return StrEq((pcstr)current(), _v.data(), _v.size());
        }

        bool eof() const
        {
            return !left();
        }

        size_type left() const
        {
            return size() - cursor();
        }

        const_pointer current() const
        {
            return data() + cursor();
        }

        size_type cursor() const
        {
            return cursor_;
        }

        istr next(size_type _n)
        {
            size_type sz = Min(_n, left());
            ctk::istr ret(current(), sz);
            advance(sz);
            return ret;
        }

    public:
        // 将StringSlice当作输入流 //
        _Self& operator>>(char& v)
        {
            v = char(*(*this));
            ++(*this);
            return *this;
        }
        _Self& operator>>(uchar& v)
        {
            v = uchar(*(*this));
            ++(*this);
            return *this;
        }
        _Self& operator>>(ctk::Byte& v)
        {
            v = Byte(*(*this));
            ++(*this);
            return *this;
        }
        //_Self& operator>>(_Self& is, StringRef v);

        _Self& read(pointer _buf, size_type& _sz)
        {
            size_type avail_size = left();
            size_type n = Min(avail_size, _sz);
            if (n>0)
                MemCopy(_buf, current(), n);
            _sz = n;
            advance(n);
            return *this;
        }

    public:
        istr readAllLeft()
        {
            istr allLeft(current(), left());
            advance(left());
            return allLeft;
        }

        istr readUntil(istr _sep)
        {
            const_pointer beg = current();
            while(!eof() && ctk::StrNe((pcstr)current(), _sep.data(), _sep.size()))
            {
                advance(1);
            }
            istr ret(beg, size_type(current() - beg));
            if (!eof())
            {
                advance(_sep.size());
            }
            return ret;
        }

        bool skipTo(istr _sep)
        {
            while(!eof() && ctk::StrNe((pcstr)current(), _sep.data(), _sep.size()))
            {
                advance(1);
            }
            if (eof())
                return false;
            advance(_sep.size());
            return true;
        }

    public:
        // utility methods (readonly)

        // 比较运算符 //

        bool operator==(const _Self& v) const
        {
            return 0 == compare(v);
        }
        bool operator!=(const _Self& v) const
        {
            return 0 != compare(v);
        }
        bool operator<(const _Self& v) const
        {
            return compare(v) < 0;
        }
        bool operator>(const _Self& v) const
        {
            return compare(v) > 0;
        }
        bool operator<=(const _Self& v) const
        {
            return compare(v) <= 0;
        }
        bool operator>=(const _Self& v) const
        {
            return compare(v) >= 0;
        }

        // 比较 //
        int compare(const _Self& v) const;

    public:
        _Self& assign(const char* _addr, size_type _size, size_type _cursor=0);
        _Self& assign(const uchar* _addr, size_type _size, size_type _cursor=0);

        _Self substr(size_type _beg, size_type _num=ctk::npos) const;

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        const_pointer addr_;
        size_type size_;  // 缓冲区片段的大小 //
        size_type cursor_; // 当前读取位置 //

    }; //end: class StringSlice
    inline std::ostream& operator<<(std::ostream& os, const ctk::StringSlice& v)
    {
        return os << ctk::istr(v);
    }
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::StringSlice& v)
    {
        return v.dump(os);
    }

    ///////////////////////////////////////////////////////////////////////////
    typedef StringSlice& (*stringslice_fn)(StringSlice&);
    inline StringSlice& operator>>(StringSlice& _is, stringslice_fn _fn)
    {
        return _fn(_is);
    }
    inline StringSlice& skip(StringSlice& _is)
    {
        return ++_is;
    }

    ///////////////////////////////////////////////////////////////////////////
    struct Skipn__
    {
        Skipn__(size_type _n) : n_(_n) { }
        StringSlice& operator()(StringSlice& _is) const
        {
            return _is.advance(n_);
        }
    private:
        size_type n_;
    };
    inline StringSlice& operator>>(StringSlice& _is, const Skipn__& _fo)
    {
        return _fo(_is);
    }
    inline Skipn__ skipn(size_type _n)
    {
        return Skipn__(_n);
    }

    ///////////////////////////////////////////////////////////////////////////
    template<class T, class _Result, class _Arg>
    struct MemFunc_T
    {
        typedef MemFunc_T<T, _Result, _Arg> _Self;
        typedef _Result (T::*fn_type)(_Arg);
        MemFunc_T(T* _this, fn_type _func)
            : this_(_this), func_(_func)
        {
        }
        MemFunc_T(const _Self& _v)
            :this_(_v.this_), func_(_v.func_)
        {
        }
        _Result operator()(_Arg _c)
        {
            CTK_ASSERT_NOTNULL(this_);
            CTK_ASSERT_NOTNULL(func_);
            return (this_->*func_)(_c);
        }
    private:
        T* this_;
        fn_type func_;
    };
    template<class T, class _Result, class _Arg>
    StringSlice&
    operator>>(StringSlice& _is, MemFunc_T<T, _Result, _Arg> _mfn)
    {
        byte c;
        _is >> c;
        _mfn(c);
        return _is;
    }
    template<class T, class _Result, class _Arg>
    MemFunc_T<T, _Result, _Arg>
    mem_func(T* _this, _Result (T::*_func)(_Arg))
    {
        return MemFunc_T<T, _Result, _Arg>(_this, _func);
    }

    ///////////////////////////////////////////////////////////////////////////
    struct CTK_API ByteRef
    {
        ByteRef(byte& _value, byte _mask)
            : value_(_value), mask_(_mask)
        {
        }
        StringSlice& operator()(StringSlice& _is) const
        {
            _is >> value_;
            value_ &= mask_;
            return _is;
        }
    private:
        byte& value_;
        byte mask_;
        ByteRef& operator=(const ByteRef&); //no impl.
    };
    inline StringSlice& operator>>(StringSlice& _is, const ByteRef& _fn)
    {
        return _fn(_is);
    }

    typedef const StringSlice& rcss;

} // namespace ctk

#endif //_Z_CTK_STRING_SLICE_H_


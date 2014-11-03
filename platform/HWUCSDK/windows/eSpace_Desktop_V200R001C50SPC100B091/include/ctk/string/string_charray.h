/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_CHARRAY_H_
#define _Z_CTK_STRING_CHARRAY_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"
#include "ctk/util/util_func.h"
#include "ctk/log/log_debug.h"
#include "ctk/string/string_ref.h"

namespace ctk
{
    // 安全的、有界的、空字符结束的字符串 //
    //
    // N 是实际允许的最大长度，缓冲区将分配N+1个字符。 //
    //
    // 占用的空间与原始的字符数组相同，但记录了最大长度，可简化赋值、拷贝等操作。 //
    //
    template <size_type N>
    class charray
    {
    public:
        typedef charray<N> _Self;

        typedef char char_type;
        typedef char_type& reference;
        typedef const char_type& const_reference;
        typedef char_type* pointer;
        typedef const char_type* const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

    public:
        // 构造函数 //
        charray()
        {
            m_buf[0] = C_null;
            m_buf[N] = C_null;
        }
        charray(char_type _c, size_type _num=npos)
        {
            m_buf[0] = C_null;
            StringRef(*this).fill(_c, _num);
            m_buf[Min(_num,N)] = C_null;
        }
        charray(const _Self& v)
        {
            assign(v.data(), v.size());
        }
        charray(const istr& v)
        {
            assign((const_pointer)v.data(), v.size());
        }
        charray(const_pointer v, size_type _sz)
        {
            assign(v, _sz);
        }
        ~charray()
        {
        }

        _Self& reset()
        {
            m_buf[0] = C_null;
            return *this;
        }

        // 赋值运算符 //
        _Self& operator=(const _Self& v)
        {
            if (this == &v)
                return *this;
            return assign(v.data(), v.size());
        }
        _Self& operator=(const istr& v)
        {
            return assign(v.data(), v.size());
        }

        // 添加操作建议用StringRef来做，因为StringRef可以记录实际长度。 //

        _Self& operator+=(char_type c)
        {
            return append(&c, 1);
        }
        _Self& operator+=(const istr& v)
        {
            return append(v.data(), v.size());
        }

        _Self operator+(char_type c) const
        {
            _Self ret(*this);
            ret += c;
            return ret;
        }
        _Self operator+(const istr& v) const
        {
            _Self ret(*this);
            ret += v;
            return ret;
        }

        operator istr () const
        {
            return istr(data(), size());
        }

        operator ostr ()
        {
            return ostr(buffer(), max_size());
        }

        operator StringRef ()
        {
            return StringRef(buffer(), max_size(), size());
        }

        // 下标操作 //

        // 高可靠版 //
        const_reference at(size_type i) const
        {
            return CharAt(data(), max_size(), i);
        }
        reference at(size_type i)
        {
            return CharAt(buffer(), max_size(), i);
        }
        
        // 高性能版 //
        const_reference operator[](size_type i) const
        {
            return data()[i];
        }
        reference operator[](size_type i)
        {
            return buffer()[i];
        }

        bool empty() const
        {
            return !*data();
        }

        pcstr c_str() const
        {
            return (pcstr)data();
        }

        // 直接返回内部缓冲区，供高级用户使用。 //
        // 小心使用，不可超出限定长度。 //
        pointer buffer()
        {
            return m_buf;
        }
        
        const_pointer data() const
        {
            return m_buf;
        }

        // 获取大小 //
        // 为了不增加空间开销，这里使用strlen来取实际长度，较慢。 //
        // 如果希望记录长度，请使用下面的ChArray<N>， //
        // 或者转换成StringRef再做操作。 //
        //
        size_type size() const
        {
            return StrLen(m_buf);
        }

        CTK_STATIC_FUN size_type max_size()
        {
            return N;
        }

    public:
        // 赋值 //
        _Self& assign(pcstr _buf, size_type _sz)
        {
            CTK_ENSURE_MSG(_sz<=max_size(), CTK_VAR(_buf)<<CTK_VAR(_sz)<<CTK_VAR(max_size()));
            MemCopyZ(buffer(), _buf, Min(_sz, max_size()));
            return *this;
        }
        _Self& assign(pcustr _buf, size_type _sz)
        {
            return assign((pcstr)_buf, _sz);
        }

        // 添加 //
        _Self& append(pcstr _buf, size_type _sz)
        {
            size_type maxSize = max_size();
            size_type curSize = size();
            CTK_ENSURE_MSG(_sz<=maxSize-curSize, CTK_VAR(_buf)<<CTK_VAR(_sz)<<CTK_VAR(maxSize)<<CTK_VAR(curSize));
            size_type n = maxSize - curSize;
            MemCopyZ(buffer()+curSize, _buf, Min(_sz, n));
            return *this;
        }
        _Self& append(pcustr _buf, size_type _sz)
        {
            return append((pcstr)_buf, _sz);
        }

    private:
        enum { maxSize_ = N };
        char_type m_buf[N + 1]; // always null terminated string

    }; //end: class charray<N>
    template <size_type N>
    inline std::ostream& operator<<(std::ostream& os, const ctk::charray<N>& v)
    {
        return os << istr(v);
    }

} // namespace ctk

#endif //_Z_CTK_STRING_CHARRAY_H_


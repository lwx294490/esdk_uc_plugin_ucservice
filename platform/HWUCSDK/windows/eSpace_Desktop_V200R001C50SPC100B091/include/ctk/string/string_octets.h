/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_OCTETS_H_
#define _Z_CTK_STRING_OCTETS_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_ref.h"

#include "ctk/log/log_macros.h"

namespace ctk
{
    // 字节数组 //
    //
    // N 是数组长度，缓冲区只分配N字节，没有结束符。 //
    //
    template <size_type N>
    class octets
    {
    public:
        typedef octets<N> _Self;

        typedef octet char_type;
        typedef char_type& reference;
        typedef const char_type& const_reference;
        typedef char_type* pointer;
        typedef const char_type* const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

    public:
        // 构造函数 //
        octets()
        {
            memset(m_buf, 0, sizeof(m_buf));
        }
        octets(char_type _c, size_type _num=npos)
        {
            StringRef(*this).fill(_c, _num);
        }
        octets(const _Self& v)
        {
            assign(v.data(), v.size());
        }
        octets(const istr& v)
        {
            assign((const_pointer)v.data(), v.size());
        }
        octets(pcstr v, size_type _sz)
        {
            assign((const_pointer)v, _sz);
        }
        octets(pcustr v, size_type _sz)
        {
            assign((const_pointer)v, _sz);
        }
        ~octets()
        {
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
            return assign((const_pointer)v.data(), v.size());
        }

        // 不能做+=操作，因为没有结束符，没有当前长度。 //

        operator istr () const
        {
            return istr((istr::const_pointer)data(), size());
        }

        operator ostr()
        {
            return ostr(buffer(), max_size());
        }

        operator StringRef ()
        {
            return StringRef((StringRef::pointer)buffer(), max_size());
        }

        // 下标操作 //

        // 高可靠版 //
        const_reference at(size_type i) const
        {
            return CharAt(data(), size(), i);
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
            return false;
        }

        // 直接返回内部缓冲区，供高级用户使用 //

        pointer buffer() // 小心使用，不可超出限定长度 //
        {
            return m_buf;
        }
        
        const_pointer data() const
        {
            return m_buf;
        }

        // 获取大小 //

        size_type size() const
        {
            return max_size();
        }

        CTK_STATIC_FUN size_type max_size()
        {
            return N;
        }

    public:
        // 赋值 //
        _Self& assign(const_pointer _buf, size_type _sz)
        {
            CTK_ENSURE(_sz<=max_size());
            MemCopy(buffer(), _buf, Min(_sz, max_size()));
            return *this;
        }

    public:
        ctk::dumper& dump(ctk::dumper& os) const
        {
            //CTK_DUMP(os, "ctk::octets<"<<N<<">");
            //DUMP_VAR(os, size());
            //DUMP_HEX(os, m_buf, max_size());
            DUMP_NVL(os, buf, istr(m_buf, size()));
            return os;
        }
        std::ostream& dump(std::ostream& _os) const
        {
            dumper d(_os);
            dump(d);
            return _os;
        }

    private:
        char_type m_buf[N];

    }; //end: class octets<N>
    template <size_type N>
    inline std::ostream& operator<<(std::ostream& os, const ctk::octets<N>& v)
    {
        return os << ctk::write_hex(v.data(), v.size());
    }
    template <size_type N>
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::octets<N>& v)
    {
        return v.dump(os);
    }

} // namespace ctk

#endif //_Z_CTK_STRING_OCTETS_H_


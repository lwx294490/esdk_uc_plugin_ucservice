/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_BUFFER_H_
#define _Z_CTK_STRING_BUFFER_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"
#include "ctk/string/string_ref.h"
#include "ctk/string/string_octets.h"

namespace ctk
{
    // 可扩展大小的字符串缓冲区 //
    //
    // 在构造函数中可指定初始大小，以后根据需要扩展。 //
    //
    // 缓冲区在堆中。 //
    //
    class CTK_API StringBuffer
    {
    public:
        typedef StringBuffer _Self;

        typedef uchar char_type;
        typedef char_type & reference;
        typedef const char_type & const_reference;
        typedef char_type * pointer;
        typedef const char_type * const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

    public:
        StringBuffer(size_type _maxSize = 0)
            : maxSize_(_maxSize)
        {
            init();
            buffer()[curSize_] = C_null;
        }
        StringBuffer(const _Self& v)
            : maxSize_(v.maxSize_)
        {
            init();
            assign(v.data(), v.size());
        }
        StringBuffer(const istr& v)
            : maxSize_(v.size())
        {
            init();
            assign(v.data(), v.size());
        }
        StringBuffer(pcstr _buf, size_type _sz)
            : maxSize_(_sz)
        {
            init();
            assign((const_pointer)_buf, _sz);
        }
        StringBuffer(pcustr _buf, size_type _sz)
            : maxSize_(_sz)
        {
            init();
            assign((const_pointer)_buf, _sz);
        }
        ~StringBuffer()
        {
            uninit();
        }

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
            _Self ret(max_size() + 1);
            ret = *this;
            ret += c;
            return ret;
        }
        _Self operator+(const istr& v) const
        {
            _Self ret(max_size() + v.size());
            ret = *this;
            ret += v;
            return ret;
        }

        operator istr() const
        {
            return istr(data(), size());
        }

        operator ostr()
        {
            return ostr(buffer(), max_size());
        }

        operator StringRef()
        {
            return StringRef(buffer(), max_size(), size());
        }
        // 不推荐转换成StringRef使用，因为本类是可以扩展大小的， //
        // 而StringRef不可以扩展。 //

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
            return !size();
        }

        pcstr c_str() const
        {
            return (pcstr)data();
        }

        String str() const
        {
            return String(data(), size());
        }

        pointer buffer()
        {
            return isInternal() ? localbuf_.buffer() : buffer_;
        }

        const_pointer data() const
        {
            return isInternal() ? localbuf_.data() : buffer_;
        }

        void size(size_type _sz)
        {
            curSize_ = _sz;
        }

        size_type size() const
        {
            return curSize_;
        }

        size_type max_size() const
        {
            return maxSize_;
        }

    public:
        _Self& operator-=(char_type& c)
        {
            size_type sz = 1;
            return read(&c, sz);
        }
        _Self& operator-=(StringRef v)
        {
            size_type sz = v.left();
            read(v.buffer(), sz);
            v.advance(sz);
            return *this;
        }

        _Self operator-(char_type& c) const
        {
            _Self ret(*this);
            ret -= c;
            return ret;
        }
        _Self operator-(StringRef v) const
        {
            _Self ret(*this);
            ret -= v;
            return ret;
        }

        _Self& write(const_pointer _buf, size_type _sz)
        {
            return append(_buf, _sz);
        }

        _Self& read(pointer _buf, size_type& _sz);

        pointer pbuf()
        {
            return buffer() + psize();
        }

        const_pointer gbuf() const
        {
            return data() + gsize();
        }

        void psize(size_type _sz)
        {
            size(_sz);
        }

        void gsize(size_type _sz)
        {
            readPos_ = _sz;
        }

        size_type psize() const // put/write size
        {
            return size();
        }

        size_type gsize() const // get/read size
        {
            return readPos_;
        }

        bool isInternal() const
        {
            return internal_;
        }

    public:
        _Self& assign(pcstr _buf, size_type _sz)
        {
            return assign((pcustr)_buf, _sz);
        }
        _Self& append(pcstr _buf, size_type _sz)
        {
            return append((pcustr)_buf, _sz);
        }
        _Self& assign(pcustr _buf, size_type _sz);
        _Self& append(pcustr _buf, size_type _sz);
        void needMore(size_type _sz);

        void swap(_Self& _v);

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        void init();
        void alloc(CTK_CURRENT_ARGS);
        void uninit();

        enum { INTERNAL_BUFSIZE = 255 };

    private:
        pointer buffer_;
        size_type maxSize_;
        size_type curSize_;

        size_type readPos_;

        octets<INTERNAL_BUFSIZE+1> localbuf_;
        bool internal_; // 是否使用内部缓冲区（局部，可使用栈） //

    }; //end of class StringBuffer
    inline std::ostream& operator<<(std::ostream& os, const ctk::StringBuffer& v)
    {
        return os << ctk::istr(v.data(), v.size());
    }
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::StringBuffer& v)
    {
        return v.dump(os);
    }
    inline void swap(StringBuffer& _l, StringBuffer& _r)
    {
        _l.swap(_r);
    }

} // namespace ctk

#endif //_Z_CTK_STRING_BUFFER_H_


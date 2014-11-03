/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_BYTES_H_
#define _Z_CTK_BASE_TYPE_BYTES_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_ostr.h"

namespace ctk
{
    struct base64
    {
        istr buf_;

        explicit base64(rcistr _buf=istr())
            : buf_(_buf)
        {
        }
    };

    // 动态分配的二进制数据，析构时删除缓冲区 //
    //
    class CTK_API Bytes
    {
    public:
        typedef Bytes _Self;
        typedef byte char_type;
        typedef char_type* buff_type;
        typedef char_type* pointer;
        typedef char_type* iterator;
        typedef const char_type* const_pointer;
        typedef const char_type* const_iterator;

    public:
        Bytes();
        explicit Bytes(size_type _max_size);
        Bytes(const _Self& v);
        Bytes(istr const& v);
        Bytes(istr v, size_type _max_size, char_type _fill);
        Bytes(base64 const& v);
        ~Bytes();

        void init(size_type _max_size);

        void resize(size_type _maxSize);

        void clear();

        Bytes& fill(char_type ch);

        operator istr() const;

        operator ostr();

        _Self& operator=(const _Self& v);
        _Self& operator=(istr v);

        _Self& operator+=(istr v);

        char_type& operator[](size_type _i) { return buffer()[_i]; }

        const char_type& operator[](size_type _i) const { return data()[_i]; }

        bool operator==(istr _v) const { return istr(*this)==_v; }
        bool operator!=(istr _v) const { return istr(*this)!=_v; }
        bool operator<=(istr _v) const { return istr(*this)<=_v; }
        bool operator>=(istr _v) const { return istr(*this)>=_v; }
        bool operator<(istr _v) const { return istr(*this)<_v; }
        bool operator>(istr _v) const { return istr(*this)>_v; }

        _Self& assign(const _Self& v);
        _Self& assign(istr v);

        _Self& append(istr v);

        void swap(_Self& _v);

        const_iterator begin() const;
        const_iterator end() const;

        pointer buffer();

        size_type max_size() const;

        const_pointer data() const;

        size_type size() const;

        pcstr c_str() const;

        bool empty() const;

        void size(size_type _sz);

    private:
        void alloc(size_type n);
        void free();

        void reset();

        void set(const _Self& v);
        void set(istr v);
        void set(pcustr psz, size_type len);
        void set(pcstr psz, size_type len);

        void copy(size_type _offset, istr _v);
        void copy(size_type _offset, pcstr _data, size_type _size);

        void advance(size_type _sz);

    private:
        char_type * buffer_;  // 接管buffer的生命周期 //
        size_type   maxSize_;
        size_type   curSize_;
    };
    inline std::ostream& operator<< (std::ostream& os, const Bytes& v)
    {
        return os << istr(v);
    }
    inline void swap(Bytes& _l, Bytes& _r)
    {
        _l.swap(_r);
    }

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_BYTES_H_


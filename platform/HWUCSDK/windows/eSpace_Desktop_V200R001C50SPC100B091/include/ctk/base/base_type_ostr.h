/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_OSTR_H_
#define _Z_CTK_BASE_TYPE_OSTR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_istr.h"

#define CTK_FROM_ARRAY(x) x, sizeof(x)/sizeof(x[0])

namespace ctk
{
    // 代替原始字符数组 //
    struct CTK_API ostr
    {
        typedef ostr _Self;
        typedef char char_type;
        typedef char_type* buff_type;
        typedef char_type* pointer;
        typedef char_type* iterator;
        typedef const char_type* const_pointer;
        typedef const char_type* const_iterator;

        ostr();
        ostr(const _Self& _v);  // 直接赋值 //
        ostr(pstr _buf, size_type _len);
        ostr(pustr _buf, size_type _len);

        // 直接赋值 //
        _Self& operator=(const _Self& _v);

        // 复制 //
        _Self& operator=(pcstr _v);
        _Self& operator=(pcustr _v);
        _Self& operator=(istr _v);

        operator istr() const;

        _Self substr(size_type _pos=0, size_type _n=npos) const;
        _Self leftstr(size_type _n=npos) const;
        _Self rightstr(size_type _n=npos) const;

        char_type& operator[](size_type _i) { return buffer()[_i]; }

        const char_type& operator[](size_type _i) const { return data()[_i]; }

        const_iterator begin() const { return data(); }

        const_iterator end() const { return data() + size(); }

        iterator begin() { return buffer(); }

        iterator end() { return buffer() + max_size(); }

        bool empty() const { return !data() || !max_size(); }

        buff_type buffer() { return buf_; }

        size_type max_size() const { return len_; }

        pcstr data() const { return (pcstr)buf_; }

        size_type size() const; // use strlen
        size_type sizeN() const;
        size_type sizeN(size_type _maxLen) const;

        _Self& clear();
        _Self& reset();

        _Self& assign(const _Self& _v);
        _Self& assign(pcstr _buf, size_type _n);
        _Self& assign(pcustr _buf, size_type _n);
        _Self& assign(pcstr _buf);
        _Self& assign(pcustr _buf);
        _Self& assign(istr _v);

        std::ostream& dump(std::ostream& os) const;

    private:
        size_type len_;
        buff_type buf_;
    };
    inline std::ostream& operator<<(std::ostream& _os, const ctk::ostr& _v)
    {
        return _os << istr(_v);
    }

    class owstr
    {
        typedef owstr _Self;
        typedef wchar_t char_type;
        typedef char_type* buffer_type;
        typedef char_type* pointer;

        buffer_type buf_;
        size_type   len_;

    public:
        owstr(pointer _buf, size_type _len)
            : buf_(_buf), len_(_len)
        {
        }

        pointer buffer()
        {
            return buf_;
        }

        size_type max_size() const
        {
            return len_;
        }

    };

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_OSTR_H_


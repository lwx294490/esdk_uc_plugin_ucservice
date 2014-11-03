/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_ISTR_H_
#define _Z_CTK_BASE_TYPE_ISTR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    // 代替函数参数(pcstr/pcustr, size_type) //
    struct CTK_API istr
    {
        typedef istr _Self;
        typedef char char_type;
        typedef const char_type* buff_type;
        typedef const char_type* const_pointer;
        typedef const char_type* const_iterator;

        istr();
        istr(const istr& _v);
        istr(const std::string& _v);
        istr(pcstr _buf, size_type _len=npos);
        istr(pcustr _buf, size_type _len=npos);
        istr(pcstr _begin, pcstr _end);
        istr(istr _v, size_type _len);

        // 编译器生成的默认构造函数和赋值运算符是可用的 //

        // 赋值运算符可以通过单参数构造函数得到 //

        _Self& operator=(const _Self& _v);

        operator std::string() const
        {
            return std::string(data(), size());
        }

        bool operator==(const _Self& _v) const;
        bool operator<(const _Self& _v) const;
        bool operator>(const _Self& _v) const;
        bool operator!=(const _Self& _v) const;
        bool operator<=(const _Self& _v) const;
        bool operator>=(const _Self& _v) const;
        int compare(const _Self& _v) const;

        istr substr(size_type _pos=0, size_type _n=npos) const;
        istr leftstr(size_type _n=npos) const;
        istr rightstr(size_type _n=npos) const;

        istr removeLeft(size_type _len) const;
        istr removeLeft(const _Self& _v) const;
        istr removeRight(size_type _len) const;
        istr removeRight(const _Self& _v) const;

        _Self trimLeft() const;
        _Self trimRight() const;
        _Self trim() const;

        bool beginWith(_Self _v) const;
        bool endWith(_Self _v) const;

        const char_type& operator[](size_type _i) const { return data()[_i]; }

        const_iterator begin() const { return data(); }

        const_iterator end() const { return data() + size(); }

        bool empty() const { return !buf_ || !len_; }

        bool is_null() const { return !buf_; }

        pcstr c_str() const { return (pcstr)buf_; }

        const_pointer data() const { return buf_; }

        size_type size() const { return len_; }

        std::ostream& dump(std::ostream& os) const;

    private:
        size_type len_;
        buff_type buf_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const ctk::istr& _v);

    typedef const istr & rcistr;

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_ISTR_H_


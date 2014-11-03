/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_IWSTR_H_
#define _Z_CTK_BASE_TYPE_IWSTR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    struct CTK_API iwstr
    {
        typedef iwstr _Self;
        typedef wchar char_type;
        typedef const char_type* buff_type;
        typedef const char_type* const_pointer;
        typedef const char_type* const_iterator;

        iwstr();
        iwstr(const iwstr& _v);
        iwstr(const std::wstring& _v);
        iwstr(pcwstr _buf, size_type _len=npos);
        iwstr(pcwstr _begin, pcwstr _end);
        iwstr(const iwstr& _v, size_type _len);

        // 编译器生成的默认构造函数和赋值运算符是可用的 //

        // 赋值运算符可以通过单参数构造函数得到 //

        _Self& operator=(const _Self& _v);

        operator std::wstring() const
        {
            return std::wstring(data(), size());
        }

        bool operator==(const _Self& _v) const;
        bool operator<(const _Self& _v) const;
        bool operator>(const _Self& _v) const;
        bool operator!=(const _Self& _v) const;
        bool operator<=(const _Self& _v) const;
        bool operator>=(const _Self& _v) const;
        int compare(const _Self& _v) const;

        iwstr substr(size_type _pos=0, size_type _n=npos) const;
        iwstr leftstr(size_type _n=npos) const;
        iwstr rightstr(size_type _n=npos) const;

        iwstr removeLeft(size_type _len) const;
        iwstr removeLeft(const _Self& _v) const;
        iwstr removeRight(size_type _len) const;
        iwstr removeRight(const _Self& _v) const;

        _Self trimLeft() const;

        bool beginWith(_Self _v) const;
        bool endWith(_Self _v) const;

        const char_type& operator[](size_type _i) const { return data()[_i]; }

        const_iterator begin() const { return data(); }

        const_iterator end() const { return data() + size(); }

        bool empty() const { return !buf_ || !len_; }

        bool is_null() const { return !buf_; }

        pcwstr c_str() const { return (pcwstr)buf_; }

        const_pointer data() const { return buf_; }

        size_type size() const { return len_; }

        std::ostream& dump(std::ostream& os) const;

    private:
        size_type len_;
        buff_type buf_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const ctk::iwstr& _v);

    typedef const iwstr & rciwstr;

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_IWSTR_H_


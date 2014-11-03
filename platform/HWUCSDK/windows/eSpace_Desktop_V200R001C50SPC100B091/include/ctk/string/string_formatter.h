/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_FORMATTER_H_
#define _Z_CTK_STRING_FORMATTER_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"
#include "ctk/string/string_ref.h"
#include "ctk/string/string_charray.h"
 
#include "ctk/log/log_macros.h"

namespace ctk
{
    template<size_type N=CTK_MAX_DEBUG_LINE_LEN>
    class StringFormatter
    {
    public:
        typedef StringFormatter<N> _Self;

        typedef ctk::charray<N> store_type;

    public:
        StringFormatter(char _f=0, size_type _num=npos)
            : fill_(_f), ref_(buf_)
        {
            fill(fill_, _num);
        }

        _Self& reset(char _f)
        {
            fill_ = _f;
            return reset();
        }

        _Self& reset()
        {
            rewind();
            fill(fill_);
            return *this;
        }

        _Self& rewind(size_type _size=0)
        {
            ref_.rewind(_size);
            return *this;
        }

        _Self& fill(char c, size_type num=npos)
        {
            ref_.fill(c, num);
            return *this;
        }

        _Self& center(const istr& s)
        {
            ref_.center(s);
            return *this;
        }

        _Self& left(const istr& s)
        {
            ref_.left(s);
            return *this;
        }

        _Self& right(const istr& s)
        {
            ref_.right(s);
            return *this;
        }

        _Self& right(char c, size_type num)
        {
            ref_.right(c, num);
            return *this;
        }

        operator istr() const
        {
            return istr(ref_);
        }

        StringRef& ref()
        {
            return ref_;
        }

        pcstr data() const
        {
            return (pcstr)ref_.data();
        }

        size_type size() const
        {
            return ref_.size();
        }

        size_type max_size() const
        {
            return ref_.max_size();
        }

    private:
        store_type buf_;
        StringRef ref_;
        char fill_;
    };
    template <size_type N>
    inline std::ostream& operator<<(std::ostream& os, const ctk::StringFormatter<N>& v)
    {
        return os << istr(v);
    }

} // namespace ctk

#endif //_Z_CTK_STRING_FORMATTER_H_


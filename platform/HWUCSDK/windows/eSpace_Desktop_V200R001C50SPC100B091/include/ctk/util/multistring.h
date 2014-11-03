/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_MULTISTRING_H_
#define _Z_CTK_UTIL_MULTISTRING_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{
    class CTK_API MultiString
    {
    public:
        typedef MultiString _Self;
        typedef std::list<String> _List;

    public:
        MultiString(istr _full, istr _sep=" ")
            : full_(_full), sep_(_sep)
        {
            split();
        }
        MultiString(const _List& _list, istr _sep=" ")
            : list_(_list), sep_(_sep)
        {
            merge();
        }

        _Self& split();
        _Self& merge();

        _Self& clear()
        {
            full_.clear();
            list_.clear();
            return *this;
        }

        _Self& set(istr _full)
        {
            return full(_full);
        }

        _Self& add(istr _seg)
        {
            if (!list_.empty())
                full_ << sep_;
            full_ << _seg;
            list_.push_back(_seg);
            return *this;
        }

        _Self& full(istr _full)
        {
            full_ = _full;
            split();
            return *this;
        }

        _Self& list(const _List& _list)
        {
            list_ = _list;
            merge();
            return *this;
        }

        _Self& separator(istr _sep)
        {
            sep_ = _sep;
            merge();
            return *this;
        }

        istr full() const
        {
            return full_;
        }

        const _List& list() const
        {
            return list_;
        }

        istr separator() const
        {
            return sep_;
        }

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        String full_;
        _List list_;
        String sep_;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::MultiString& v)
    {
        return v.dump(os);
    }
    inline std::ostream& operator<<(std::ostream& os, const ctk::MultiString& v)
    {
        return v.dump(os);
    }

} // namespace ctk

#endif //_Z_CTK_UTIL_MULTISTRING_H_


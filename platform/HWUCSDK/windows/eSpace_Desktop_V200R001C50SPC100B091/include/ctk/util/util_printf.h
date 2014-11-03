/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_PRINTF_H_
#define _Z_CTK_UTIL_PRINTF_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk {

    class CTK_API Printf
    {
    public:
        typedef Printf _Self;

    public:
        struct Tag
        {
            pcstr beg_;
            pcstr end_;

            Tag(pcstr _beg, pcstr _end)
                : beg_(_beg), end_(_end)
            {
            }

            operator istr() const
            {
                return istr(beg_, (size_type)(end_-beg_));
            }
            
            ptrdiff_t size() const
            {
                return end_-beg_;
            }

            ctk::dumper& dump(ctk::dumper& _os) const;
            std::ostream& dump(std::ostream& _os) const;
        };
        typedef std::vector<Tag> _Tags;

    public:
        Printf(pcstr _fmt, char _flag='$', char _left='(', char _right=')', char _escape='\\');

        // 为了重复利用，从头开始 //
        _Self& reset();

        // 得到结果 //
        rcstr str() const;

        // 替换 //
        const _Self& replaceNext(istr _v) const;

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        String format_;
        _Tags tags_;
        char flag_;
        char left_;
        char right_;
        char escape_;
        mutable size_type curr_; // current index in vector
        mutable String tempbuf_;
        mutable String result_;

    };
    inline ctk::dumper& operator<<(ctk::dumper& _os, const Printf::Tag& _v)
    {
        return _v.dump(_os);
    }
    inline ctk::dumper& operator<<(ctk::dumper& _os, const Printf& _v)
    {
        return _v.dump(_os);
    }
    inline std::ostream& operator<<(std::ostream& _os, const Printf::Tag& _v)
    {
        return _v.dump(_os);
    }
    inline std::ostream& operator<<(std::ostream& _os, const Printf& _v)
    {
        return _os << _v.str();
    }

    //为了在表达式中直接使用Printf构造临时变量，在参数和返回类型增加const属性 //
    template<class T>
    const Printf& operator%(const Printf& _os, const T& _v)
    {
        std::ostringstream oss;
        oss << _v;
        return _os.replaceNext(oss.str());
    }

} // end of namespace ctk

#endif //_Z_CTK_UTIL_PRINTF_H_


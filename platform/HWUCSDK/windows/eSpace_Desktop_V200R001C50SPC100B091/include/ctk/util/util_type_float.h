/* CTK(Mini Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_FLOAT_H_
#define _Z_CTK_UTIL_TYPE_FLOAT_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"

#include "ctk/util/util_func.h"

namespace ctk
{
    class CTK_API Float
    {
    public:
        typedef Float _Self;

        typedef float value_type;

    public:
        Float()
            : value_(0)
        {
        }
        Float(value_type _v)
            : value_(_v)
        {
        }
        explicit Float(rcstr _s)
        {
            fromString(_s);
        }
        explicit Float(rcwstr _s)
        {
            fromString(ctk::to_ansi(_s));
        }

        _Self& fromString(rcstr _s)
        {
            _s >> value_;
            return *this;
        }

        String toString() const
        {
            String ret;
            ret << value_;
            return ret;
        }

        _Self& operator=(value_type _v)
        {
            value_ = _v;
            return *this;
        }

        _Self operator-() const
        {
            return _Self(-value_);
        }

        operator value_type& ()
        {
            return value_;
        }

        operator value_type () const
        {
            return value_;
        }

        value_type& value()
        {
            return value_;
        }

        value_type value() const
        {
            return value_;
        }

    public:
        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const
        {
            return _os << print(value_);
        }

    private:
        value_type value_;

    };
    inline std::ostream& operator<<(std::ostream& os, const Float& v)
    {
        return os << v.value();
    }

}

#endif //_Z_CTK_UTIL_FLOAT_H_


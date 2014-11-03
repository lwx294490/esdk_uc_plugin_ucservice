/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_FUNCNAME_H_
#define _Z_CTK_UTIL_FUNCNAME_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{

    class CTK_API Funcname
    {
    public:
        typedef Funcname _Self;

        Funcname()
        {
        }
        Funcname(istr _full)
            : full_(_full)
        {
            split();
        }
        Funcname(istr _ns, istr _func)
            : ns_(_ns), func_(_func)
        {
            merge();
        }

        _Self& split();
        _Self& merge();

        _Self& full(istr _full)
        {
            full_ = _full;
            split();
            return *this;
        }
        _Self& ns(istr _ns)
        {
            ns_ = _ns;
            merge();
            return *this;
        }
        _Self& func(istr _func)
        {
            func_ = _func;
            merge();
            return *this;
        }

        istr full() const
        {
            return full_;
        }
        istr ns() const
        {
            return ns_;
        }
        istr func() const
        {
            return func_;
        }

        CTK_STATIC_FUN pcstr separator();

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        String full_;
        String ns_;   // namespace name
        String func_;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::Funcname& v)
    {
        return v.dump(os);
    }
    inline std::ostream& operator<<(std::ostream& os, const ctk::Funcname& v)
    {
        return v.dump(os);
    }

} // namespace ctk

#endif //_Z_CTK_UTIL_FUNCNAME_H_


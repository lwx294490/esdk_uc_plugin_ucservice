/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_FILENAME_H_
#define _Z_CTK_UTIL_FILENAME_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{
    class CTK_API Filename
    {
    public:
        typedef Filename _Self;
        typedef wchar    _Char;
        typedef iwstr    _Istr;
        typedef Wstring  _String;

        Filename();
        Filename(_Istr _full);
        Filename(_Istr _dir, _Istr _file);

        _Self& split();
        _Self& merge();

        _Self& full(_Istr _full);
        _Self& dir(_Istr _dir);
        _Self& file(_Istr _file);

        _Istr full() const;
        _Istr dir() const;
        _Istr file() const;

        CTK_STATIC_FUN _Char separator();

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        _String full_;
        _String dir_;
        _String file_;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::Filename& v)
    {
        return v.dump(os);
    }
    inline std::ostream& operator<<(std::ostream& os, const ctk::Filename& v)
    {
        return v.dump(os);
    }

} // namespace ctk

#endif //_Z_CTK_UTIL_FILENAME_H_


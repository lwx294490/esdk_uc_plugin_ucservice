/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_STRING_H_
#define _Z_CTK_XML_STRING_H_

#include "ctk/xml/XMLBase.h"

namespace ctk {

    class CTK_API XMLInputString
    {
        String str_;

    public:
        XMLInputString()
        {
        }
        explicit XMLInputString(rcistr _str)
            : str_(_str)
        {
        }

        rcstr str() const
        {
            return str_;
        }

    };

} // end of namespace ctk

#endif // _Z_CTK_XML_STREAM_H_


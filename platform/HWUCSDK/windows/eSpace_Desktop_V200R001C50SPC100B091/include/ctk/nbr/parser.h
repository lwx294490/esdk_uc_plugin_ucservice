/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// NBR(Nested Binary Representation)
// LSD(LengthOfSize Size Data)

#ifndef _Z_CTK_NBR_PARSER_H_
#define _Z_CTK_NBR_PARSER_H_

#include "ctk/ctk_config.h"

#include "ctk/nbr/lsd.h"

namespace ctk {
namespace nbr {

    struct CTK_API DecodeException : public Exception
    {
        typedef Exception _Super;

        DecodeException(CTK_CURRENT_ARGS, pcstr _msg);
    };

    class CTK_API parser
    {
        ctk::StringSlice iptr_;

    public:
        parser(ctk::istr _in);

        static ValueBase* from(ctk::istr _in);
        static ValueBase* from(ctk::istr _in, tag_t _peekTag);

    private:

        ValueBase* parseValue(bool _peekOnly=false, tag_t _peekTag=0);

        SimpleValue* readSimple(bool _peekOnly=false);

        bool peekValue(istr& _val, bool& _textual);

    }; // parser

} // end of namespace nbr
} // end of namespace ctk

#endif // !_Z_CTK_NBR_PARSER_H_


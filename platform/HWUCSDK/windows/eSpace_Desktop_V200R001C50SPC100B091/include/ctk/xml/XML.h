/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_H_
#define _Z_CTK_XML_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLAttr.h"
#include "ctk/xml/XMLNode.h"
#include "ctk/xml/XMLParser.h"
#include "ctk/xml/XMLCodec.h"
#include "ctk/xml/XMLString.h"
#include "ctk/xml/XMLStreamBase.h"
#include "ctk/xml/XMLStream.h"
#include "ctk/xml/XMLInStream.h"
#include "ctk/xml/XMLOutStream.h"
#include "ctk/xml/XMLSTL.h"

namespace ctk {
namespace xml {

    using ::ctk::XMLRuntimeException;
    using ::ctk::XMLParserCallback;

    using ::ctk::XMLAttr;

    using ::ctk::cdata_t;
    using ::ctk::XMLNode;

    using ::ctk::XMLParser;

    using ::ctk::XMLCodecBase;

    using ::ctk::XMLInputString;

    using ::ctk::in_t;
    using ::ctk::out_t;
    using ::ctk::XMLStreamBase;

    using ::ctk::XMLStream;
    using ::ctk::xstream;

    using ::ctk::XMLInStream;
    using ::ctk::XMLInStreamIterator;
    using ::ctk::Decoder;
    using ::ctk::xistream;

    using ::ctk::XMLOutStream;
    using ::ctk::Encoder;
    using ::ctk::xostream;

} // end of namespace xml
} // end of namespace ctk

#endif // _Z_CTK_XML_H_


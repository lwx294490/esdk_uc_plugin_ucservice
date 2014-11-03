/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_CODEC_H_
#define _Z_CTK_XML_CODEC_H_

#include "ctk/xml/XMLBase.h"

#include "ctk/base/interface.h"

namespace ctk {

    class XMLStream;
    class XMLInStream;
    class XMLOutStream;

    struct CTK_API XMLCodecBase : virtual public ctk::Interface
    {
        virtual ~XMLCodecBase();

        void fromXml(ctk::rcistr _xml);

        ctk::String toXml(bool _formatted=false) const;

        // �����������encodeXml��decodeXml����������codecXml������Ҫ�����ء� //
        // Ĭ������£�encodeXml��decodeXml����codecXmlʵ�ֵġ� //

        //{{{ group 1
        virtual void encodeXml(XMLOutStream& _xos) const;
        virtual void decodeXml(const XMLInStream& _xis);
        //}}}

        //{{{ group 2
        virtual void codecXml(XMLStream& _xs);
        //}}}

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLCodecBase& _v);

    inline void operator<<(XMLOutStream& _xos, const XMLCodecBase& _v)
    {
        _v.encodeXml(_xos);
    }

    inline void operator>>(const XMLInStream& _xis, XMLCodecBase& _v)
    {
        _v.decodeXml(_xis);
    }

} // end of namespace ctk

#endif // _Z_CTK_XML_CODEC_H_


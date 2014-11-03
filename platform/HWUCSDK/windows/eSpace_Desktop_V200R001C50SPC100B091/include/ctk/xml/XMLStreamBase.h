/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_STREAM_BASE_H_
#define _Z_CTK_XML_STREAM_BASE_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLNode.h"

namespace ctk {

    struct in_t { };
    struct out_t { };

    class CTK_API XMLStreamBase
    {
    public:
        XMLStreamBase();
        XMLStreamBase(const XMLStreamBase& _v);
        XMLStreamBase(XMLNode* _node, out_t);
        XMLStreamBase(const XMLNode* _node, in_t);
        XMLStreamBase(bool _inputting, bool _shouldDelete, XMLNode* _node);
        ~XMLStreamBase();

        XMLStreamBase& operator=(const XMLStreamBase& _v);

        void swap(XMLStreamBase& _v);

        bool isInputting() const;

        void setInputting(bool _v);

        void setOutputNode(XMLNode* _node, bool _shouldDelete);

        void setInputNode(const XMLNode* _node, bool _shouldDelete);

        void assign(bool _inputting, bool _shouldDelete, XMLNode* _node);

        void clear();

        rcstr name() const;

        void name(rcistr _name);

        rcstr type() const;
        
        void type(rcistr _type);

        rcstr cdata() const;

        void cdata(rcistr _cdata);

        bool isNull() const;

        XMLNode* release();

        void checkNode();

        XMLNode& node();

        const XMLNode& node() const;

        const XMLAttr& attrAt( size_type _index ) const ;
        size_type numofAttrs() const;

        const XMLNode& childAt( size_type _index ) const ;
        size_type numofChildren() const;

        String str(bool _formatted=false, uint _depth=0) const;

        ctk::dumper& dump(ctk::dumper& _d) const;

    private:
        Boolean inputting_;
        Boolean shouldDelete_;
        Pointer<XMLNode> node_;

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLStreamBase& _v);

} // end of namespace ctk

#endif // _Z_CTK_XML_STREAM_BASE_H_


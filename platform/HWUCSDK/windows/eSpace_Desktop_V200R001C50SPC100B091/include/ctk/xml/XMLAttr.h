/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_ATTR_H_
#define _Z_CTK_XML_ATTR_H_
 
#include "ctk/xml/XMLBase.h"

namespace ctk {

    class XMLNode;

    class CTK_API XMLAttr
    {
    public:
        XMLAttr(rcistr _name=istr(), rcistr _value=istr(), XMLNode* _node = 0);
        XMLAttr(const XMLAttr& _v);
        virtual ~XMLAttr();

        XMLAttr& operator=(const XMLAttr& _v);

        // equal to XMLAttr::null()
        bool isNull() const;

        rcstr name() const;

        void name(rcistr _name);

        rcstr value() const;

        void value( rcistr _value );

        XMLNode* node() const;

        void node( XMLNode* _node );

        String str() const ;

        ctk::dumper& dump(ctk::dumper& _d) const;

        static const XMLAttr& null();
        static void destroy_null();

    private:
        String name_;
        String value_;
        ctk::Pointer<XMLNode> node_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLAttr& _v);

} // end of namespace ctk

#endif // _Z_CTK_XML_ATTR_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_PARSER_H_
#define _Z_CTK_XML_PARSER_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLNode.h"

namespace ctk {

    class CTK_API XMLParser
    {
    public:
        typedef std::map<String, String> _EntityMap;

        enum XMLTagType 
        {
            TagCDATA	=	-3,
            TagComment	=	'!',
            TagSymbol	=	-1,
            TagOpen	    =	'<',
            TagClose	=	'>',
            TagEnd		=	'/',
            TagEquals	=	'=',
            TagQuote	=	'"',
            TagQuote2	=	'\'',
            tagNothing  =   0
        };

    public:
        XMLParser(void);
        XMLParser(rcistr _xmlString);
        XMLParser(std::ifstream& _ifs);
        virtual ~XMLParser(void);

        void setCallback(XMLParserCallback* _callback);

        /**
        *tries to parse and process the next node.
        *@return bool true if successful, false if the parsing failed.
        */
        bool nextNode();

        /**
        *parses the XML data represented by the xmlString argument.
        *@param String the XML data to parse
        */
        void parse( rcistr _xmlString );

        void parse( std::ifstream& _ifs );

        const XMLNode* rootNode() const;

        XMLNode* release();

    private:
        void init();

        pcstr parseComments( pcstr _commentPtrStart );

        void parseEntity( pcstr _entityPtrStart, pcstr _entityPtrEnd );

        pcstr parseNode( pcstr _nodePtrStart, pcstr _nodePtrEnd );

        pcstr parseAttrs( pcstr _attrPtrStart, pcstr _attrPtrEnd );

        void clearNodes();

        pcstr skipWhitespace( pcstr _begin, pcstr _end );

        pcstr skipTillWhitespace( pcstr _begin, pcstr _end );

        String decodeText( rcistr _text );

        bool isWhiteSpace( char _ch );

    private:
        String xmlString_;
        size_t sourceSize_;
        pcstr xmlBufferStart_;
        pcstr xmlBufferEnd_;
        pcstr sourcePtr_;
        pcstr tokenPtr_;
        XMLTagType token_;
        bool dtdStarted_;

        _EntityMap entityMap_;

        ctk::Pointer<XMLNode> currentNode_;
        ctk::Pointer<XMLNode> rootNode_;

        ctk::Pointer<XMLParserCallback> callback_;

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLParser& _v);

} // end of namespace ctk

#endif // _Z_CTK_XML_PARSER_H_


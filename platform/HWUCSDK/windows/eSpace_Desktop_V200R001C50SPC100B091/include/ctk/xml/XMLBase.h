/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_BASE_H_
#define _Z_CTK_XML_BASE_H_

#include <ctk/ctk_config.h>

#include <ctk/base/base_type.h>
#include <ctk/base/exception.h>
#include <ctk/util/util_type.h>
#include <ctk/util/util_func.h>
#include <ctk/util/base64.h>
 
#define CTK_DEFINE_FIELD(type, value) \
        private: \
            type value##_; \
        public: \
            type& value() { return value##_; } \
            const type& value() const { return value##_; } \
            void value(const type& _value) { value##_ = _value; }

namespace ctk {

    class XMLAttr;
    class XMLNode;
    class XMLParser;

    class CTK_API XMLRuntimeException : public std::exception
    {
    public:
        XMLRuntimeException(rcistr _msg);
        XMLRuntimeException(rcistr _msg, rcistr _file, size_t _line);
        virtual ~XMLRuntimeException() throw ();

        virtual const char *what() const throw ()
        {
            return "XMLRuntimeException";
        }

    public:
        String message_;
        String fileName_;
        size_t lineNumber_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLRuntimeException& _e);

    struct CTK_API XMLParserCallback
    {
        virtual ~XMLParserCallback()
        {
        }

        virtual void onNodeBegin (XMLParser* _parser, XMLNode* _found )
        {
        }

        virtual void onNodeEnd   (XMLParser* _parser, XMLNode* _found )
        {
        }

        virtual void onCDATAFound(XMLParser* _parser, XMLNode* _found )
        {
        }

        virtual void onAttrFound (XMLParser* _parser, XMLAttr* _found )
        {
        }

    };

    namespace xml
    {
        typedef char xchar;
        typedef String xstring;
        typedef const xstring& rcxstr;

        const xchar XML_TAG_LEFT   = '<';
        const xchar XML_TAG_RIGHT  = '>';
        const xchar XML_TAG_CLOSE  = '/';
        const xchar XML_TAG_SPACE  = ' ';
        const xchar XML_TAG_ATTR   = '=';
        const xchar XML_TAG_QUOTE  = '"';
        const xchar XML_TAG_QUOTE2 = '\'';

        str_def XML_TAG_CDATA_BEG = ("<![CDATA[");
        str_def XML_TAG_CDATA_END = ("]]>");
        str_def XML_TAG_COMMENT_BEG = ("<!--");
        str_def XML_TAG_COMMENT_END = ("-->");
        str_def XML_TAG_DIRECTIVE_BEG = ("<?");
        str_def XML_TAG_DIRECTIVE_END = ("?>");
        str_def INDENT_STR = ("    ");
        str_def NEWLINE_STR = ("\n");

        CTK_API void encode_cdata(xstring& _s);
        CTK_API void decode_cdata(xstring& _s);

        CTK_API void encode_attr(xstring& _s);
        CTK_API void decode_attr(xstring& _s);

        CTK_API void escape (xstring& _os, istr _text);
        CTK_API void unescape(xstring& _os, istr _s);

    }

} // end of namespace ctk

#endif // _Z_CTK_XML_BASE_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_STREAM_H_
#define _Z_CTK_XML_STREAM_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLInStream.h"
#include "ctk/xml/XMLOutStream.h"
#include "ctk/xml/XMLString.h"

#define CTK_XML_CODEC(xs, field)                 xs(CTK_NV_VAR(field))       // 标准字段（xml标签是变量名去除_后缀的部分） //
#define CTK_XML_CODEC_EL(xs, field, elem)        xs(CTK_NV_VAR(field), elem) // 容器字段，指定元素的名字 //
#define CTK_XML_CODEC_FN(xs, field, fn)          xs(CTK_NV_VAR(field), fn)   // 容器字段，通过函数对象可以任意操纵容器元素 //

#define CTK_XML_CODEC_NV(xs, name, var)          xs(name, var)       // xml名和变量名不同，分别指定 //
#define CTK_XML_CODEC_NV_EL(xs, name, var, elem) xs(name, var, elem) 
#define CTK_XML_CODEC_NV_FN(xs, name, var, fn)   xs(name, var, fn)   

namespace ctk {

    class CTK_API XMLStream : public XMLInStream, public XMLOutStream
    {
    public:
        //{{{ output stream
        XMLStream();
        XMLStream(rcistr _name);
        XMLStream(out_t, rcistr _name);
        XMLStream(out_t, rcistr _nodeName, XMLOutStream& _parent);
        XMLStream(out_t, XMLNode& _node);
        //}}}
        //{{{ input stream
        XMLStream(const XMLInputString& _xml);
        XMLStream(std::ifstream& _ifs);
        XMLStream(in_t, rcistr _xml);
        XMLStream(in_t, rcistr _nodeName, const XMLInStream& _parent);
        XMLStream(in_t, const XMLNode& _node);
        //}}}
        ~XMLStream();

        template<class T>
        bool attribute(rcistr _attrName, T& _attrValue)
        {
            if (isInputting())
                return XMLInStream::attribute(_attrName, _attrValue);

            XMLOutStream::attribute(_attrName, _attrValue);
            return true;
        }

        template<class T>
        bool attribute(rcistr _attrName, T& _attrValue) const
        {
            return XMLInStream::attribute(_attrName, _attrValue);
        }

        template<class T>
        bool content(T& _value)
        {
            if (isInputting())
                return XMLInStream::content(_value);

            XMLOutStream::content(_value);
            return true;
        }

        template<class T>
        bool content(T& _value) const
        {
            return XMLInStream::content(_value);
        }

        // 如果节点名已经存在，则覆盖，否该新建。 //
        template<class T>
        void element(rcistr _childName, T& _childValue)
        {
            if (isInputting())
                XMLInStream::element(_childName, _childValue);
            else
                XMLOutStream::element(_childName, _childValue);
        }

        template<class T>
        void element(rcistr _childName, T& _childValue) const
        {
            XMLInStream::element(_childName, _childValue);
        }

        // T is a container, such as vector<>
        template<class T>
        void element(rcistr _childName, T& _childValue, pcstr _elemName)
        {
            element(_childName, _childValue, (istr)_elemName);
        }

        // T is a container, such as vector<>
        template<class T>
        void element(rcistr _childName, T& _childValue, istr _elemName)
        {
            if (isInputting())
                XMLInStream::element(_childName, _childValue);
            else
                XMLOutStream::element(_childName, _childValue, _elemName);
        }

        template<class T>
        void element(rcistr _childName, T& _childValue, pcstr _elemName) const
        {
            element(_childName, _childValue, (istr)_elemName);
        }

        template<class T>
        void element(rcistr _childName, T& _childValue, istr _elemName) const
        {
            XMLInStream::element(_childName, _childValue);
        }

        template<class T>
        void element(std::vector<T>& _value, rcistr _elemName)
        {
            if (isInputting())
                XMLInStream::element(_value, _elemName);
            else
                XMLOutStream::element(_value, _elemName);
        }

        template<class T>
        void element(std::vector<T>& _value, rcistr _elemName) const
        {
            XMLInStream::element(_value, _elemName);
        }

        template<class T, class Fn>
        void element(rcistr _childName, T& _childValue, Fn _fn)
        {
            if (isInputting())
                XMLInStream::element(_childName, _childValue, _fn);
            else
                XMLOutStream::element(_childName, _childValue, _fn);
        }

        template<class T, class Fn>
        void element(rcistr _childName, T& _childValue, Fn _fn) const
        {
            XMLInStream::element(_childName, _childValue, _fn);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value)
        {
            if (isInputting())
            {
                // 输入时可以分别检查属性和子节点。 //
                XMLInStream::operator()(_name, _value);
            }
            else
            {
                // 输出只能输出到子节点。 //
                // 如果要输出到属性就要用attribute函数。 //
                XMLOutStream::operator()(_name, _value);
            }
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value) const
        {
            XMLInStream::operator()(_name, _value);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::pcstr _elemName)
        {
            operator()(_name, _value, (ctk::istr)_elemName);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::istr _elemName)
        {
            if (isInputting())
            {
                XMLInStream::operator()(_name, _value);
            }
            else
            {
                XMLOutStream::operator()(_name, _value, _elemName);
            }
        }

        template<class T, class Fn>
        void operator()(ctk::rcistr _name, T& _value, Fn _fn)
        {
            if (isInputting())
            {
                XMLInStream::operator()(_name, _value, _fn);
            }
            else
            {
                XMLOutStream::operator()(_name, _value, _fn);
            }
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::pcstr _elemName) const
        {
            operator()(_name, _value, (ctk::istr)_elemName);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::istr _elemName) const
        {
            XMLInStream::operator()(_name, _value);
        }

        template<class T, class Fn>
        void operator()(ctk::rcistr _name, T& _value, Fn _fn) const
        {
            XMLInStream::operator()(_name, _value, _fn);
        }

        template<class T>
        void codecAttr(rcistr _name, T& _value, rcistr _altName=istr(), bool _protectedValue=false)
        {
            attribute(ctk::altName(_name, _altName), _value);
        }

        template<class T>
        void codecField(rcistr _name, T& _value, rcistr _altName=istr(), bool _protectedValue=false)
        {
            element(ctk::altName(_name, _altName), _value);
        }

        template<class T>
        void codecFields(rcistr _name, std::vector<T>& _value, rcistr _elemName)
        {
            element(_name, _value, _elemName);
        }

        template<class T>
        void codecFieldList(rcistr _dummyName, std::vector<T>& _value, rcistr _elemName)
        {
            element(_value, _elemName);
        }

        template<class T>
        void codecFieldAttr(rcistr _fieldname, rcistr _attrname, T& _value, rcistr _altFieldName=istr(), rcistr _altAttrName=istr(), bool _protectedValue=false)
        {
            if (isInputting())
            {
                XMLInStream::child(ctk::altName(_fieldname, _altFieldName)).attr(ctk::altName(_attrname, _altAttrName)) >> _value;
            }
            else
            {
                child(ctk::altName(_fieldname, _altFieldName)).attr(ctk::altName(_attrname, _altAttrName)) << _value;
            }
        }

        template<class T>
        void codecContent(rcistr _name, T& _value, bool _protectedValue=false)
        {
            content(_value);
        }

        template<class T>
        void io(int _id, rcistr _name, T& _value, bool _protectedValue=false)
        {
            codecField(_name, _value);
        }

        void enter(istr _type, istr _name, istr _class=istr(), istr _super=istr());
        
        void leave();
        
        void enterSuper();

        void leaveSuper();

        // attribute accessor

        XMLAttr& attr( rcistr _name )
        {
            if (isInputting())
            {
                return const_cast<XMLAttr&>(XMLInStream::attr(_name));
            }
            else
            {
                return XMLOutStream::attr(_name);
            }
        }

        XMLAttr& operator()( rcistr _name )
        {
            return attr(_name);
        }

        const XMLAttr& attr( rcistr _name ) const
        {
            return XMLInStream::attr(_name);
        }

        const XMLAttr& operator()( rcistr _name ) const
        {
            return attr(_name);
        }

        // element accessor

        XMLNode& child( rcistr _name )
        {
            if (isInputting())
            {
                return const_cast<XMLNode&>(XMLInStream::child(_name));
            }
            else
            {
                return XMLOutStream::child(_name);
            }
        }

        XMLNode& operator[]( rcistr _name )
        {
            return child(_name);
        }

        const XMLNode& child( rcistr _name ) const
        {
            return XMLInStream::child(_name);
        }

        const XMLNode& operator[]( rcistr _name ) const
        {
            return child(_name);
        }

    };

    typedef XMLStream xstream;

} // end of namespace ctk

#endif // _Z_CTK_XML_STREAM_H_


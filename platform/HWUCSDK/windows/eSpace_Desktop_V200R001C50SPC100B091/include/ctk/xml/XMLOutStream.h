/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_OUT_STREAM_H_
#define _Z_CTK_XML_OUT_STREAM_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLStreamBase.h"

#define CTK_XML_ENCODE(xos, field)                 xos(CTK_NV_VAR(field))
#define CTK_XML_ENCODE_EL(xos, field, elem)        xos(CTK_NV_VAR(field), elem)
#define CTK_XML_ENCODE_FN(xos, field, fn)          xos(CTK_NV_VAR(field), fn)

#define CTK_XML_ENCODE_NV(xos, name, var)          xos(name, var)
#define CTK_XML_ENCODE_NV_EL(xos, name, var, elem) xos(name, var, elem)
#define CTK_XML_ENCODE_NV_FN(xos, name, var, fn)   xos(name, var, fn)

namespace ctk {

    class CTK_API XMLOutStream : virtual public XMLStreamBase
    {
    public:
        XMLOutStream();
        XMLOutStream(rcistr _nodeName);
        XMLOutStream(rcistr _nodeName, XMLOutStream& _parent);
        XMLOutStream(XMLNode& _node);
        ~XMLOutStream();

        XMLOutStream& operator+=(const XMLOutStream& _v);

        XMLAttr& operator()( rcistr _name );
        XMLAttr& attr( rcistr _name );

        XMLNode& operator[]( rcistr _name );
        XMLNode& child( rcistr _name );

        void operator<<(bool _value);
        void operator<<(char _value);
        void operator<<(uchar _value);
        void operator<<(int16 _value);
        void operator<<(uint16 _value);
        void operator<<(int32 _value);
        void operator<<(uint32 _value);
#if defined(_CTK_INT32_IS_LONG)
        void operator<<(int _value);
        void operator<<(uint _value);
#endif
        void operator<<(int64 _value);
        void operator<<(uint64 _value);
        void operator<<(float _value);
        void operator<<(double _value);
        void operator<<(istr _value);
        void operator<<(iwstr _value);
        void operator<<(pcstr _value);
        void operator<<(pcustr _value);
        void operator<<(pcwstr _value);
        void operator<<(const void* _value); // do not implement
        
        void operator<<(const Int1& _value);
        void operator<<(const Int8& _value);
        void operator<<(const Int16& _value);
        void operator<<(const Int32& _value);
        void operator<<(const Int64& _value);
        void operator<<(const Uint8& _value);
        void operator<<(const Uint16& _value);
        void operator<<(const Uint32& _value);
        void operator<<(const Uint64& _value);
        void operator<<(const Real32& _value);
        void operator<<(const Real64& _value);
        void operator<<(const Wchar& _value);
        void operator<<(const string& _v);
        void operator<<(const String& _value);
        void operator<<(const Wstring& _value);
        void operator<<(const Bytes& _value);
        void operator<<(const Time& _value);

        // 对于除了以上基本类型的自定义类型，假设其提供了encodeXml函数 //
        template<class T>
        void operator<<(const T& _v)
        {
            _v.encodeXml(*this);
        }

        template<class T>
        XMLOutStream& write(const T& _v)
        {
            (*this) << _v;
            return *this;
        }

        template<class T>
        XMLOutStream& attribute(rcistr _attrName, const T& _attrValue)
        {
            attr(_attrName) << _attrValue;
            return *this;
        }

        template<class T>
        XMLOutStream& content(const T& _value)
        {
            node() << _value;
            return *this;
        }

        // 如果节点名已经存在，则覆盖，否则新建。 //
        template<class T>
        XMLOutStream& element(rcistr _childName, const T& _childValue)
        {
            child(_childName) << _childValue;
            return *this;
        }

        // _childValue is a container
        template<class T>
        XMLOutStream& element(rcistr _childName, const T& _childValue, ctk::pcstr _elemName)
        {
            return element(_childName, _childValue, (istr)_elemName);
        }

        // _childValue is a container
        template<class T>
        XMLOutStream& element(rcistr _childName, const T& _childValue, ctk::istr _elemName)
        {
            XMLOutStream childStream(child(_childName));
            childStream.output(_elemName, _childValue.begin(), _childValue.end());
            return *this;
        }

        // _childValue is a container
        template<class T, class _Fn>
        XMLOutStream& element(rcistr _childName, const T& _childValue, _Fn _fn)
        {
            XMLOutStream childStream(child(_childName));
            childStream.iterate(_childValue, _fn);
            return *this;
        }

        template<class T>
        XMLOutStream& element(const std::vector<T>& _childrenValue, rcistr _childElementName)
        {
            output(_childElementName, _childrenValue.begin(), _childrenValue.end());
            return *this;
        }

        template<class T>
        XMLOutStream& add(rcistr _childName, const T& _childValue)
        {
            XMLOutStream childStream(*node().addChildNode(_childName));
            childStream << _childValue;
            return *this;
        }

        template<class _It>
        XMLOutStream& output(const _It& _begin, const _It& _end)
        {
            return output("any", _begin, _end);
        }

        template<class _It>
        XMLOutStream& output(rcistr _elemName, const _It& _begin, const _It& _end)
        {
            for (_It i=_begin; i!=_end; ++i)
            {
                add(_elemName, *i);
            }
            return *this;
        }

        // 函数子例子： //
        //struct FnUserXmlOut
        //{
        //    ctk::XMLOutStream operator()(ctk::rcstr _uri)
        //    {
        //        ctk::XMLOutStream xos("user");
        //        xos("uri") << _uri;     // equals to xos.attribute("uri", _uri);
        //        // xos["uri"] << _uri;  // equals to xos.element("uri", _uri);
        //        return xos;
        //    }
        //};

        template<class T, class _Fn>
        XMLOutStream& iterate(const T& _c, _Fn _fn)
        {
            return call(_c.begin(), _c.end(), _fn);
        }

        template<class _It, class _Fn>
        XMLOutStream& call(const _It& _begin, const _It& _end, _Fn _fn)
        {
            for (_It i=_begin; i!=_end; ++i)
            {
                (*this) += _fn(*i);
            }
            return *this;
        }

        // 对于双参数()运算符，作为子节点存储，不能作为属性，这是与输入流不一样的 //
        // 如果要存入属性，就用xos(attrname) << attrvalue的形式 //
        // 或者用attr或attribute函数明确指出 //
        template<class T>
        XMLOutStream& operator()(ctk::rcistr _name, const T& _value)
        {
            return element(_name, _value);
        }

        // _value is a container
        template<class T>
        XMLOutStream& operator()(ctk::rcistr _name, const T& _value, ctk::pcstr _elemName)
        {
            return operator()(_name, _value, (istr)_elemName);
        }

        // _value is a container
        template<class T>
        XMLOutStream& operator()(ctk::rcistr _name, const T& _value, ctk::istr _elemName)
        {
            return element(_name, _value, _elemName);
        }

        // _value is a container
        template<class T, class _Fn>
        XMLOutStream& operator()(ctk::rcistr _name, const T& _value, _Fn _fn)
        {
            return element(_name, _value, _fn);
        }

    };

    // 结合XMLOutStream的[]使用 //
    template<class T>
    void operator<<(XMLNode& _n, const T& _v)
    {
        XMLOutStream xos(_n);
        xos << _v;
    }

    // 结合XMLOutStream的单参数()使用 //
    template<class T>
    void operator<<(XMLAttr& _n, const T& _v)
    {
        XMLOutStream xos;
        xos << _v;
        _n.value(xos.cdata());
    }

    // 缺省的编码函数子 //
    template<class T>
    struct Encoder
    {
        XMLOutStream operator()(const T& _v)
        {
            XMLOutStream xos;
            xos << _v;
            return xos;
        }
    };

    // 自定义类型（结构）需要重载: //
    //     void operator<<(XMLOutStream& _xos, const UserDefinedClass& _v);
    // 建议在UserDefinedClass中定义encodeXml函数: //
    //     void encodeXml(XMLOutStream& _xos);
    // 供operator<<调用。 //
    // 或从XMLCodecBase派生，参见XMLCodec.h。 //

    typedef XMLOutStream xostream;

} // end of namespace ctk

#endif // _Z_CTK_XML_OUT_STREAM_H_


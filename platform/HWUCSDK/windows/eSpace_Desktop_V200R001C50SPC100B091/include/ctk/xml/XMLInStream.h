/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_IN_STREAM_H_
#define _Z_CTK_XML_IN_STREAM_H_

#include "ctk/xml/XMLBase.h"
#include "ctk/xml/XMLStreamBase.h"
#include "ctk/xml/XMLParser.h"

#define CTK_XML_DECODE(xis, field)                 xis(CTK_NV_VAR(field))
#define CTK_XML_DECODE_FN(xis, field, fn)          xis(CTK_NV_VAR(field), fn)

#define CTK_XML_DECODE_NV(xis, name, var)          xis(name, var)
#define CTK_XML_DECODE_NV_FN(xis, name, var, fn)   xis(name, var, fn)

namespace ctk {

    template<class T> struct Decoder;

    class CTK_API XMLInStream : virtual public XMLStreamBase
    {
    public:
        XMLInStream();
        XMLInStream(rcistr _xml);
        XMLInStream(std::ifstream& _ifs);
        XMLInStream(rcistr _nodeName, const XMLInStream& _parent);
        XMLInStream(const XMLNode& _node);
        ~XMLInStream();

        void parse(rcistr _xml);
        void parse(std::ifstream& _ifs);

        const XMLAttr& operator()( rcistr _name ) const;
        const XMLAttr& attr( rcistr _name ) const;

        const XMLNode& operator[]( rcistr _name ) const ;
        const XMLNode& child( rcistr _name ) const ;

        bool operator>>(bool& _value) const;
        bool operator>>(char& _value) const;
        bool operator>>(uchar& _value) const;
        bool operator>>(int16& _value) const;
        bool operator>>(uint16& _value) const;
        bool operator>>(int32& _value) const;
        bool operator>>(uint32& _value) const;
#if defined(_CTK_INT32_IS_LONG)
        bool operator>>(int& _value) const;
        bool operator>>(uint& _value) const;
#endif
        bool operator>>(int64& _value) const;
        bool operator>>(uint64& _value) const;
        bool operator>>(float& _value) const;
        bool operator>>(double& _value) const;
        template<class T>
        bool inputPrimitive(T& _value) const
        {
            if (isNull())
                return false;
            String s;
            if (!((*this) >> s))
                return false;
            return s >> _value;
        }

        bool operator>>(volatile bool& _value) const;
        bool operator>>(volatile char& _value) const;
        bool operator>>(volatile uchar& _value) const;
        bool operator>>(volatile int16& _value) const;
        bool operator>>(volatile uint16& _value) const;
        bool operator>>(volatile int32& _value) const;
        bool operator>>(volatile uint32& _value) const;
#if defined(_CTK_INT32_IS_LONG)
        bool operator>>(volatile int& _value) const;
        bool operator>>(volatile uint& _value) const;
#endif
        bool operator>>(volatile int64& _value) const;
        bool operator>>(volatile uint64& _value) const;
        bool operator>>(volatile float& _value) const;
        bool operator>>(volatile double& _value) const;
        template<class T>
        bool inputVolatile(volatile T& _value) const
        {
            if (isNull())
                return false;
            T v = 0;
            if (!((*this) >> v))
                return false;
            _value = v;
            return true;
        }
        
        bool operator>>(Int1& _value) const;
        bool operator>>(Int8& _value) const;
        bool operator>>(Int16& _value) const;
        bool operator>>(Int32& _value) const;
        bool operator>>(Int64& _value) const;
        bool operator>>(Uint8& _value) const;
        bool operator>>(Uint16& _value) const;
        bool operator>>(Uint32& _value) const;
        bool operator>>(Uint64& _value) const;
        bool operator>>(Real32& _value) const;
        bool operator>>(Real64& _value) const;
        template<class T>
        bool inputNumber(T& _value) const
        {
            if (isNull())
                return false;
            typename T::value_type v = 0;
            if (!((*this) >> v))
                return false;
            _value = v;
            return true;
        }

        bool operator>>(Wchar& _value) const;
        bool operator>>(string& _value) const;
        bool operator>>(String& _value) const;
        bool operator>>(Wstring& _value) const;
        bool operator>>(Bytes& _value) const;
        bool operator>>(Time& _value) const;

        // ��ȥ����Ļ������ͣ������Զ�������Ӧ�ô�CodecBase����������Ӧ��֧��decodeXml //
        template<class T>
        bool operator>>(T& _v) const
        {
            if (isNull())
                return false;
            _v.decodeXml(*this);
            return true;
        }

        template<class T>
        bool attribute(rcistr _attrName, T& _attrValue) const
        {
            return attr(_attrName) >> _attrValue;
        }

        template<class T>
        bool element(rcistr _childName, T& _childValue) const
        {
            return child(_childName) >> _childValue;
        }

        template<class T>
        bool content(T& _value) const
        {
            return node() >> _value;
        }

        // ����ֻ������Ԫ��Ϊ�����ͻ��������Զ����������ú����ӡ� //
        // �����Զ������ͣ����������м������뺯����Ȼ���֧��<<��>>�ˡ� //
        // ��������Ӽ������ //
        // <userlist>
        //   <user uri="..."/>
        //   <user uri="..."/>
        // </userlist>
        // ���롣 //
        //ctk::vector<ctk::String> userlist;
        //struct FnUserXmlIn
        //{
        //    void operator()(const XMLInStream& xis, ctk::String& _uri)
        //    {
        //        xis("uri") >> _uri; // �ȼ��� xis.attribute("uri", uri_); //
        //    }
        //};
        //xisSome.element("userlist", userlist, FnUserXmlIn());
        //��xisSome("userlist", userlist, FnUserXmlIn()); //
        template<class T, class _Fn>
        bool element(rcistr _childName, T& _childValue, _Fn _fn) const
        {
            const XMLNode& node = child(_childName);
            if (node.isNull())
                return false;
            XMLInStream xis(node);
            return xis.iterate(_childValue, _fn);
        }

        template<class T>
        bool element(std::vector<T>& _childrenValue, rcistr _childElementName) const
        {
            XMLNode::_NodeList children;
            node().getChildren(_childElementName, children);
            _childrenValue.clear();
            for (XMLNode::_NodeList::const_iterator i=children.begin(); i!=children.end(); ++i)
            {
                XMLInStream xis(**i);
                if (xis.isNull())
                    return false;
                T tmp;
                xis >> tmp;
                _childrenValue.push_back(tmp);
            }
            return true;
        }

        // _childValue��һ�����������ڰ���һ����������Ԫ�����͵�value_type����׼��std��ctk�������У��� //
        // ��ctk::set��ctk::map������������������input������ָ������������Ϊctk::random_inserter���� //
        template<class T, class _Fn>
        bool iterate(T& _childValue, _Fn _fn) const
        {
            if (isNull())
                return false;

            for (size_type i=0; i<numofChildren(); ++i)
            {
                typename T::value_type tmp;
                XMLInStream xis(childAt(i));
                if (xis.isNull())
                    return false;

                _fn(xis, tmp);

                *std::back_inserter(_childValue) = tmp;
            }

            return true;
        }

        template<class _Inserter>
        bool input(_Inserter _inserter) const
        {
            return input(_inserter, Decoder<typename _Inserter::container_type::value_type>());
        }

        template<class _Inserter, class _Fn>
        bool input(_Inserter _inserter, _Fn _fn) const
        {
            if (isNull())
                return false;

            for (size_type i=0; i<numofChildren(); ++i)
            {
                typename _Inserter::container_type::value_type tmp;
                XMLInStream xis(childAt(i));
                if (xis.isNull())
                    return false;

                 _fn(xis, tmp);

                *_inserter = tmp;
            }

            return true;
        }

        template<class T>
        bool operator()(ctk::rcistr _name, T& _value) const
        {
            if (element(_name, _value))
                return true;

            if (attribute(_name, _value))
                return true;
            
            return false;
        }

        template<class T, class _Fn>
        bool operator()(ctk::rcistr _name, T& _value, _Fn _fn) const
        {
            if (element(_name, _value, _fn))
                return true;

            if (attribute(_name, _value))
                return true;
            
            return false;
        }

    };

    /** ���������������� //
        XMLInStream xis("<field var='stream-method'>"
                        "  <value method='offline'/>"
                        "  <value method='p2p'></value>"
                        "  <value method='MSRP'/>"
                        "</field>");
        XMLInStreamIterator values(xis.node()); //Ҳ������ĳ��xis���ӽڵ�xis["child"] //
        XMLInStream value;
        while (values -= value)
        {
            value("method") >> method;
        }
    */
    class XMLInStreamIterator
    {
        const XMLNode& node_;
        size_t index_;

    public:
        XMLInStreamIterator(const XMLNode& _node)
            : node_(_node), index_(0)
        {
        }

        bool operator-=(XMLInStream& _xisChild)
        {
            if (index_ >= node_.numofChildren())
                return false;
            _xisChild = node_.child(index_++);
            return true;
        }

    };

    // ���XMLInStream��[]ʹ�� //
    template<class T>
    bool operator>>(const XMLNode& _n, T& _v)
    {
        if (_n.isNull())
            return false;

        XMLInStream xis(_n);
        return xis >> _v;
    }

    // ���XMLInStream��()ʹ�� //
    template<class T>
    bool operator>>(const XMLAttr& _n, T& _v)
    {
        if (_n.isNull())
            return false;

        XMLNode node(_n.value(), cdata_t());
        XMLInStream xis(node);
        return xis >> _v;
    }

    // ȱʡ�Ľ��뺯���� //
    template<class T>
    struct Decoder
    {
        void operator()(const XMLInStream& _xis, T& _v)
        {
            (_xis >> _v);
        }
    };

    // �Զ������ͣ��ṹ����Ҫ����: //
    //     void operator>>(const XMLInStream& _xis, UserDefinedClass& _v);
    // ������UserDefinedClass�ж���decodeXml����: //
    //     void decodeXml(const XMLInStream& _xis);
    // ��operator>>���á� //
    // ���XMLCodecBase�������μ�XMLCodec.h�� //

    typedef XMLInStream xistream;

} // end of namespace ctk

#endif // _Z_CTK_XML_IN_STREAM_H_


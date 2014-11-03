/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// NBR(Nested Binary Representation)

#ifndef _Z_CTK_NBR_STREAM_H_
#define _Z_CTK_NBR_STREAM_H_

#include "ctk/ctk_config.h"

#include "ctk/nbr/lsd.h"

#include "ctk/base/base_type_enum.h"

namespace ctk {
namespace nbr {

    class CTK_API OutputStream
    {
        ctk::StringBuffer ss_;

    public:
        OutputStream();

        ctk::istr str() const;

        void swap(OutputStream& _v);

        void reset();

        template<class T>
        OutputStream&
        operator()(tag_t _tag, const T& _v)
        {
            return write(_tag, _v);
        }

        template<class T>
        OutputStream&
        write(tag_t _tag, const T& _v)
        {
            writeRaw(_tag);
            (*this) << _v;
            return *this;
        }

        void operator<<(ctk::null_type _val)    ;
        void operator<<(ctk::empty_type _val)   ;
        void operator<<(ctk::int1 _val)         ;
        void operator<<(ctk::int8 _val)         ;
        void operator<<(ctk::uint8 _val)        ;
        void operator<<(ctk::int16 _val)        ;
        void operator<<(ctk::uint16 _val)       ;
        void operator<<(ctk::int32 _val)        ;
        void operator<<(ctk::uint32 _val)       ;
        void operator<<(ctk::int64 _val)        ;
        void operator<<(ctk::uint64 _val)       ;
        void operator<<(ctk::real32 _val)       ;
        void operator<<(ctk::real64 _val)       ;
        void operator<<(ctk::istr _val)         ;
        void operator<<(ctk::iwstr _val)        ;
        void operator<<(const ctk::Int1& _val)  ;
        void operator<<(const ctk::Int8& _val)  ;
        void operator<<(const ctk::Int16& _val) ;
        void operator<<(const ctk::Int32& _val) ;
        void operator<<(const ctk::Int64& _val) ;
        void operator<<(const ctk::Uint8& _val) ;
        void operator<<(const ctk::Uint16& _val);
        void operator<<(const ctk::Uint32& _val);
        void operator<<(const ctk::Uint64& _val);
        void operator<<(const ctk::Real32& _val);
        void operator<<(const ctk::Real64& _val);
        void operator<<(const ctk::Wchar& _val);
        void operator<<(const ctk::String& _val);
        void operator<<(const ctk::Wstring& _val);
        void operator<<(const ctk::Bytes& _val) ;
        void operator<<(const ctk::Time& _val)  ;

        ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        void writeInt(ctk::int64 _val, ctk::size_type _maxBytes);
        void writeInt(ctk::uint64 _val, ctk::size_type _maxBytes);
        void write_i(ctk::pcstr _data, ctk::size_type _size, bool _textual);

        void writeRaw(ctk::pcstr _data, ctk::size_type _size);
        void writeRaw(ctk::istr _val);
        void writeRaw(ctk::byte _val);

        friend class CodecStream;

    public:
        friend class Entry;
        class CTK_API Entry
        {
            OutputStream& os_;

        public:
            Entry(OutputStream& _os);
            ~Entry();

        }; // Entry

    }; // OutputStream
    inline ctk::dumper& operator<<(ctk::dumper& os, const OutputStream& v)
    {
        return v.dump(os);
    }
    CTK_API std::ostream& operator<<(std::ostream& _os, const OutputStream& _v);

    template<class T>
        inline void
        operator<<(OutputStream& _os, const T& _v)
    {
        // 要求自定义类实现 void encode(ctk::nbr::OutputStream& _os) const 函数 //
        OutputStream::Entry __entry(_os);
        _v.encode(_os);
    }

    template<typename E>
        inline void
        operator<<(OutputStream& _os, const ctk::Enum<E>& _val)
    {
        _os << (int32)(int)_val;
    }

    class CTK_API InputStream
    {
        ValueBase* value_;
        bool destroyMe_;

    public:
        InputStream(ValueBase* _value=0);
        InputStream(istr _buf);
        InputStream(istr _buf, tag_t _peekTag);
        ~InputStream();

        void swap(InputStream& _v);

        ValueBase* get() const;

        ValueBase* getChild(tag_t _tag) const;

        SimpleValue* getSimpleValue() const;

        template<class T>
        const InputStream&
        operator()(tag_t _tag, T& _v) const
        {
            read(_tag, _v);
            return *this;
        }

        template<class T>
        bool
        read(tag_t _tag, T& _v) const
        {
            ValueBase* vbChild = getChild(_tag);
            if (!vbChild)
            {
                // not exist, don't change old value
                return false;
            }

            InputStream child(vbChild);
            child >> _v;
            return true;
        }

        template<class T>
        void
        readValue(T& _v) const
        {
            SimpleValue* sv = getSimpleValue();
            if (sv)
            {
                sv->read(_v);
            }
        }

        ctk::dumper& dump(ctk::dumper& _os) const;

    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const InputStream& v)
    {
        return v.dump(os);
    }
    CTK_API std::ostream& operator<<(std::ostream& _os, const InputStream& _v);

    inline void operator>>(InputStream& _is, ctk::int1& _val)   { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::int8& _val)   { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::uint8& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::int16& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::uint16& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::int32& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::uint32& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::int64& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::uint64& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::real32& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::real64& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Int1& _val)   { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Int8& _val)   { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Int16& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Int32& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Int64& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Uint8& _val)   { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Uint16& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Uint32& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Uint64& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Real32& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Real64& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Wchar& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::String& _val) { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Wstring& _val){ _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::istr& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Bytes& _val)  { _is.readValue(_val); }
    inline void operator>>(InputStream& _is, ctk::Time& _val)   { _is.readValue(_val); }

    template<class T>
        inline void
        operator>>(InputStream& _is, T& _v)
    {
        // 要求自定义类实现 void decode(ctk::nbr::InputStream& _is) 函数 //
        _v.decode(_is);
    }

    template<typename E>
        inline void
        operator>>(InputStream& _is, ctk::Enum<E>& _val)
    {
        ctk::int32 v = -1;
        _is >> v;
        _val = v;
    }

    class CTK_API CodecStream
    {
        bool encoding_;
        InputStream bis_;
        OutputStream bos_;

    public:
        CodecStream(); // encode
        CodecStream(ctk::istr _buf); // decode

        bool encoding();
        InputStream& bis();
        OutputStream& bos();

        ctk::istr str() const; // get output

        template <class T>
        CodecStream& operator()(tag_t _tag, T& _v)
        {
            if (encoding_)
                bos_(_tag, _v);
            else
                bis_(_tag, _v);
            return *this;
        }

        template <class T>
        void operator<<(T& _v)
        {
            OutputStream::Entry __entry(bos());
            _v.codec(*this);
        }

        template <class T>
        void operator>>(T& _v)
        {
            _v.codec(*this);
        }

        template<class T>
        void io(int _id, rcistr _name, T& _value, bool _protectedValue=false)
        {
            operator()((tag_t)_id, _value);
        }

        void enter(istr _type, istr _name=istr(), istr _class=istr(), istr _super=istr());
        
        void leave();
        
        void enterSuper();

        void leaveSuper();

    };

    class CTK_API CodecInterface
    {
    public:
        virtual ~CodecInterface() { }

        virtual void codec(CodecStream& _s) = 0;

        void encode(OutputStream& _os) const;

        void decode(InputStream& _is);

    };

    struct CTK_API dump_buf
    {
        istr buf_;

        dump_buf(rcistr _buf)
            : buf_(_buf)
        {
        }

        dumper& dump(dumper& _os) const;

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const dump_buf& _v);

} // end of namespace nbr

inline void swap(nbr::OutputStream& _v1, nbr::OutputStream& _v2)
{
    _v1.swap(_v2);
}

inline void swap(nbr::InputStream& _v1, nbr::InputStream& _v2)
{
    _v1.swap(_v2);
}

} // end of namespace ctk

#include "ctk/nbr/nbr_stl.h"

#endif // !_Z_CTK_NBR_STREAM_H_


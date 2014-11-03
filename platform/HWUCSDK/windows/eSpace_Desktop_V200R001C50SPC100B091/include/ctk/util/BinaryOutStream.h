/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_BINARYOUTSTREAM_H_
#define _Z_CTK_UTIL_BINARYOUTSTREAM_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_buffer.h"

#include "ctk/util/util_type.h"

namespace ctk
{

    /*
        [0]: size of data length
        [1:<size of data length>]: data length
        [<1+<size of data length>>:<data length>]: data
    */

    class CTK_API BinaryOutStream
    {
        typedef ctk::StringBuffer _Buffer;

    public:
        BinaryOutStream(); // output mode

        ctk::istr str() const; // get output

        _Buffer& buffer();

    public:
        BinaryOutStream& write(ctk::null_type _val);
        BinaryOutStream& write(ctk::empty_type _val);
        BinaryOutStream& write(ctk::int1 _val);
        BinaryOutStream& write(ctk::int8 _val);
        BinaryOutStream& write(ctk::uint8 _val);
        BinaryOutStream& write(ctk::int16 _val);
        BinaryOutStream& write(ctk::uint16 _val);
        BinaryOutStream& write(ctk::int32 _val);
        BinaryOutStream& write(ctk::uint32 _val);
        BinaryOutStream& write(ctk::int64 _val);
        BinaryOutStream& write(ctk::uint64 _val);
        BinaryOutStream& write(ctk::real32 _val);
        BinaryOutStream& write(ctk::real64 _val);
        BinaryOutStream& write(ctk::istr _val);
        BinaryOutStream& write(ctk::iwstr _val);
        BinaryOutStream& write(const ctk::Int1& _val);
        BinaryOutStream& write(const ctk::Int8& _val);
        BinaryOutStream& write(const ctk::Int16& _val);
        BinaryOutStream& write(const ctk::Int32& _val);
        BinaryOutStream& write(const ctk::Int64& _val);
        BinaryOutStream& write(const ctk::Uint8& _val);
        BinaryOutStream& write(const ctk::Uint16& _val);
        BinaryOutStream& write(const ctk::Uint32& _val);
        BinaryOutStream& write(const ctk::Uint64& _val);
        BinaryOutStream& write(const ctk::Real32& _val);
        BinaryOutStream& write(const ctk::Real64& _val);
        BinaryOutStream& write(const ctk::Wchar& _value);
        BinaryOutStream& write(const ctk::String& _value);
        BinaryOutStream& write(const ctk::Wstring& _value);
        BinaryOutStream& write(const ctk::Bytes& _value);
        BinaryOutStream& write(const ctk::Time& _value);

        BinaryOutStream& writeRaw(ctk::byte _val);
        BinaryOutStream& writeRaw(ctk::istr _val);
        BinaryOutStream& writeRaw(ctk::pcstr _data, ctk::size_type _size);

        template<class T>
        BinaryOutStream& operator<<(const T& _v)
        {
            return write(_v);
        }

    private:
        BinaryOutStream& write(ctk::int64 _val, ctk::size_type _maxBytes);
        BinaryOutStream& write(ctk::uint64 _val, ctk::size_type _maxBytes);
        BinaryOutStream& write(ctk::pcstr _data, ctk::size_type _size);

    private:
        _Buffer ss_;
    };

} // end of namespace ctk

#endif //_Z_CTK_UTIL_BINARYOUTSTREAM_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_BINARYINSTREAM_H_
#define _Z_CTK_UTIL_BINARYINSTREAM_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_slice.h"

#include "ctk/util/util_type.h"

#include "ctk/util/BinaryStream.h"

namespace ctk
{
    /*
        [0]: size of data length
        [1:<size of data length>]: data length
        [<1+<size of data length>>:<data length>]: data
    */

    class CTK_API BinaryInStream
    {
    public:
        BinaryInStream(const ctk::istr& _in); // input mode

        void str(const ctk::istr& _in); // set input

        ctk::istr str() const;

    public:
        BinaryInStream& read(ctk::int1& _val);
        BinaryInStream& read(ctk::int8& _val);
        BinaryInStream& read(ctk::uint8& _val);
        BinaryInStream& read(ctk::int16& _val);
        BinaryInStream& read(ctk::uint16& _val);
        BinaryInStream& read(ctk::int32& _val);
        BinaryInStream& read(ctk::uint32& _val);
        BinaryInStream& read(ctk::int64& _val);
        BinaryInStream& read(ctk::uint64& _val);
        BinaryInStream& read(ctk::real32& _val);
        BinaryInStream& read(ctk::real64& _val);
        BinaryInStream& read(ctk::Int1& _val);
        BinaryInStream& read(ctk::Int8& _val);
        BinaryInStream& read(ctk::Int16& _val);
        BinaryInStream& read(ctk::Int32& _val);
        BinaryInStream& read(ctk::Int64& _val);
        BinaryInStream& read(ctk::Uint8& _val);
        BinaryInStream& read(ctk::Uint16& _val);
        BinaryInStream& read(ctk::Uint32& _val);
        BinaryInStream& read(ctk::Uint64& _val);
        BinaryInStream& read(ctk::Real32& _val);
        BinaryInStream& read(ctk::Real64& _val);
        BinaryInStream& read(ctk::Wchar& _val);
        BinaryInStream& read(ctk::String& _val);
        BinaryInStream& read(ctk::Wstring& _val);
        BinaryInStream& read(ctk::Bytes& _val);
        BinaryInStream& read(ctk::Time& _val);

        BinaryInStream& readRaw(char& _val);
        BinaryInStream& readRaw(ctk::byte& _val);
        BinaryInStream& readRaw(ctk::pstr _data, ctk::size_type* _size);

        byte readLos();

        template<class T>
        BinaryInStream& operator>>(T& _v)
        {
            return read(_v);
        }

    private:
        BinaryInStream& read(ctk::int64& _val, ctk::size_type _maxBytes);
        BinaryInStream& read(ctk::uint64& _val, ctk::size_type _maxBytes);

        bool eof() const;

    private:
        typedef ctk::StringSlice _Buffer;
        _Buffer ss_;
    };

} // end of namespace ctk

#endif //_Z_CTK_UTIL_BINARYINSTREAM_H_


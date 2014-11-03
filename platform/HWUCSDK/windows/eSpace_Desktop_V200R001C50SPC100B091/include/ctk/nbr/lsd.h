/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// NBR(Nested Binary Representation)
// LSD(LengthOfSize Size Data)

#ifndef _Z_CTK_NBR_LSD_H_
#define _Z_CTK_NBR_LSD_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_buffer.h"
#include "ctk/string/string_slice.h"

#include "ctk/util/util_type.h"

namespace ctk {
namespace nbr {

    typedef ctk::byte tag_t;

    const tag_t TAG_INVALID = 0xFF;
    const tag_t TAG_DUMMY = 0x00;

    const ctk::size_type NEST_TAG_LEN = 3;
    const ctk::pcstr NEST_BEGIN = "\xFF\x01("; //, NEST_TAG_LEN);
    const ctk::pcstr NEST_END = "\xFF\x01)"; //, NEST_TAG_LEN);

    class CTK_API ValueBase
    {
    public:
        virtual ~ValueBase() { }
        virtual bool simple() const = 0;
        virtual ctk::dumper& dump(ctk::dumper& _os) const = 0;
    };
    CTK_API ctk::dumper& operator<<(ctk::dumper& os, const ValueBase& v);
    CTK_API std::ostream& operator<<(std::ostream& _os, const ValueBase& _v);

    class CTK_API SimpleValue : public ValueBase
    {
        typedef ctk::istr _Data;
        _Data data_;
        bool textual_;

    public:
        SimpleValue(bool _textual=false);
        SimpleValue(ctk::istr _data, bool _textual=false);
        ~SimpleValue();

        virtual bool simple() const;

        const _Data& data() const;

        void read(ctk::int1& _val)   const;
        void read(ctk::int8& _val)   const;
        void read(ctk::uint8& _val)  const;
        void read(ctk::int16& _val)  const;
        void read(ctk::uint16& _val) const;
        void read(ctk::int32& _val)  const;
        void read(ctk::uint32& _val) const;
        void read(ctk::int64& _val)  const;
        void read(ctk::uint64& _val) const;
        void read(ctk::real32& _val) const;
        void read(ctk::real64& _val) const;
        void read(ctk::Int1& _val)   const;
        void read(ctk::Int8& _val)   const;
        void read(ctk::Int16& _val)   const;
        void read(ctk::Int32& _val)   const;
        void read(ctk::Int64& _val)   const;
        void read(ctk::Uint8& _val)   const;
        void read(ctk::Uint16& _val)   const;
        void read(ctk::Uint32& _val)   const;
        void read(ctk::Uint64& _val)   const;
        void read(ctk::Real32& _val)   const;
        void read(ctk::Real64& _val)   const;
        void read(ctk::Wchar& _val) const;
        void read(ctk::String& _val) const;
        void read(ctk::Wstring& _val) const;
        void read(ctk::istr& _val) const;
        void read(ctk::Bytes& _val)  const;
        void read(ctk::Time& _val)   const;

        ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        ctk::int64 readInt(ctk::size_type _maxBytes) const;
        ctk::uint64 readUint(ctk::size_type _maxBytes) const;

    }; // SimpleValue

    class CTK_API ComplexValue : public ValueBase
    {
    public:
        class Item;

        typedef ctk::list<Item> _Data;
        typedef _Data::const_iterator const_iterator;

        typedef ctk::map<tag_t, ValueBase*> _Map;

    private:
        _Data data_;
        
        _Map map_;

    public:
        ComplexValue();
        ~ComplexValue();

        virtual bool simple() const { return false; }

        const _Data& data() const { return data_; }

        const_iterator begin() const { return data_.begin(); }
        const_iterator end() const { return data_.end(); }

        void add(tag_t _tag, ValueBase* _val);

        ValueBase* get(tag_t _tag) const;

        ctk::dumper& dump(ctk::dumper& _os) const;

    public:
        class Item
        {
            friend class ComplexValue;

            tag_t tag_;
            ValueBase* value_;
        
        public:
            Item(ValueBase* _value=0, tag_t _tag=TAG_INVALID)
                : tag_(_tag), value_(_value)
            {
            }
            ~Item()
            {
                value_ = 0;
            }

            ValueBase* value() const
            {
                return value_;
            }
        
            ctk::dumper& dump(ctk::dumper& _os) const;

        };

    }; // ComplexValue
    inline ctk::dumper& operator<<(ctk::dumper& os, const ComplexValue::Item& v)
    {
        return v.dump(os);
    }

} // end of namespace nbr
} // end of namespace ctk

#endif // !_Z_CTK_NBR_LSD_H_


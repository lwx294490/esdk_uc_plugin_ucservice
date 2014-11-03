/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_BITS_H_
#define _Z_CTK_STRING_BITS_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_octets.h"

namespace ctk
{
    class CTK_API BitPos
    {
    public:
        typedef BitPos _Self;

        typedef ushort byte_no_type;
        typedef uchar bit_no_type;
        typedef size_type total_bit_no_type;

    public:
        BitPos()
            : byte_no_(0), bit_no_(0)
        {
        }
        BitPos(total_bit_no_type _no)
        {
            fromTotal(_no);
        }
        BitPos(byte_no_type _byte_no, bit_no_type _bit_no)
            : byte_no_(_byte_no), bit_no_(_bit_no&0x7)
        {
        }

        _Self& fromTotal(total_bit_no_type v)
        {
            byte_no_ = byte_no_type(v / 8);
            bit_no_ = bit_no_type(v % 8);
            return *this;
        }

        total_bit_no_type toTotal() const
        {
            return byte_no_ * 8UL + bit_no_;
        }

        byte_no_type byte_no() const
        {
            return byte_no_;
        }

        bit_no_type bit_no() const
        {
            return bit_no_;
        }

    private:
        byte_no_type byte_no_;
        bit_no_type  bit_no_;  // 0..7
    }; // BitPos

    class CTK_API BitsSub
    {
    public:
        BitsSub(const BitPos& _begin, size_type _num)
            : begin_(_begin), num_(_num)
        {
        }

        BitPos begin() const
        {
            return begin_;
        }

        BitPos end() const
        {
            return BitPos(begin_.toTotal() + num_);
        }

        size_type size() const
        {
            return num_;
        }

    private:
        BitPos begin_;
        size_type num_;
    }; // BitsSub

    template<size_type N>
    class bits
    {
    public:
        typedef bits<N> _Self;

        typedef ctk::octets<(N+7)/8> store_type;
        typedef BitPos::total_bit_no_type total_bit_no_type;

    public:
        bits() : bytes_(0)
        {
        }

        Byte::BitHelper operator[](total_bit_no_type _pos)
        {
            BitPos bp(_pos);
            byte& c = bytes_[bp.byte_no()];
            return Byte::BitHelper(c, bp.bit_no());
        }

        bool operator[](total_bit_no_type _pos) const
        {
            BitPos bp(_pos);
            Byte c = bytes_[bp.byte_no()];
            return c[bp.bit_no()];
        }

        _Self& set(total_bit_no_type _pos, bool _val=true)
        {
            (*this)[_pos] = _val;
            return *this;
        }
        _Self& reset(total_bit_no_type _pos)
        {
            (*this)[_pos] = false;
            return *this;
        }

        bool get(total_bit_no_type _pos) const
        {
            return (*this)[_pos];
        }

        size_type max_size() const
        {
            return N;
        }

        const store_type& store() const
        {
            return bytes_;
        }

    public:
        ctk::dumper& dump(ctk::dumper& _os) const
        {
            CTK_DUMP(_os, "ctk::bits<"<<N<<">");
            DUMP_VAR(_os, bytes_);
            return _os;
        }
        std::ostream& dump(std::ostream& _os) const
        {
            for (size_type i=0; i<bytes_.size(); ++i)
            {
                if (i) _os << C_space;
                for (int j=7; j>=0; --j)
                {
                    _os << Byte(bytes_[i]).get((byte)j); 
                }
            }
            return _os;
        }

    private:
        store_type bytes_;
        //                                 bit no
        //                             H G F E D C B A
        // octet 1, byte 0           : 7 6 5 4 3 2 1 0
        // octet 2, byte 1 (bit 8+)  : 7 6 5 4 3 2 1 0
        // octet 3, byte 2 (bit 16+) : 7 6 5 4 3 2 1 0
        // octet 4, byte 3 (bit 24+) : 7 6 5 4 3 2 1 0
        // ...
    };
    template<size_type N>
    inline std::ostream& operator<<(std::ostream& os, const bits<N>& v)
    {
        return os << v.store();
    }
    template<size_type N>
    inline dumper& operator<<(dumper& os, const bits<N>& v)
    {
        return v.dump(os);
    }

} // namespace ctk

#endif //_Z_CTK_STRING_BITS_H_


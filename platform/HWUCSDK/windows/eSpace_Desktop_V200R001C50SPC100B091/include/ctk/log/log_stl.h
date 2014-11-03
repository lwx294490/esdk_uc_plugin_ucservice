/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_STL_H_
#define _Z_CTK_LOG_STL_H_

#include "ctk/base/base_type_stl.h"
#include "ctk/base/base_type_enum.h"
#include "ctk/base/base_type_pointer.h"
#include "ctk/base/base_type_array.h"

#include "ctk/string/string_charray.h"
#include "ctk/string/string_formatter.h"

#include "ctk/log/log_dumper.h"
#include "ctk/log/log_macros.h"

#include "ctk/mt/handle.h"

namespace ctk
{
    struct CTK_API hexdata
    {
        pcustr buf_;
        size_type len_;

        hexdata(istr _s)
            : buf_((pcustr)_s.data()), len_(_s.size())
        {
        }
        hexdata(istr _s, size_type _len)
            : buf_((pcustr)_s.data()), len_(std::min(_s.size(), _len))
        {
        }
        hexdata(pcustr _buf, size_type _len)
            : buf_(_buf), len_(_len)
        {
        }
        hexdata(pcstr _buf, size_type _len)
            : buf_((pcustr)_buf), len_(_len)
        {
        }

        ctk::dumper& operator()(ctk::dumper& os) const;
        std::ostream& operator()(std::ostream& os) const;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::hexdata& v)
    {
        return v(os);
    }
    inline std::ostream& operator<<(std::ostream& os, const ctk::hexdata& v)
    {
        return v(os);
    }

    struct CTK_API write_hex
    {
        pcustr buf_;
        size_type len_;

        write_hex(istr _buf)
            : buf_((pcustr)_buf.data()), len_(_buf.size())
        {
        }
        write_hex(pcustr _buf, size_type _len)
            : buf_(_buf), len_(_len)
        {
        }
        write_hex(pcstr _buf, size_type _len)
            : buf_((pcustr)_buf), len_(_len)
        {
        }

        ctk::dumper& operator()(ctk::dumper& os) const;
        std::ostream& operator()(std::ostream& os) const;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const write_hex& v)
    {
        return v(os);
    }
    inline std::ostream& operator<<(std::ostream& _os, const write_hex& _v)
    {
        return _v(_os);
    }

    struct CTK_API show_printable
    {
        show_printable(char _c) : c_(_c) { }
        char c_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const show_printable& _v);

    struct CTK_API dump_hex_base
    {
        pcustr buf_;
        size_type len_;

        dump_hex_base(istr _buf)
            : buf_((pcustr)_buf.data()), len_(_buf.size())
        {
        }
        dump_hex_base(pcustr _buf, size_type _len)
            : buf_(_buf), len_(_len)
        {
        }
        dump_hex_base(pcstr _buf, size_type _len)
            : buf_((pcustr)_buf), len_(_len)
        {
        }

        std::ostream& operator()(std::ostream& _os) const;

        virtual void output(std::ostream& _os, uchar _c) const = 0;
    };
    template<class HowShow=show_printable>
    struct dump_hex : public dump_hex_base
    {
        dump_hex(istr _buf)
            : dump_hex_base(_buf)
        {
        }
        dump_hex(pcustr _buf, size_type _len)
            : dump_hex_base(_buf, _len)
        {
        }
        dump_hex(pcstr _buf, size_type _len)
            : dump_hex_base((pcustr)_buf, _len)
        {
        }

        virtual void output(std::ostream& _os, uchar _c) const
        {
            _os << HowShow(_c);
        }
    };
    template<class T>
    inline std::ostream& operator<<(std::ostream& _os, const dump_hex<T>& _v)
    {
        return _v(_os);
    }

    inline std::ostream& operator<<(std::ostream& _os, const Dumpable& _v)
    {
        ctk::dumper d(_os, false);
        _v.dump(d);
        return _os;
    }

    template<class T>
    String ToNormalString(const T& obj)
    {
        ctk::dumper os(true);
        os << obj;
        return os.str();
    }
    template<class T>
    String ToDumperString(const T& obj)
    {
        ctk::dumper os;
        os << obj;
        return os.str();
    }

    template<class T>
    inline ctk::dumper& operator<<(ctk::dumper& os, const T& v)
    {
        return v.dump(os);
    }

    template<class T>
    inline ctk::dumper& operator<<(ctk::dumper& _os, const Handle<T>& _v)
    {
        if (!_v)
            return _os << "null";
        return _os << *_v.get();
    }

    template<typename E>
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::Enum<E>& v)
    {
        return os.write(v.str()).write("~").write((int)v.get());
    }

    template<size_type N>
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::charray<N>& v)
    {
        return os.write((istr)v);
    }

    template<size_type N>
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::StringFormatter<N>& v)
    {
        return os.write((istr)v);
    }

    template<typename T>
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::Pointer<T>& v)
    {
        return v ? os << *v : os.write("null");
    }

    template<class T>
    inline ctk::dumper& operator<<(ctk::dumper& os, T* const & v)
    {
        return v ? os << *v : os.write("null");
    }

    template<class T>
    inline ctk::dumper& operator<<(ctk::dumper& os, T const * const & v)
    {
        return v ? os << *v : os.write("null");
    }

    // ¶ÔSTLÀàÐÍÀ©³ä //

    template<class T1, class T2>
    dumper& operator<<(dumper& _d, const std::pair<T1, T2>& _v)
    {
        String s;
        s << _v.first;
        return _d << ctk::rawstring(s.data()) << ctk::rawstring(_d.compact()?":":" : ") << _v.second;
    }

    // T is iterator
    template<class T>
    dumper& output_(dumper& _os, T _begin, T _end)
    {
        for (T it=_begin; it!=_end; ++it)
        {
            DUMP_VAL(_os, *it);
        }
        return _os;
    }

    // T is iterator
    template<class T>
    dumper& output_array_(dumper& _os, T _begin, T _end)
    {
        ctk::size_type idx = 0;
        for (T it=_begin; it!=_end; ++it, ++idx)
        {
            ctk::String name;
            name << "[" << idx << "]";
            DUMP_ONE(_os, name, *it, "");
        }
        return _os;
    }

    // T is container
    template<class T>
    dumper& output(dumper& _os, const T& _v)
    {
        return output_(_os, _v.begin(), _v.end());
    }
    template<class T>
    dumper& output_array(dumper& _os, const T& _v)
    {
        return output_array_(_os, _v.begin(), _v.end());
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::vector<T>& _v)
    {
        CTK_DUMP(_d, "ctk::vector");
        return output_array(_d, _v);
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::deque<T>& _v)
    {
        CTK_DUMP(_d, "ctk::deque");
        return output(_d, _v);
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::queue<T>& _v)
    {
        CTK_DUMP(_d, "ctk::queue");
        return output(_d, _v._Get_c());
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::stack<T>& _v)
    {
        CTK_DUMP(_d, "ctk::stack");
        return output(_d, _v._Get_c());
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::list<T>& _v)
    {
        CTK_DUMP(_d, "ctk::list");
        return output(_d, _v);
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::set<T>& _v)
    {
        CTK_DUMP(_d, "ctk::set");
        return output(_d, _v);
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::multiset<T>& _v)
    {
        CTK_DUMP(_d, "ctk::multiset");
        return output(_d, _v);
    }

    template<class _K, class _V>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::map<_K,_V>& _v)
    {
        CTK_DUMP(_d, "ctk::map");
        return output(_d, _v);
    }

    template<class _K, class _V>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::multimap<_K,_V>& _v)
    {
        CTK_DUMP(_d, "ctk::multimap");
        return output(_d, _v);
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::array_ref<T>& _v)
    {
        CTK_DUMP(_d, "ctk::array");
        return output_array(_d, _v);
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::array_ref<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

} // end of namespace ctk

namespace std
{
    inline std::ostream& operator<<(std::ostream& _os, const std::ostringstream& _v)
    {
        return _os << _v.str();
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::vector<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::deque<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::queue<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::stack<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::list<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::set<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::multiset<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class K, class V>
    std::ostream& operator<<(std::ostream& _os, const ctk::map<K, V>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class K, class V>
    std::ostream& operator<<(std::ostream& _os, const ctk::multimap<K, V>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

} // end of namespace std

#endif//_Z_CTK_LOG_STL_H_


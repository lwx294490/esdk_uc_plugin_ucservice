/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_ENUM_H_
#define _Z_CTK_BASE_TYPE_ENUM_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_string.h"

#include <stdexcept>

#define CTK_ENUM_INIT(E, v, n) ctk::Enum<E>::add(v, n)
#define CTK_ENUM_INIT_NV(E, v) CTK_ENUM_INIT(E, v, #v)

namespace ctk
{

    template<typename E>
        struct Enum
        {
            typedef Enum<E> _Self;
            typedef E _Value;
            typedef ctk::String _String;
            typedef const _String& _RCString;
            typedef std::map<_Value, _String> _Value2string;
            typedef std::map<_String, _Value> _String2value;

            struct _Pair : public std::pair<_Value, _String>
            {
                typedef std::pair<_Value, _String> _Super;
            public:
                _Pair() { }
                _Pair(_Value _v, _RCString _s) : _Super(_v, _s) { }
                _Pair(_RCString _s, _Value _v) : _Super(_v, _s) { }
            };
            typedef std::list<_Pair> _PairList;

            Enum() { set(default_value()); }
            Enum(_Value _v) { set(_v); }
            explicit Enum(int _v) { set(_v); }
            explicit Enum(_RCString _v) { set(_v); }

            _Self& operator=(int _v) { set(_v); return *this; }
            _Self& operator=(_Value _v) { set(_v); return *this; }
            _Self& operator=(_RCString _v) { set(_v); return *this; }

            void set(int _v) { value_ = static_cast<_Value>(_v); }
            void set(_Value _v) { value_ = _v; }
            void set(_RCString _v) { value_ = from(_v); }

            operator _Value() const { return get(); }

            _Value get() const { return value_; }
            _RCString str() const { return from(get()); }

            bool operator==(_Value _v) { return value_ == _v; }

            void swap(_Self& _v) { ctk::swap(value_, _v.value_); }

            static _Value from(_RCString _v)
            {
                if (string2value().find(_v)==string2value().end())
                {
                    throw std::invalid_argument("invalid enum value string");
                    //return default_value_;
                }
                return string2value()[_v];
            }
            static _RCString from(_Value _v)
            {
                return value2string().find(_v)!=value2string().end()
                    ? value2string()[_v]
                    : ctk::String::null();
            }

            static void add(_Value _v, _RCString _s)
            {
                value2string()[_v] = _s;
                string2value()[_s] = _v;
            }
            static void init(const _PairList& _values)
            {
                for (typename _PairList::const_iterator i=_values.begin(); i!=_values.end(); ++i)
                {
                    add((*i).first, (*i).second);
                }
            }
            static void init(const _Pair* _begin, const _Pair* _end)
            {
                for (const _Pair* i=_begin; i!=_end; ++i)
                {
                    add((*i).first, (*i).second);
                }
            }
            static void fini()
            {
                CTK_DELETE(value2string_i());
                CTK_DELETE(string2value_i());
            }

            static void set_default(_Value _v)
            {
                default_value() = _v;
            }
            static _Value get_default()
            {
                return default_value();
            }

            static const _String2value& get_string_to_value_map()
            {
                return string2value();
            }

            static const _Value2string& get_value_to_string_map()
            {
                return value2string();
            }

        private:
            _Value value_;

            static _Value2string& value2string() { return *value2string_i(); }
            static _Value2string*& value2string_i()
            {
                static _Value2string* value2string_ = CTK_NEW(_Value2string);
                return value2string_;
            }
            static _String2value& string2value() { return *string2value_i(); }
            static _String2value*& string2value_i()
            {
                static _String2value* string2value_ = CTK_NEW(_String2value);
                return string2value_;
            }
            static _Value& default_value() { static _Value default_value_ = (_Value)-1; return default_value_; }
        };
    template<typename E>
        inline std::ostream&
        operator<<(std::ostream& _os, const Enum<E>& _v)
        {
            return _os << (int)_v;
        }
    template<typename E>
        inline std::istream&
        operator>>(std::istream& _is, Enum<E>& _v)
        {
            int v = Enum<E>::default_value_; _is >> v; _v = v;
            return _is;
        }

    template<typename E>
        inline ctk::String&
        operator<<(ctk::String& _os, const Enum<E>& _v)
        {
            return _os << _v.str();
        }

    template<typename E>
        inline
        void swap(Enum<E>& _l, Enum<E>& _r)
    {
        _l.swap(_r);
    }

    template<typename E>
        inline ctk::Enum<E>
        to_enum(E _v)
    {
        return ctk::Enum<E>(_v);
    }

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_ENUM_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_T_H_
#define _Z_PML_PML_T_H_

#include "ctk/pml/pml_parser.h"

namespace ctk {
namespace pml {

template <class IN_TYPE> 
class Inputer
{
public:
    Inputer(IN_TYPE& _is, ntv::Unit& _ntv)
        : is_(_is), ntv_(_ntv)
    {
    }

private:
    IN_TYPE& is_;
    ntv::Unit& ntv_;
};

template <class CHAR_TYPE, class IN_TYPE> 
bool 
__NtvFromPml(ntv::Unit& _ntv, IN_TYPE& _is)
{
    _ntv.clear();
    pmlParser<CHAR_TYPE> parser(&_ntv);
    return parser.doParser(_is);
}

template <class CHAR_TYPE, class IN_TYPE> 
bool 
__NtvFromValueString(ntv::Unit& _ntv, IN_TYPE& _is)
{
    _ntv.clear();
    pmlValueParser<CHAR_TYPE> parser(&_ntv);
    return parser.doParser(_is);
}

template <class CHAR_TYPE, class OUT_TYPE>
void
__WritePath(OUT_TYPE& os, rcstr _path)
{
    os << Const<CHAR_TYPE>::LEFT_COMMENT_STR << " " << _path << " " << Const<CHAR_TYPE>::RIGHT_COMMENT_STR << " ";
}

template <class CHAR_TYPE, class OUT_TYPE>
void
__WriteValue(OUT_TYPE& os, ntv::ValueBase* _value)
{
    if (_value)
        os << *_value;
}

template <class CHAR_TYPE, class OUT_TYPE>
void
__WriteName(OUT_TYPE& _os, rcstr _name)
{
    String s(_name);
    pml::escapeString(s);
    pml::unescapeString(s);
    _os << s;
}

template <class CHAR_TYPE, class OUT_TYPE>
void
__WriteType(OUT_TYPE& _os, rcstr _type)
{
    _os << Const<CHAR_TYPE>::TYPE_IDENTITY_STR;
    _os << _type;
}

template <class CHAR_TYPE, class OUT_TYPE>
void __WriteIndent(OUT_TYPE& _os, int _nIndent, pcstr _lpszIndent="    ")
{
    for (int i=0; i<_nIndent; ++i)
        _os << _lpszIndent;
}

template <class CHAR_TYPE, class OUT_TYPE>
void __WriteLineSeparator(OUT_TYPE& _os, int _nIndent, pcstr _lpszIndent="    ", pcstr _lpszNewline="\n")
{
    _os << _lpszNewline;
    __WriteIndent<CHAR_TYPE>(_os, _nIndent, _lpszIndent);
}

template <class CHAR_TYPE, class OUT_TYPE>
bool
__NtvToCompactPml(const ntv::Unit& _u, OUT_TYPE& _os, ShowPattern _sp)
{
    /*
        N:T(V) or
        N:T(N:T(V)N:T(N:T(V)N:T(V))N:T(:T(V):T(V)))
    */

    if (SHOW_NAME(_sp))
        __WriteName<CHAR_TYPE>(_os, _u.name());

    if (SHOW_TYPE(_sp) && !_u.type().empty())
    {
        __WriteType<CHAR_TYPE>(_os, _u.type());
    }

    _os << Const<CHAR_TYPE>::LEFT_TAG;

    if (_u.value()!=0)
    {
        if (_u.value()->single())
        {
            if (SHOW_VALUE(_sp))
            {
                __WriteValue<CHAR_TYPE>(_os, _u.value());
            }
        }
        else
        {
            ntv::ListValue* p = 0;
            if (_u.getValue(p))
            {
                typedef typename ntv::ListValue::const_iterator _It;
                for (_It it=p->begin(); it!=p->end(); ++it)
                {
                    __NtvToCompactPml<CHAR_TYPE>(*(*it), _os, _sp);
                }
            }
        }
    }

    _os << Const<CHAR_TYPE>::RIGHT_TAG;

    return true;
}

template <class CHAR_TYPE, class OUT_TYPE>
bool 
__NtvToFormattedPml(const ntv::Unit& _u, OUT_TYPE& _os, int& _nIndent, ShowPattern _sp, pcstr _lpszIndent="    ")
{
    /*
        N:T(
            N:T(V)
            N:T(
                N:T(V)
                N:T(V)
            )
            N:T(
                :T(V)
                :T(V)
            )
        )
    */
    /*
        1. 叶子单占一行 //
        2. ')'单占一行 //
        3. 'N('或'('单占一行 //
        4. 每个'('后就多缩进，每个')'前就少缩进 //
        5. 长字符串分行 //
    */
    
    __WriteIndent<CHAR_TYPE>(_os, _nIndent, _lpszIndent);

    if (SHOW_PATH(_sp))
        __WritePath<CHAR_TYPE>(_os, _u.path());

    if (_u.childWasSingle())
    {
        return __NtvToCompactPml<CHAR_TYPE>(_u, _os, _sp);
    }

    if (SHOW_NAME(_sp))
        __WriteName<CHAR_TYPE>(_os, _u.name());

    if (SHOW_TYPE(_sp) && !_u.type().empty())
    {
        __WriteType<CHAR_TYPE>(_os, _u.type());
    }

    _os << Const<CHAR_TYPE>::LEFT_TAG;

    ntv::ListValue* pL = 0;
    if (!_u.getValue(pL)) return false;
    CTK_ASSERT(pL!=0);

    _os << "\n";
    _nIndent++;

    for (ntv::ListValue::const_iterator it=pL->begin(); it!=pL->end(); ++it)
    {
        const ntv::Unit* pU = *it;
        __NtvToFormattedPml<CHAR_TYPE>(*pU, _os, _nIndent, _sp, _lpszIndent);
        _os << "\n";
    }

    _nIndent--;
    __WriteIndent<CHAR_TYPE>(_os, _nIndent, _lpszIndent);
    
    _os << Const<CHAR_TYPE>::RIGHT_TAG;

    return true;
}

template <class CHAR_TYPE, class OUT_TYPE>
bool 
__NtvToMixedPml(const ntv::Unit& _u, OUT_TYPE& _os, int _nIndent, ShowPattern _sp, pcstr _lpszIndent="    ")
{
    /*
        N:T(N:T(V)N:T(V)N:T(N:T(V)N:T(V))N:T(
            :T(V)
            :T(V)
            :T(V)
        ))
    */
    /*
        1. 节点头及其随后的简单属性们占一行 //
        2. 复杂属性（list等，其成员无名）节点的每个成员单占一行 //
    */
    
    __WriteIndent<CHAR_TYPE>(_os, _nIndent, _lpszIndent);

    if (_u.childWasSingle())
    {
        return __NtvToCompactPml<CHAR_TYPE>(_u, _os, _sp);
    }

    if (SHOW_NAME(_sp))
    {
        __WriteName<CHAR_TYPE>(_os, _u.name());
    }

    if (SHOW_TYPE(_sp) && !_u.type().empty())
    {
        __WriteType<CHAR_TYPE>(_os, _u.type());
    }

    _os << Const<CHAR_TYPE>::LEFT_TAG;

    int oldIndent = _nIndent;
    bool isList = _u.childrenWereUnnamedList();
    if (isList)
    {
        _nIndent++;
    }

    ntv::ListValue* pL = 0;
    if (!_u.getValue(pL)) return false;
    CTK_ASSERT(pL!=0);
    
    ntv::ListValue::const_iterator it = pL->begin();
    for (; it != pL->end(); ++it)
    {
        const ntv::Unit* pU = *it;
        if (pU->name().empty() && !pU->type().empty())
        {
            __WriteLineSeparator<CHAR_TYPE>(_os, _nIndent, _lpszIndent);
        }
        __NtvToMixedPml<CHAR_TYPE>(*pU, _os, _nIndent, _sp, _lpszIndent);
    }

    _nIndent = oldIndent;
    if (isList)
    {
        __WriteLineSeparator<CHAR_TYPE>(_os, _nIndent, _lpszIndent);
    }
    
    _os << Const<CHAR_TYPE>::RIGHT_TAG;

    return true;
}

template <class CHAR_TYPE, class OUT_TYPE>
bool 
__NtvToSimplePml(const ntv::Unit& _u, OUT_TYPE& _os, int _nIndent, ShowPattern _sp, pcstr _lpszIndent="    ")
{
    /*
        N:T(
            N:T(N:T(N:T(V)))
            N:T(
                N:T(V)
                N:T(V)
                N:T(V)
            )
        )
    */
    /*
        1. 子孙单传的节点占一行 //
        2. 其它节点可占多行 //
    */
    
    __WriteIndent<CHAR_TYPE>(_os, _nIndent, _lpszIndent);

    if (_u.childWasSingle())
    {
        return __NtvToCompactPml<CHAR_TYPE>(_u, _os, _sp);
    }

    if (SHOW_NAME(_sp))
    {
        __WriteName<CHAR_TYPE>(_os, _u.name());
    }

    if (SHOW_TYPE(_sp) && !_u.type().empty())
    {
        __WriteType<CHAR_TYPE>(_os, _u.type());
    }

    _os << Const<CHAR_TYPE>::LEFT_TAG;

    ntv::ListValue* pL = 0;
    if (!_u.getValue(pL)) return false;
    CTK_ASSERT(pL!=0);

    _os << "\n";
    _nIndent++;

    for (ntv::ListValue::const_iterator it=pL->begin(); it!=pL->end(); ++it)
    {
        const ntv::Unit* pU = *it;
        __NtvToSimplePml<CHAR_TYPE>(*pU, _os, _nIndent, _sp, _lpszIndent);
        _os << "\n";
    }

    _nIndent--;
    __WriteIndent<CHAR_TYPE>(_os, _nIndent, _lpszIndent);

    _os << Const<CHAR_TYPE>::RIGHT_TAG;

    return true;
}

template <class IN_TYPE, class OUT_TYPE>
bool 
__FormatPML(IN_TYPE& _is, OUT_TYPE& _os, ShowMode _sm, ShowPattern _sp)
{
    ntv::Unit u;
    if (!ntvFromPml(u, _is))
        return false;
    return ntvToPml(u, _os, _sm, _sp);
}

template <class IN_TYPE>
ctk::pml::ntv::Unit*
__NewNTV(IN_TYPE& _is)
{
    ntv::Unit* p = ctk::allocate<ntv::Unit>(CTK_CURRENT);
    if (!p)
        return p;
    if (!ntvFromPml(*p, _is))
    {
        ctk::destroy(p, CTK_CURRENT);
    }
    return p;
}

template <class IN_TYPE>
ctk::pml::ntv::ValueBase*
__NewNtvValue(IN_TYPE& _is)
{
    ntv::Unit u;
    if (!ntvFromValueString(u, _is))
        return 0;
    return u.popValue();
}

template<class CHAR_TYPE>
bool
__isSpeacialChar(CHAR_TYPE c)
{
    return c==Const<CHAR_TYPE>::LEFT_TAG_CHAR
        || c==Const<CHAR_TYPE>::RIGHT_TAG_CHAR
        || c==Const<CHAR_TYPE>::TYPE_IDENTITY_CHAR
        || c==Const<CHAR_TYPE>::COMMENT_CHAR
        || c==Const<CHAR_TYPE>::ESCAPE_CHAR
        || c==Const<CHAR_TYPE>::STR_TAG1_CHAR
        || c==Const<CHAR_TYPE>::STR_TAG2_CHAR
        ;
}

template<class CHAR_TYPE>
void
__escapeString(std::basic_string<CHAR_TYPE>& _value)
{
    if (_value.empty())
        return;

    bool hasSpeacialChar = ctk::CharIsSpace(_value[0]) || ctk::CharIsSpace(_value[_value.size()-1]);

    size_type pos=0;
    while(pos<_value.size())
    {
        if (__isSpeacialChar(_value[pos]) || (byte)_value[pos]>=0x80)
        {
            hasSpeacialChar = true;
            if (_value[pos]==Const<CHAR_TYPE>::ESCAPE_CHAR ||
                _value[pos]==Const<CHAR_TYPE>::STR_TAG_CHAR)
            {
                _value.insert(pos, Const<CHAR_TYPE>::ESCAPE_STR);
                pos += StrLen(Const<CHAR_TYPE>::ESCAPE_STR);
            }
        }
        ++pos;
    }

    if (hasSpeacialChar)
    {
        _value.insert(0, Const<CHAR_TYPE>::STR_TAG_STR);
        _value += Const<CHAR_TYPE>::STR_TAG_STR;
    }
}

template<class CHAR_TYPE>
void
__unescapeString(std::basic_string<CHAR_TYPE>& _value)
{
    if (!_value.empty())
    {
        if (_value[0]==Const<CHAR_TYPE>::STR_TAG1_CHAR)
            trimLeftRight(_value, Const<CHAR_TYPE>::STR_TAG1_CHAR);
        else if (_value[0]==Const<CHAR_TYPE>::STR_TAG2_CHAR)
            trimLeftRight(_value, Const<CHAR_TYPE>::STR_TAG2_CHAR);
    }
}

} // namespace pml
} // namespace ctk

#endif // !defined(_Z_PML_PML_T_H_)


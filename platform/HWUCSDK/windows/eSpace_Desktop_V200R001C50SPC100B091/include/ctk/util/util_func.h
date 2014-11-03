/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_FUNC_H_
#define _Z_CTK_UTIL_FUNC_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

namespace ctk
{
    const byte INVALID_HEX = (byte)~0;

    // String (null terminated) manipulate

    CTK_API inline size_type StrLen(pcstr src, size_type _n=npos)
    {
        return !src ? 0
            : _n==npos ? (size_type)std::strlen(src)
            : _n;
    }

    CTK_API inline size_type StrLen(pcwstr src, size_type _n=npos)
    {
        return !src ? 0
            : _n==npos ? (size_type)std::wcslen(src)
            : _n;
    }

    CTK_API size_type StrLenN(pcstr src, size_type maxLen);

    // dest should be at least char[n+1]
    CTK_API pstr StrCopy(pstr dest, pcstr src, size_type n=npos);

    CTK_API pstr StrCat(pstr dest, pcstr src, size_type n=npos);

    CTK_API int StrCmp(pcstr s1, pcstr s2, size_type n=npos, bool _noCase=false);
    CTK_API int StrCmp(ctk::istr s1, ctk::istr s2, size_type n=npos, bool _noCase=false);
    CTK_API int StrCmpUnsafe(pcstr s1, pcstr s2, size_type n=npos, bool _noCase=false);

    inline bool StrEq(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n)==0;
    }
    inline bool StrNe(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n)!=0;
    }
    inline bool StrLt(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n)<0;
    }
    inline bool StrLe(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n)<=0;
    }
    inline bool StrGt(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n)>0;
    }
    inline bool StrGe(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n)>=0;
    }

    inline int StrCmpNoCase(rcistr s1, rcistr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n, true);
    }

    inline int StrCmpNoCase(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmp(s1, s2, n, true);
    }

    inline bool StrIs(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmpNoCase(s1, s2, n)==0;
    }
    inline bool StrIsNot(pcstr s1, pcstr s2, size_type n=npos)
    {
        return StrCmpNoCase(s1, s2, n)!=0;
    }

    CTK_API pstr StrToUpper(pstr s, size_type n=npos);
    CTK_API pstr StrToLower(pstr s, size_type n=npos);

    CTK_API bool StrIsAllDigits(pcstr v);

    inline bool StrIsEmpty(pcstr _s)
    {
        return !_s || !*_s;
    }

    inline bool StrIsEnd(pcstr _s, size_type _pos, size_type _n=npos)
    {
        return !_s[_pos] || _pos>=_n;
    }

    CTK_API void StrTrimRight(string& me);
    CTK_API void StrTrimRight(wstring& me);

    template<class CHAR_TYPE>
    void __trimLeftRight(std::basic_string<CHAR_TYPE>& _s, CHAR_TYPE _c);
    CTK_API void trimLeftRight(string& _s, cchar _c);
    CTK_API void trimLeftRight(wstring& _s, wchar _c);

    CTK_API bool StrBeginWith(pcstr _s, istr _v);
    inline bool StrBeginWith(pcustr _s, istr _v)
    {
        return StrBeginWith((pcstr)_s, _v);
    }

    // Memory manipulate

    CTK_API void* MemSet(void* dest, int c, size_type n);

    CTK_API void* MemCopy(void* dest, const void* src, size_type n);
    CTK_API void* MemCopyZ(void* dest, const void* src, size_type n);

    CTK_API int MemCmp(const void* s1, const void* s2, size_type n);
    inline bool MemEq(const void* s1, const void* s2, size_type n)
    {
        return MemCmp(s1, s2, n)==0;
    }
    inline bool MemNe(const void* s1, const void* s2, size_type n)
    {
        return MemCmp(s1, s2, n)!=0;
    }
    inline bool MemLt(const void* s1, const void* s2, size_type n)
    {
        return MemCmp(s1, s2, n)<0;
    }
    inline bool MemLe(const void* s1, const void* s2, size_type n)
    {
        return MemCmp(s1, s2, n)<=0;
    }
    inline bool MemGt(const void* s1, const void* s2, size_type n)
    {
        return MemCmp(s1, s2, n)>0;
    }
    inline bool MemGe(const void* s1, const void* s2, size_type n)
    {
        return MemCmp(s1, s2, n)>=0;
    }

    // Character manipulate

    CTK_API char HexToChar(byte v);
    CTK_API byte HexFromChar(char v);

    CTK_API bool CharIn(char _c, pcstr _s);

    CTK_API bool CharIsSpace(char _c);
    CTK_API bool CharIsSpace(wchar _c);
    CTK_API bool CharIsPrint(char _c);
    CTK_API bool CharIsPrint(wchar _c);
    CTK_API bool CharIsCntrl(char _c);
    CTK_API bool CharIsUpper(char _c);
    CTK_API bool CharIsLower(char _c);
    CTK_API bool CharIsAlpha(char _c);
    CTK_API bool CharIsDigit(char _c);
    CTK_API bool CharIsPunct(char _c);
    CTK_API bool CharIsXdigit(char _c);
    CTK_API bool CharIsAlnum(char _c);
    CTK_API bool CharIsGraph(char _c);

    CTK_API char CharToLower(char _c);
    CTK_API char CharToUpper(char _c);

    CTK_API const char& CharAt(const char* _buf, size_type _size, size_type i);
    CTK_API char& CharAt(char* _buf, size_type _max_size, size_type i);
    CTK_API const uchar& CharAt(const uchar* _buf, size_type _size, size_type i);
    CTK_API uchar& CharAt(uchar* _buf, size_type _max_size, size_type i);

    template<class _Char>
        inline const _Char&
        GetNull()
    {
        CTK_STATIC_CONST _Char nullCh = 0;
        return nullCh;
    }

    // Byte manipulate

    template<typename T>
        byte
        GetByte(T _value, size_type _n)
    {
        size_type i = _n;
        while(i-- && _value)
            _value >>= 8;
        return byte(_value & 0xFF);
    }

    template<size_type N, typename T>
        byte
        ByteGet(T _value)
    {
        return GetByte(_value, N);
    }

    template<typename T>
        T
        SetByte(T& _value, size_type _n, byte _b)
    {
        size_type i = _n;
        if (i >= sizeof _value)
            return _value;
        T mask = 0xFF;
        T bval = _b;
        while(i--)
        {
            mask <<= 8;
            bval <<= 8;
        }
        _value &= ~mask;
        _value |= bval;
        return _value;
    }

    template<size_type N, typename T>
        T
        ByteSet(T& _value, byte _b)
    {
        return SetByte(_value, N, _b);
    }

    // Print helper

    template<typename T>
        inline std::ostream&
        Print(std::ostream& _os, T _v)
    {
        return _os << _v;
    }
    CTK_API std::ostream& Print(std::ostream& _os, pcstr _v);
    CTK_API std::ostream& Print(std::ostream& _os, char _c);
    inline std::ostream& Print(std::ostream& _os, pcustr _v)
    {
        return Print(_os, (pcstr)_v);
    }
    inline std::ostream& Print(std::ostream& _os, pstr _v)
    {
        return Print(_os, (pcstr)_v);
    }
    inline std::ostream& Print(std::ostream& _os, pustr _v)
    {
        return Print(_os, (pcstr)_v);
    }
    inline std::ostream& Print(std::ostream& _os, uchar _c)
    {
        return Print(_os, (char)_c);
    }

    template<typename T>
    struct print__
    {
        print__(T _val, int _width=0, char _fill=0, bool _hex=false)
            : val_(_val), width_(_width), fill_(_fill), hex_(_hex)
        {
        }

        T val_;
        int width_;
        char fill_;
        bool hex_;
    };
    template<typename T>
        inline std::ostream&
        operator<<(std::ostream& _os, const print__<T>& _v)
    {
        if (_v.fill_)
            _os << std::setfill(_v.fill_);
        if (_v.hex_)
            _os << std::hex;
        if (_v.width_)
            _os << std::setw(_v.width_);

        ctk::Print(_os, _v.val_);
        
        if (_v.fill_)
            _os << std::setfill(C_space);
        if (_v.hex_)
            _os << std::dec;
        return _os;
    }
    template<typename T>
        inline print__<T>
        print(T _v, int _width=0, char _fill=0, bool _hex=false)
    {
        return print__<T>(_v, _width, _fill, _hex);
    }
    template<typename T>
        inline print__<T>
        print_hex(T _v, int _width=0, char _fill=0)
    {
        return print__<T>(_v, _width, _fill, true);
    }

    struct print_ascii__
    {
        print_ascii__(istr _buf)
            : buf_(_buf)
        {
        }

        std::ostream& operator()(std::ostream& _os) const
        {
            for (istr::const_iterator p = buf_.begin(); p!=buf_.end(); ++p)
            {
                if (ctk::CharIsPrint(*p))
                {
                    _os << *p;
                }
                else
                {
                    _os << "\\x";
                    _os << std::uppercase << std::hex << std::setfill(C_0);
                    _os << std::setw(2) << ushort(uchar(*p));
                    _os << std::nouppercase << std::dec << std::setfill(C_space);
                }
            }
            return _os;
        }

        istr buf_;
    };
    inline std::ostream&
        operator<<(std::ostream& _os, const print_ascii__& _v)
    {
        return _v(_os);
    }
    inline print_ascii__
        print_ascii(istr _buf)
    {
        return print_ascii__(_buf);
    }

    template<class _K, class _V> _V*
    GetMapValuePtr(std::map<_K, _V>& _m, const _K& _k)
    {
        typename std::map<_K, _V>::iterator it = _m.find(_k);
        if (it==_m.end())
            return 0;
        return &((*it).second);
    }

    template<class D, class S>
        inline void cast_copy(D& _dest, const S& _src)
    {
        assert(sizeof(_dest)==sizeof(_src));
        ctk::MemCopy(&_dest, &_src, sizeof(D));
    }

    template<class T>
        inline bool equal(T* _p1, T* _p2)
    {
        return _p1 && _p2 && (*_p1 == *_p2);
    }

    template<class T>
        inline bool equal(std::list<T*> _l1, std::list<T*> _l2)
    {
        if (_l1.size() != _l2.size())
            return false;
        for (typename std::list<T*>::const_iterator i1=_l1.begin(), i2=_l2.begin();
            i1!=_l1.end() && i2!=_l2.end();
            ++i1, ++i2)
        {
            if (!equal(*i1, *i2))
                return false;
        }
        return true;
    }

    inline istr altName(istr _primary, istr _alt)
    {
        return !_alt.empty() ? _alt : _primary;
    }

    CTK_API String getenv(pcstr _name);

    CTK_API int getLastErrno();
    CTK_API String getLastErrorMsg();
    CTK_API String getLastErrorMsg(int _lastErrno);

    CTK_API String normalizeName(rcistr _name);

    CTK_API String getProgramDir();
    CTK_API String getApplicationDir(int type);

}

#endif //_Z_CTK_UTIL_FUNC_H_


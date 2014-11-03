/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_STRING_H_
#define _Z_CTK_BASE_TYPE_STRING_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_bytes.h"

#include "ctk/base/base_type_auto.h"

#include "ctk/base/base_type_iwstr.h"

#define CTK_CP_UTF8     65001       // UTF-8 translation CP_UTF8
#define CTK_CP_UTF7     65000       // UTF-7 translation CP_UTF7

#define CTK_CP_LOCALE   0           // CP_ACP
#define CTK_CP_ANSI     0           // CP_ACP
#define CTK_CP_GB2312   20936
#define CTK_CP_GBK      936

#define CTK_CP_DEFAULT  ctk::ConfigFile::codepage() // default code page is UTF-8 now
#define CTK_CP_CFGFILE  (-1)                        // use CTK_CP_DEFAULT as default code page

namespace ctk
{
    using std::string;
    using std::wstring;

    class String;
    typedef const String& rcstr;

    typedef wstring Wstring;
    typedef const Wstring& rcwstr;

#ifdef _CTK_UNICODE
    typedef Wstring tstring;
#else
    typedef String tstring;
#endif
    typedef const tstring& rctstr;

    struct cp_default { };

    class CTK_API CharBuffer
    {
        typedef char char_type;

        char_type* buffer_;
        size_t     length_;

    public:
        explicit CharBuffer(size_t _length=0);
        CharBuffer(const CharBuffer& _other);
        CharBuffer(const istr& _s);
        ~CharBuffer();

        CharBuffer& operator=(const CharBuffer& _other);
        CharBuffer& operator=(const istr& _other);

        void swap(CharBuffer& _other);

        char_type* release();

        char_type* buffer();
        size_t max_size() const;

        const char_type* data() const;
        size_t size() const;

        operator istr() const;
        operator ostr();

    };

    class CTK_API WcharBuffer
    {
        typedef wchar_t char_type;

        char_type* buffer_;
        size_t     length_;

    public:
        explicit WcharBuffer(size_t _length=0);
        WcharBuffer(const WcharBuffer& _other);
        WcharBuffer(const iwstr& _s);
        ~WcharBuffer();

        WcharBuffer& operator=(const WcharBuffer& _other);
        WcharBuffer& operator=(const iwstr& _other);

        void swap(WcharBuffer& _other);

        char_type* release();

        char_type* buffer();
        size_t max_size() const;

        const char_type* data() const;
        size_t size() const;

        operator iwstr() const;
        operator owstr();

    };

    struct CTK_API istr_cp
    {
        istr str_;
        int32 codepage_;

        istr_cp(rcistr _str=istr(), int32 _codepage=CTK_CP_CFGFILE);
        istr_cp(pcstr _str, int32 _codepage=CTK_CP_CFGFILE);
        istr_cp(pcustr _str, int32 _codepage=CTK_CP_CFGFILE);
        istr_cp(string const& _str, int32 _codepage=CTK_CP_CFGFILE);
        istr_cp(String const& _str, int32 _codepage=CTK_CP_CFGFILE);
        istr_cp(pstr const& _str, int32 _codepage=CTK_CP_CFGFILE);
    };

    struct CTK_API iwstr_cp
    {
        iwstr str_;
        int32 codepage_;

        iwstr_cp(rciwstr _str=iwstr(), int32 _codepage=CTK_CP_CFGFILE);
        iwstr_cp(pcwstr _str, int32 _codepage=CTK_CP_CFGFILE);
        iwstr_cp(rcwstr _str, int32 _codepage=CTK_CP_CFGFILE);
        iwstr_cp(pwstr const& _str, int32 _codepage=CTK_CP_CFGFILE);
    };

    class CTK_API String : public std::string
    {
    public:
        typedef std::string _Super;
        typedef String _Self;

    public:
        String();
        String(const _Self& _v);
        String(const _Super& _v);
        explicit String(const Wstring& _v, int32 _codepage=CTK_CP_CFGFILE);
        String(rcistr _v);
        explicit String(rciwstr _v, int32 _codepage=CTK_CP_CFGFILE);
        String(pcstr _v);
        String(pcustr _v);
        explicit String(pcwstr _v, int32 _codepage=CTK_CP_CFGFILE);
        String(pcstr _begin, pcstr _end);
        String(pcstr _v, size_type _len);
        String(pcustr _v, size_type _len);
        ~String();

        _Self& operator=(const _Self& _v);
        _Self& operator=(const _Super& _v);
        _Self& operator=(const Wstring& _v); // use codepage CTK_CP_CFGFILE
        _Self& operator=(rcistr _v);
        _Self& operator=(rciwstr _v); // use codepage CTK_CP_CFGFILE
        _Self& operator=(pcstr _v);
        _Self& operator=(pcustr _v);
        _Self& operator=(pcwstr _v); // use codepage CTK_CP_CFGFILE

        _Self& operator+=(_Self const & _v);
        _Self& operator+=(_Super const & _v);
        _Self& operator+=(Wstring const & _v); // use codepage CTK_CP_CFGFILE
        _Self& operator+=(istr const & _v);
        _Self& operator+=(iwstr const & _v); // use codepage CTK_CP_CFGFILE
        _Self& operator+=(pstr const & _v);
        _Self& operator+=(pustr const & _v);
        _Self& operator+=(pwstr const & _v); // use codepage CTK_CP_CFGFILE
        _Self& operator+=(pcstr const & _v);
        _Self& operator+=(pcustr const & _v);
        _Self& operator+=(pcwstr const & _v); // use codepage CTK_CP_CFGFILE
        _Self& operator+=(char const & _v);
        _Self& operator+=(uchar const & _v);

        template<class T>
        _Self& operator+=(T const & _v)
        {
            std::ostringstream oss;
            oss << _v;
            return (*this) += oss.str();
        }

        operator Wstring() const; // use codepage CTK_CP_CFGFILE

        operator ctk::istr() const
        {
            return ctk::istr(data(), size());
        }

        // use in if condition expression
        operator void *() const;
        bool operator!() const;

        bool operator==(const _Self& _v) const
        {
            return istr(*this)==istr(_v);
        }
        bool operator!=(const _Self& _v) const
        {
            return istr(*this)!=istr(_v);
        }
        bool operator<(const _Self& _v) const
        {
            return istr(*this)<istr(_v);
        }
        bool operator>(const _Self& _v) const
        {
            return istr(*this)>istr(_v);
        }
        bool operator<=(const _Self& _v) const
        {
            return istr(*this)<=istr(_v);
        }
        bool operator>=(const _Self& _v) const
        {
            return istr(*this)>=istr(_v);
        }

        bool operator==(istr _v) const
        {
            return istr(*this)==(_v);
        }
        bool operator!=(istr _v) const
        {
            return istr(*this)!=(_v);
        }
        bool operator<(istr _v) const
        {
            return istr(*this)<(_v);
        }
        bool operator>(istr _v) const
        {
            return istr(*this)>(_v);
        }
        bool operator<=(istr _v) const
        {
            return istr(*this)<=(_v);
        }
        bool operator>=(istr _v) const
        {
            return istr(*this)>=(_v);
        }

        bool operator==(pcstr _v) const
        {
            return istr(*this)==istr(_v);
        }
        bool operator!=(pcstr _v) const
        {
            return istr(*this)!=istr(_v);
        }
        bool operator<(pcstr _v) const
        {
            return istr(*this)<istr(_v);
        }
        bool operator>(pcstr _v) const
        {
            return istr(*this)>istr(_v);
        }
        bool operator<=(pcstr _v) const
        {
            return istr(*this)<=istr(_v);
        }
        bool operator>=(pcstr _v) const
        {
            return istr(*this)>=istr(_v);
        }

        pcstr data() const
        {
            return _Super::c_str();
        }

        ctk::size_type size() const
        {
            return (ctk::size_type)_Super::size();
        }

        bool empty() const
        {
            return _Super::empty();
        }

        _Self& clear();

        _Self& trimLeftRight(char _c);

        void ansiFromUtf8(rcistr _v, int32 _codepage=CTK_CP_CFGFILE);
        void ansiToUtf8(Bytes& _v, int32 _codepage=CTK_CP_CFGFILE) const;
        void ansiFromWstring(rciwstr _v, int32 _codepage=CTK_CP_CFGFILE);
        void ansiToWstring(Wstring& _v, int32 _codepage=CTK_CP_CFGFILE) const;

        static String fromUtf8(rcistr _utf8, int32 _codepage=CTK_CP_CFGFILE);
        String toUtf8(int32 _codepage=CTK_CP_CFGFILE) const;
        static String fromWstring(rciwstr _wstr, int32 _codepage=CTK_CP_CFGFILE);
        Wstring toWstring(int32 _codepage=CTK_CP_CFGFILE) const;

        _Self& replace( const _Super &_old, const _Super &_new );

        static const String& null();

    };
    inline std::ostream& operator<<(std::ostream& _os, const String& _v)
    {
        return _os << istr(_v);
    }

    inline void swap(String& _l, String& _r)
    {
        _l.swap(_r);
    }

    template<class T>
        inline String& operator<<(String& _os, T const & _v)
    {
        return _os += _v;
    }

    template<class T>
        inline bool operator>>(const ctk::String& _is, T& _v)
    {
        if (_is.empty())
            return false;
        std::istringstream iss(_is);
        iss >> _v;
        return !iss.fail();
    }
    template<>
        inline bool operator>>(const ctk::String& _is, ctk::String& _v)
    {
        _v = _is;
        return true;
    }
    template<>
        inline bool operator>>(const ctk::String& _is, std::string& _v)
    {
        _v = _is;
        return true;
    }

    template <class T>
    inline ctk::String
    operator|(const ctk::String& _v1, const T& _v2)
    {
        ctk::String ret;
        ret << _v1 << _v2;
        return ret;
    }

    template <class T>
    inline ctk::String
    operator|(const T& _v1, const ctk::String& _v2)
    {
        ctk::String ret;
        ret << _v1 << _v2;
        return ret;
    }

    inline ctk::String
    operator|(const  ctk::String& _v1, const ctk::String& _v2)
    {
        ctk::String ret;
        ret << _v1 << _v2;
        return ret;
    }

    struct utf8
    {
        istr buf_;
        explicit utf8(istr _buf) : buf_(_buf) { }
    };

    struct ansi
    {
        istr buf_;
        explicit ansi(istr _buf) : buf_(_buf) { }
    };
    inline ansi make_str(rcstr _buf)
    {
        return ansi(_buf);
    }

    struct wstr
    {
        iwstr buf_;
        wstr(iwstr _buf) : buf_(_buf) { }
    };
    inline wstr make_str(rcwstr _buf)
    {
        return wstr(_buf);
    }

    // 返回的自动对象只在函数被调用语句的生命周期内有效，如果要长久使用，可以用release(). //
    // 通常用法： //
    //     ctk::String s = ctk::to_str(...).get();
    // 长久化用法： //
    //     ctk::AutoStr s = ctk::to_str(...).release();
    CTK_API AutoStr to_str(pcstr _pA);
    CTK_API AutoStr to_str(pcwstr _pW, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API AutoWstr to_wstr(pcstr _pA, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API AutoWstr to_wstr(pcwstr _pW);
    CTK_API AutoStr to_utf8str(pcwstr _pW);

    CTK_API String to_ansi(rcistr _sA);
    CTK_API String to_ansi(rciwstr _sW, int32 _codepage=CTK_CP_CFGFILE);

    CTK_API void utf8ToAnsi(const istr& _is, String& _os, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API void ansiToUtf8(const istr& _is, Bytes& _os, int32 _codepage=CTK_CP_CFGFILE);

    CTK_API void utf8ToWstring(const istr& _is, Wstring& _os);
    CTK_API void wstringToUtf8(const iwstr& _is, Bytes& _os);

    CTK_API void ansiToWstring(const istr& _is, Wstring& _os, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API void wstringToAnsi(const iwstr& _is, String& _os, int32 _codepage=CTK_CP_CFGFILE);

    CTK_API void ansiToAnsi(const istr& _isSrc, int32 _codepageSrc, String& _osDest, int32 _codepageDest);

    CTK_API Bytes   toUtf8   (wstr _wstr);
    CTK_API String  toAnsi   (wstr _wstr, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API Wstring toWstring(wstr _wstr);

    CTK_API Bytes   toUtf8   (ansi _ansi, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API String  toAnsi   (ansi _ansi);
    CTK_API Wstring toWstring(ansi _ansi, int32 _codepage=CTK_CP_CFGFILE);

    CTK_API Bytes   toUtf8   (utf8 _utf8);
    CTK_API String  toAnsi   (utf8 _utf8, int32 _codepage=CTK_CP_CFGFILE);
    CTK_API Wstring toWstring(utf8 _utf8);

    inline Bytes   wstr_to_utf8(iwstr _wstr)
    {
        return toUtf8(wstr(_wstr));
    }
    inline String  wstr_to_ansi(iwstr _wstr, int32 _codepage=CTK_CP_CFGFILE)
    {
        return toAnsi(wstr(_wstr), _codepage);
    }
    inline Wstring wstr_to_wstr(iwstr _wstr)
    {
        return toWstring(wstr(_wstr));
    }

    inline Bytes   ansi_to_utf8(istr _ansi, int32 _codepage=CTK_CP_CFGFILE)
    {
        return toUtf8(ansi(_ansi), _codepage);
    }
    inline String  ansi_to_ansi(istr _ansi)
    {
        return toAnsi(ansi(_ansi));
    }
    inline Wstring ansi_to_wstr(istr _ansi, int32 _codepage=CTK_CP_CFGFILE)
    {
        return toWstring(ansi(_ansi), _codepage);
    }

    inline Bytes   utf8_to_utf8(istr _utf8)
    {
        return toUtf8(utf8(_utf8));
    }
    inline String  utf8_to_ansi(istr _utf8, int32 _codepage=CTK_CP_CFGFILE)
    {
        return toAnsi(utf8(_utf8), _codepage);
    }
    inline Wstring utf8_to_wstr(istr _utf8)
    {
        return toWstring(utf8(_utf8));
    }

    inline Wstring stringToWstring(rcistr _ansi, int32 _codepage=CTK_CP_CFGFILE)
    {
        return toWstring(ansi(_ansi), _codepage);
    }

    inline String wstringToString(rciwstr _wstr, int32 _codepage=CTK_CP_CFGFILE)
    {
        return toAnsi(wstr(_wstr), _codepage);
    }

    inline void swap(Wstring& _l, Wstring& _r)
    {
        _l.swap(_r);
    }

    template<>
        inline bool operator>>(const ctk::String& _is, Wstring& _v)
    {
        ansiToWstring(_is, _v);
        return true;
    }

} // namespace ctk

namespace std
{

    inline std::ostream& operator<<(std::ostream& _os, const std::wstring& _v)
    {
        return _os << ctk::iwstr(_v);
    }

    inline std::ostream& operator<<(std::ostream& _os, const wchar_t* _v)
    {
        return _os << ctk::iwstr(_v);
    }

    template<class T>
    inline std::wstring& operator<<(std::wstring& _os, const T& _v)
    {
        std::wostringstream oss;
        oss << _v;
        _os += oss.str();
        return _os;
    }
    
    template<>
    inline std::wstring& operator<<(std::wstring& _os, const ctk::iwstr& _v)
    {
        _os.append(_v.data(), _v.size());
        return _os;
    }

    template<>
    inline std::wstring& operator<<(std::wstring& _os, const std::wstring& _v)
    {
        return _os << (ctk::iwstr)_v;
    }

    template<>
    inline std::wstring& operator<<(std::wstring& _os, const ctk::istr& _v)
    {
        std::wstring wstr;
        ctk::ansiToWstring(_v, wstr);
        return _os << wstr;
    }

    template<>
    inline std::wstring& operator<<(std::wstring& _os, const std::string& _v)
    {
        return _os << (ctk::istr)_v;
    }

    template<>
    inline std::wstring& operator<<(std::wstring& _os, const ctk::String& _v)
    {
        return _os << (ctk::istr)_v;
    }

    inline std::wstring& operator<<(std::wstring& _os, ctk::pcstr const & _v)
    {
        return _os << (ctk::istr)_v;
    }

    inline std::wstring& operator<<(std::wstring& _os, ctk::pcustr const & _v)
    {
        return _os << (ctk::istr)_v;
    }

    inline std::wstring& operator<<(std::wstring& _os, ctk::pcwstr const & _v)
    {
        return _os << (ctk::iwstr)_v;
    }

    inline std::wstring& operator<<(std::wstring& _os, ctk::pstr const & _v)
    {
        return _os << (ctk::istr)_v;
    }

    inline std::wstring& operator<<(std::wstring& _os, ctk::pustr const & _v)
    {
        return _os << (ctk::istr)_v;
    }

    inline std::wstring& operator<<(std::wstring& _os, ctk::pwstr const & _v)
    {
        return _os << (ctk::iwstr)_v;
    }

}

#endif //_Z_CTK_BASE_TYPE_STRING_H_


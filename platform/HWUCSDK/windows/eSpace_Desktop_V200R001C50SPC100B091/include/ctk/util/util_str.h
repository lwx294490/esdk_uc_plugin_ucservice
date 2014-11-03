/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_STR_H_
#define _Z_CTK_UTIL_STR_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type.h"
#include "ctk/base/base_func.h"
#include "ctk/util/util_func.h"

/*
    Str         String utility
    Mem         Memory utility
*/

namespace ctk
{
    class CTK_API Str
    {
    public:
        typedef Str _Self;
        typedef ctk::ostr store_type;
        typedef store_type::pointer pointer;
        typedef store_type::const_pointer const_pointer;

    public:
        Str()
            : store_()
        {
        }
        Str(const store_type& _v)
            : store_(_v)
        {
        }
        explicit Str(pointer _p, size_type _n=npos)
            : store_(_p, _n)
        {
        }

        _Self& operator=(const ctk::istr& _src)
        {
            return copy(_src);
        }

        _Self& operator+=(const ctk::istr& _src)
        {
            return cat(_src);
        }

        operator ctk::istr() const
        {
            return istr(data(), size());
        }

        operator ctk::ostr() const
        {
            return store_;
        }

        _Self substr(size_type _pos=0, size_type _n=npos) const
        {
            return store_.substr(_pos, _n);
        }

        _Self leftstr(size_type _n=npos) const
        {
            return store_.leftstr(_n);
        }

        _Self rightstr(size_type _n=npos) const
        {
            return store_.rightstr(_n);
        }

        _Self& copy(const ctk::istr& _src);

        _Self& cat(const ctk::istr& _src);

        int cmp(const_pointer _p, size_type _n=npos, bool _noCase=false) const
        {
            return ctk::StrCmp(data(), _p, _n, _noCase);
        }

        int cmp(const ctk::istr& _src, size_type _n=npos, bool _noCase=false) const
        {
            return ctk::StrCmp(istr(*this), _src, _n, _noCase);
        }

        bool operator==(const ctk::istr& _src) const
        {
            return cmp(_src)==0;
        }
        bool operator!=(const ctk::istr& _src) const
        {
            return cmp(_src)!=0;
        }
        bool operator<(const ctk::istr& _src) const
        {
            return cmp(_src)<0;
        }
        bool operator<=(const ctk::istr& _src) const
        {
            return cmp(_src)<=0;
        }
        bool operator>(const ctk::istr& _src) const
        {
            return cmp(_src)>0;
        }
        bool operator>=(const ctk::istr& _src) const
        {
            return cmp(_src)>=0;
        }

        int cmpNoCase(const_pointer _p, size_type _n=npos) const
        {
            return cmp(_p, _n, true);
        }

        int cmpNoCase(const ctk::istr& _src, size_type _n=npos) const
        {
            return cmp(_src, _n, true);
        }
        
        bool is(const ctk::istr& _src, size_type _n=npos) const
        {
            return cmpNoCase(_src, _n)==0;
        }
        bool isNot(const ctk::istr& _src, size_type _n=npos) const
        {
            return cmpNoCase(_src, _n)!=0;
        }

        _Self& toUpper(size_type _n=npos)
        {
            ctk::StrToUpper(buffer(), _n==npos?max_size():_n);
            return *this;
        }

        _Self& toLower(size_type _n=npos)
        {
            ctk::StrToLower(buffer(), _n==npos?max_size():_n);
            return *this;
        }

        bool isAllDigits() const
        {
            return ctk::StrIsAllDigits(data());
        }

        _Self& reset()
        {
            store_.reset();
            return *this;
        }

        _Self& fill(int _c, size_type _n=npos)
        {
            if (buffer())
            {
                size_type n = Min(_n, max_size()-1);
                std::memset(buffer(), _c, n);
                buffer()[n-1]=0;
            }
            return *this;
        }

        bool beginWith(const ctk::istr& _src, size_type _n=npos, bool _noCase=false) const
        {
            return leftstr(_n).cmp(_src, _n, _noCase)==0;
        }

        bool endWith(const ctk::istr& _src, size_type _n=npos, bool _noCase=false) const
        {
            return rightstr(_n).cmp(_src, _n, _noCase)==0;
        }

    public:
        bool empty() const
        {
            return ctk::StrIsEmpty(data());
        }

        bool isEnd(size_type _pos) const
        {
            return ctk::StrIsEnd(data(), _pos, size());
        }

        size_type left() const
        {
            if (max_size()==npos)
                return max_size();
            return max_size() - size();
        }

        pointer buffer()
        {
            return store_.buffer();
        }

        size_type max_size() const
        {
            return store_.max_size();
        }

        const_pointer data() const
        {
            return store_.data();
        }

        size_type size() const
        {
            return store_.size();
        }

        size_type sizeN() const
        {
            return store_.sizeN();
        }

        size_type sizeN(size_type _maxLen) const
        {
            return store_.sizeN(_maxLen);
        }

    public:
        std::ostream& dump(std::ostream& _os) const
        {
            return store_.dump(_os);
        }

    private:
        store_type store_;
    };
    inline std::ostream& operator<<(std::ostream& _os, const Str& _v)
    {
        return _os << istr(_v);
    }

    class CTK_API Mem
    {
    public:
        typedef Mem _Self;
        typedef void* pointer;
        typedef const void* const_pointer;

    public:
        Mem()
            : p_(0), n_(0)
        {
        }
        Mem(pointer _p, size_type _n)
            : p_(_p), n_(_n)
        {
        }

        _Self& operator=(const istr& _s)
        {
            return copy(_s);
        }

        operator istr() const
        {
            return istr((pcstr)data(), size());
        }

        _Self& fill(int _c)
        {
            ctk::MemSet(p_, _c, n_);
            return *this;
        }

        _Self& copy(const istr& _s)
        {
            ctk::MemCopy(p_, _s.data(), Min(n_, _s.size()));
            return *this;
        }

        _Self& copyZ(const istr& _s)
        {
            ctk::MemCopyZ(p_, _s.data(), Min(n_-1, _s.size()));
            return *this;
        }

        int cmp(const istr& _s) const
        {
            int ret = ctk::MemCmp(data(), _s.data(), Min(size(), _s.size()));
            return ret ? ret : (size()-_s.size());
        }

        const_pointer data() const
        {
            return p_;
        }

        size_type size() const
        {
            return n_;
        }

    public:
        std::ostream& dump(std::ostream& _os) const
        {
            return istr(*this).dump(_os);
        }

    private:
        pointer p_;
        size_type n_;
    };
    inline std::ostream& operator<<(std::ostream& _os, const Mem& _v)
    {
        return _os << istr(_v);
    }

}

#endif //_Z_CTK_UTIL_STR_H_


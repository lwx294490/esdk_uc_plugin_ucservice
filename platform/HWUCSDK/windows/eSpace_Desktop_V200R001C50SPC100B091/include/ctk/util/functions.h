/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_FUNCTIONS_H_
#define _Z_CTK_UTIL_FUNCTIONS_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

#include "ctk/pml/pml_stream.h"

#include "ctk/log/log_dumper.h"
#include "ctk/log/log_macros.h"
#include "ctk/log/log_logger.h"

#include "ctk/util/hex16.h"

namespace ctk
{
    template<class T, class S>
    inline void
    cast_assign(T& _d, const S& _s)
    {
        _d = static_cast<T>(_s);
    }

    template<class T, class S>
    inline void
    dyna_cast(T*& _d, S* _s)
    {
        _d = dynamic_cast<T*>(_s);
    }

    template<class T, class S>
    inline void
    dyna_cast(const T*& _d, const S* _s)
    {
        _d = dynamic_cast<T*>(_s);
    }

    template <class T>
    struct pml_str__
    {
        T& obj_;
        ctk::pml::ShowMode sm_;

        pml_str__(T& _obj, ctk::pml::ShowMode _sm)
            : obj_(_obj), sm_(_sm)
        {
        }
    };
    template <class T>
    inline std::ostream&
    operator<<(std::ostream& _os, const pml_str__<T>& _v)
    {
        ctk::pml::stream mps;
        _v.obj_.codec(mps);
        _os << mps.str(_v.sm_);
        return _os;
    }
    template <class T>
    inline pml_str__<T>
    pml_str(T& _obj, ctk::pml::ShowMode _sm=ctk::pml::ShowMode::COMPACT)
    {
        return pml_str__<T>(_obj, _sm);
    }

    template <class T>
    struct dump_str__
    {
        const T& obj_;

        dump_str__(const T& _obj)
            : obj_(_obj)
        {
        }
    };
    template <class T>
    inline std::ostream&
    operator<<(std::ostream& _os, const dump_str__<T>& _v)
    {
        ctk::dumper d(_os, false);
        d << _v.obj_;
        return _os;
    }
    template <class T>
    inline dump_str__<T>
    dump_str(const T& _obj)
    {
        return dump_str__<T>(_obj);
    }

    struct limited_str
    {
        istr data_;
        size_type n_;

        limited_str(istr _data, size_type _n=CTK_DUMP_MAX_SIZE)
            : data_(_data), n_(_n)
        {
        }
        std::ostream& dump(std::ostream& _os) const
        {
            _os << istr(data_, n_);
            if (n_<data_.size())
                _os << "<omit data up to "<<data_.size()<<">";
            return _os;
        }
    };
    inline std::ostream&
    operator<<(std::ostream& _os, const limited_str& _v)
    {
        return _v.dump(_os);
    }

    struct hex_str
    {
        istr data_;

        hex_str(rcistr _data)
            : data_(_data)
        {
        }

        std::ostream& dump(std::ostream& _os) const
        {
            ctk::String s;
            ctk::Hex16::encode(data_, s);
            return _os << s;
        }
    };
    inline std::ostream&
    operator<<(std::ostream& _os, const hex_str& _v)
    {
        return _v.dump(_os);
    }

    inline uint16
    maxBits(uint32 _v)
    {
    	uint16 bits = 0;
    	while (_v!=0)
    	{
    		_v >>= 1;
            ++bits;
    	}
    	return bits;
    }

    template <class K, class V>
    void reverseMap(const ctk::map<K, V>& _src, ctk::map<V, K>& _dst)
    {
        for (typename ctk::map<K, V>::const_iterator i=_src.begin(); i!=_src.end(); ++i)
        {
            _dst[(*i).second] = (*i).first;
        }
    }

    template<class T>
        inline T
        ensureNotZero(const T& _v)
    {
        return _v ? _v : (T)1;
    }

    template<class T>
    void removeDuplicated(const std::vector<T>& _local, const std::vector<T>& _remote, std::vector<T>& _result)
    {
        _result.clear();
        std::set<T> uniqLocal;
        for (typename std::vector<T>::const_iterator it=_local.begin(); it!=_local.end(); ++it)
        {
            uniqLocal.insert(*it);
        }
        for (typename std::vector<T>::const_iterator it=_remote.begin(); it!=_remote.end(); ++it)
        {
            if (uniqLocal.find(*it) == uniqLocal.end())
                _result.push_back(*it);
        }
    }

    template<class T>
    void getCommon(const std::vector<T>& _local, const std::vector<T>& _remote, std::vector<T>& _common)
    {
        _common.clear();
        std::set<T> sorted;
        for (typename std::vector<T>::const_iterator it=_local.begin(); it!=_local.end(); ++it)
        {
            sorted.insert(*it);
        }
        for (typename std::vector<T>::const_iterator it=_remote.begin(); it!=_remote.end(); ++it)
        {
            if (sorted.find(*it) != sorted.end())
                _common.push_back(*it);
        }
    }

}

#endif //_Z_CTK_UTIL_FUNCTIONS_H_


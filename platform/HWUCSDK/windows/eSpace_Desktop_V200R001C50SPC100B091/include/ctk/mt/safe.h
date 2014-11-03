/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_SAFE_H_
#define _Z_CTK_MT_SAFE_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/mutex.h"

namespace ctk {
namespace mt {

    template<class T>
    class Safe
    {
        typedef Safe<T> _Self;
        typedef ctk::Mutex _Mutex;
        typedef T _Value;

    private:
        _Value val_;
        _Mutex mtx_;

    public:
        Safe()
        {
        }
        Safe(const _Self& _v)
        {
            _v.copyTo(val_);
        }
        Safe(const _Value& _val)
            : val_(_val)
        {
        }
        ~Safe()
        {
        }

        _Value get() const
        {
            _Value v;
            {
                _Mutex::Lock __lck(mtx_);
                v = val_;
            }
            return v;
        }

        _Self& operator=(const _Self& _v)
        {
            if (this==&_v)
                return *this;
            {
                _Mutex::Lock __lck(mtx_);
                _v.copyTo(val_);
            }
            return *this;
        }

        _Self& operator=(const _Value& _val)
        {
            set(_val);
            return *this;
        }

        _Self& operator+=(const _Value& _val)
        {
            {
                _Mutex::Lock __lck(mtx_);
                val_ += _val;
            }
            return *this;
        }

        _Self& operator-=(const _Value& _val)
        {
            {
                _Mutex::Lock __lck(mtx_);
                val_ -= _val;
            }
            return *this;
        }

        _Value operator++()
        {
            _Value v;
            {
                _Mutex::Lock __lck(mtx_);
                v = ++val_;
            }
            return v;
        }

        _Value operator++(int)
        {
            _Value v;
            {
                _Mutex::Lock __lck(mtx_);
                v = val_++;
            }
            return v;
        }

        _Value operator--()
        {
            _Value v;
            {
                _Mutex::Lock __lck(mtx_);
                v = --val_;
            }
            return v;
        }

        _Value operator--(int)
        {
            _Value v;
            {
                _Mutex::Lock __lck(mtx_);
                v = val_--;
            }
            return v;
        }

        _Value exchange(const _Value& _val)
        {
            _Value old;
            {
                _Mutex::Lock __lck(mtx_);
                old = val_;
                val_ = _val;
            }
            return old;
        }

        _Value exchangeIncrement(const _Value& _val)
        {
            _Value old;
            {
                _Mutex::Lock __lck(mtx_);
                old = val_;
                val_ += _val;
            }
            return old;
        }

        _Value exchangeDecrement(const _Value& _val)
        {
            _Value v;
            {
                _Mutex::Lock __lck(mtx_);
                val_ -= _val;
                v = val_;
            }
            return v;
        }

        void set(const _Value& _val)
        {
            _Mutex::Lock __lck(mtx_);
            val_ = _val;
        }

        void copyTo(_Value& _val) const
        {
            _Mutex::Lock __lck(mtx_);
            _val = val_;
        }

        void takeOut(_Value& _val)
        {
            _Mutex::Lock __lck(mtx_);
            ctk::swap(_val, val_);
        }

        template <class _Function>
        void
        for_all(_Function _f)
        {
            _Mutex::Lock __lck(mtx_);
            _f(val_);
        }

        template <class _Function>
        void
        for_all(_Function _f) const
        {
            _Mutex::Lock __lck(mtx_);
            _f(val_);
        }

        ctk::dumper& dump(ctk::dumper& d) const
        {
            _Mutex::Lock __lck(mtx_);
            d << val_;
            return d;
        }

    };

} // namespace mt
} // namespace ctk

#endif //_Z_CTK_MT_SAFE_H_


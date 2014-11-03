/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_HANDLE_H_
#define _Z_CTK_MT_HANDLE_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/threadexception.h"

#include <algorithm>

namespace ctk
{

    template<class SHARED>
    class SmartPtrBase
    {
    public:
        SHARED* get() const
        {
            return ptr_;
        }

        SHARED* operator->() const
        {
            if (!ptr_)
            {
                throw NullHandleException(CTK_CURRENT);
            }

            return ptr_;
        }

        SHARED& operator*() const
        {
            if (!ptr_)
            {
                throw NullHandleException(CTK_CURRENT);
            }

            return *ptr_;
        }

        operator void*() const
        {
            return ptr_;
        }

        bool operator!() const
        {
            return !ptr_;
        }

        void swap(SmartPtrBase& _other)
        {
            ctk::swap(ptr_, _other.ptr_);
        }

        SHARED* ptr_;
    };

    template<typename SHARED, typename U>
    inline bool operator==(const SmartPtrBase<SHARED>& _lv, const SmartPtrBase<U>& _rv)
    {
        SHARED* l = _lv.get();
        U* r = _rv.get();
        if (l && r)
        {
            return *l == *r;
        }
        else
        {
            return !l && !r;
        }	
    }

    template<typename SHARED, typename U>
    inline bool operator!=(const SmartPtrBase<SHARED>& _lv, const SmartPtrBase<U>& _rv)
    {
        SHARED* l = _lv.get();
        U* r = _rv.get();
        if (l && r)
        {
            return *l != *r;
        }
        else
        {
            return l || r;
        }	
    }

    template<typename SHARED, typename U>
    inline bool operator<(const SmartPtrBase<SHARED>& _lv, const SmartPtrBase<U>& _rv)
    {
        SHARED* l = _lv.get();
        U* r = _rv.get();
        if (l && r)
        {
            return *l < *r;
        }
        else
        {
            return !l && r;
        }
    }

    //
    //  Handle
    //

    template<typename SHARED>
    class Handle : public SmartPtrBase<SHARED>
    {
    public:
        Handle(SHARED* _p = 0)
        {
            this->ptr_ = _p;

            if (this->ptr_)
            {
                this->ptr_->__AddRef();
            }
        }
        
        template<typename Y>
        Handle(const Handle<Y>& _r)
        {
            this->ptr_ = _r.ptr_;

            if (this->ptr_)
            {
                this->ptr_->__AddRef();
            }
        }

        Handle(const Handle& _r)
        {
            this->ptr_ = _r.ptr_;

            if (this->ptr_)
            {
                this->ptr_->__AddRef();
            }
        }
        
        ~Handle()
        {
            if(this->ptr_)
            {
                this->ptr_->__SubRef();
            }
        }
        
        Handle& operator=(SHARED* _p)
        {
            if(this->ptr_ != _p)
            {
                if (_p)
                {
                    _p->__AddRef();
                }

                SHARED* ptr = this->ptr_;

                this->ptr_ = _p;

                if (ptr)
                {
                    ptr->__SubRef();
                }
            }
    	    return *this;
        }
            
        template<typename Y>
        Handle& operator=(const Handle<Y>& _r)
        {
            return operator=(_r.ptr_);
        }

        Handle& operator=(const Handle& _r)
        {
            return operator=(_r.ptr_);
        }
            
        long refCount() const
        {
            return this->ptr_ ? this->ptr_->__GetRef() : 0;
        }

        template<class Y>
        static Handle castFrom(const SmartPtrBase<Y>& _r)
        {
            return Handle(dynamic_cast<SHARED*>(_r.ptr_));
        }

        template<class Y>
        static Handle castFrom(Y* _p)
        {
            return Handle(dynamic_cast<SHARED*>(_p));
        }

    };

} // end namespace ctk

#endif //_Z_CTK_MT_HANDLE_H_


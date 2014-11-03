/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_SHARED_PTR_H_
#define _Z_CTK_MT_SHARED_PTR_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/shared.h"
#include "ctk/mt/handle.h"

namespace ctk
{
    template<class T>
    struct SharedObj : public Shared, public noncopyable
    {
        SharedObj(T* _p)
            : ptr_(_p)
        {
        }

        ~SharedObj()
        {
            ctk::destroy(ptr_, CTK_CURRENT);
        }

        T* get() const
        {
            return ptr_;
        }

        template<class U>
        bool operator==(const SharedObj<U>& _rhs)
        {
            T* l = this->get();
            U* r = _rhs.get();
            if (l && r)
            {
                return *l == *r;
            }
            else
            {
                return !l && !r;
            }	
        }

        template<class U>
        bool operator!=(const SharedObj<U>& _rhs)
        {
            T* l = this->get();
            U* r = _rhs.get();
            if (l && r)
            {
                return *l != *r;
            }
            else
            {
                return l || r;
            }	
        }

        template<class U>
        bool operator<(const SharedObj<U>& _rhs)
        {
            T* l = this->get();
            U* r = _rhs.get();
            if (l && r)
            {
                return *l < *r;
            }
            else
            {
                return !l && r;
            }
        }

    private:
        T* ptr_;

    };

    template<class T>
    struct SharedPtr
    {
        typedef SharedObj<T> _ObjPtr;
        typedef SharedPtr _Self;

        SharedPtr()
        {
        }
        SharedPtr(T* _p)
        {
            reset(_p);
        }
        SharedPtr(_ObjPtr* _p)
        {
            ptr_ = _p;
        }
        SharedPtr(const SharedPtr& _v)
        {
            ptr_ = _v.ptr_;
        }
        template<class U>
        SharedPtr(const SharedPtr<U>& _v)
        {
            ptr_ = _v.ptr_;
        }
        ~SharedPtr()
        {
        }

        template<typename Y>
        SharedPtr& operator=(const SharedPtr<Y>& _r)
        {
            ptr_ = _r.ptr_;
            return *this;
        }
        SharedPtr& operator=(const SharedPtr& _r)
        {
            ptr_ = _r.ptr_;
            return *this;
        }
        SharedPtr& reset(T* _p)
        {
            if (_p)
            {
                if (get() != _p)
                    ptr_ = ctk::allocate<_ObjPtr>(CTK_CURRENT, _p);
            }
            else
            {
                ptr_ = 0;
            }
    	    return *this;
        }
            
        T* get() const
        {
            return ptr_ ? ptr_->get() : 0;
        }
        
        T* operator->() const
        {
            T* p = get();
            if (!p)
            {
                throw NullHandleException(CTK_CURRENT);
            }

            return p;
        }

        T& operator*() const
        {
            T* p = get();
            if (!p)
            {
                throw NullHandleException(CTK_CURRENT);
            }

            return *p;
        }

        operator void*() const
        {
            return get();
        }

        bool operator!() const
        {
            return !get();
        }

        long refCount() const
        {
            return ptr_ ? ptr_.refCount() : 0;
        }

        template<class U>
        bool operator==(const SharedPtr<U>& _rhs)
        {
            return ptr_ == _rhs.ptr_;
        }

        template<class U>
        bool operator!=(const SharedPtr<U>& _rhs)
        {
            return ptr_ != _rhs.ptr_;
        }

        template<class U>
        bool operator<(const SharedPtr<U>& _rhs)
        {
            return ptr_ < _rhs.ptr_;
        }

    private:
        Handle<_ObjPtr> ptr_;
    };

}

#endif // _Z_CTK_MT_SHARED_PTR_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_SHARED_H_
#define _Z_CTK_MT_SHARED_H_

#include "ctk/ctk_config.h"

#include "ctk/base/mlcheck.h"

#include "ace/Atomic_Op.h"

namespace ctk
{

    template<class T>
    void destroy_this(T* _this, CTK_CURRENT_ARGS)
    {
        ctk::destroy(_this, CTK_CURRENT_VARS);
    }

    class CTK_API Shared
    {
        friend void ctk::destroy_no_mlc<Shared>(Shared*&, CTK_CURRENT_ARGS);

    protected:
        virtual ~Shared()
        {
        }

    public:
        Shared()
            : dontDelete_(false)
        {
        }

        Shared(const Shared&)
            : dontDelete_(false)
        {
        }

        Shared& operator=(const Shared&)
        {
            return *this;
        }

        void __AddRef()
        {
            ++ref_;
        }

        void __SubRef()
        {
            if(--ref_ == 0 && !dontDelete_)
            {
                dontDelete_ = true;

                ctk::destroy_this(this, CTK_CURRENT);
            }
        }

        long __GetRef() const
        {
            return ref_.value();
        }

        void __setNoDelete(bool _v)
        {
            dontDelete_ = _v;
        }

    protected:

        ACE_Atomic_Op<ACE_Thread_Mutex, long> ref_;

        bool dontDelete_;
    };

}

#endif //_Z_CTK_MT_SHARED_H_


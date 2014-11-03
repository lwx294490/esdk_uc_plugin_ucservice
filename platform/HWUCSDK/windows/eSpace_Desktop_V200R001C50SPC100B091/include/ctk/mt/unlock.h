/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_UNLOCK_H_
#define _Z_CTK_MT_UNLOCK_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/threadexception.h"

namespace ctk
{
    template <typename T>
    class Unlock_T
    {
    public:
        Unlock_T(const T& _mutex)
            : mutex_(_mutex)
        {
            mutex_.unlock();
        }

        ~Unlock_T()
        {
            mutex_.lock();
        }

    private:
        Unlock_T(const Unlock_T&);
        Unlock_T& operator=(const Unlock_T&);

        const T& mutex_;
    };

} // end of namespace ctk

#endif //_Z_CTK_MT_UNLOCK_H_


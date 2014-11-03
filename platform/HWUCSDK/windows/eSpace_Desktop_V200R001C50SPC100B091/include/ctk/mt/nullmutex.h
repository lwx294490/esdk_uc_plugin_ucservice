/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_NULLMUTEX_H_
#define _Z_CTK_MT_NULLMUTEX_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/lock.h"

namespace ctk
{
    class NullMutex
    {
    public:
        typedef Guard_T<NullMutex> Lock;
        typedef TryGuard_T<NullMutex> TryLock;

    public:
        NullMutex()
        {
        }

        ~NullMutex()
        {
        }

        void lock() const
        {
        }

        bool tryLock() const
        {
            return true;
        }

        void unlock() const
        {
        }

        bool willUnlock() const
        {
            return true;
        }

    private:
        NullMutex(const NullMutex&);
        NullMutex& operator=(const NullMutex&);

    };

} // end of namespace ctk

#endif // _Z_CTK_MT_NULLMUTEX_H_


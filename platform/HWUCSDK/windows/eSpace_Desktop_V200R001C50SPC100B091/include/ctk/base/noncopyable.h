/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_NONCOPYABLE_H_
#define _Z_CTK_BASE_NONCOPYABLE_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{
    //
    // subclasses will not be copyable or assignable
    //
    class CTK_API noncopyable
    {
    protected:
        noncopyable() { }
        ~noncopyable() { } // should not be virtual

    private:
        // declare but no implement to disable them
        noncopyable(const noncopyable&);
        const noncopyable& operator=(const noncopyable&);
    };

} // namespace ctk

#endif //_Z_CTK_BASE_NONCOPYABLE_H_


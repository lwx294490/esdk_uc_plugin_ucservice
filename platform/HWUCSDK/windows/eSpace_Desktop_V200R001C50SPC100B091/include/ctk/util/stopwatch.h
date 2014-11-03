/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_STOPWATCH_H_
#define _Z_CTK_UTIL_STOPWATCH_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_time.h"

namespace ctk
{
    class CTK_API Stopwatch
    {
    public:
        typedef Stopwatch _Self;

    public:
        Stopwatch()
        {
            start();
        }

        void start()
        {
            stop_ = start_ = Time::now();
        }

        _Self& stop()
        {
            stop_ = Time::now();
            return *this;
        }

        Time begin() const
        {
            return start_;
        }

        Time end() const
        {
            return stop_;
        }

        Time elapsed() const
        {
            return stop_ - start_;
        }

    private:
        Time start_;
        Time stop_;
    };

} // namespace ctk

#endif //_Z_CTK_UTIL_STOPWATCH_H_


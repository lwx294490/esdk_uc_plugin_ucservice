/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_TIMECOUNTER_H_
#define _Z_CTK_TIMER_TIMECOUNTER_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_time.h"

namespace ctk {

    class CTK_API TimeCounter
    {
    public:
        TimeCounter();

        void go(const ctk::Time& past);

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        size_t    num;
        ctk::Time cost;
    };
    inline std::ostream& operator<<(std::ostream& os, const TimeCounter& v)
    {
        return v.dump(os);
    }
    inline ctk::dumper& operator<<(ctk::dumper& os, const TimeCounter& v)
    {
        return v.dump(os);
    }

} // end of namespace ctk

#endif // _Z_CTK_TIMER_TIMECOUNTER_H_


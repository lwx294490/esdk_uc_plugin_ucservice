/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_ID_H_
#define _Z_CTK_TIMER_ID_H_

#include "ctk/ctk_config.h"

namespace ctk {

    struct CTK_API TimerId
    {
        typedef TimerId _Self;
        typedef uint32 timer_id_t;

        uint32 uniq_;
        uint32 base_;

        CTK_STATIC_CONST uint32 INVALID = uint32(-1);

        TimerId();
        TimerId(timer_id_t _mixed);
        TimerId(uint32 _uniq, uint32 _base);

        void reset();

        bool empty() const;

        timer_id_t get() const;

        bool operator==(const _Self& v) const;
        bool operator!=(const _Self& v) const;
        bool operator<(const _Self& v) const;
        bool operator<=(const _Self& v) const;
        bool operator>(const _Self& v) const;
        bool operator>=(const _Self& v) const;

        std::ostream& dump(std::ostream& os) const;

        ctk::dumper& dump(ctk::dumper& os) const;

    };
    inline std::ostream& operator<<(std::ostream& os, const TimerId& v)
    {
        return v.dump(os);
    }

} // end of namespace ctk

#endif // _Z_CTK_TIMER_ID_H_


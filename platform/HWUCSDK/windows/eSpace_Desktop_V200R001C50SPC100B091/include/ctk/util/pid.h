/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _CTK_PID_H_
#define _CTK_PID_H_

#include <ctk/ctk_config.h>

namespace ctk {

    struct ProcessId
    {
        typedef pid_t type;

        type id_;

        ProcessId(type _id=0)
            : id_(_id)
        {
        }

        operator type() const
        {
            return id_;
        }
    };
    inline
    std::ostream&
    operator<<(std::ostream& _os, const ProcessId& _v)
    {
        return _os << std::setw(4) << _v.id_;
    }

}

#endif // _CTK_PID_H_


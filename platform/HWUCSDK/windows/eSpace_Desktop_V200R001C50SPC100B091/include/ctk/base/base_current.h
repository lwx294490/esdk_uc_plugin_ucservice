/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_CURRENT_H_
#define _Z_CTK_BASE_CURRENT_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_istr.h"
#include "ctk/base/base_type_stl.h"

namespace ctk
{
    class CTK_API Current
    {
        typedef Current _Self;

    public:
        Current();
        Current(CTK_CURRENT_ARGS);
        ~Current();

        bool operator<(const Current& _v) const;

        const _Self& prefix(pcstr _v) const;

        istr prefix() const;

        pcstr file() const;

        uint line() const;

        pcstr func() const;

    private:
        CTK_CURRENT_DEFS();
        mutable std::string prefix_;

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const Current& _v);

    class CTK_API CallStack
    {
    public:
        typedef CallStack _Self;
        typedef Current _Item;
        typedef ctk::stack<_Item> _Stack;
        typedef _Stack::container_type seq_type;
        typedef seq_type::const_reverse_iterator const_reverse_iterator;

        CallStack();
        ~CallStack();

        const _Self& separator(pcstr _sep) const;

        istr separator() const;

        _Stack& container();

        const _Stack& container() const;

    private:
        _Stack container_;
        mutable std::string separator_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const CallStack& _v);

} // namespace ctk

#endif //_Z_CTK_BASE_CURRENT_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_COMMON_H_
#define _Z_CTK_BASE_COMMON_H_

#include "ctk/ctk_config.h"

#include <utility>

#define CTK_SWAP_TYPE(t)     namespace ctk { inline void swap(t& _v1, t& _v2) { _v1.swap(_v2); } }
#define CTK_SWAP_FIELD(o, v) ctk::swap(v, o.v)

namespace ctk
{
    class CTK_API dumper;

    using std::swap;

    template<class T>
    struct MemberTypeBase
    {
        typedef T type;
    };
    template<class T>
    struct MemberType : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<T&> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<const T> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<const T&> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<volatile T> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<volatile T&> : public MemberTypeBase<T>
    {
    };

} // namespace ctk

#endif //_Z_CTK_BASE_COMMON_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_H_
#define _Z_CTK_VERSION_H_

#define CTK_VERSION_MAJOR       2
#define CTK_VERSION_MINOR       0
#define CTK_VERSION_PATCH       3

#define _CTK_STRINGIZE(X)       _CTK_STRINGIZE_AUX(X)
#define _CTK_STRINGIZE_AUX(X)   #X

#define _CTK_LIB_VERSION_STR    _CTK_STRINGIZE(CTK_VERSION_MAJOR)"."_CTK_STRINGIZE(CTK_VERSION_MINOR)"."_CTK_STRINGIZE(CTK_VERSION_PATCH)

#define CTK_MERGE3(a, b, c)     CTK_MERGE(a, CTK_MERGE(b, c))
#define CTK_MERGE(a, b)         CTK_MERGE_AUX(a, b)
#define CTK_MERGE_AUX(a, b)     a##b

#define CTK_VERSION             CTK_MERGE3(CTK_VERSION_MAJOR, CTK_VERSION_MINOR, CTK_VERSION_PATCH)

#define CTK_NAMESPACE(x)        CTK_MERGE(x##_, CTK_VERSION)

#define CTK_VERSIONED_NAMESPACE CTK_NAMESPACE(ctk)

namespace CTK_VERSIONED_NAMESPACE {

}

#endif //_Z_CTK_VERSION_H_


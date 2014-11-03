/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_TYPE_H_
#define _Z_CTK_UTIL_TYPE_H_

#include "ctk/ctk_config.h"

#include "ctk/util/util_type_bit.h"
#include "ctk/util/util_type_byte.h"
#include "ctk/util/util_type_char.h"
#include "ctk/util/util_type_wchar.h"
#include "ctk/util/util_type_short.h"
#include "ctk/util/util_type_ushort.h"
#include "ctk/util/util_type_long.h"
#include "ctk/util/util_type_ulong.h"
#include "ctk/util/util_type_longlong.h"
#include "ctk/util/util_type_ulonglong.h"
#include "ctk/util/util_type_float.h"
#include "ctk/util/util_type_double.h"

/*              bits   signed           Java
    --------------------------------------------
    Bit         1                       Boolean
    Wchar       16                      Character
    Char|Sbyte  8      signed           Byte
    Byte        8      unsigned         X
    Short       16     signed           Short
    Ushort      16     unsigned         X
    Long        32     signed           Integer
    Ulong       32     unsigned         X
    Longlong    64     signed           Long
    Ulonglong   64     unsigned         X
*/

namespace ctk
{
    // Float

    // Double

    typedef Bit Boolean;

    typedef Wchar WideChar;

    typedef Char Sbyte;

    typedef Bit Int1;
    typedef Sbyte Int8;
    typedef Byte Uint8;
    typedef Short Int16;
    typedef Ushort Uint16;
    typedef Long Int32;
    typedef Ulong Uint32;
    typedef Longlong Int64;
    typedef Ulonglong Uint64;
    typedef Float Real32;
    typedef Double Real64;

}

#endif //_Z_CTK_UTIL_TYPE_H_


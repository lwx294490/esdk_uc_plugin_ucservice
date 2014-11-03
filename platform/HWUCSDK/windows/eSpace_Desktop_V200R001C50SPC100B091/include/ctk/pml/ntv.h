/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

#ifndef _Z_PML_NTV_H_
#define _Z_PML_NTV_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_unit.h"

#include "ctk/pml/ntv_valuebase.h"
#include "ctk/pml/ntv_boolean_value.h"
#include "ctk/pml/ntv_bytes_value.h"
#include "ctk/pml/ntv_character_value.h"
#include "ctk/pml/ntv_float_value.h"
#include "ctk/pml/ntv_integervalue.h"
#include "ctk/pml/ntv_listvalue.h"
#include "ctk/pml/ntv_stringvalue.h"
#include "ctk/pml/ntv_time_value.h"
#include "ctk/pml/ntv_unsigned_value.h"
#include "ctk/pml/ntv_wchar_value.h"
#include "ctk/pml/ntv_wstring_value.h"

#include "ctk/pml/ntv_stl.h"

namespace ctk {
namespace pml {
namespace ntv {

    CTK_API Unit& operator<<(Unit& _os, const ShowPattern& _v);
    CTK_API Unit& operator<<(Unit& _os, const ShowMode& _v);

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_H_


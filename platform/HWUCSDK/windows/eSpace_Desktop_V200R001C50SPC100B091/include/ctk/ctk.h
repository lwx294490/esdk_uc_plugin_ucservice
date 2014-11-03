/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

#ifndef _Z_CTK_CTK_H_
#define _Z_CTK_CTK_H_

#ifdef WIN32
#pragma warning(disable:4100) // This function or variable may be unsafe.
#pragma warning(disable:4996) // This function or variable may be unsafe.
#pragma warning(disable:4512) // assignment operator could not be generated.
#pragma warning(disable:4251) // class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4127) // conditional expression is constant
#endif

#include "ctk/ctk_config.h"

#include "ctk/base.h"
#include "ctk/base/base_type_stl.h"

#include "ctk/cfg/config_file.h"
#include "ctk/cfg/init_fini.h"

#include "ctk/log.h"
#include "ctk/log/log_stl.h"

#include "ctk/mlc/mlc_helper.h"

#include "ctk/mt.h"
#include "ctk/mt/stl.h"

#include "ctk/nbr.h"
#include "ctk/nbr/nbr_stl.h"

#include "ctk/pml.h"
#include "ctk/pml/ntv_stl.h"

#include "ctk/strings.h"

#include "ctk/tcp.h"

#include "ctk/icmp.h"

#include "ctk/timer/timer.h"

#include "ctk/util.h"
#include "ctk/util/functions.h"
#include "ctk/util/memfun.h"
#include "ctk/util/util_params.h"
#include "ctk/util/singleton_T.h"

#include "ctk/version.h"

#include "ctk/xml/XML.h"
#include "ctk/xml/XMLSTL.h"

#if 0
#include "ctk/util/test.h"
#endif

#endif//_Z_CTK_CTK_H_


#ifndef _Z_CTK_AUTO_LINK_H_
#define _Z_CTK_AUTO_LINK_H_

#include <ace/Version.h>

#include "ctk/ctk_version.h"

#if CTK_WIN32

#ifndef _Z_CTK_CONFIG_H_
#pragma message ("WARNING: ctk/auto_link.h should be included in ctk/ctk_config.h!")
#endif

#ifdef _DEBUG
#define _CTK_LIB_OPTIM_MODE "d"
#else
#define _CTK_LIB_OPTIM_MODE ""
#endif

#ifdef _CTK_USE_STATIC_LIB
#define _CTK_LIB_TYPE "_static"
#else
#define _CTK_LIB_TYPE ""
#endif

#ifdef ACE_AS_STATIC_LIBS
#define _ACE_LIB_TYPE "s"
#else
#define _ACE_LIB_TYPE ""
#endif

#ifdef ACE_USES_WCHAR
#define _ACE_LIB_U "u"
#else
#define _ACE_LIB_U ""
#endif

#define _ACE_LIB_VERSION_STR _CTK_STRINGIZE(ACE_MAJOR_VERSION)"."_CTK_STRINGIZE(ACE_MINOR_VERSION)"."_CTK_STRINGIZE(ACE_BETA_VERSION)
#define _ACE_LIB_NAME "ACE"_ACE_LIB_U""_ACE_LIB_TYPE""_CTK_LIB_OPTIM_MODE"."_ACE_LIB_VERSION_STR".lib"
#pragma message ("ACE: Auto linking to "_ACE_LIB_NAME)
#pragma comment (lib, _ACE_LIB_NAME)

//#define _CTK_LIB_NAME "ctk"_CTK_LIB_OPTIM_MODE""_CTK_LIB_TYPE"."_CTK_LIB_VERSION_STR".lib"
#define _CTK_LIB_NAME "ctk"_CTK_LIB_TYPE""_CTK_LIB_OPTIM_MODE".lib"
#ifdef CTK_API_EXPORTS
#pragma message ("CTK: Creating "_CTK_LIB_NAME)
#else
#pragma message ("CTK: Auto linking to "_CTK_LIB_NAME)
#pragma comment (lib, _CTK_LIB_NAME)
#endif

#undef _CTK_LIB_OPTIM_MODE
#undef _CTK_LIB_TYPE
#undef _ACE_LIB_TYPE
#undef _ACE_LIB_VERSION_STR
#undef _ACE_LIB_NAME
#undef _CTK_LIB_NAME

#endif // CTK_WIN32

#endif


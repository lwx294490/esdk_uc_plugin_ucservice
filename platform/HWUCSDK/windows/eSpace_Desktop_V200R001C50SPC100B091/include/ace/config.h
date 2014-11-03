#ifndef _ACE_USR_CONFIG_H_
#define _ACE_USR_CONFIG_H_

#ifndef ACE_HAS_STANDARD_CPP_LIBRARY
#define ACE_HAS_STANDARD_CPP_LIBRARY 1
#endif

#ifdef _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#ifndef ACE_HAS_MFC
#define ACE_HAS_MFC 1
#endif

#ifndef ACE_USES_WCHAR
#define ACE_USES_WCHAR 1
#endif

//Support ICMP
#if !defined (ACE_HAS_ICMP_SUPPORT)
#define ACE_HAS_ICMP_SUPPORT 1
#endif


#ifdef _MSC_VER
//     ... : This function or variable may be unsafe. Consider using ... instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#pragma warning( disable : 4996) // VC9
#endif

#include "ace/config-win32.h"

#elif defined(__APPLE_CC__) || defined(__APPLE_CPP__)

#include "ace/config-macosx-snowleopard.h"

#else

#include "ace/config-linux.h"

#endif

#endif//_ACE_USR_CONFIG_H_

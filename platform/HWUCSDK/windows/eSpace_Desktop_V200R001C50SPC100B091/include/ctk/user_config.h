#ifndef _Z_CTK_USER_CONFIG_H_
#define _Z_CTK_USER_CONFIG_H_

//#ifndef _CTK_USE_STATIC_LIB
//#define _CTK_USE_STATIC_LIB
//#endif

//#ifdef _CTK_USE_STATIC_LIB
//#define ACE_AS_STATIC_LIBS
//#endif

#if CTK_WIN32

#ifndef _CTK_USE_MFC
#define _CTK_USE_MFC 1
#endif

#ifndef ACE_USES_WCHAR
#define ACE_USES_WCHAR
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#ifndef WINVER
#define WINVER 0x0500
#endif

#elif CTK_MAC

#elif CTK_LINUX

#else

#endif // WIN32, MAC, LINUX

#endif // _Z_CTK_USER_CONFIG_H_


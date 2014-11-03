/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _CTK_TARGET_PLATFORM_H_
#define _CTK_TARGET_PLATFORM_H_

//
// OS
// ==
//   Windows: CTK_WIN32, CTK_WINDOWS
//   Android: CTK_ANDROID
//   Linux:   CTK_LINUX
//   Mac OSX: CTK_MAC
//   iOS:     CTK_IOS, CTK_IPHONE(TARGET_OS_IPHONE,TARGET_IPHONE_SIMULATOR)
//
// Bits
// ====
//   CTK_32BIT
//   CTK_64BIT
//
// Debug
// =====
//   CTK_DEBUG
//
// Endian
// ======
//   CTK_LITTLE_ENDIAN
//   CTK_BIG_ENDIAN
//
// CPU
// ===
//   CTK_INTEL
//   CTK_PPC
//
// Compiler
// ========
//   CTK_GCC
//   CTK_MSVC
//

#if (defined (_WIN32) || defined (_WIN64))
  #define       CTK_WIN32 1
  #define       CTK_WINDOWS 1
#elif defined (CTK_ANDROID)
  #undef        CTK_ANDROID
  #define       CTK_ANDROID 1
#elif defined (LINUX) || defined (__linux__)
  #define     CTK_LINUX 1
#elif defined (__APPLE_CPP__) || defined(__APPLE_CC__)
  #include <CoreFoundation/CoreFoundation.h>

  #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    #define     CTK_IPHONE 1
    #define     CTK_IOS 1
  #else
    #define     CTK_MAC 1
  #endif
#else
  #error "Unknown OS!"
#endif

#if CTK_WINDOWS
  #ifdef _MSC_VER
    #ifdef _WIN64
      #define CTK_64BIT 1
    #else
      #define CTK_32BIT 1
    #endif
  #endif

  #ifdef _DEBUG
    #define CTK_DEBUG 1
  #endif

  #ifdef __MINGW32__
    #define CTK_MINGW 1
  #endif

  #define CTK_LITTLE_ENDIAN 1

  #define CTK_INTEL 1
#endif

#if CTK_MAC || CTK_IOS

  #if defined (DEBUG) || defined (_DEBUG) || ! (defined (NDEBUG) || defined (_NDEBUG))
    #define CTK_DEBUG 1
  #endif

  #if ! (defined (DEBUG) || defined (_DEBUG) || defined (NDEBUG) || defined (_NDEBUG))
    #warning "You should set one of DEBUG/_DEBUG/NDEBUG/_NDEBUG"
  #endif

  #ifdef __LITTLE_ENDIAN__
    #define CTK_LITTLE_ENDIAN 1
  #else
    #define CTK_BIG_ENDIAN 1
  #endif
#endif

#if CTK_MAC

  #if defined (__ppc__) || defined (__ppc64__)
    #define CTK_PPC 1
  #else
    #define CTK_INTEL 1
  #endif

  #ifdef __LP64__
    #define CTK_64BIT 1
  #else
    #define CTK_32BIT 1
  #endif

  #if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4
    #error "Too old version <= OSX 10.3!"
  #endif

  #ifndef MAC_OS_X_VERSION_10_5
    #error "For OSX 10.4, use 10.5 or 10.6 SDK, set target to 10.4"
  #endif

#endif

#if CTK_LINUX || CTK_ANDROID

  #ifdef _DEBUG
    #define CTK_DEBUG 1
  #endif

  #if defined (__LITTLE_ENDIAN__) || ! defined (CTK_BIG_ENDIAN)
    #define CTK_LITTLE_ENDIAN 1
    #undef CTK_BIG_ENDIAN
  #else
    #undef CTK_LITTLE_ENDIAN
    #define CTK_BIG_ENDIAN 1
  #endif

  #if defined (__LP64__) || defined (_LP64)
    #define CTK_64BIT 1
  #else
    #define CTK_32BIT 1
  #endif

  #if __MMX__ || __SSE__ || __amd64__
    #define CTK_INTEL 1
  #endif
#endif

#ifdef __GNUC__
  #define CTK_GCC 1
#elif defined (_MSC_VER)
  #define CTK_MSVC 1

  #if _MSC_VER < 1500
    #define CTK_VC8_OR_EARLIER 1

    #if _MSC_VER < 1400
      #define CTK_VC7_OR_EARLIER 1

      #if _MSC_VER < 1300
        #define CTK_VC6 1
      #endif
    #endif
  #endif

  #if ! CTK_VC7_OR_EARLIER
    #define CTK_USE_INTRINSICS 1
  #endif
#else
  #error Compiler unknown
#endif

#endif   // _CTK_TARGET_PLATFORM_H_


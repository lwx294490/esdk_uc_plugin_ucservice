/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_CONFIG_H_
#define _Z_CTK_CONFIG_H_

#include <ctk/ctk_target_platform.h>

#include "ctk/user_config.h"

#include <ace/OS.h>
#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Log_Record.h>
#include <ace/Version.h>

#ifdef CTK_WINDOWS
#include <tchar.h>
#endif

#if defined (CTK_MAC)
# if !defined (ACE_HAS_LLSEEK) && !defined (ACE_HAS_LSEEK64)
#  define llseek lseek
# endif
#  define _O_CREAT O_CREAT
#  define _O_EXCL  O_EXCL
#  define _O_TRUNC O_TRUNC
// 0x08 is used for O_APPEND.  0x1000 looks free.
//#  define _O_TEMPORARY 0x1000 /* see fcntl.h */
#  define _O_RDWR   O_RDWR
#  define _O_WRONLY O_WRONLY
#  define _O_RDONLY O_RDONLY
#  define _O_APPEND O_APPEND
#  define _O_BINARY O_BINARY
#  define _O_TEXT   O_TEXT
#endif /* CTK_MAC */

#include "ctk/ctk_version.h"

#include "ctk/auto_link.h"

//
// compile options:
//
// _CTK_USE_STATIC_LIB
// CTK_API_EXPORTS
//
//_CTK_UNICODE
//
//_WIN32 _DLL _MT _MSC_VER
//
//_DEBUG NDEBUG
//
//_CTK_UNIT_TEST_ON=1
//
//_CTK_TRACE_OFF=1
//

//
// defined symbols:
//
//_CTK_DEBUG_ON
//_CTK_TRACE_ON
//_CTK_TRACE_LOG_ON
//_CTK_MEMLEAKCHECK_ON
//_CTK_ASSERT_ON
//_CTK_ASSERT_ABORT_ON
//_CTK_BREAK_ON_EXCEPTION 0
//_CTK_THROW_REALLY 0
//
//_CTK_TEST_ON
//_CTK_COMM_LOG_ON
//
// CTK_COPYRIGHT
// CTK_VERSION
// CTK_VERSION_STR
// CTK_VERSION_MAJOR
// CTK_VERSION_MINOR
// CTK_VERSION_PATCH
//
// CTK_DECLSPEC_EXPORT
// CTK_DECLSPEC_IMPORT
// CTK_API
//
// CTK_FILE
// CTK_LINE
// CTK_FUNC
//
// CTK_NEW(t)
// CTK_DELETE(p)
// CTK_DELETE_A(p)
//
// _T(s)
// CTK_INT64(n)
//
// CTK_NO_ARG(v)
// CTK_USED_VAR(v)
// CTK_STATIC_VAR
// CTK_STATIC_FUN
// CTK_STATIC_CONST
// CTK_NV(v)
//

//
// compile switches
//
#if defined(_CTK_UNIT_TEST_ON) && _CTK_UNIT_TEST_ON
    #if !defined(_CTK_TRACE_OFF) || !_CTK_TRACE_OFF
        #define _CTK_TRACE_ON
    #endif
    #if !defined(_CTK_DEBUG_OFF) || !_CTK_DEBUG_OFF
        #define _CTK_DEBUG_ON
    #endif
    #if !defined(_CTK_TRACE_LOG_OFF) || !_CTK_TRACE_LOG_OFF
        #define _CTK_TRACE_LOG_ON
    #endif
    #define _CTK_MEMLEAKCHECK_ON
    #define _CTK_ASSERT_ON
    //#define _CTK_ASSERT_ABORT_ON
    //#define _CTK_BREAK_ON_EXCEPTION 1
    //#define _CTK_THROW_REALLY 1
#elif defined(_DEBUG)
    #if !defined(_CTK_TRACE_OFF) || !_CTK_TRACE_OFF
        #define _CTK_TRACE_ON
    #endif
    #if !defined(_CTK_DEBUG_OFF) || !_CTK_DEBUG_OFF
        #define _CTK_DEBUG_ON
    #endif
    #if !defined(_CTK_TRACE_LOG_OFF) || !_CTK_TRACE_LOG_OFF
        #define _CTK_TRACE_LOG_ON
    #endif
    #define _CTK_MEMLEAKCHECK_ON
    #define _CTK_ASSERT_ON
    #define _CTK_ASSERT_ABORT_ON
    #define _CTK_BREAK_ON_EXCEPTION 1
    #define _CTK_THROW_REALLY 1
#else
    //#define _CTK_TRACE_ON
    //#define _CTK_DEBUG_ON
    //#define _CTK_TRACE_LOG_ON
    //#define _CTK_MEMLEAKCHECK_ON
    //#define _CTK_ASSERT_ON
    //#define _CTK_ASSERT_ABORT_ON
    //#define _CTK_BREAK_ON_EXCEPTION 0
    #define _CTK_THROW_REALLY 1
#endif

#ifdef _UNICODE
#   ifndef _CTK_UNICODE
#   define _CTK_UNICODE
#   endif
#endif

#if defined(_MSC_VER) || (defined(__HP_aCC) && defined(__HP_WINDLL))
#   define CTK_DECLSPEC_EXPORT __declspec(dllexport)
#   define CTK_DECLSPEC_IMPORT __declspec(dllimport)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550)
#   define CTK_DECLSPEC_EXPORT __global
#   define CTK_DECLSPEC_IMPORT
#else
#   define CTK_DECLSPEC_EXPORT /**/
#   define CTK_DECLSPEC_IMPORT /**/
#endif

#if !defined(_CTK_USE_STATIC_LIB)
# ifdef CTK_API_EXPORTS
#  define CTK_API CTK_DECLSPEC_EXPORT
# else
#  define CTK_API CTK_DECLSPEC_IMPORT
# endif
#else
# define CTK_API
#endif

#if defined(_WIN32)

#   ifndef _WIN32_WINNT
#       define _WIN32_WINNT 0x0500
#   endif

#   if !defined(_DLL) || !defined(_MT)
#       error "Only multi-threaded DLL libraries can be used with CTK!"
#   endif

// ACE may include windows.h or afxwin.h
#if defined(_CTK_USE_MFC) && _CTK_USE_MFC!=0
//#   ifndef __AFX_H__
//#      include <afx.h>
//#   endif
#   ifndef __AFXWIN_H__
#      include <afxwin.h>
#   endif
#else
#   ifndef _WINDOWS_
#      include <windows.h>
#   endif
#endif

#   ifdef _MSC_VER
#      pragma warning( disable : 4800 )
#      pragma warning( disable : 4786 )
#      pragma warning( disable : 4355 )
#      pragma warning( disable : 4251 )
#      pragma warning( disable : 4250 )
#      pragma warning( disable : 4275 )
#      pragma warning( disable : 4503 )
#      pragma warning( disable : 4127)
#      pragma warning( disable : 4267)
#      pragma warning( disable : 4100)
#      pragma warning( disable : 4121)
#   endif

#endif

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cwchar>
#include <cstring>

#include <memory> // std::auto_ptr

#include <string>
//解决vs2012中npos的链接问题 //
#if _MSC_VER >= 1600
const std::basic_string<char>::size_type std::basic_string<char>::npos = (std::basic_string<char>::size_type)-1;
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#include <algorithm>
#include <functional>

#ifndef _WIN32
#   include <pthread.h>
#   include <errno.h>
#endif

//
// If we use Visual C++ 6.0, we must use STLport
//
#if defined(_MSC_VER) && (_MSC_VER < 1300) && !defined(_STLP_BEGIN_NAMESPACE)
#   error "CTK for Visual C++ 6.0 requires STLport"
#endif

#define CTK_FILE __FILE__

#define CTK_LINE __LINE__

#if defined(__GNUC__) && defined(_DEBUG) && !defined(__APPLE_CC__)
#include <assert.h>
#define CTK_FUNC __ASSERT_FUNCTION
#else
#define CTK_FUNC __FUNCTION__
#endif

#ifndef _T
#ifndef _CTK_UNICODE
#define _T(s) s
#else
#define _T(s) L##s
#endif
#endif

//
// CTK_INT64: macro for int64 literal values
//
#if defined(_MSC_VER)
#   define CTK_INT64(n) n##i64
#elif defined(CTK_64BIT)
#   define CTK_INT64(n) n##L
#else
#   define CTK_INT64(n) n##LL
#endif

#define CTK_NO_ARG(x) /* x */
#define CTK_USED_VAR(x) (void*)&x /* do ; while(!&x) */

#define CTK_STATIC_VAR static
#define CTK_STATIC_MEM static
#define CTK_STATIC_FUN static
#define CTK_STATIC_CONST static const

#define CTK_NV(v)     #v, v
#define CTK_NV_VAR(v) #v, v##_

#ifdef _STLP_CALL
#define CTK_CALL _STLP_CALL
#else
#define CTK_CALL
#endif

#define CTK_CURRENT                 CTK_FILE,            CTK_LINE,            CTK_FUNC
#define CTK_CURRENT_ARGS            ctk::pcstr _file,    ctk::uint _line,     ctk::pcstr _func
#define CTK_CURRENT_VARS            _file,               _line,               _func
#define CTK_CURRENT_MEMS            file_,               line_,               func_
#define CTK_CURRENT_INIT            file_(_file),        line_(_line),        func_(_func)
#define CTK_CURRENT_ARGS_DEFAULT    ctk::pcstr _file=0,  ctk::uint _line=0,   ctk::pcstr _func=0
#define CTK_CURRENT_UNUSED_VARS()   CTK_USED_VAR(_file); CTK_USED_VAR(_line); CTK_USED_VAR(_func)
#define CTK_CURRENT_DEFS()          ctk::pcstr file_;    ctk::uint line_;     ctk::pcstr func_

#define CTK_OK_FAIL(x) ((x) ? ctk::S_ok : ctk::S_fail)
#define CTK_YES_NO(x) ((x) ? ctk::S_yes : ctk::S_no)
#define CTK_ON_OFF(x) ((x) ? ctk::S_on : ctk::S_off)
#define CTK_TRUE_FALSE(x) ((x) ? ctk::S_true : ctk::S_false)

#if defined(_DEBUG) && defined(_MSC_VER) && defined(_DLL) && _CTK_USE_MFC
#define ctk_new    new(__FILE__, __LINE__)
#else
#define ctk_new    new
#endif
#define ctk_delete delete

#define CTK_NEW_AT(p) new(p)

#if defined(_DEBUG) && defined(_MSC_VER) && defined(_DLL)
#define CTK_NEW(expr) ctk_new expr
#else
#define CTK_NEW(expr) new expr
#endif

#define CTK_DELETE(var) do if (var) { delete var; var = 0; } while(0)
#define CTK_DELETE_A(var) do if (var) { delete [] var; var = 0; } while(0)

#define CTK_STATIC_CHECK(expr, msg) do { char ERROR_##msg[expr!=0]; (void)ERROR_##msg; } while(0)

#define CTK_ZERO_MEM(p, sz)  memset((void*)p, 0, sz)

namespace ctk
{
    // builtin: char, wchar_t, short, int, long, float, double

    typedef bool            boolean;

    typedef char            cchar;
    typedef wchar_t         wchar;
    typedef char            schar;
    typedef unsigned char   uchar;
#ifndef _CTK_UNICODE
    typedef cchar           tchar;
#else
    typedef wchar           tchar;
#endif

    typedef short           sshort;
    typedef int             sint;
    typedef long            slong;

#ifndef __USE_MISC
    typedef unsigned short  ushort;
    typedef unsigned int    uint;
    typedef unsigned long   ulong;
#else
    using ::ushort;
    using ::uint;
    using ::ulong;
#endif

//
// longlong(int64) typedef
//
#ifdef _STLP_LONG_LONG
    typedef _STLP_LONG_LONG     longlong;
    typedef unsigned _STLP_LONG_LONG   ulonglong;
#elif defined(_MSC_VER)
    // On Windows, long is always 32-bit
    typedef __int64             longlong;
    typedef unsigned __int64    ulonglong;
#elif defined(CTK_64BIT)
    typedef long                longlong;
    typedef unsigned long       ulonglong;
#else
    typedef long long           longlong;
    typedef unsigned long long  ulonglong;
#endif
    typedef longlong            slonglong;

    typedef boolean     bit;
    typedef uchar       byte;
    typedef schar       sbyte;
    typedef byte        octet;

    typedef bit         int1;
    typedef schar       int8;
    typedef uchar       uint8;
    typedef sshort      int16;
    typedef ushort      uint16;
#if (defined(CTK_64BIT) && !defined(_MSC_VER))
    // long is 64 bits, so use int as int32
    typedef sint        int32;
    typedef uint        uint32;
#else 
#   define _CTK_INT32_IS_LONG
    typedef slong       int32;
    typedef ulong       uint32;
#endif
    typedef slonglong   int64;
    typedef ulonglong   uint64;

    typedef float       real32;
    typedef double      real64;

#ifdef CTK_64BIT
    typedef uint64      size_type;
    typedef int64       ssize_type;
#else
    typedef uint32      size_type;
    typedef int32       ssize_type;
#endif

    typedef char*           pstr;
    typedef uchar*          pustr;
    typedef wchar*          pwstr;
    typedef tchar*          ptstr;

    typedef const char*     pcstr;
    typedef const uchar*    pcustr;
    typedef const wchar*    pcwstr;
    typedef const tchar*    pctstr;

    typedef const char      chr_def;
    typedef const int       int_def;
    typedef const pcstr     str_def;

    chr_def C_null       = '\0';
    chr_def C_true       = '1';
    chr_def C_false      = '0';
    chr_def C_quota1     = '\'';
    chr_def C_quota2     = '"';
    chr_def C_0          = '0';
    chr_def C_9          = '9';
    chr_def C_A          = 'A';
    chr_def C_F          = 'F';
    chr_def C_a          = 'a';
    chr_def C_f          = 'f';
    chr_def C_space      = ' ';
    chr_def C_comma      = ',';
    chr_def C_minus      = '-';
    chr_def C_underline  = '_';
    chr_def C_period     = '.';
    chr_def C_colon      = ':';
    chr_def C_slash      = '/';
    chr_def C_backslash  = '\\';
    chr_def C_newline    = '\n';
    chr_def C_return     = '\r';
    chr_def C_tab        = '\t';
    chr_def C_xor        = '^';
    chr_def C_assign     = '=';
#ifdef _WIN32
    chr_def C_DirSep     = C_backslash;
#else
    chr_def C_DirSep     = C_slash;
#endif

    const void * const null = 0;
    str_def S_null      = 0;
    str_def S_empty     = "";
    str_def S_true      = "true";
    str_def S_false     = "false";
    str_def S_on        = "on";
    str_def S_off       = "off";
    str_def S_yes       = "yes";
    str_def S_no        = "no";
    str_def S_ok        = "ok";
    str_def S_fail      = "fail";
    str_def S_quota1    = "'";
    str_def S_quota2    = "\"";
    str_def S_slash     = "/";
    str_def S_backslash = "\\";
#ifdef _WIN32
    str_def S_DirSep    = S_backslash;
#else
    str_def S_DirSep    = S_slash;
#endif

    const size_type npos    = ~(size_type)0;

    class CTK_API dumper;

    namespace pml
    {

        class CTK_API stream;

    }

} // namespace ctk

#endif //_Z_CTK_CONFIG_H_


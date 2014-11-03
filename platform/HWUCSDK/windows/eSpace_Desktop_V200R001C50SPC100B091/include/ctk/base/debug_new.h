/* CTK(Common Tool Kit, author: luyunhai 117629(3664)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

#ifndef _Z_DEBUG_NEW_H_
#define _Z_DEBUG_NEW_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/mlcheck.h"

#if defined(_DEBUG) && defined(_MSC_VER)

//inline void * __cdecl operator new(size_t s)
//    { return ::operator new(s, _NORMAL_BLOCK, __FILE__, __LINE__); }
//inline void* __cdecl operator new[](size_t s)
//    { return ::operator new[](s, _NORMAL_BLOCK, __FILE__, __LINE__); }

//extern void* __cdecl operator new( size_t, const char*, int );
//extern void* __cdecl operator new[]( size_t, const char*, int );
//
//extern void __cdecl operator delete( void*, const char*, int);
//extern void __cdecl operator delete[]( void*, const char*, int);

#ifdef new
#undef new
#endif
#define new ctk_new

#define REG_DEBUG_NEW() _RegDebugNew()

CTK_API void _RegDebugNew( void ); 

#else

#define REG_DEBUG_NEW()

#endif // _DEBUG && _MSC_VER

#endif // _Z_DEBUG_NEW_H_


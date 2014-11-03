#pragma once

#define AUTH_LIB_NAME "auth.lib"

#ifdef _DEBUG
# define AUTH_LIB_MSG AUTH_LIB_NAME" (debug)"
#else
# define AUTH_LIB_MSG AUTH_LIB_NAME" (release)"
#endif

#ifdef WIN32 
#ifdef AUTH_EXPORTS
# define AUTH_API __declspec(dllexport)
# pragma message("AUTH : Creating "AUTH_LIB_MSG)
#else
# define AUTH_API __declspec(dllimport)
# pragma message("AUTH : Auto linking to "AUTH_LIB_MSG)
# pragma comment(lib, AUTH_LIB_NAME)
#endif
#else
#define AUTH_API 
#endif

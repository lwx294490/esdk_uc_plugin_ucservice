#pragma once

#define HISTORY_LIB_NAME "history.lib"

#ifdef _DEBUG
# define HISTORY_LIB_MSG HISTORY_LIB_NAME" (debug)"
#else
# define HISTORY_LIB_MSG HISTORY_LIB_NAME" (release)"
#endif

#ifdef WIN32 
#ifdef HISTORY_EXPORTS
# define HISTORY_API __declspec(dllexport)
# pragma message("history : Creating "HISTORY_LIB_MSG)
#else
# define HISTORY_API __declspec(dllimport)
# pragma message("history : Auto linking to "HISTORY_LIB_MSG)
# pragma comment(lib, HISTORY_LIB_NAME)
#endif
#else
#define HISTORY_API 
#endif

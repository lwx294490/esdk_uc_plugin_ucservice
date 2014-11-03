#pragma once

#define HWUC_LIB_NAME "hwuc.lib"

#ifdef _DEBUG
# define HWUC_LIB_MSG HWUC_LIB_NAME" (debug)"
#else
# define HWUC_LIB_MSG HWUC_LIB_NAME" (release)"
#endif

#ifdef WIN32 
#ifdef APPCLASSLAYER_EXPORTS
# define APPCLASSLAYER_API __declspec(dllexport)
# pragma message("hwuc : Creating "HWUC_LIB_MSG)
#else
# define APPCLASSLAYER_API __declspec(dllimport)
# pragma message("hwuc : Auto linking to "HWUC_LIB_MSG)
# pragma comment(lib, HWUC_LIB_NAME)
#endif
#else
#define APPCLASSLAYER_API 
#endif

#define HWUC_CLASSLAYER  "HWUC"

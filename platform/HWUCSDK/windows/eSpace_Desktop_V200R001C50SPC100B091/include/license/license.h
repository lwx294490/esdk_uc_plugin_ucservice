#pragma once

#define LICENSECHECK_LIB_NAME "license.lib"

#ifdef _DEBUG
# define LICENSECHECK_LIB_MSG LICENSECHECK_LIB_NAME" (debug)"
#else
# define LICENSECHECK_LIB_MSG LICENSECHECK_LIB_NAME" (release)"
#endif

#ifdef LICENSECHECK_EXPORTS
# define LICENSECHECK_API __declspec(dllexport)
# pragma message("licensecheck : Creating "LICENSECHECK_LIB_MSG)
#else
# define LICENSECHECK_API __declspec(dllimport)
# pragma message("licensecheck : Auto linking to "LICENSECHECK_LIB_MSG)
# pragma comment(lib, LICENSECHECK_LIB_NAME)
#endif // LICENSECHECK_EXPORTS

BOOL LICENSECHECK_API LicenseCheck();

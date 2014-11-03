#ifndef _UC_SSO_H
#define _UC_SSO_H

//单点登录类,因为单点登录需要用到FASTSDK中的httpapi库，而UC API未开放，所以未做成单点登陆。
class SSOLogin
{
public:
	//static void GetRandom(const std::string& strPortalUrl, std::string& strRandom);
	//static void GetPortalRandom(const std::string& strPortalUrl, std::string& strRandom);
	//static void OpenPortal(const std::string& strRandom, const std::string& strPortalUrl, bool bIsHelp = false);
	static void OpenURL(const CString& strURI);
private:
	//static CString GetLine(char* lpData, int& ndx);
	//static int GetHeadLength(char* lpData);
	//static void EncodeURI(std::string& strIn);
};

#endif


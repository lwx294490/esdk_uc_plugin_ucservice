#ifndef _UC_SSO_H
#define _UC_SSO_H

//�����¼��,��Ϊ�����¼��Ҫ�õ�FASTSDK�е�httpapi�⣬��UC APIδ���ţ�����δ���ɵ����½��
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


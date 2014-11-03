#ifndef _ESDKTOOL_H
#define _ESDKTOOL_H

//工具类
class eSDKTool
{
private:
	eSDKTool(void);
	~eSDKTool(void);
public:
	static void GetStartTime(historydata::Date& startdate,historydata::Time& starttime,unsigned int duration);
	static void getCurrentPath(std::string& cstrPath);//获取当前程序可执行路径	
	static bool IsValidUri(const std::string& uri);//判断是否是有效uri
	static bool IsVirtualUri(const std::string& uri);//判断是否是模拟的uri，没有绑定任何号码	
	static std::string GetNoFromUri(const std::string & uri);//从uri中提取号码
	static std::string MergeString(const std::vector<std::string>& strList);// 以','为间隔合并字符串列表
	static void SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList);//按照逗号分解字符串
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);//输入“10.10.10.10:10”，解析出“10.10.10.10”和10
	static std::string CreateGuidStr();
	static std::string utf82unicode(const std::string& utf_str);
	static std::wstring utf8_2_unicode_w(const std::string & utf_str);
	static CString utf8_2_unicode(const std::string & utf_str)
	{ 
		return utf8_2_unicode_w(utf_str).c_str(); 
	}
	static std::string unicode_w_2_utf8(const std::wstring & uni_str);
	static std::string unicode_2_utf8(const CString & uni_str)
	{ 
		/*lint -save -e64*/
		std::wstring _wstr = uni_str.GetString();
		return unicode_w_2_utf8(_wstr); 
		/*lint -restore*/
	}
	static void GetNumStringFromCmd(const std::string& _spker, std::string& _spkeNum0, std::string& _spkeNum1);
};

#endif



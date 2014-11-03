#ifndef _ESDKTOOL_H
#define _ESDKTOOL_H

//������
class eSDKTool
{
private:
	eSDKTool(void);
	~eSDKTool(void);
public:
	static void GetStartTime(historydata::Date& startdate,historydata::Time& starttime,unsigned int duration);
	static void getCurrentPath(std::string& cstrPath);//��ȡ��ǰ�����ִ��·��	
	static bool IsValidUri(const std::string& uri);//�ж��Ƿ�����Чuri
	static bool IsVirtualUri(const std::string& uri);//�ж��Ƿ���ģ���uri��û�а��κκ���	
	static std::string GetNoFromUri(const std::string & uri);//��uri����ȡ����
	static std::string MergeString(const std::vector<std::string>& strList);// ��','Ϊ����ϲ��ַ����б�
	static void SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList);//���ն��ŷֽ��ַ���
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);//���롰10.10.10.10:10������������10.10.10.10����10
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



#include "StdAfx.h"
#include "eSDKTool.h"

eSDKTool::eSDKTool(void)
{
}

eSDKTool::~eSDKTool(void)
{
}

void eSDKTool::getCurrentPath(std::string& strPath)
{
	HMODULE hModule = GetModuleHandle(_T("UCService.dll"));
	char path[MAX_PATH+1] = {0};
	::GetModuleFileNameA(hModule, path, MAX_PATH);
	std::string strModulePath = path;
	unsigned int loc = strModulePath.find_last_of("\\");
	if( loc != string::npos )
	{
		strPath = strModulePath.substr(0,loc);
	}
}

void eSDKTool::GetStartTime(historydata::Date& startdate,historydata::Time& starttime,unsigned int duration)
{
	_tzset();
	CTime times =  CTime::GetCurrentTime();
	times -= (long long)duration;
	startdate.year = times.GetYear();
	startdate.month = times.GetMonth();
	startdate.day = times.GetDay();
	starttime.hour = times.GetHour();
	starttime.minute = times.GetMinute();
	starttime.second = times.GetSecond();
}
bool eSDKTool::IsValidUri(const std::string& uri)
{
	size_t nSip = uri.find("sip:");
	if (nSip != 0) //必须以sip:开头
	{
		return false;
	}
	return true;
}
bool eSDKTool::IsVirtualUri(const std::string& uri)
{
	//模拟的没有绑定任何号码的用户uri
	if (0 == uri.find("sip:index"))
	{
		return true;
	}
	return false;
}
std::string eSDKTool::GetNoFromUri(const std::string & uri)
{
	size_t nSip = uri.find("sip:");

	if (nSip != 0) //必须以sip:开头
	{
		return "";
	}

	if (IsVirtualUri(uri))
	{
		return "";
	}

	size_t nAt = uri.find('@');
	if (std::string::npos == nAt) //必须含有@字符
	{
		return "";
	}
	//取sip:与@之间的字符串，注意要除去长度为4的"sip:"
	std::string strNum = uri.substr(/*nSip +*/ 4, (nAt /*- nSip*/) - 4); //程序执行到此行时，nSip==0

	if (strNum.find('+') != std::string::npos)
	{
		strNum = strNum.substr(1);
	}

	return strNum;
}

std::string eSDKTool::MergeString(const std::vector<std::string>& strList)
{
	unsigned int iSize = strList.size();
	std::string outStr("");
	if(iSize == 0)
	{
		return outStr;
	}
	if(iSize == 1)
	{
		outStr.append(strList.at(0));
		return outStr;
	}
	for(unsigned int i=0;i<(iSize-1);++i)
	{
		outStr.append(strList.at(i));
		outStr.append(",");
	}
	outStr.append(strList.at(iSize-1));
	return outStr;
}
void eSDKTool::SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList)
{
	stroutputList.clear();

	std::string instr = inputstr;
	int pos = -1;
	do{
		pos = (int)instr.find(',');
		stroutputList.push_back(instr.substr(0,(unsigned int)pos));
		instr = instr.substr((unsigned int)(pos+1));
	}while(-1 != pos && instr!="");
	return;
}
void eSDKTool::GetIPPort(const std::string& serverURL,std::string& ip,int& port)
{
	ip.clear();
	std::string instr = serverURL;
	string::size_type pos = instr.find(':');
	if( pos != string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort = instr.substr(pos+1);
		port =  atoi(outPort.c_str());
	}
	else
	{
		ip = "";
		port = 0;
	}


	return;
}
std::string eSDKTool::CreateGuidStr()
{
	GUID guid;
	(void)::CoCreateGuid(&guid);

	char buf[64];
	(void)::sprintf_s(buf, 
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", 
		(unsigned int)guid.Data1, guid.Data2, guid.Data3, 
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], 
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	return buf;
}
//UTF8转化为unicode
std::string eSDKTool::utf82unicode(const std::string& utf_str)
{
	std::wstring strOut = L"";
	ctk::utf8ToWstring(utf_str,strOut);

	int len= WideCharToMultiByte(CP_ACP,0,strOut.c_str(),(int)wcslen(strOut.c_str()),NULL,0,NULL,NULL); 
	char* pChar=new char[(unsigned int)len+1]; 
	WideCharToMultiByte(CP_ACP,0,strOut.c_str(),(int)wcslen(strOut.c_str()),pChar,len,NULL,NULL); 
	pChar[len]='\0';

	std::string str(pChar);
	delete[] pChar;
	return  str;
}

std::wstring eSDKTool::utf8_2_unicode_w(const std::string & utf_str)
{
	if (utf_str.empty())
	{
		return std::wstring();
	}
	std::wstring strOut;
	ctk::utf8ToWstring(utf_str, strOut);

	return strOut;
}

std::string eSDKTool::unicode_w_2_utf8(const std::wstring & uni_str)
{
	if (uni_str.empty())
	{
		return std::string();
	}
	std::string strOut(ctk::to_utf8str(uni_str.c_str()));

	return strOut;
}

void eSDKTool::GetNumStringFromCmd(const std::string& _spker, std::string& _spkeNum0, std::string& _spkeNum1)
{
	std::string spker = _spker;
	std::string::size_type pos = spker.find("#");
	if ( pos != std::string::npos )
	{
		_spkeNum0 = spker.substr(0,pos);
		spker = spker.substr(pos+1);
		pos = spker.find("#");
		if ( pos != std::string::npos )
		{
			_spkeNum1 = spker.substr(0,pos);       
		}
	}
	else if ( !spker.empty() )
	{
		_spkeNum0 = spker;
	}
	else
	{
	}
}




#include "StdAfx.h"
#include "UCConfigMgr.h"
#include "SSOLogin.h"

PhoneJointEventCB UCConfigMgr::m_OnPJEventCB = NULL;

const std::string ChineseSimplified = "2052";	//简体中文
const std::string BrazilPortuguese	= "1046";	//巴西葡萄牙文

UCConfigMgr::UCConfigMgr(void):m_pUCSelf(NULL),m_pConvMgr(NULL),m_pSSOClient(NULL)
{
}

UCConfigMgr::~UCConfigMgr(void)
{
	try
	{
		m_pUCSelf = NULL;
		m_pConvMgr = NULL;
		//等待线程结束
		m_pSSOClient = NULL;
	}
	catch (...)
	{
	}
}

void UCConfigMgr::Init(void)
{
	uc::model::UCClient* pUCClient = UCClient::GetClient();
	if(NULL == pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is NULL.";
		return;
	}
	m_pUCSelf = pUCClient->Self;
	m_pConvMgr = pUCClient->ConvManager;

	//加载联动的配置
	std::string ConfigPath;
	eSDKTool::getCurrentPath(ConfigPath);
	ConfigPath.append("\\");
	ConfigPath.append(CONFIG_FILE);
	m_ConfigPath = ConfigPath;

	ConectPhoneJointSignal();
	return;
}

void UCConfigMgr::Uninit(void)
{
	DisConectPhoneJointSignal();
	m_pUCSelf = NULL;
	m_pConvMgr = NULL;
}

int UCConfigMgr::GetPhoneJointDevType(int& _iDevType)
{
	if(NULL == m_pUCSelf)
	{
		ERROR_LOG() << "m_pUCSelf is NULL.";
		return UC_SDK_Failed;
	}	
	if(!m_pUCSelf->HasPermission(DoPhoneJoint))
	{
		ERROR_LOG() << "client has no PhoneJoint right.";
		return UC_SDK_NoRight;
	}

	const int LENGTH = 10;
	char tchValue[LENGTH] = {0};
	(void)::GetPrivateProfileStringA("UCService","activedevice","",tchValue,LENGTH-1,m_ConfigPath.c_str());

	std::string strActiveDev(tchValue);
	if(0 == strActiveDev.compare("pc"))
	{
		INFO_LOG() << "ActiveDev is PC";
		_iDevType = (int)PC_Device;
	}
	else
	{
		INFO_LOG() << "ActiveDev is IPPhone";
		_iDevType = (int)IPPhone_Device;
	}

	INFO_PARAM1(_iDevType);

	return UC_SDK_Success;
}
int UCConfigMgr::SetPhoneJointDevType(int _iDevType)
{
	if(NULL == m_pUCSelf)
	{
		ERROR_LOG() << "Self is NULL.";
		return UC_SDK_Failed;
	}	
	if(!m_pUCSelf->HasPermission(DoPhoneJoint))
	{
		ERROR_LOG() << "client has no PhoneJoint right.";
		return UC_SDK_NoRight;
	}
	if( PC_Device == _iDevType)
	{
		if(!::WritePrivateProfileStringA("UCService","activedevice","pc",m_ConfigPath.c_str()))
		{
			ERROR_LOG() << "WriteProfileString pc failed.";
		}
	}
	else if(IPPhone_Device == _iDevType)
	{
		if(!::WritePrivateProfileStringA("UCService","activedevice","ipphone",m_ConfigPath.c_str()))
		{
			ERROR_LOG() << "WriteProfileString ipphone failed.";
		}
	}
	else
	{
		ERROR_LOG() << "DevType is invalid.";
		return UC_SDK_InvalidPara;
	}

	std::map<uc::model::UCSelf::PubContactInfoType, std::string> infomap_;
	std::ostringstream os;
	os << _iDevType;		
	infomap_[uc::model::UCSelf::CallDeviceDesc] = os.str();

	bool bRet = m_pUCSelf->PublishSelfInformation(infomap_);
	if(!bRet)
	{
		ERROR_LOG() << "Set PhoneJoint DevType Failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}

int UCConfigMgr::SetPhoneJointEventCB(PhoneJointEventCB _EventCB)const
{
	m_OnPJEventCB = _EventCB;
	return UC_SDK_Success;
}

void UCConfigMgr::ConectPhoneJointSignal()
{
	if(NULL == m_pConvMgr)
	{
		ERROR_LOG() << "m_pConvMgr is NULL.";
		return;
	}

	m_pConvMgr->AVPhoneJointRelated.disconnect_all();
	m_pConvMgr->AVPhoneJointRelated.connect(&m_phoneJointEvent,&PhoneJointEvent::OnPhoneJointRelated);

	return;
}
void UCConfigMgr::DisConectPhoneJointSignal()
{
	if(NULL == m_pConvMgr)
	{
		ERROR_LOG() << "m_pConvMgr is NULL.";
		return;
	}

	m_pConvMgr->AVPhoneJointRelated.disconnect_all();

	return;

}
void UCConfigMgr::onThreadExit(ctk::Thread* _thr)
{
	if(NULL == _thr)
	{
		ERROR_LOG() << "thread is null";
		return;
	}
	ctk::ThreadId::type threadId = _thr->id().id_;

	INFO_PARAM1(threadId);
}
int UCConfigMgr::OpenPortal(int _type)
{
	m_pSSOClient = new SSOClient(this);
	m_pSSOClient->SetPortalType(_type);
	m_pSSOClient->start();

	return UC_SDK_Success;
}

void UCConfigMgr::SSOClient::run()
{
	UCClient* pClient = UCClient::GetClient();
	if(NULL == pClient)
	{
		ERROR_LOG() << "m_pClient is NULL.";
		return;
	}

	uc::model::UCSelf* pSelf = pClient->Self;
	if(NULL == pSelf)
	{
		ERROR_LOG() << "Self is NULL.";
		return;
	}

	//判断有没有登录
	const SelfProfile &profile = pSelf->GetProfile();
	std::string strPortalUrl = profile.portaladdr;
	if(Offline == pSelf->selfStatus)
	{
		//解析URL，找出登录地址
		string::size_type index = strPortalUrl.find("login.do",0);
		if(string::npos != index)
		{
			strPortalUrl = strPortalUrl.substr(0,index);
		}
		SSOLogin::OpenURL(eSDKTool::utf8_2_unicode(strPortalUrl));
		INFO_LOG() << "Not Login,Open:" << strPortalUrl;
		return;
	}

	//配置单点登录地址
	if (SelfMgr_Portal == m_PortalType)
	{
		strPortalUrl += "?bmuUserType=2";//目前2是个人管理平台
	}
	else if (BookConf_Portal == m_PortalType)
	{
		strPortalUrl += "?bmuUserType=2";//2是预约会议平台
	}

	strPortalUrl += "&userId=" + pSelf->selfInfo.ucAcc_;
	strPortalUrl += "&loginToken=" + pSelf->GetProfile().token;

	string strlang = pClient->SignConfig.lang;
	if (strlang == ChineseSimplified)
	{
		(void)strPortalUrl.append("&language=zh_cn");
	}
	else if(strlang == BrazilPortuguese)
	{
		(void)strPortalUrl.append("&language=pt-br");
	}	
	else  
	{
		(void)strPortalUrl.append("&language=en");//英文
	}

	if (BookConf_Portal == m_PortalType)
	{
		(void)strPortalUrl.append("&desturl=listScheduleConf");//预约会议平台要加上
	}	

	SSOLogin::OpenURL(eSDKTool::utf8_2_unicode(strPortalUrl));

	return;
}

#include "StdAfx.h"
#include "UCRegManager.h"
#include "UCConfigMgr.h"
#include "UCContactMgr.h"

//lint -e1762
//lint -e1788
ClientSignInNotifyCB UCRegManager::OnClientSignInNotifyCB = NULL;
StatusChangedCB UCRegManager::OnStatusChangedCB = NULL;

UCRegManager::UCRegManager(void):m_pUCClient(NULL),m_pSelf(NULL),m_pSubscribeMgr(NULL)
{
}

UCRegManager::~UCRegManager(void)
{
	m_pUCClient = NULL;
	m_pSelf = NULL;
	m_pSubscribeMgr = NULL;
}
void UCRegManager::Init(void)
{
	ctk::Mutex::Lock lck(m_RegMutex);

	m_pUCClient = UCClient::GetClient();
	if(NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is NULL";
		return;
	}
	(void)m_pUCClient->Init();

	m_pSelf = m_pUCClient->Self;
	m_pSubscribeMgr = m_pUCClient->ContactSubManager;

	OnClientSignInNotifyCB = NULL;
	OnStatusChangedCB = NULL;

}
void UCRegManager::Uninit(void)
{
	ctk::Mutex::Lock lck(m_RegMutex);

	m_pSelf = NULL;
	m_pSubscribeMgr = NULL;
	if(NULL != m_pUCClient)
	{
		(void)m_pUCClient->UnInit();
		UCClient::ReleaseClient();
		m_pUCClient = NULL;
	}

	OnClientSignInNotifyCB = NULL;
	OnStatusChangedCB = NULL;
}
void UCRegManager::InitSubscribe(void)
{
	if(NULL == m_pSubscribeMgr)
	{
		ERROR_LOG() << "m_pSubscribeMgr is NULL.";
		return;
	}
	m_pSubscribeMgr->Init();
	m_pSubscribeMgr->InitSubContactlist();
}
void UCRegManager::UnInitSubscribe(void)
{
	if(NULL == m_pSubscribeMgr)
	{
		ERROR_LOG() << "m_pSubscribeMgr is NULL.";
		return;
	}

	m_pSubscribeMgr->ClearSubList();
	m_pSubscribeMgr->Uninit();

}
int UCRegManager::SignInByPWD(const std::string& _account,const std::string& _pwd,const std::string& _serverUrl,const std::string& _langID)
{
	if(NULL == m_pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is NULL.";
		return UC_SDK_NotInit;
	}

	m_pUCClient->SignConfig.account = _account;			//登录账号
	m_pUCClient->SignConfig.pwd = _pwd;					//登录密码	
	m_pUCClient->SignConfig.internalurl = _serverUrl;	//登录URL，格式为IP:Port
	m_pUCClient->SignConfig.externalsurl = _serverUrl;
	m_pUCClient->SignConfig.lang = _langID;				//语言

	//其他参数采用默认				
	m_pUCClient->SignConfig.ver = "v2.1.3.35";			//版本
	m_pUCClient->SignConfig.signinmode = AccountAndPwd;	//登录模式默认为账户+密码
	m_pUCClient->SignConfig.initStatus = Online;	
	m_pUCClient->SignConfig.siteID = Server1;

	//not use svn
	m_pUCClient->SignConfig.svntunnel        = false;
	m_pUCClient->SignConfig.svnServerIp      = "";
	m_pUCClient->SignConfig.svnServerIpPort  = "";
	m_pUCClient->SignConfig.svnacc           = "";
	m_pUCClient->SignConfig.svnpwd           = "";
	m_pUCClient->SignConfig.svnLoginDlgHwnd  = NULL;

	//not use https
	m_pUCClient->SignConfig.aaTunnelType = uc::model::AA_CONNECTION_HTTP;

	//GetUpdateAddress
	std::string ip;
	int port;
	eSDKTool::GetIPPort(_serverUrl,ip,port);
	if(!m_pUCClient->GetUpdateAddress(ip,port,_account))
	{
		WARN_LOG() << "GetUpdateAddress failed.";
	}

	//login
	if (!m_pUCClient->SignIn())
	{
		ERROR_LOG() << "SignIn failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}
int UCRegManager::SignOut()
{
	if(NULL == m_pUCClient)
	{
		return UC_SDK_NotInit;
	}

	//断开信号连接
	UCConfigMgr::Instance().DisConectPhoneJointSignal();

	if(!m_pUCClient->SignOut())
	{
		WARN_LOG() << "SignOut Failed.";
		return  UC_SDK_Failed;
	}

	return UC_SDK_Success;
}

int UCRegManager::SetLoginEventCB(ClientSignInNotifyCB _loginEventCB)
{
	if(NULL == m_pUCClient)
	{
		return UC_SDK_NotInit;
	}
	//连接登陆信号
	m_pUCClient->SignInNotify_.disconnect_all();
	m_pUCClient->SignInNotify_.connect(&m_RegEvent, &RegEvent::OnSignInNotify);
	m_pUCClient->SipOkNotify_.disconnect_all();
	m_pUCClient->SipOkNotify_.connect(&m_RegEvent,&RegEvent::OnSipRegNotify);

	UCRegManager::OnClientSignInNotifyCB = _loginEventCB;
	return UC_SDK_Success;

}
int UCRegManager::SetStatusEventCB(StatusChangedCB _statusEventCB)
{
	if(NULL == m_pUCClient)
	{
		return UC_SDK_NotInit;
	}

	if (NULL == m_pSubscribeMgr)
	{
		return UC_SDK_NotInit;
	}

	//连接状态信号
	m_pSubscribeMgr->UserAvailabilityChanged_.disconnect_all();
	m_pSubscribeMgr->UserAvailabilityChanged_.connect(&m_RegEvent, &RegEvent::OnStatusChanged);

	UCRegManager::OnStatusChangedCB = _statusEventCB;

	return UC_SDK_Success;
}

//个人忙碌状态描述
const std::string USER_STATUS_DESC_CONST_CALLING = "1";
const std::string USER_STATUS_DESC_CONST_INMEETING = "2";

int UCRegManager::PubSelfStatus(ContactAvailability _state,const::string& _desc)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pUCClient )
	{
		ERROR_LOG() << "m_pUCClient is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotInit;
	}
	if(NULL == m_pUCClient->ConvManager)
	{
		ERROR_LOG() << "ConvManager is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotInit;
	}
	if(NULL == m_pSelf)
	{
		ERROR_LOG() << "m_pSelf is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotInit;
	}

	INFO_PARAM2(_state,_desc);
	if(_state == m_pSelf->selfStatus)
	{
		WARN_LOG() << "state is already published.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_Success;
	}

	std::map<UCSelf::PubContactInfoType, std::string> infomap_;
	std::ostringstream os;
	os << _state;
	infomap_[UCSelf::Availability] = os.str();
	if(0 < m_pUCClient->ConvManager->GetAVSessionConvCount())
	{
		if(m_pUCClient->ConvManager->HasConfAVSessionConv())
		{
			infomap_[UCSelf::CustomStatusDesc] = USER_STATUS_DESC_CONST_INMEETING;
		}
		else
		{
			infomap_[UCSelf::CustomStatusDesc] = USER_STATUS_DESC_CONST_CALLING;
		}
	}
	else
	{
		infomap_[UCSelf::CustomStatusDesc] = _desc;
	}
	
	m_pSelf->PublishSelfInformation(infomap_);

	DEBUG_LOG() << "--- LEAVE";

	return UC_SDK_Success;

}
int UCRegManager::DisSubscribeStatus(const std::string& strUri)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pUCClient )
	{
		ERROR_LOG() << "m_pUCClient is NULL";
		return UC_SDK_NotInit;
	}
	if(NULL == m_pSelf)
	{
		ERROR_LOG() << "Self is NULL";
		return UC_SDK_NotInit;
	}
	if(strUri == m_pSelf->selfInfo.uri_)
	{
		WARN_LOG() << "Cannot DisSubscribe Self";
		return UC_SDK_Failed;
	}

	if(!eSDKTool::IsValidUri(strUri))
	{
		INFO_LOG() << "Not need to DisSubscribe contact [" << strUri << "] .";
		return UC_SDK_Failed;
	}

	if(NULL == m_pSubscribeMgr)
	{
		ERROR_LOG() << "ContactSubManager is NULL";
		return UC_SDK_NotInit;
	}

	if(m_pSubscribeMgr->HasSubContact(strUri))
	{
		m_pSubscribeMgr->RemoveSubContact(strUri);
		INFO_LOG() << "DisSubscribe contact [ "<< strUri <<" ] Success.";
		return UC_SDK_Success;
	}
	else
	{
		INFO_LOG() << "Not Subscribe contact [ "<< strUri <<" ].";
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;

}
int UCRegManager::SubscribeStatus(const std::string& strUri)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pUCClient )
	{
		ERROR_LOG() << "m_pUCClient is NULL";
		return UC_SDK_NotInit;
	}
	if(NULL == m_pSelf)
	{
		ERROR_LOG() << "Self is NULL";
		return UC_SDK_NotInit;
	}

	//if(strUri == m_pSelf->selfInfo.uri_)
	//{
	//	WARN_LOG() << "Cannot Subscribe Self";
	//	return UC_SDK_Failed;
	//}

	if(!eSDKTool::IsValidUri(strUri))
	{
		INFO_LOG() << "Not need to subscribe contact [" << strUri << "] .";
		return UC_SDK_Failed;
	}

	if(NULL == m_pSubscribeMgr)
	{
		ERROR_LOG() << "ContactSubManager is NULL";
		return UC_SDK_NotInit;
	}

	if(m_pSubscribeMgr->HasSubContact(strUri))
	{
		//INFO_LOG() << "has already Subscribed contact ["<< strUri <<"] .";
		return UC_SDK_Success;
	}

	if(m_pSubscribeMgr->AddSubContact(strUri))
	{
		//INFO_LOG() << "Subscribe contact ["<< strUri <<"] Success.";
	}
	else
	{
		WARN_LOG() << "Subscribe contact ["<< strUri <<"] Failed.";
	}
	

	DEBUG_LOG() << "--- LEAVE";

	return UC_SDK_Success;

}
int UCRegManager::NotifyStatus(const Contact& _contact,ContactAvailability _state,const std::string& _desc)
{
	if (NULL == UCRegManager::OnStatusChangedCB)
	{
		return UC_SDK_Failed;
	}
	STContact st = {0};	
	(void)strcpy_s(st.location_,_contact.location_.c_str());
	(void)strcpy_s(st.webSite_,_contact.webSite_.c_str());
	(void)strcpy_s(st.ipphone1_,_contact.ipphone1_.c_str());
	(void)strcpy_s(st.deptName_,_contact.deptName_.c_str());
	(void)strcpy_s(st.email_,_contact.email_.c_str());
	(void)strcpy_s(st.mobile_,_contact.mobile_.c_str());
	(void)strcpy_s(st.officePhone2_,_contact.officePhone2_.c_str());
	(void)strcpy_s(st.officePhone_,_contact.officePhone_.c_str());
	(void)strcpy_s(st.homePhone_,_contact.homePhone_.c_str());
	(void)strcpy_s(st.nickName_,_contact.nickName_.c_str());
	(void)strcpy_s(st.name_,_contact.name_.c_str());
	(void)strcpy_s(st.staffNo_,_contact.staffNo_.c_str());
	(void)strcpy_s(st.ucAcc_,_contact.ucAcc_.c_str());
	(void)strcpy_s(st.uri_,_contact.uri_.c_str());
	(void)strcpy_s(st.id_,_contact.id_.c_str());

	INFO_PARAM3(_contact.ucAcc_,_state,_desc);

	DEBUG_LOG() << "--- OnStatusChangedCB ENTER";
	UCRegManager::OnStatusChangedCB((int)_state, st);
	DEBUG_LOG() << "--- OnStatusChangedCB LEAVE";
	return UC_SDK_Success;


}
int UCRegManager::CheckSignStatus(void)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pUCClient )
	{
		WARN_LOG() << "m_pUCClient is NULL";
		return UC_SDK_NotInit;
	}
	if(NULL == m_pSelf)
	{
		WARN_LOG() << "Self is NULL";
		return UC_SDK_NotInit;
	}

	if(Offline == m_pSelf->selfStatus)
	{
		WARN_LOG() << "client is Offline";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotLogin;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;

}

int UCRegManager::GetContactStatus(const std::string& _account,int& _status)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pUCClient )
	{
		ERROR_LOG() << "m_pUCClient is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotInit;
	}
	if(NULL == m_pSubscribeMgr)
	{
		ERROR_LOG() << "ContactSubManager is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotInit;
	}

	Contact uccontact;
	if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(_account,uccontact))
	{
		_status = Offline;

		WARN_LOG() << " " << _account << " is Offline.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_Failed;
	}

	_status = (ContactAvailability)m_pSubscribeMgr->GetContactStatus(uccontact.uri_);

	INFO_LOG() << "[" << _account << "] status is " << _status;

	//IPT2.2异步获取状态
	std::list<std::string> listContact;
	listContact.push_back(_account);
	m_pUCClient->EntAddrbookManager_.GetEntStaffStatus(listContact);

 	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;
}

int UCRegManager::GetContactInfo(const std::string& _account,STContact& _Contact)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == m_pUCClient )
	{
		ERROR_LOG() << "m_pUCClient is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotInit;
	}

	Contact ucContact;
	if(UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(_account,ucContact))
	{
		WARN_LOG() << " getContactByAccount failed";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_Failed;
	}

	//IPT2.2异步获取状态
	std::list<std::string> listContact;
	listContact.push_back(_account);
	m_pUCClient->EntAddrbookManager_.GetEntStaffStatus(listContact);

	ctk::MemSet(_Contact.address_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.address_,ucContact.address_.c_str(),(ucContact.address_.size()<(STRING_LENGTH)) ? (ucContact.address_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.avtool_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.avtool_,ucContact.avtool_.c_str(),(ucContact.avtool_.size()<(STRING_LENGTH)) ? (ucContact.avtool_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.corpName_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.corpName_,ucContact.corpName_.c_str(),(ucContact.corpName_.size()<(STRING_LENGTH)) ? (ucContact.corpName_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.deptName_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.deptName_,ucContact.deptName_.c_str(),(ucContact.deptName_.size()<(STRING_LENGTH)) ? (ucContact.deptName_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.desc_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.desc_,ucContact.desc_.c_str(),(ucContact.desc_.size()<(STRING_LENGTH)) ? (ucContact.desc_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.device_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.device_,ucContact.device_.c_str(),(ucContact.device_.size()<(STRING_LENGTH)) ? (ucContact.device_.size()) : (STRING_LENGTH-1));

	ctk::MemSet(_Contact.duty_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.duty_,ucContact.duty_.c_str(),(ucContact.duty_.size()<(STRING_LENGTH)) ? (ucContact.duty_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.email_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.email_,ucContact.email_.c_str(),(ucContact.email_.size()<(STRING_LENGTH)) ? (ucContact.email_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.fax_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.fax_,ucContact.fax_.c_str(),(ucContact.fax_.size()<(STRING_LENGTH)) ? (ucContact.fax_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.fullUri_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.fullUri_,ucContact.fullUri_.c_str(),(ucContact.fullUri_.size()<(STRING_LENGTH)) ? (ucContact.fullUri_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.homePhone_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.homePhone_,ucContact.homePhone_.c_str(),(ucContact.homePhone_.size()<(STRING_LENGTH)) ? (ucContact.homePhone_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.ipphone1_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.ipphone1_,ucContact.ipphone1_.c_str(),(ucContact.ipphone1_.size()<(STRING_LENGTH)) ? (ucContact.ipphone1_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.ipphone2_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.ipphone2_,ucContact.ipphone2_.c_str(),(ucContact.ipphone2_.size()<(STRING_LENGTH)) ? (ucContact.ipphone2_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.mobile_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.mobile_,ucContact.mobile_.c_str(),(ucContact.mobile_.size()<(STRING_LENGTH)) ? (ucContact.mobile_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.officePhone2_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.officePhone2_,ucContact.officePhone2_.c_str(),(ucContact.officePhone2_.size()<(STRING_LENGTH)) ? (ucContact.officePhone2_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.officePhone_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.officePhone_,ucContact.officePhone_.c_str(),(ucContact.officePhone_.size()<(STRING_LENGTH)) ? (ucContact.officePhone_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.otherPhone2_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.otherPhone2_,ucContact.otherPhone2_.c_str(),(ucContact.otherPhone2_.size()<(STRING_LENGTH)) ? (ucContact.otherPhone2_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.otherPhone_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.otherPhone_,ucContact.otherPhone_.c_str(),(ucContact.otherPhone_.size()<(STRING_LENGTH)) ? (ucContact.otherPhone_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.staffNo_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.staffNo_,ucContact.staffNo_.c_str(),(ucContact.staffNo_.size()<(STRING_LENGTH)) ? (ucContact.staffNo_.size()) : (STRING_LENGTH-1));


	ctk::MemSet(_Contact.uri_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.uri_,ucContact.uri_.c_str(),(ucContact.uri_.size()<(STRING_LENGTH)) ? (ucContact.uri_.size()) : (STRING_LENGTH-1));
	
	ctk::MemSet(_Contact.zip_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.zip_,ucContact.zip_.c_str(),(ucContact.zip_.size()<(STRING_LENGTH)) ? (ucContact.zip_.size()) : (STRING_LENGTH-1));


	ctk::MemSet(_Contact.ucAcc_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.ucAcc_,ucContact.ucAcc_.c_str(),(ucContact.ucAcc_.size()<(STRING_LENGTH)) ? (ucContact.ucAcc_.size()) : (STRING_LENGTH-1));

	ctk::MemSet(_Contact.gender_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.gender_,ucContact.gender_.c_str(),(ucContact.gender_.size()<(STRING_LENGTH)) ? (ucContact.gender_.size()) : (STRING_LENGTH-1));


	ctk::MemSet(_Contact.id_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.id_,ucContact.ucAcc_.c_str(),(ucContact.id_.size()<(STRING_LENGTH)) ? (ucContact.id_.size()) : (STRING_LENGTH-1));

	ctk::MemSet(_Contact.name_,0,STRING_LENGTH);
	ctk::MemCopy(_Contact.name_,ucContact.name_.c_str(),(ucContact.name_.size()<(STRING_LENGTH)) ? (ucContact.name_.size()) : (STRING_LENGTH-1));

	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;
}

int UCRegManager::GetSigninErrorDesc(const std::string _reason,std::string& _errordesc)
{
	string::size_type pos = _reason.find("AAresult");
	string errorcode;
	int remaintries = -1;

	if (pos == string::npos)
	{
		_errordesc = _reason;
		return UC_SDK_Failed;
	}

	ctk::xml::XMLInStream xis(_reason);
	int AAretrytimes = -1;
	int AAmaxretrytimes = -1;

	xis["AAresult"] >> errorcode;
	xis["retrytimes"] >> AAretrytimes;   //注意：输入错误次数达到限制时，此时AA返回的该值为0
	xis["maxretrytimes"] >> AAmaxretrytimes;

	if(AAmaxretrytimes > 0 && AAretrytimes >= 0 )
	{ 
		if( 0 == AAretrytimes)
		{
			remaintries = 0;
		}
		else if(AAmaxretrytimes >= AAretrytimes)
		{
			remaintries = AAmaxretrytimes - AAretrytimes;
		}
		else
		{
			remaintries = 0;
		}
	}

	long lErrorCode = atol(errorcode.c_str());
	switch (lErrorCode)
	{
	case LOGIN_PASSWORD_ERROR:
		{
			_errordesc = ERROR_PWD;
			break;
		}
	case LOGIN_ACCOUNT_DONOT_EXIST:
		{
			_errordesc = ACC_NOT_EXISTED;
			break;
		}
	case LOGIN_ACCOUNT_LOCK:
		{
			_errordesc = ACC_LOCKED;
			break;
		}
	case LOGIN_ACCOUNT_ERROR:
		{
			_errordesc = ACC_ERROR;
			break;
		}
	case LOGIN_NEED_CHANGE_PASSWORD:
		{
			_errordesc = NEED_CHANGEPWD;
			break;
		}
	case LOGIN_TIMEOUT:
		{
			_errordesc = TIME_OUT;
			break;
		}
	case LOGIN_NEED_NEWVERSION:
		{
			_errordesc = NEED_NEW_VERSION;
			break;
		}
	case LOGIN_NEED_ACTIVE:
		{
			_errordesc = NEED_ACTIVE;
			break;
		}
	default:
		{
			_errordesc = NORMAL_ERROR;
		}

	}

	INFO_PARAM2(_errordesc,remaintries);

	return UC_SDK_Success;
	
}


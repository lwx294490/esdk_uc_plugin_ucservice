#include "StdAfx.h"
#include "UCContactMgr.h"

UCContactMgr::UCContactMgr(void):m_pContactMgr(NULL),m_pEntContactMgr(NULL)
{
}

UCContactMgr::~UCContactMgr(void)
{
	m_pContactMgr = NULL;
	m_pEntContactMgr = NULL;
}
void UCContactMgr::Init(void)
{
	uc::model::UCClient* pUCClient = UCClient::GetClient();
	if(NULL == pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is NULL.";
		return;
	}

	m_pContactMgr = pUCClient->ContactManager;
	m_pEntContactMgr = &pUCClient->EntAddrbookManager_;

}
void UCContactMgr::Uninit(void)
{
	m_pContactMgr = NULL;
	m_pEntContactMgr = NULL;	
}
int UCContactMgr::getContactByUri(const std::string& _uri, Contact& _contact)
{
	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		return UC_SDK_NotInit;
	}

	if("" == _uri)
	{
		ERROR_LOG() << "_uri is empty.";
		return UC_SDK_InvalidPara;
	}

	//先查本地
	bool bRet = m_pContactMgr->GetContactByUri(_uri,_contact);
	if(bRet)
	{	
		INFO_PARAM2(_uri,_contact.ucAcc_);
		return UC_SDK_Success;
	}

	bRet = m_pContactMgr->RefreshContactByUri(_uri,_contact);
	if(!bRet)
	{
		INFO_LOG() << _uri << " is not associated with UC account";
		return UC_SDK_NotFound;
	}

	INFO_PARAM2(_uri,_contact.ucAcc_);
	return UC_SDK_Success;
}
int UCContactMgr::getContactByAccount(const std::string& _account, Contact& _contact)
{
	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		return UC_SDK_NotInit;
	}

	if(NULL == m_pEntContactMgr)
	{
		ERROR_LOG() << "m_pEntContactMgr is NULL.";
		return UC_SDK_NotInit;
	}

	//先查本地，找不到再进行企业通讯录查询
	if(m_pContactMgr->GetContactByAccount(_account,_contact))
	{
		INFO_PARAM3(_contact.uri_,_contact.ucAcc_,_contact.fullUri_);
		return UC_SDK_Success;
	}

	//上企业通讯录查询
	const int PAGE_SIZE = 2;			//每次查找返回的最大个数
	Dept::_ContactStatuses staffList;	//返回的结果
	int recamount = 0;					//返回的个数
	(void)m_pEntContactMgr->SearchContact(_account, "", true, 0, PAGE_SIZE, 0, recamount, staffList);

	if(0 == staffList.size())
	{
		ERROR_LOG() << "Not Find UC Account";
		return UC_SDK_NotFound;
	}

	//上面只查询一个结果，所以取第一个
	_contact.uri_ = (staffList.at(0).first).uri_;
	_contact.ucAcc_ = (staffList.at(0).first).ucAcc_;
	_contact.fullUri_ = (staffList.at(0).first).fullUri_;

	INFO_PARAM3(_contact.uri_,_contact.ucAcc_,_contact.fullUri_);
	
	return UC_SDK_Success;
}

int UCContactMgr::getContactByPhoneNum(const std::string& _phone, Contact& _contact)
{
	if(NULL == m_pContactMgr)
	{
		ERROR_LOG() << "m_pContactMgr is NULL.";
		return UC_SDK_NotInit;
	}

	if(NULL == m_pEntContactMgr)
	{
		ERROR_LOG() << "m_pEntContactMgr is NULL.";
		return UC_SDK_NotInit;
	}

	//先查本地，
	if(m_pContactMgr->GetContactByPhoneNum(_phone,_contact))
	{
		if(eSDKTool::GetNoFromUri(_contact.fullUri_) == _phone)
		{
			return UC_SDK_Success;
		}		
	}

	//上企业通讯录查询
	const int PAGE_SIZE = 10;			//每次查找返回的最大个数
	Dept::_ContactStatuses staffList;	//返回的结果
	int recamount = 0;					//返回的个数

	m_pEntContactMgr->SearchContact(_phone, "", true, 0, PAGE_SIZE, 0, recamount, staffList);

	if(0 == staffList.size())
	{
		WARN_LOG() << "Search EnterpriseContact By PhoneNum Failed.";
		return UC_SDK_NotFound;
	}

	//上面只查询一个结果，所以取第一个
	std::string strUri = (staffList.at(0).first).fullUri_;
	if(eSDKTool::GetNoFromUri(strUri) != _phone)
	{
		WARN_LOG() << "Search Enter Contact Result Invalid";
		return UC_SDK_NotFound;
	}

	_contact.uri_ = strUri;
	_contact.ucAcc_ = (staffList.at(0).first).ucAcc_;
	_contact.fullUri_ = (staffList.at(0).first).fullUri_;

	INFO_PARAM3(_contact.uri_,_contact.ucAcc_,_contact.fullUri_);

	return UC_SDK_Success;
}




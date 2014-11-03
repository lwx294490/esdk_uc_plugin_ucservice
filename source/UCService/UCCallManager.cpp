#include "StdAfx.h"
#include "UCCallManager.h"
#include "UCRegManager.h"
#include "UCContactMgr.h"
#include "UCTonePlay.h"


//lint -e1788
UCSDKObserver UCCallManager::m_UCSDKObserver;
AVSessionClosedCB UCCallManager::OnAVSessionClosedCB=NULL;			//呼叫断开回调函数指针
AVSessionConnectedCB UCCallManager::OnAVSessionConnectedCB=NULL;		//连接成功回调函数指针
AVSessAddedCB UCCallManager::OnAVSessAddedCB=NULL;					//新呼叫连接回调函数指针
ConfMemberEventCB UCCallManager::OnConfMemberEventCB=NULL;
VideoCallEventCB UCCallManager::OnVideoCallEventCB=NULL;


UCCallManager::UCCallManager(void)
{
	try
	{
		m_ConversationID.clear();
		m_pConvMgr = NULL;
		m_MemUriList.clear();
		m_MemPhoneList.clear();
		m_ConvMemberMap.clear();
		isConfStart = false;
	}
	catch(...)
	{
	}

}

UCCallManager::~UCCallManager(void)
{
	try
	{
		m_ConversationID.clear();
		m_pConvMgr = NULL;
		m_MemUriList.clear();
		m_MemPhoneList.clear();
		m_ConvMemberMap.clear();
		isConfStart = false;
	}
	catch(...)
	{
	}
}

void UCCallManager::Init(void)
{	
	uc::model::UCClient* pUCClient = UCClient::GetClient();
	if(NULL == pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is NULL.";
		return;
	}

	m_pConvMgr = pUCClient->ConvManager;
	if(NULL != m_pConvMgr)
	{
		m_pConvMgr->observer = &m_UCSDKObserver;
	}

	m_ConversationID = "";
	m_MemUriList.clear();
	m_MemPhoneList.clear();
	m_ConvMemberMap.clear();

	OnAVSessionClosedCB = NULL;
	OnAVSessionConnectedCB = NULL;
	OnAVSessAddedCB = NULL;

}
void UCCallManager::Uninit(void)
{
	m_pConvMgr = NULL;
	OnAVSessionClosedCB = NULL;
	OnAVSessionConnectedCB = NULL;
	OnAVSessAddedCB = NULL;
	m_ConversationID = "";
	m_MemUriList.clear();
	m_MemPhoneList.clear();
	m_ConvMemberMap.clear();

}

int UCCallManager::InsertUCMember(const std::string& _ucUri)
{
	m_MemUriList.insert(_ucUri);
	return UC_SDK_Success;
}
int UCCallManager::InsertPhoneMember(const std::string& _phone)
{
	m_MemPhoneList.insert(_phone);
	return UC_SDK_Success;
}
int UCCallManager::MakeCall(void)
{
	size_t nMemberCount = m_MemUriList.size();
	size_t nPhoneNum = m_MemPhoneList.size();
	size_t nNum = nMemberCount + nPhoneNum;
	if (0 == nNum)
	{
		ERROR_LOG() << "memberList is empty";
		return UC_SDK_NotHaveCallTarget;
	}

	if (1 == nMemberCount && 0 == nPhoneNum)//呼叫单个账户
	{
		conversation::Conversation* pConversation = GetConversation();
		if (NULL == pConversation)
		{
			ERROR_LOG() << "pConversation is null pointer";
			return UC_SDK_NullPtr;
		}

		Contact member;
		member.uri_ = *(m_MemUriList.begin());
		(void)UCContactMgr::Instance().getContactByUri(member.uri_, member);
		pConversation->AddParticipant(member);

		conversation::Session* pIMSession = pConversation->AddSession(uc::model::InstantMessage);
		if(NULL == pIMSession)
		{
			ERROR_LOG() << "add IM Session Failed.";
			return UC_SDK_Failed;
		}
		(void)pIMSession->Connect();

		conversation::AVSession* pAVSession = AddAVSession();
		if(NULL == pAVSession)
		{
			ERROR_LOG() << "add AVSession Failed.";
			return UC_SDK_Failed;
		}

		//发起呼叫
		ConectVideoSignal(pAVSession);
		(void)pAVSession->Connect();
		return UC_SDK_Success;
	}
	if (0 == nMemberCount && 1 == nPhoneNum)//呼叫单个电话
	{
		conversation::Conversation* pConversation = GetConversation();
		if (NULL == pConversation)
		{
			ERROR_LOG() << "pConversation is null pointer";
			return UC_SDK_NullPtr;
		}

		Contact member;
		member.uri_ = "";
		member.mobile_ = *(m_MemPhoneList.begin());
		member.name_ = member.mobile_;

		pConversation->AddParticipant(member);

		conversation::Session* pIMSess = pConversation->AddSession(uc::model::InstantMessage);
		if(NULL == pIMSess)
		{
			ERROR_LOG() << "add IMSess Failed.";
			return UC_SDK_Failed;
		}
		(void)pIMSess->Connect();

		conversation::AVSession* pAVSess = AddAVSession();
		if(NULL == pAVSess)
		{
			ERROR_LOG() << "add AVSess Failed.";
			return UC_SDK_Failed;
		}

		//发起呼叫
		(void)pAVSess->Connect();
		return UC_SDK_Success;

	}

	if (UC_SDK_Success != CreateTempGroup())
	{
		ERROR_LOG() << "CreateTempGroup failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
	
}


int UCCallManager::HoldCall(void)
{
	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pAVSess is NULL";
		return UC_SDK_Failed;
	}

	if(!pAVSess->Hold())
	{
		ERROR_LOG() << "Hold Call failed.";
		return UC_SDK_Failed;	
	}

	return UC_SDK_Success;	
}

int UCCallManager::ResumeCall(void)
{
	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pAVSess is NULL";
		return UC_SDK_Failed;
	}
	
	if(!pAVSess->Resume())
	{
		ERROR_LOG() << "Resume Call failed.";
		return UC_SDK_Failed;	
	}
	return UC_SDK_Success;	
}


int UCCallManager::MakeVideoCall(const STVideoWindow& stLocalWnd, const STVideoWindow& stRemoteWnd)
{
	conversation::Conversation* pConv = GetConversation();
	if (NULL == pConv)
	{
		ERROR_LOG() << "pConv is null.";
		return UC_SDK_NullPtr;
	}

	if (1 == pConv->members_.size())		//首次开启视频
	{
		unsigned int ucMemSize = m_MemUriList.size();
		unsigned int phoneMemSize = m_MemPhoneList.size();
		if(1 != (ucMemSize+phoneMemSize))
		{
			ERROR_LOG() << "memberList size is not 1";
			return UC_SDK_NotHaveCallTarget;
		}

		Contact member;
		if(1 == ucMemSize)
		{		
			member.uri_ = *(m_MemUriList.begin());
			(void)UCContactMgr::Instance().getContactByUri(member.uri_, member);
		}
		else if(1 == phoneMemSize)
		{
			member.uri_ = "";
			member.name_ = *(m_MemPhoneList.begin());
			member.mobile_ = member.name_;
		}	

		pConv->AddParticipant(member);
	}
	else if (2 == pConv->members_.size())	//语音中开启视频
	{
	}
	else
	{
		ERROR_LOG() << "the member size is greater than 2 what in conversation";
		return UC_SDK_Failed;
	}


	//已存在语音
	conversation::AVSession* pAVSess = NULL;
	if(pConv->HasSession(AudioVideo))
	{
		pAVSess = GetAVSession();
		if(NULL == pAVSess)
		{
			ERROR_LOG() << "add AVSession Failed.";
			return UC_SDK_Failed;
		}

		//挂接视频通知信号
		ConectVideoSignal(pAVSess);

		if(conversation::avchannel::ChannelInActive == pAVSess->videochannel_.state_)
		{
			//初始化视频窗口
			pAVSess->videochannel_.remotewnd_.wnd_ = (HWND)stRemoteWnd.hWnd;
			pAVSess->videochannel_.remotewnd_.top_ = stRemoteWnd.top;
			pAVSess->videochannel_.remotewnd_.left_ = stRemoteWnd.left;
			pAVSess->videochannel_.remotewnd_.height_ = stRemoteWnd.height;
			pAVSess->videochannel_.remotewnd_.width_ = stRemoteWnd.width;
			pAVSess->videochannel_.localwnd_.wnd_ = (HWND)stLocalWnd.hWnd;
			pAVSess->videochannel_.localwnd_.top_ = stLocalWnd.top;
			pAVSess->videochannel_.localwnd_.left_ = stLocalWnd.left;
			pAVSess->videochannel_.localwnd_.height_ = stLocalWnd.height;
			pAVSess->videochannel_.localwnd_.width_ = stLocalWnd.width;
			
			if(!pAVSess->videochannel_.Start())
			{
				ERROR_LOG()<<"pSess->videochannel_.Start() failed.";
				return UC_SDK_Failed;
			}
		}
	}
	else
	{
		conversation::Session* pIMSess = pConv->AddSession(uc::model::InstantMessage);
		if(NULL == pIMSess)
		{
			ERROR_LOG() << "add IMSession Failed.";
			return UC_SDK_Failed;
		}
		(void)pIMSess->Connect();


		pAVSess = AddAVSession();
		if(NULL == pAVSess)
		{
			ERROR_LOG() << "add AVSession Failed.";
			return UC_SDK_Failed;
		}

		//挂接视频通知信号
		ConectVideoSignal(pAVSess);

		//初始化视频窗口
		pAVSess->videochannel_.remotewnd_.wnd_ = (HWND)stRemoteWnd.hWnd;
		//pAVSess->videochannel_.remotewnd_.top_ = stRemoteWnd.top;
		//pAVSess->videochannel_.remotewnd_.left_ = stRemoteWnd.left;
		pAVSess->videochannel_.remotewnd_.height_ = stRemoteWnd.height;
		pAVSess->videochannel_.remotewnd_.width_ = stRemoteWnd.width;
		pAVSess->videochannel_.localwnd_.wnd_ = (HWND)stLocalWnd.hWnd;
		//pAVSess->videochannel_.localwnd_.top_ = stLocalWnd.top;
		//pAVSess->videochannel_.localwnd_.left_ = stLocalWnd.left;
		pAVSess->videochannel_.localwnd_.height_ = stLocalWnd.height;
		pAVSess->videochannel_.localwnd_.width_ = stLocalWnd.width;

		if(!pAVSess->Connect())
		{
			(void)pAVSess->Disconnect();
			(void)HangupCall();
			ERROR_LOG() << "video call Failed.";
			return UC_SDK_Failed;
		}
	}

	return UC_SDK_Success;
}
int UCCallManager::UpdateConvMember(const std::string& _strAcct,EM_MemStatusInCall _status)
{
	ctk::Mutex::Lock lck(m_mtx);
	isConfStart = true;
	
	ConvMemberMap::iterator iter = m_ConvMemberMap.find(_strAcct);
	ConvMemberMap::iterator iterEnd = m_ConvMemberMap.end();
	if(iterEnd == iter )
	{
		if(_status == CONF_MEM_DEL)
		{
			WARN_LOG() << _strAcct << " is not conference member";
			return UC_SDK_Failed;
		}
		else
		{
			m_ConvMemberMap[_strAcct] = _status;
			return UC_SDK_Success;		
		}			
	}
	else
	{
		EM_MemStatusInCall oldStatus = (*iter).second;

		if(_status == CONF_MEM_DEL)
		{
			m_ConvMemberMap.erase(iter);
		}
		
		if(_status != oldStatus)
		{
			m_ConvMemberMap[_strAcct] = _status;
			return UC_SDK_Success;
		}
		else
		{
			INFO_LOG() << _strAcct << " status has not been changed.";
			return UC_SDK_Failed;
		}
	}	
}

int UCCallManager::ClearConvMember()
{
	ctk::Mutex::Lock lck(m_mtx);
	m_ConvMemberMap.clear();
	isConfStart = false;
	return UC_SDK_Success;
}
int UCCallManager::ClearCallMember()
{
	m_MemPhoneList.clear();
	m_MemUriList.clear();	
	return UC_SDK_Success;
}
int UCCallManager::ClearConvID()
{
	if(NULL != m_pConvMgr)
	{
		(void)m_pConvMgr->RemoveConversation(m_ConversationID);
	}
	else
	{
		ERROR_LOG() << "m_pConvMgr is null pointer";
	}
	INFO_LOG() << "Remove ConvID=" << m_ConversationID;
	m_ConversationID = "";
	return UC_SDK_Success;
}
bool UCCallManager::GetConvStarted()const
{
	return isConfStart;
}
int UCCallManager::CreateTempGroup()
{
	if (!m_ConversationID.empty())
	{
		ERROR_LOG() << "You are in tempGroup Now.";
		return UC_SDK_InTempGroupNow;
	}

	if (NULL == m_pConvMgr)
	{
		ERROR_LOG() << "m_pConvMgr is null pointer";
		return UC_SDK_NullPtr;
	}

	conversation::Conversation* pConversation = m_pConvMgr->AddConversation();
	if (NULL == pConversation)
	{
		ERROR_LOG() << "pConversation is null pointer";
		return UC_SDK_NullPtr;
	}

	m_ConversationID = pConversation->propmap_[conversation::ConvIdentifier];
	INFO_LOG() << "Add ConvID = " << m_ConversationID;

	pConversation->propmap_[conversation::ConvSubject] = "Default Chat";

	//add uc participant
	CallList::const_iterator it = m_MemUriList.begin();
	CallList::const_iterator iter_e = m_MemUriList.end();
	for (; it!=iter_e; it++)
	{
		Contact member;
		member.uri_ = *it;
		(void)UCContactMgr::Instance().getContactByUri(member.uri_, member);
		pConversation->AddParticipant(member);
	}

	//add IPphone participant
	it = m_MemPhoneList.begin();
	iter_e = m_MemPhoneList.end();
	for (; it!=iter_e; it++)
	{
		Contact member;
		member.uri_ = "";
		member.mobile_ = *it;
		member.name_ = member.mobile_;
		pConversation->AddParticipant(member);
	}

	//add IM session
	conversation::InstantMsgSession* pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConversation->AddSession(InstantMessage));
	if (NULL != pIMSess)
	{
		INFO_PARAM1(pIMSess);

		if(!pIMSess->Connect())
		{
			WARN_LOG() << "IMSession connect failed.";
		}
	}	

	//ad av session
	conversation::AVSession* pAVSess = dynamic_cast<conversation::AVSession*>(pConversation->AddSession(AudioVideo));
	if(NULL == pAVSess)
	{
		ERROR_LOG() << "pAVSess is NULL";
		return UC_SDK_Failed;
	}
	INFO_PARAM1(pAVSess);
	if(!pAVSess->Connect())
	{
		WARN_LOG() << "AVSession connect failed.";
	}

	ConectConfSignal(pConversation);
	return UC_SDK_Success;	
}

int UCCallManager::InviteMemberInCall(EM_MemberType memberType,const std::string& strAccount)
{
	conversation::Conversation* pConv = GetConversation();
	if (NULL == pConv)
	{
		ERROR_LOG() << "pConv is null.";
		return UC_SDK_Failed;
	}

	Contact _contact;
	std::string strUri;
	if(UC_ACCOUNT == memberType)
	{
		if (UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount, _contact))
		{
			ERROR_LOG() << "_strAccount is not uc account";			
			return UC_SDK_NotFound;
		}
		strUri = _contact.uri_;
	}
	else
	{
		strUri = strAccount;
		_contact.uri_ = "";
		_contact.mobile_ = strAccount;
		_contact.name_ = strAccount;
	}

	int nRet = GetMemberInCall(pConv,strUri,_contact);
	if (UC_SDK_Success == nRet)//成员已经在会议中，刷新会议成员状态
	{				
		WARN_LOG() << strAccount << " is already in conference" ;
		return UC_SDK_Failed;
	}
	else//不在会议中就更新本地成员状态
	{
		(void)UpdateConvMember(strAccount,CONF_MEM_DEL);
	}

	InstantMsgSession* pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConv->GetSession(InstantMessage));
	if(NULL == pIMSess)
	{
		pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConv->AddSession(InstantMessage));
	}
	if(NULL == pIMSess)
	{
		ERROR_LOG() << "pIMSess is null.";
		return UC_SDK_Failed;
	}
	
	if(SessionDisconnected == pIMSess->state_)
	{
		pConv->propmap_[conversation::ConvSubject] = "Default Chat";
		if(!pIMSess->Connect())
		{
			WARN_LOG() << "IMSession connect failed.";
		}
	}

	pConv->AddParticipant(_contact);
	if(UC_ACCOUNT == memberType)
	{		
		m_MemUriList.insert(_contact.uri_);
		(void)UCRegManager::Instance().SubscribeStatus(_contact.uri_);
	}
	else
	{
		m_MemPhoneList.insert(strAccount);
	}
	
	ConectConfSignal(pConv);

	return UC_SDK_Success;
}

int UCCallManager::DeleteMemberInCall(EM_MemberType _memberType,const std::string& strAccount)
{
	conversation::Conversation* pConversation = GetConversation();
	if (NULL == pConversation)
	{
		ERROR_LOG() << "pConv is null.";
		return UC_SDK_Failed;
	}

	Contact _contact;
	std::string strUri;
	if(UC_ACCOUNT == _memberType)
	{
		if (UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount, _contact))
		{
			ERROR_LOG() << "getContactByAccount failed.";
			return UC_SDK_NotFound;
		}
		strUri = _contact.uri_;
	}
	else
	{
		strUri = strAccount;
		_contact.uri_ = "";
		_contact.mobile_ = strAccount;
		_contact.name_ = strAccount;
	}

	if(UC_ACCOUNT == _memberType)
	{
		CallList::iterator iter = m_MemUriList.find(_contact.uri_);
		if (iter != m_MemUriList.end())
		{
			m_MemUriList.erase(iter);
			(void)UCRegManager::Instance().DisSubscribeStatus(_contact.uri_);
		}		
	}
	else
	{
		CallList::iterator iter = m_MemPhoneList.find(_contact.uri_);
		if (iter != m_MemPhoneList.end())
		{
			m_MemPhoneList.erase(iter);
		}
	}
	
	int nRet = GetMemberInCall(pConversation,strUri,_contact);

	if (UC_SDK_Success != nRet)//成员已经不在会议中
	{	
		(void)UpdateConvMember(strAccount,CONF_MEM_DEL);
		return UC_SDK_Success;
	}

	//删除成员
	if(!pConversation->RemoveParticipant(_contact))
	{
		ERROR_LOG() << "RemoveParticipant failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}
int UCCallManager::ModifyMemberStatusInCall(EM_ConvnerOperateType operateType, EM_MemberType _memberType, const std::string& strAccount)
{
	DEBUG_LOG() << "--- Enter";
	conversation::Conversation* pConv  = GetConversation();
	if (NULL == pConv)
	{
		ERROR_LOG() << "pConv is null.";
		return UC_SDK_Failed;
	}

	Contact _contact;
	std::string strUri;
	if(UC_ACCOUNT == _memberType)
	{
		if (UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount, _contact))
		{
			ERROR_LOG() << "getContactByAccount failed.";
			return UC_SDK_FindUriErr;
		}
		strUri = _contact.uri_;
	}
	else
	{
		strUri = strAccount;
		_contact.uri_ = "";
		_contact.mobile_ = strAccount;
		_contact.name_ = strAccount;		
	}

	int nRet = GetMemberInCall(pConv,strUri,_contact);
	if (UC_SDK_Success != nRet)//成员已经不在会议中
	{	
		ERROR_LOG() << "Cannot modify member status.";

		return UC_SDK_Failed;
	}

	uc::model::conversation::Participant part_;
	part_.contact_ = _contact;

	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pAVSess is Null.";
		return UC_SDK_NullPtr;
	}

	//结束某成员的通话
	if(EndCallMember == operateType)
	{
		pAVSess->KickParticipant(part_);
	}
	//重新呼叫某成员
	else if(ReInviteMember == operateType)
	{
		(void)UpdateConvMember(strAccount,CONF_MEM_INVITING);		
		InstantMsgSession* pIMSess = dynamic_cast<conversation::InstantMsgSession*>(pConv->GetSession(InstantMessage));
		if(NULL != pIMSess)
		{
			pIMSess->ConnectParticipant(part_);
		}
		pAVSess->ConnectParticipant(part_);
	}
	//对某成员静音
	else if(MuteMember == operateType)
	{
		std::vector<uc::model::conversation::Participant> partlist_;
		partlist_.push_back(part_);
		pConv->Mute(partlist_);
	}
	//对某成员取消静音
	else if(UnMuteMember == operateType)
	{
		std::vector<uc::model::conversation::Participant> partlist_;
		partlist_.push_back(part_);
		pConv->UnMute(partlist_);
	}
	else
	{
		ERROR_LOG() << "Invalid operateType.";
		return UC_SDK_Failed;
	}

	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;
}
int UCCallManager::HangupCall(void)
{	
	ctk::Mutex::Lock lck(m_ConvMutex);
	//挂断语音
	DEBUG_LOG() << "--- ENTER";
	conversation::AVSession* pAVSess = GetAVSession();
	if(NULL != pAVSess)
	{
		DisConectVideoSignal(pAVSess);
		if(!pAVSess->Disconnect())
		{
			WARN_LOG() << "Disconnect AVSesion failed.";
		}
	}

	//挂断临时群
	InstantMsgSession* pIMSess = GetIMSession();
	if(NULL != pIMSess)
	{
		pIMSess->Disconnect();
	}

	if (NULL != m_pConvMgr && !m_ConversationID.empty())
	{
		conversation::Conversation* pConversation = m_pConvMgr->GetConversation(m_ConversationID);
		if (NULL != pConversation)
		{
			pConversation->RemoveSession(AudioVideo);
			pConversation->RemoveSession(InstantMessage);
			pConversation->End();
			
		}
		(void)ClearConvID();
	}
	
	//删除用户列表
	m_MemUriList.clear();
	m_MemPhoneList.clear();

	//停止响铃
	(void)UCTonePlay::Instance().EndPlay();

	//清除成员
	(void)UCCallManager::Instance().ClearConvMember();

	DEBUG_LOG() << "--- LEAVE";

	return UC_SDK_Success;
}

int UCCallManager::HangupVideoCall(void)
{
	//挂断语音
	DEBUG_LOG() << "--- ENTER";
	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}

	pAVSess->videochannel_.Stop();
	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;
}
int UCCallManager::AcceptCall(void)
{
	if(NULL == m_pConvMgr)
	{
		ERROR_LOG() << "ConvManager is Null Pointer";
		return UC_SDK_NullPtr;
	}

	if(m_ConversationID.empty())
	{
		ERROR_LOG() << "No Call";
		return UC_SDK_Failed;
	}

	conversation::Conversation* pConv = m_pConvMgr->GetConversation(m_ConversationID);
	if (NULL == pConv)
	{
		ERROR_LOG() << "pConv is Null Pointer";
		return UC_SDK_NullPtr;
	}

	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}


	ConectVideoSignal(pAVSess);
	if(!pAVSess->Accept())
	{
		ERROR_LOG() << "Accept call failed";
		pAVSess->Disconnect();
		(void)HangupCall();
		return UC_SDK_Failed;
	}	
	
	return UC_SDK_Success;
}
int UCCallManager::AcceptVideoCall(const STVideoWindow& stLocalWnd,const STVideoWindow& stRemoteWnd)
{
	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}

	//设置视频信息
	pAVSess->videochannel_.localwnd_.width_ = stLocalWnd.width;
	pAVSess->videochannel_.localwnd_.height_ = stLocalWnd.height;
	pAVSess->videochannel_.localwnd_.left_ = stLocalWnd.left;
	pAVSess->videochannel_.localwnd_.top_ = stLocalWnd.top;
	pAVSess->videochannel_.localwnd_.wnd_ = (HWND)stLocalWnd.hWnd;

	pAVSess->videochannel_.remotewnd_.width_ = stRemoteWnd.width;
	pAVSess->videochannel_.remotewnd_.height_ = stRemoteWnd.height;
	pAVSess->videochannel_.remotewnd_.left_ = stRemoteWnd.left;
	pAVSess->videochannel_.remotewnd_.top_ = stRemoteWnd.top;
	pAVSess->videochannel_.remotewnd_.wnd_ = (HWND)stRemoteWnd.hWnd;

	if(conversation::SessionConnected != pAVSess->state_)
	{
		ConectVideoSignal(pAVSess);
		if (!pAVSess->Accept())
		{
			ERROR_LOG() << "Accept video call failed";
			pAVSess->Disconnect();
			(void)HangupCall();
			return UC_SDK_Failed;
		}
	}
	else
	{
		if (!pAVSess->videochannel_.Start())
		{
			ERROR_LOG() << "accept video call failed. ";
			return UC_SDK_Failed;
		}
	}

	return UC_SDK_Success;

}
int UCCallManager::RejectCall(void)
{
	if(NULL == m_pConvMgr)
	{
		ERROR_LOG() << "ConvManager is Null Pointer";
		return UC_SDK_NullPtr;
	}

	if(m_ConversationID.empty())
	{
		ERROR_LOG() << "No Call";
		return UC_SDK_Failed;
	}

	conversation::Conversation* pConversation = m_pConvMgr->GetConversation(m_ConversationID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "pConversation is Null Pointer";
		return UC_SDK_NullPtr;
	}

	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}

	if(pAVSess->Reject())
	{
		pConversation->RemoveSession(AudioVideo);
		m_ConversationID = "";
	}


	//停止响铃
	(void)UCTonePlay::Instance().EndPlay();

	//清除成员
	(void)ClearConvMember();

	return UC_SDK_Success;
}
int UCCallManager::RejectCall(const std::string& conversationID)
{
	DEBUG_LOG() << "Enter the function which to reject the new call.";
	if(NULL == m_pConvMgr)
	{
		ERROR_LOG() << "ConvManager is Null Pointer";
		return UC_SDK_NullPtr;
	}

	if (conversationID.empty())
	{
		ERROR_LOG() << "No new Call";
		return UC_SDK_Failed;
	}

	conversation::Conversation* pConversation = m_pConvMgr->GetConversation(conversationID);
	if (NULL == pConversation)
	{
		ERROR_LOG() << "pConversation is Null Pointer";
		return UC_SDK_NullPtr;
	}

	conversation::AVSession* pAVSess = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}
	
	if(pAVSess->Reject())
	{
		pConversation->RemoveSession(AudioVideo);
	}
	return UC_SDK_Success;
}
int UCCallManager::RejectVideoCall(void)
{
	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}


	if(!pAVSess->videochannel_.Stop())
	{
		ERROR_LOG() << "reject video failed";
		return UC_SDK_NullPtr;
	}

	//判断是否挂断语音
	if(conversation::avchannel::ChannelConnecting == pAVSess->audiochannel_.state_)
	{
		(void)RejectCall();
	}

	return UC_SDK_Success;

}
int UCCallManager::SendDTMF(char tone)
{
	conversation::AVSession* pAVSess = GetAVSession();
	if (NULL == pAVSess)
	{
		ERROR_LOG() << "pSess is Null Pointer";
		return UC_SDK_NullPtr;
	}

	//检测DTMF
	if (('0' <= tone && '9' >= tone) || '*' == tone || '#' == tone)		// #*0123456789
	{
		//发送DTMF
		std::string strDTMF;
		strDTMF.append(&tone);
		INFO_PARAM1(strDTMF);
		(void)UCTonePlay::Instance().PlayDTMFTone(tone);
		int iRet = pAVSess->audiochannel_.SendDTMF(strDTMF);		
		return iRet;
	}
	else
	{
		ERROR_LOG() << "tones have Error Number";
		return UC_SDK_InvalidPara;
	}
}
int UCCallManager::ForwardCall(EM_MemberType iMemberType, const std::string& strMember)
{
	conversation::AVSession* pSess = AddAVSession();
	if (NULL == pSess)
	{
		ERROR_LOG() << "pSess is null pointer.";
		return UC_SDK_NullPtr;
	}

	Contact contact;
	if (UC_ACCOUNT == iMemberType)
	{
		if (UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strMember, contact))
		{
			ERROR_LOG() << "getContactByAccount failed.";
			return UC_SDK_FindUriErr;
		}
	}
	else if (UC_IPPHONE == iMemberType)
	{
		contact.uri_ = "";
		contact.mobile_ = strMember;
		contact.name_ = strMember;
	}
	else
	{
		ERROR_LOG() << "iMemberType is invalid.";
		return UC_SDK_InvalidPara;
	}

	if (!pSess->Forward(contact))
	{
		ERROR_LOG() << "Forward failed.";
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}
int UCCallManager::SetCallEventCB(AVSessionClosedCB aVSessionClosedCallBack,
						  AVSessionConnectedCB aVSessionConnectedCallBack,
						  AVSessAddedCB aVSessAddedCallBack)
{
	if (NULL == m_pConvMgr)
	{
		ERROR_LOG() << "ConvManager is Null Pointer";
		return UC_SDK_NullPtr;
	}

	//删除连接信号
	m_pConvMgr->AVSessionClosed.disconnect_all();
	m_pConvMgr->AVSessionConnected.disconnect_all();
	m_pConvMgr->AVSessAdded.disconnect_all();
	m_pConvMgr->AVSessionRinged.disconnect_all();

	//连接呼叫信号
	m_pConvMgr->AVSessionRinged.connect(&m_CallEvent, &CallEvent::OnCallRing);
	m_pConvMgr->AVSessionClosed.connect(&m_CallEvent, &CallEvent::OnCallClosed);
	m_pConvMgr->AVSessionConnected.connect(&m_CallEvent, &CallEvent::OnCallConnected);
	m_pConvMgr->AVSessAdded.connect(&m_CallEvent, &CallEvent::OnCallIncoming);

	OnAVSessionClosedCB = aVSessionClosedCallBack;
	OnAVSessionConnectedCB = aVSessionConnectedCallBack;
	OnAVSessAddedCB = aVSessAddedCallBack;

	return UC_SDK_Success;
}

int UCCallManager::SetCallEventCB(VideoCallEventCB callEventCallBack)const
{
	OnVideoCallEventCB = callEventCallBack;
	return UC_SDK_Success;
}
int UCCallManager::SetConfMemEventCB(ConfMemberEventCB _confmemberEventCB)const
{
	OnConfMemberEventCB = _confmemberEventCB;
	return UC_SDK_Success;
}
conversation::AVSession* UCCallManager::GetAVSession()
{
	conversation::Conversation* pConversation = NULL;
	conversation::AVSession* pAVSession = NULL;

	if(!m_ConversationID.empty() && NULL != m_pConvMgr)
	{
		pConversation = m_pConvMgr->GetConversation(m_ConversationID);
		if (NULL != pConversation)
		{
			pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->GetSession(AudioVideo));
		}
	}

	return pAVSession;
}
conversation::InstantMsgSession* UCCallManager::GetIMSession()
{
	conversation::Conversation* pConversation = NULL;
	conversation::InstantMsgSession* pIMSession = NULL;

	if(!m_ConversationID.empty() && NULL != m_pConvMgr)
	{
		pConversation = m_pConvMgr->GetConversation(m_ConversationID);
		if (NULL != pConversation)
		{
			pIMSession = dynamic_cast<conversation::InstantMsgSession*>(pConversation->GetSession(InstantMessage));
		}
	}

	return pIMSession;

}
conversation::AVSession* UCCallManager::AddAVSession()
{
	conversation::Conversation* pConversation = NULL;
	conversation::AVSession* pAVSession = NULL;

	if(!m_ConversationID.empty() && NULL != m_pConvMgr)
	{
		pConversation = m_pConvMgr->GetConversation(m_ConversationID);
		if (NULL != pConversation)
		{
			pAVSession = dynamic_cast<conversation::AVSession*>(pConversation->AddSession(AudioVideo));
		}
	}

	return pAVSession;
}
conversation::Conversation* UCCallManager::GetConversation()
{
	conversation::Conversation* pConversation = NULL;

	if(NULL == m_pConvMgr)
	{
		ERROR_LOG() << "ConvManager is Null Pointer";
		return pConversation;
	}

	if(!m_ConversationID.empty())
	{
		pConversation = m_pConvMgr->GetConversation(m_ConversationID);
	}

	if(NULL == pConversation)
	{
		pConversation = m_pConvMgr->AddConversation();
		if (NULL == pConversation)
		{
			ERROR_LOG() << "add conversation failed.";
			return pConversation;
		}

		m_ConversationID = pConversation->propmap_[conversation::ConvIdentifier];
		INFO_LOG() << "Add ConvID = " << m_ConversationID;
	}

	return pConversation;
}
void UCCallManager::ShowConvMember(conversation::Conversation* _pConv)
{
	if (NULL == _pConv)
	{
		ERROR_LOG() << "_pConv is Null.";
		return;
	}

	conversation::Conversation::MemList_::iterator itor = _pConv->members_.begin();
	conversation::Conversation::MemList_::const_iterator itorEnd = _pConv->members_.end();
	for(;itor!=itorEnd;itor++)
	{
		std::string uri = (*itor).first;
		std::string ucAcc = (*itor).second->contact_.ucAcc_;
		INFO_PARAM2(uri,ucAcc);
	}

	ConvMemberMap::iterator iter = m_ConvMemberMap.begin();
	ConvMemberMap::iterator iterEnd = m_ConvMemberMap.end();
	for(;iter!=iterEnd;iter++)
	{
		std::string ucAcc = (*iter).first;
		EM_MemStatusInCall status = (*iter).second;
		INFO_PARAM2(ucAcc,status);
	}

}
int UCCallManager::GetMemberInCall(conversation::Conversation* _pConv,const std::string& strUri,Contact& _contact)
{
	if (NULL == _pConv)
	{
		ERROR_LOG() << "_pConv is Null.";
		return UC_SDK_NullPtr;
	}

	INFO_PARAM1(strUri);

	ShowConvMember(_pConv);

	conversation::Conversation::MemList_::const_iterator itorfind = _pConv->members_.find(strUri);
	conversation::Conversation::MemList_::const_iterator itorEnd = _pConv->members_.end();
	if(itorEnd == itorfind)//没找到
	{
		WARN_LOG() << strUri << " is not in conference.";
		return UC_SDK_NotFound;
	}
	else
	{
		//INFO_LOG() << strUri << " is in conference.";
		_contact.uri_ = (*itorfind).second->contact_.uri_;
		_contact.ucAcc_ = (*itorfind).second->contact_.ucAcc_;
		_contact.name_ = (*itorfind).second->contact_.name_;
		_contact.mobile_ = (*itorfind).second->contact_.mobile_;
		_contact.ipphone1_ = (*itorfind).second->contact_.ipphone1_;
		_contact.ipphone2_ = (*itorfind).second->contact_.ipphone2_;
		return UC_SDK_Success;
	}


}

void UCCallManager::ConectConfSignal(conversation::Conversation* pConv) 
{
	if(NULL == pConv)
	{
		WARN_LOG() << "pConv is null.";
		return;
	}

	if(NULL == m_pConvMgr)
	{
		WARN_LOG() << "ConvMgr is null.";
		return;
	}

	if(!pConv->InstantSessConnected.isconnected(&m_ConferenceEvent))
	{
		pConv->InstantSessConnected.connect(&m_ConferenceEvent, &ConfEvent::OnConvIMConnected);
	}
	if(!pConv->ConvMemberStatusChanged.isconnected(&m_ConferenceEvent))
	{
		pConv->ConvMemberStatusChanged.connect(&m_ConferenceEvent, &ConfEvent::OnConvStatusChanged);
	}
	if(!pConv->ConvMemAllowSpeak.isconnected(&m_ConferenceEvent))
	{
		pConv->ConvMemAllowSpeak.connect(&m_ConferenceEvent, &ConfEvent::OnConvAllowSpk);
	}
	if(!pConv->ConvMemForbidSpeak.isconnected(&m_ConferenceEvent))
	{
		pConv->ConvMemForbidSpeak.connect(&m_ConferenceEvent, &ConfEvent::OnConvForbidSpk);
	}
	if(!pConv->ConvCurSpeaker.isconnected(&m_ConferenceEvent))
	{
		pConv->ConvCurSpeaker.connect(&m_ConferenceEvent, &ConfEvent::OnConvCurSpker);
	}
	if(!m_pConvMgr->ConvGroupMemberChanged.isconnected(&m_ConferenceEvent))
	{
		m_pConvMgr->ConvGroupMemberChanged.connect(&m_ConferenceEvent,&ConfEvent::OnConvNumChanged);
	}	
	if(!pConv->ConfDelMemSucc.isconnected(&m_ConferenceEvent))
	{
		pConv->ConfDelMemSucc.connect(&m_ConferenceEvent,&ConfEvent::OnConvDelSucc);
	}
	if(!pConv->ConvRequstToSpeak.isconnected(&m_ConferenceEvent))
	{
		pConv->ConvRequstToSpeak.connect(&m_ConferenceEvent,&ConfEvent::OnConvRequestToSpeak);
	}
	if(!pConv->InstantSessMerged.isconnected(&m_ConferenceEvent))
	{
		pConv->InstantSessMerged.connect(&m_ConferenceEvent,&ConfEvent::OnInstantSessMerged);
	}
	if(!pConv->MuteAllSuc.isconnected(&m_ConferenceEvent))
	{
		pConv->MuteAllSuc.connect(&m_ConferenceEvent,&ConfEvent::OnMuteAllAttender);
	}	
	if(!pConv->ConvSetVideoSource.isconnected(&m_ConferenceEvent))
	{
		pConv->ConvSetVideoSource.connect(&m_ConferenceEvent,&ConfEvent::OnSetVideoSource);
	}

}
void UCCallManager::DisConectConfSignal(conversation::Conversation* pConv)const
{
	if(NULL == pConv)
	{
		WARN_LOG() << "pConv is null.";
		return;
	}
	pConv->InstantSessConnected.disconnect_all();
	pConv->ConvMemberStatusChanged.disconnect_all();
	pConv->ConvMemAllowSpeak.disconnect_all();
	pConv->ConvMemForbidSpeak.disconnect_all();
	pConv->ConvCurSpeaker.disconnect_all();	
	pConv->ConfDelMemSucc.disconnect_all();
	pConv->ConvRequstToSpeak.disconnect_all();
	pConv->InstantSessMerged.disconnect_all();
	pConv->MuteAllSuc.disconnect_all();
	pConv->ConvSetVideoSource.disconnect_all();

	if(NULL == m_pConvMgr)
	{
		WARN_LOG() << "pConvMgr is null.";
		return;
	}
	m_pConvMgr->ConvGroupMemberChanged.disconnect_all();

}

void UCCallManager::ConectVideoSignal(conversation::AVSession* _pAVSess)
{
	if(NULL == _pAVSess)
	{
		WARN_LOG() << "AVSess is NULL";
		return;
	}

	if(!_pAVSess->videochannel_.ChannelStateChanged.isconnected(&m_VideoEvent))
	{
		_pAVSess->videochannel_.ChannelStateChanged.connect(&m_VideoEvent,&VideoChannelEvent::OnChannelStateChanged);
	}

	return;
}
void UCCallManager::DisConectVideoSignal(conversation::AVSession* _pAVSess)const
{
	if(NULL == _pAVSess)
	{
		WARN_LOG() << "AVSess is NULL";
		return;
	}

	_pAVSess->videochannel_.ChannelStateChanged.disconnect_all();

	return;
}




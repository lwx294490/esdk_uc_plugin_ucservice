#include "StdAfx.h"
#include "UCEventMgr.h"
#include "UCCallManager.h"
#include "UCContactMgr.h"
#include "UCConfigMgr.h"
#include "UCRegManager.h"

UCEventMgr::UCEventMgr()
{
	m_pAgent = NULL;
}
UCEventMgr::~UCEventMgr()
{
	try
	{
		WaitAgentStart();
		m_pAgent = NULL;
	}
	catch(...)
	{
	}
}
void UCEventMgr::WaitAgentStart() const
{
	if(NULL != m_pAgent)
	{
		while(m_pAgent->living())
		{
			INFO_LOG() << "wait thread [" << m_pAgent->id().id_<<"] live";
			Sleep(100);
		}
	}

}
void UCEventMgr::NotifyStatusEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";
	//WaitAgentStart();
	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(CONTACT_STATUS_EVENT,_strPara);
	m_pAgent->start();
	DEBUG_LOG() << "--- LEAVE";
	return;
}
void UCEventMgr::NotifyPubPJEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";
	WaitAgentStart();
	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(PUB_PJ_EVENT,_strPara);
	m_pAgent->start();
	DEBUG_LOG() << "--- LEAVE";
	return;
}
void UCEventMgr::NotifyCallCloseEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";

	WaitAgentStart();

	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(CALL_CLOSE_EVENT,_strPara);
	m_pAgent->start();

	DEBUG_LOG() << "--- LEAVE";
	return;

}

void UCEventMgr::NotifyCallConnectedEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";

	WaitAgentStart();

	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(CALL_CONNECT_EVENT,_strPara);
	m_pAgent->start();

	DEBUG_LOG() << "--- LEAVE";
	return;
}

void UCEventMgr::NotifyVideoEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";

	WaitAgentStart();

	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(VIDEO_EVENT,_strPara);
	m_pAgent->start();

	DEBUG_LOG() << "--- LEAVE";
	return;

}
void UCEventMgr::NotifyCallIncomingEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";
	WaitAgentStart();
	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(CALL_INCOMING_EVENT,_strPara);
	m_pAgent->start();
	DEBUG_LOG() << "--- LEAVE";
	return;
}
void UCEventMgr::NotifyConvMemEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";
	WaitAgentStart();
	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(CONV_EVENT,_strPara);
	m_pAgent->start();
	DEBUG_LOG() << "--- LEAVE";
	return;

}
void UCEventMgr::NotifyPJEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";
	WaitAgentStart();
	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(PJ_NOTIFY_EVENT,_strPara);
	m_pAgent->start();
	DEBUG_LOG() << "--- LEAVE";
	return;
}
void UCEventMgr::NotifyRejectNewCallEvent(const std::string& _strPara)
{
	DEBUG_LOG() << "--- ENTER";
	WaitAgentStart();
	m_pAgent = new EventAgent(this);
	m_pAgent->SetEventPara(RejectNewCall_EVENT,_strPara);
	m_pAgent->start();
	DEBUG_LOG() << "--- LEAVE";
	return;
}
void UCEventMgr::onThreadExit(ctk::Thread* _thr)
{
	if(NULL == _thr)
	{
		ERROR_LOG() << "thread is null";
		return;
	}
	ctk::ThreadId::type threadId = _thr->id().id_;
	INFO_PARAM1(threadId);
}

void UCEventMgr::EventAgent::run()
{
	ctk::ThreadId::type threadId = id().id_;
	INFO_PARAM1(threadId);
	OnNotifyEvent();
}
void UCEventMgr::EventAgent::SetEventPara(EventType _eventType,const std::string& _strPara)
{
	m_eventType = _eventType;
	m_EventPara = _strPara;
}
bool UCEventMgr::EventAgent::OnNotifyEvent()
{
	if(m_EventPara.empty())
	{
		WARN_LOG() << "m_EventPara is empty.";
		return false;
	}

	switch (m_eventType)
	{
	case REG_EVENT:
		{
			break;
		}
	case CALL_CLOSE_EVENT:
		{
			NotifyCallClosed();
			break;
		}
	case CALL_CONNECT_EVENT:
		{
			NotifyCallConnect();
			break;
		}
	case CALL_INCOMING_EVENT:
		{
			NotifyCallIncoming();
			break;
		}
	case CONV_EVENT:
		{
			NotifyConv();			
			break;
		}
	case VIDEO_EVENT:
		{
			NotifyVideo();
			break;
		}
	case PJ_NOTIFY_EVENT:
		{
			NotifyPhoneJointCB();
			break;
		}
	case RejectNewCall_EVENT:
		{
			NotifyRejectNewCall();
			break;
		}
	case PUB_PJ_EVENT:
		{
			NotifyPublishPJ();
			break;
		}
	case CONTACT_STATUS_EVENT:
		{
			NotifyContactStatus();
			break;		
		}

	default:
		break;
	}

	m_EventPara.clear();
	return true;
}
void UCEventMgr::EventAgent::NotifyConv(void) const
{
	if(NULL == UCCallManager::OnConfMemberEventCB)
	{
		WARN_LOG() << "OnConfMemberEventCB is NULL.";
		return;
	}

	INFO_PARAM1(m_EventPara);

	STConfParam item;
	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string membType;
	xmlStr["type"] >> membType;

	if("UCAccount" == membType)
	{
		item.memType = UC_ACCOUNT;
	}
	else if("IPPhone" == membType)
	{
		item.memType = UC_IPPHONE;
	}
	else
	{
		WARN_LOG() << "Event Para membType is invalid";
		return;
	}

	std::string membStatus;
	xmlStr["status"] >> membStatus;	
	if("Inviting" == membStatus)
	{
		item.memStatus = CONF_MEM_INVITING;
	}
	else if("Hangup" == membStatus)
	{
		item.memStatus = CONF_MEM_HANGUP;
	}
	else if("Quit" == membStatus)
	{
		item.memStatus = CONF_MEM_QUIT;
	}
	else if("Mute" == membStatus)
	{
		item.memStatus = CONF_MEM_MUTE;
	}
	else if("UnMute" == membStatus)
	{
		item.memStatus = CONF_MEM_UnMute;
	}
	else if("Speaking" == membStatus)
	{
		item.memStatus = CONF_MEM_SPK;
	}
	else if("Delete" == membStatus)
	{
		item.memStatus = CONF_MEM_DEL;
	}
	else if("Add" == membStatus)
	{
		item.memStatus = CONF_MEM_ADD;
	}
	else
	{
		WARN_LOG() << "Event Para membStatus is invalid";
		return;
	}

	std::string membAccount;
	xmlStr["account"] >> membAccount;
	ctk::MemSet(item.ucAcc,0,STRING_LENGTH);
	ctk::MemCopy(item.ucAcc,membAccount.c_str(),(membAccount.size()<(STRING_LENGTH)) ? (membAccount.size()) : (STRING_LENGTH-1));


	if(CONF_MEM_SPK == item.memStatus)
	{
		//speak状态提前处理
		UCCallManager::OnConfMemberEventCB(item);
	}
	else
	{
		if(UC_SDK_Success == UCCallManager::Instance().UpdateConvMember(membAccount,(EM_MemStatusInCall)item.memStatus))
		{
			UCCallManager::OnConfMemberEventCB(item);
			if(CONF_MEM_ADD == item.memStatus)
			{
				//增加成员时，推送一下在线状态
				ctk::xml::XMLOutStream eventXML("event");
				Contact _cont;
				(void)UCContactMgr::Instance().getContactByAccount(membAccount,_cont);
				eventXML["caller"] << _cont.uri_;
				UCEventMgr::Instance().NotifyStatusEvent(eventXML.str());
			}
		}
	}
}
void UCEventMgr::EventAgent::NotifyCallClosed() const
{
	INFO_PARAM1(m_EventPara);
	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string id;
	xmlStr["id"] >> id;
	std::string callerNum;
	xmlStr["callerNum"] >> callerNum;
	std::string reason;
	xmlStr["reason"] >> reason;
	std::string conversationId;
	xmlStr["conversationId"] >> conversationId;

	if (conversationId == UCCallManager::Instance().GetConvID())
	{
		(void)UCCallManager::Instance().ClearCallMember();
		(void)UCCallManager::Instance().ClearConvMember();
		(void)UCCallManager::Instance().ClearConvID();
	}

	if(NULL == UCCallManager::OnAVSessionClosedCB)
	{
		ERROR_LOG() << "UCCallManager::OnAVSessionClosedCB is null.";
		return;
	}

	STMsgAVSessionClosedParam item = {0};
	(void)strcpy_s(item.AVSessionId_,id.c_str());
	(void)strcpy_s(item.callerUri_,callerNum.c_str());
	(void)strcpy_s(item.reason_,reason.c_str());

	DEBUG_LOG() << "--- OnAVSessionClosedCB ENTER ";
	UCCallManager::OnAVSessionClosedCB(item);
	DEBUG_LOG() << "--- OnAVSessionClosedCB LEAVE ";
}
void UCEventMgr::EventAgent::NotifyCallConnect() const
{
	if (NULL == UCCallManager::OnAVSessionConnectedCB)
	{
		WARN_LOG() << "OnAVSessionConnectedCB is null";
		return;
	}

	INFO_PARAM1(m_EventPara);

	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string caller;
	xmlStr["caller"] >> caller;  
	std::string conID ;
	xmlStr["convid"] >> conID;

	DEBUG_LOG() << "--- OnAVSessionConnectedCB ENTER ";
	UCCallManager::OnAVSessionConnectedCB();
	DEBUG_LOG() << "--- OnAVSessionConnectedCB LEAVE ";

}
void UCEventMgr::EventAgent::NotifyCallIncoming() const
{
	if (NULL == UCCallManager::OnAVSessAddedCB)
	{
		WARN_LOG() << "OnAVSessAddedCB is null";
		return;
	}

	INFO_PARAM1(m_EventPara);
	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string callerUri;
	xmlStr["callerUri"] >> callerUri;
	std::string video;
	xmlStr["video"] >> video;
	std::string callmode;
	xmlStr["callmode"] >> callmode;
	std::string accountType;
	xmlStr["accounttype"] >> accountType;

	STAudioVideoParam item = {0};
	item.isvideo_ = 0;
	item.callMode = 0;
	item.AccountType = 0;
	Contact ctact;
	if(eSDKTool::IsValidUri(callerUri))
	{
		if(UC_SDK_Success == UCContactMgr::Instance().getContactByUri(callerUri,ctact))
		{
			ctk::MemSet(item.ucAcc,0,STRING_LENGTH);
			ctk::MemCopy(item.ucAcc,ctact.ucAcc_.c_str(),(ctact.ucAcc_.size()<(STRING_LENGTH)) ? (ctact.ucAcc_.size()) : (STRING_LENGTH-1));
		}
		else
		{
			ctk::MemSet(item.ucAcc,0,STRING_LENGTH);
			ctk::MemCopy(item.ucAcc,callerUri.c_str(),(callerUri.size()<(STRING_LENGTH)) ? (callerUri.size()) : (STRING_LENGTH-1));
		}
	}
	else
	{
		ctk::MemSet(item.ucAcc,0,STRING_LENGTH);
		ctk::MemCopy(item.ucAcc,callerUri.c_str(),(callerUri.size()<(STRING_LENGTH)) ? (callerUri.size()) : (STRING_LENGTH-1));
	}
	
	if("true" == video)
	{
		item.isvideo_ = 1;
	}
	if("IPPhone" == callmode)
	{
		item.callMode = 1;
	}
	if("IPPhone" == accountType)
	{
		item.AccountType = 1;
	}

	DEBUG_LOG() << "--- OnAVSessAddedCB ENTER ";
	UCCallManager::OnAVSessAddedCB(item);
	DEBUG_LOG() << "--- OnAVSessAddedCB LEAVE ";
}


void UCEventMgr::EventAgent::NotifyVideo() const
{
	if(NULL == UCCallManager::OnVideoCallEventCB)
	{
		WARN_LOG() << "OnVideoCallEventCB is null";
		return;
	}

	INFO_PARAM1(m_EventPara);
	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string strVideoState;
	xmlStr["video"] >> strVideoState;
	std::string strAcc;
	xmlStr["account"] >> strAcc;
	STVideoCallParam st={0};
	ctk::MemSet(st.ucAcc,0,STRING_LENGTH);
	ctk::MemCopy(st.ucAcc,strAcc.c_str(),(strAcc.size()<(STRING_LENGTH)) ? (strAcc.size()) : (STRING_LENGTH-1));

	if("connecting" == strVideoState)
	{
		st.callStatus = CALL_VIDEO_REQ;
	}
	else if("connected" == strVideoState)
	{
		st.callStatus = CALL_VIDEO_CONNECTED;
	}
	else
	{
		st.callStatus = CALL_VIDEO_CLOSE;
	}

	DEBUG_LOG() << "--- OnVideoCallEventCB ENTER ";
	UCCallManager::OnVideoCallEventCB(st);
	DEBUG_LOG() << "--- OnVideoCallEventCB LEAVE ";

}
void UCEventMgr::EventAgent::NotifyPhoneJointCB() const
{

	INFO_PARAM1(m_EventPara);

	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string strStatus;
	xmlStr["status"] >> strStatus;
	int iStatus = -1;
	if("0" == strStatus)
	{
		iStatus = STATUS_START_SUCC;
	}
	else if("1" == strStatus)
	{
		iStatus = STATUS_START_FAILED;
	}
	else if("2" == strStatus)
	{
		iStatus = STATUS_STOP_SUCC;
	}
	else if("3" == strStatus)
	{
		iStatus = STATUS_STOP_FAILED;
	}
	else if("4" == strStatus)
	{
		iStatus = STATUS_ONLINE;
	}
	else if("5" == strStatus)
	{
		iStatus = STATUS_OFFLINE;
	}
	else if("6" == strStatus)
	{
		iStatus = STATUS_OFFHOOK;
	}

	if(NULL == UCConfigMgr::m_OnPJEventCB)
	{
		WARN_LOG() << "m_OnPJEventCB is null";
		return;
	}

	DEBUG_LOG() << "--- OnPJEventCB ENTER ";
	UCConfigMgr::m_OnPJEventCB((EM_PhoneJointStatusType)iStatus);
	DEBUG_LOG() << "--- OnPJEventCB LEAVE ";

	return;
}
void UCEventMgr::EventAgent::NotifyRejectNewCall(void) const
{
	INFO_PARAM1(m_EventPara);
	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string conversationID;
	xmlStr["conversationID"] >> conversationID;

	(void)UCCallManager::Instance().RejectCall(conversationID);

}
void UCEventMgr::EventAgent::NotifyPublishPJ(void) const
{
	INFO_PARAM1(m_EventPara);
	int iType = -1;
	if(UC_SDK_Success == UCConfigMgr::Instance().GetPhoneJointDevType(iType))
	{
		(void)UCConfigMgr::Instance().SetPhoneJointDevType(iType);
	}
}
void UCEventMgr::EventAgent::NotifyContactStatus(void) const
{
	INFO_PARAM1(m_EventPara);
	ctk::xml::XMLInStream xmlStr(m_EventPara);
	std::string uri;
	xmlStr["caller"] >> uri;

	Contact _contact;
	if(UC_SDK_Success != UCContactMgr::Instance().getContactByUri(uri,_contact))
	{
		return;
	}

	if(NULL == UCRegManager::Instance().m_pSubscribeMgr)
	{
		WARN_LOG() << "m_pSubscribeMgr is null";
		return;
	}

	std::string _desc;
	ContactAvailability _state = UCRegManager::Instance().m_pSubscribeMgr->GetContactStatus(uri,_desc);
	(void)UCRegManager::Instance().NotifyStatus(_contact,_state,_desc);
}


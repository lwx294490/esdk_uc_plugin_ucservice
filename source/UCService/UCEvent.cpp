//lint -e1762
//lint -e818
#include "StdAfx.h"
#include "UCEvent.h"
#include "UCEventMgr.h"
#include "UCCallManager.h"
#include "UCContactMgr.h"
#include "UCRegManager.h"
#include "UCDeviceMgr.h"
#include "UCTonePlay.h"
#include "UCConfigMgr.h"

const std::string BOOK_CONF_NUM = "600000";//预约会议号

void RegEvent::OnSignInNotify(UCClient::SignInState _state, std::string _reason)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM2(_state,_reason);

	std::string strDesc;

	if (UCClient::Client_SignedIn == _state)
	{
		UCDeviceMgr::Instance().Init();
		UCDeviceMgr::Instance().UpdateDevCfg();
		UCRegManager::Instance().InitSubscribe();
		UCConfigMgr::Instance().ConectPhoneJointSignal();
		HistoryManager * pHisMgr = HistoryManager::Instance();
		if(NULL != pHisMgr)
		{
			pHisMgr->InitializeHistoryData();
		}
		if(NULL != UCRegManager::Instance().m_pSelf)
		{
			UCRegManager::Instance().m_pSelf->NotifyDispatchMsg(true); 
		}
		
	}
	else
	{
		//通知上层呼叫结束
		if( "" != UCCallManager::Instance().GetConvID() )
		{
			if(NULL != UCCallManager::OnAVSessionClosedCB)
			{
				STMsgAVSessionClosedParam item = {0};
				UCCallManager::OnAVSessionClosedCB(item);
			}
			//挂断进行中的呼叫
			(void)UCCallManager::Instance().HangupCall();
		}


		if(NULL != UCRegManager::Instance().m_pSelf)
		{
			UCRegManager::Instance().m_pSelf->selfStatus = Offline;
		}

		if(SIGNINFAIL_SIP_KICKOUT == _reason)
		{
			strDesc  = ACC_KICKED;
		}
		else if(SIGNOUT_OK == _reason)
		{
			strDesc  = LOGOUT_OK;
		}
		else
		{
			(void)UCRegManager::Instance().GetSigninErrorDesc(_reason,strDesc);		
		}	

		UCDeviceMgr::Instance().Uninit();
		UCRegManager::Instance().UnInitSubscribe();
		HistoryManager * pHisMgr = HistoryManager::Instance();
		if(NULL != pHisMgr)
		{
			pHisMgr->FinalizeHistoryData();
		}
	}

	//如果登录失败，先通知上层，再置NULL；登录成功，先不回调，等到SIP注册成功再回调
	if (NULL != UCRegManager::OnClientSignInNotifyCB)
	{
		if(UCClient::Client_SignedIn != _state)
		{
			DEBUG_LOG() << "--- ENTER OnClientSignInNotifyCB";
			UCRegManager::OnClientSignInNotifyCB((int)_state,strDesc.c_str());
			DEBUG_LOG() << "--- LEAVE OnClientSignInNotifyCB";
			UCRegManager::OnClientSignInNotifyCB = NULL;
		}

	}	

	DEBUG_LOG() << "--- LEAVE";
}
void RegEvent::OnSipRegNotify(int iResult)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(iResult);
	
	if (0 != iResult)
	{
		ERROR_LOG() << "SipReg failed.";		
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	//发布自身状态
	ctk::xml::XMLOutStream eventXML("event");
	UCEventMgr::Instance().NotifyPubPJEvent(eventXML.str());

	if(NULL == UCRegManager::OnClientSignInNotifyCB)
	{
		ERROR_LOG() << "OnClientSignInNotifyCB is NULL.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	std::string info = "";
	DEBUG_LOG() << "--- ENTER OnClientSignInNotifyCB";
	UCRegManager::OnClientSignInNotifyCB((int)(UCClient::Client_SignedIn),info.c_str());
	DEBUG_LOG() << "--- LEAVE OnClientSignInNotifyCB";

	DEBUG_LOG() << "--- LEAVE";
}

void RegEvent::OnStatusChanged(ContactAvailability _state, std::string _desc, const Contact& _contact, std::string)
{
	DEBUG_LOG() << "--- ENTER";

	std::string UCAcct = _contact.ucAcc_;
	INFO_PARAM2(UCAcct,_state);

	if (NULL != UCRegManager::OnStatusChangedCB)
	{
		STContact st = {0};

		(void)strcpy_s(st.id_,_contact.id_.c_str());
		(void)strcpy_s(st.uri_,_contact.uri_.c_str());
		(void)strcpy_s(st.ucAcc_,UCAcct.c_str());
		(void)strcpy_s(st.staffNo_,_contact.staffNo_.c_str());
		(void)strcpy_s(st.name_,_contact.name_.c_str());
		(void)strcpy_s(st.nickName_,_contact.nickName_.c_str());
		(void)strcpy_s(st.homePhone_,_contact.homePhone_.c_str());
		(void)strcpy_s(st.officePhone_,_contact.officePhone_.c_str());
		(void)strcpy_s(st.officePhone2_,_contact.officePhone2_.c_str());
		(void)strcpy_s(st.mobile_,_contact.mobile_.c_str());
		(void)strcpy_s(st.email_,_contact.email_.c_str());
		(void)strcpy_s(st.deptName_,_contact.deptName_.c_str());
		(void)strcpy_s(st.ipphone1_,_contact.ipphone1_.c_str());
		(void)strcpy_s(st.webSite_,_contact.webSite_.c_str());
		(void)strcpy_s(st.location_,_contact.location_.c_str());		

		UCRegManager::OnStatusChangedCB((int)_state, st);
	}
	DEBUG_LOG() << "--- LEAVE";
}

void CallEvent::OnCallRing(conversation::Conversation* _pConv,std::string _remoreuri)
{
	DEBUG_LOG() << "--- ENTER";
	if(NULL == _pConv)
	{
		ERROR_LOG() << "_pConv is NULL.";		
		return;
	}

	INFO_PARAM2(_pConv,_remoreuri);

	(void)UCTonePlay::Instance().EndPlay();
	(void)UCTonePlay::Instance().StartPlayRingBack();

	DEBUG_LOG() << "--- LEAVE";
	return;
}
void CallEvent::OnCallClosed(conversation::Conversation* _pConv, conversation::sMsgAVSessionClosedParam& _avParam)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		ERROR_LOG() << "pConv is null";
		return;
	}

	INFO_PARAM1(_pConv);

	//end play
	(void)UCTonePlay::Instance().EndPlay();

	//notify
	std::string strConID = _pConv->propmap_[conversation::ConvIdentifier];
	ctk::xml::XMLOutStream eventXML("event");
	eventXML["id"] << _avParam.AVSessionId_;
	eventXML["callerNum"] << _avParam.caller_;
	eventXML["reason"] << _avParam.reason_;
	eventXML["conversationId"] << strConID;
	UCEventMgr::Instance().NotifyCallCloseEvent(eventXML.str());

	UCCallManager::Instance().DisConectConfSignal(_pConv);

	DEBUG_LOG() << "--- LEAVE";
}//lint !e1764

void CallEvent::OnCallConnected(conversation::Conversation* _pConv)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		ERROR_LOG() << "pConv is null";
		return;
	}

	INFO_PARAM1(_pConv);

	//如果会议还未开始则清理会议列表
	if(!UCCallManager::Instance().GetConvStarted())
	{
		(void)UCCallManager::Instance().ClearConvMember();
	}
	

	//结束呼叫
	(void)UCTonePlay::Instance().EndPlay();

	//上报呼叫接通消息
	conversation::Conversation::MemList_::iterator itor = _pConv->members_.begin();
	if(_pConv->members_.end() == itor )
	{
		ERROR_LOG() << "pConv has no member.";
		return;
	}
	ctk::xml::XMLOutStream eventXML("event");
	std::string caller = (*itor).first;
	eventXML["caller"] << caller;
	std::string convID = _pConv->propmap_[conversation::ConvIdentifier];
	eventXML["convid"] << convID;
	UCEventMgr::Instance().NotifyCallConnectedEvent(eventXML.str());	

	//查询所有成员状态，上报状态
	conversation::Conversation::MemList_::iterator it = _pConv->members_.begin();
	conversation::Conversation::MemList_::iterator itorEnd = _pConv->members_.end();
	while (it != itorEnd)
	{		
		std::string calleruri = (*it).first;
		if(!eSDKTool::IsValidUri(calleruri))
		{			
			it++;
			continue;
		}
		ctk::xml::XMLOutStream eventOutXML("event");
		eventOutXML["caller"] << calleruri;
		UCEventMgr::Instance().NotifyStatusEvent(eventOutXML.str());
		it++;
	}

	DEBUG_LOG() << "--- LEAVE";
}

void CallEvent::OnCallIncoming(conversation::Conversation* _pConv, conversation::sAudioVideoParam& _avParam)
{
	DEBUG_LOG() << "--- ENTER";

	if (NULL == _pConv)
	{
		ERROR_LOG() << "_pConv is Null.";
		return;
	}

	INFO_PARAM1(_pConv);

	std::string strNewConversationID = _pConv->propmap_[conversation::ConvIdentifier];
	//已经在通话中，拒绝新的来电
	if (!UCCallManager::Instance().GetConvID().empty())
	{		
		if (strNewConversationID.empty())
		{
			ERROR_LOG() << "strNewConversationID is empty.";
			return;
		}
		ctk::xml::XMLOutStream eventXML("event");
		eventXML["conversationID"] << strNewConversationID;
		UCEventMgr::Instance().NotifyRejectNewCallEvent(eventXML.str());
		return;
	}

	(void)UCTonePlay::Instance().EndPlay();
	(void)UCTonePlay::Instance().StartPlayIncomingCall();

	UCCallManager::Instance().SetConvID(strNewConversationID);
	INFO_LOG() << "Add ConvID = " << strNewConversationID;

	//临时群会议，挂接会议信号
	UCCallManager::Instance().ConectConfSignal(_pConv);

	ctk::xml::XMLOutStream eventXML("event");
	//判断是否是预约会议
	if(BOOK_CONF_NUM == _avParam.caller_)
	{
		//预约会议取出主席
		conversation::Conversation::MemList_::iterator it = _pConv->members_.begin();
		if(it != _pConv->members_.end())
		{
			std::string  strURI = (*it).first;
			eventXML["callerUri"] << strURI;
			eventXML["accounttype"] << "UCAccount";
		}		
	}
	else
	{
		eventXML["callerUri"] << _avParam.caller_;
		if(eSDKTool::IsValidUri(_avParam.caller_))
		{
			eventXML["accounttype"] << "UCAccount";
		}
		else
		{
			eventXML["accounttype"] << "IPPhone";
		}
	}
	
	if(_avParam.isvideo_)
	{
		eventXML["video"] << "true";
	}
	else
	{
		eventXML["video"] << "false";
	}
	if(_avParam.callmode_)
	{
		eventXML["callmode"] << "IPPhone";
	}
	else
	{
		eventXML["callmode"] << "UCAccount";
	}

	UCEventMgr::Instance().NotifyCallIncomingEvent(eventXML.str());

	DEBUG_LOG() << "--- LEAVE";
}//lint !e1764
void ConfEvent::OnConvIMConnected(conversation::Conversation* _pConv)
{
	DEBUG_LOG() << "--- ENTER";
	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	INFO_PARAM1(_pConv);

	conversation::AVSession* pAVSess =dynamic_cast<conversation::AVSession*>(_pConv->AddSession(AudioVideo));
	if(NULL == pAVSess)
	{
		ERROR_LOG() << "add AVSession Failed.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	if(!pAVSess->Connect())
	{
		WARN_LOG() << "AVSession connect failed.";
	}

	DEBUG_LOG() << "--- LEAVE";
	return;

}
void ConfEvent::OnConvStatusChanged(conversation::Conversation* _pConv, int type, std::string strUrl)
{
	DEBUG_LOG() << "--- ENTER";
	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv is NULL";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	INFO_PARAM2(type,strUrl);	

	//遍历成员，上报会议状态
	conversation::Conversation::MemList_::iterator itor = _pConv->members_.begin();
	conversation::Conversation::MemList_::iterator itorEnd = _pConv->members_.end();
	while (itor != itorEnd)
	{
		std::string strConvURI = (*itor).first;
		(void)UCRegManager::Instance().SubscribeStatus(strConvURI);//订阅新成员状态

		Participant* pPart = (*itor).second;
		if (NULL == pPart)
		{
			ERROR_LOG() << "pPart is null pointer";
			return;
		}

		ctk::xml::XMLOutStream eventXML("event");
		std::string ucacc = pPart->contact_.ucAcc_;		

		if("" == ucacc)
		{
			ucacc = itor->first;
			eventXML["type"] << "IPPhone";
		}
		else
		{
			eventXML["type"] << "UCAccount";
		}
		eventXML["account"] << ucacc;

		std::string stateString = pPart->propmap_[PartConfState];
		INFO_PARAM3(ucacc,strConvURI,stateString);

		if (conversation::PART_CONFSTATE_INVITING == stateString)
		{				
			eventXML["status"] << "Inviting";
		}
		else if (conversation::PART_CONFSTATE_HANGUP == stateString)
		{
			eventXML["status"] << "Hangup";
		}
		else if (conversation::PART_CONFSTATE_QUIT == stateString)
		{
			eventXML["status"] << "Quit";
		}
		else if (conversation::PART_CONFSTATE_INCONF == stateString)
		{
			//处理是否静音，需要会议中的状态才需要处理是否会议
			std::string muteString = pPart->propmap_[PartIsMuted];
			if(conversation::PART_AUDIO_MUTED == muteString)
			{
				eventXML["status"] << "Mute";
			}
			else
			{
				eventXML["status"] << "UnMute";
			}
		}
		else
		{
			WARN_LOG() << "invalid state,state is [" <<stateString<<"]";
			eventXML["status"] << "Add";
		}
		
		UCEventMgr::Instance().NotifyConvMemEvent(eventXML.str());
		itor++;
	}

	

	DEBUG_LOG() << "--- LEAVE";
	return;
}
void ConfEvent::OnConvAllowSpk(conversation::Conversation* pConv, conversation::Participant part_)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == pConv)
	{
		WARN_LOG() << "pConv is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	ctk::xml::XMLOutStream eventXML("event");
	std::string uri = part_.contact_.ucAcc_;		
	Contact ctact;
	if(UC_SDK_Success == UCContactMgr::Instance().getContactByUri(uri,ctact))
	{
		eventXML["type"] << "UCAccount";
		eventXML["account"] << ctact.ucAcc_;
	}
	else
	{
		eventXML["type"] << "IPPhone";
		std::string phone = eSDKTool::GetNoFromUri(uri);			
		eventXML["account"] << phone;
	}
	eventXML["status"] << "UnMute";

	UCEventMgr::Instance().NotifyConvMemEvent(eventXML.str());

	DEBUG_LOG() << "--- LEAVE";
	return;
}
void ConfEvent::OnConvForbidSpk(conversation::Conversation* pConv_, conversation::Participant part_)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == pConv_)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	ctk::xml::XMLOutStream eventXML("event");
	std::string strUrl = part_.contact_.ucAcc_;		
	Contact ctact;
	if(UC_SDK_Success == UCContactMgr::Instance().getContactByUri(strUrl,ctact))
	{
		eventXML["type"] << "UCAccount";
		eventXML["account"] << ctact.ucAcc_;
	}
	else
	{
		eventXML["type"] << "IPPhone";

		std::string phone = eSDKTool::GetNoFromUri(strUrl);			
		eventXML["account"] << phone;
	}
	eventXML["status"] << "Mute";

	UCEventMgr::Instance().NotifyConvMemEvent(eventXML.str());

	DEBUG_LOG() << "--- LEAVE";
	return;
}
void ConfEvent::OnConvCurSpker(conversation::Conversation* , std::string strUrl)
{
	INFO_PARAM1(strUrl);
	return;
}
void ConfEvent::OnConvNumChanged(conversation::Conversation* pConv,
								std::vector<std::string> _kicklist, 
								std::vector<std::string> _addlist)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == pConv)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	INFO_PARAM1(pConv);

	unsigned int _kickSize = _kicklist.size();
	unsigned int _addSize = _addlist.size();
	if(0 == _kickSize && 0 == _addSize)
	{
		UCCallManager::Instance().ShowConvMember(pConv);
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	for(unsigned int i =0;i<_kickSize;++i)
	{
		ctk::xml::XMLOutStream eventXML("event");
		std::string url = _kicklist[i];
		Contact cont_;
		if(UC_SDK_Success == UCContactMgr::Instance().getContactByUri(url,cont_))
		{
			eventXML["type"] << "UCAccount";
			eventXML["account"] << cont_.ucAcc_;
		}
		else
		{
			eventXML["type"] << "IPPhone";
			std::string phone = eSDKTool::GetNoFromUri(url);
			if("" == phone)
			{
				eventXML["account"] << url;
			}
			else
			{
				eventXML["account"] << phone;
			}
			
		}
		eventXML["status"] << "Delete";
		UCEventMgr::Instance().NotifyConvMemEvent(eventXML.str());
	}

	
	for(unsigned int i =0;i<_addSize;++i)
	{
		ctk::xml::XMLOutStream eventXML("event");
		std::string url = _addlist[i];
		Contact cont_;
		if(UC_SDK_Success == UCContactMgr::Instance().getContactByUri(url,cont_))
		{
			eventXML["type"] << "UCAccount";
			eventXML["account"] << cont_.ucAcc_;

			//新增成员需要订阅
			(void)UCRegManager::Instance().SubscribeStatus(url);//订阅新成员状态
		}
		else
		{
			eventXML["type"] << "IPPhone";
			std::string phone = eSDKTool::GetNoFromUri(url);			
			if("" == phone)
			{
				eventXML["account"] << url;
			}
			else
			{
				eventXML["account"] << phone;
			}
		}
		eventXML["status"] << "Add";
		UCEventMgr::Instance().NotifyConvMemEvent(eventXML.str());

		
	}
	
	DEBUG_LOG() << "--- LEAVE";
	return;
}

void ConfEvent::OnConvDelSucc(conversation::Conversation* _pConv,const std::string _parti)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	INFO_PARAM2(_pConv,_parti);

	DEBUG_LOG() << "--- LEAVE";

	return;
}

void ConfEvent::OnConvRequestToSpeak(conversation::Conversation* _pConv,const std::string _parti,bool bUnmute)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	if(bUnmute)
	{
		INFO_PARAM2(_pConv,_parti) << " true";
	}
	else
	{
		INFO_PARAM2(_pConv,_parti) << " false";
	}
	

	DEBUG_LOG() << "--- LEAVE";

	return;

}
void ConfEvent::OnInstantSessMerged(conversation::Conversation* _pConv,conversation::Conversation* _pConvmerged)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}
	if(NULL == _pConvmerged)
	{
		WARN_LOG() << "_convmerged is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	INFO_PARAM2(_pConv,_pConvmerged);

	UCCallManager::Instance().DisConectConfSignal(_pConvmerged);
	ConversationMgr*  pConMgr = UCCallManager::Instance().GetConvMgr();
	if(NULL != pConMgr)
	{
		(void)pConMgr->RemoveConversation(_pConvmerged->propmap_[ConvIdentifier]);
	}
	UCCallManager::Instance().ConectConfSignal(_pConv);

	DEBUG_LOG() << "--- LEAVE";

	return;

}
void ConfEvent::OnMuteAllAttender(conversation::Conversation* _pConv,bool bSuc)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	if(bSuc)
	{
		INFO_PARAM1(_pConv) << "true";
	}
	else
	{
		INFO_PARAM1(_pConv) << "false";

	}
	INFO_PARAM1(_pConv);

	DEBUG_LOG() << "--- LEAVE";

	return;

}
void ConfEvent::OnSetVideoSource(conversation::Conversation* _pConv,const std::string _parti)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _pConv)
	{
		WARN_LOG() << "pConv_ is null.";
		DEBUG_LOG() << "--- LEAVE";
		return;
	}

	INFO_PARAM2(_pConv,_parti);

	DEBUG_LOG() << "--- LEAVE";

	return;

}

void VideoChannelEvent::OnChannelStateChanged(conversation::avchannel::ChannelState _state, 
											  conversation::Session* _pSess)
{
	DEBUG_LOG() << "--- ENTER";
	
	if(NULL == _pSess)
	{
		WARN_LOG() << "pSess is NULL.";
		return;
	}
	INFO_PARAM2(_state,_pSess);

	conversation::Conversation* pConv = _pSess->pConv_;
	if(NULL == pConv)
	{
		WARN_LOG() << "pConv is NULL.";
		return;
	}
	
	conversation::Conversation::MemList_::iterator it = pConv->members_.begin();
	Participant* pPart = (*it).second;
	if(NULL == pPart)
	{
		WARN_LOG() << "participant is null.";
		return;
	}

	std::string ucAccount = pPart->contact_.ucAcc_;
	if("" == ucAccount)
	{
		ucAccount = eSDKTool::GetNoFromUri((*it).first);
	}

	conversation::AVSession* pAVSess = dynamic_cast<conversation::AVSession*>(_pSess);
	if(NULL == pAVSess)
	{
		WARN_LOG() << "pAVSess is NULL.";
		return;
	}
	
	avchannel::ChannelState vchStatus = pAVSess->videochannel_.state_;
	INFO_PARAM1(vchStatus);

	ctk::xml::XMLOutStream eventXML("event");
	eventXML["account"] << ucAccount;
	switch (_state)
	{
	case conversation::avchannel::ChannelConnecting:
		{
			//收到对方视频请求
			INFO_LOG() << "recv video request";			
			eventXML["video"] << "connecting";
			break;
		}
	case conversation::avchannel::ChannelSendReceive:
		{
			//视频连接建立
			INFO_LOG() << "video has connected";
			eventXML["video"] << "connected";
			break;
		}
	case conversation::avchannel::ChannelInActive:
		{
			//视频连接关闭或者对方关闭视频
			INFO_LOG() << "video has closed";
			eventXML["video"] << "closed";				
			break;
		}
	default:
		WARN_LOG() << "invalid video state.";
		return;
	}

	UCEventMgr::Instance().NotifyVideoEvent(eventXML.str());
	DEBUG_LOG() << "--- LEAVE";
	return;
}

void PhoneJointEvent::OnPhoneJointRelated(int _type)
{
	DEBUG_LOG() << "--- ENTER";

	UCClient* pClient = UCClient::GetClient();
	if (NULL == pClient)
	{
		ERROR_LOG() << "pClient is NULL.";
		return;
	}

	INFO_PARAM1(_type);
	ctk::xml::XMLOutStream eventXML("event");
	std::ostringstream os;
	os << _type;
	eventXML["status"] << os.str();
	UCEventMgr::Instance().NotifyPJEvent(eventXML.str());	

	DEBUG_LOG() << "--- LEAVE";
	return;
}

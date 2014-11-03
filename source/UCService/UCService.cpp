//lint -e1784
// UCService.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "UCService.h"
#include "UCRegManager.h"
#include "UCCallManager.h"
#include "UCDeviceMgr.h"
#include "UCContactMgr.h"
#include "UCHistoryMgr.h"
#include "UCConfigMgr.h"
#include "UCEventMgr.h"

#ifdef WIN32

//状态与注册
#pragma comment(linker, "/EXPORT:UC_SDK_Init=_UC_SDK_Init@0")
#pragma comment(linker, "/EXPORT:UC_SDK_SignInByPWD=_UC_SDK_SignInByPWD@16")
#pragma comment(linker, "/EXPORT:UC_SDK_SignOut=_UC_SDK_SignOut@0")
#pragma comment(linker, "/EXPORT:UC_SDK_UnInit=_UC_SDK_UnInit@0")
#pragma comment(linker, "/EXPORT:UC_SDK_PubSelfStatus=_UC_SDK_PubSelfStatus@8")
#pragma comment(linker, "/EXPORT:UC_SDK_GetContactStatus=_UC_SDK_GetContactStatus@12")
#pragma comment(linker, "/EXPORT:UC_SDK_GetContactInfo=_UC_SDK_GetContactInfo@8")
#pragma comment(linker, "/EXPORT:UC_SDK_SubscribeStatus=_UC_SDK_SubscribeStatus@4")
#pragma comment(linker, "/EXPORT:UC_SDK_UnSubscribeStatus=_UC_SDK_UnSubscribeStatus@4")


//呼叫管理
#pragma comment(linker, "/EXPORT:UC_SDK_AddCallMember=_UC_SDK_AddCallMember@8")
#pragma comment(linker, "/EXPORT:UC_SDK_MakeCall=_UC_SDK_MakeCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_HangupCall=_UC_SDK_HangupCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_AcceptCall=_UC_SDK_AcceptCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_RejectCall=_UC_SDK_RejectCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_SendDTMF=_UC_SDK_SendDTMF@4")
#pragma comment(linker, "/EXPORT:UC_SDK_HoldCall=_UC_SDK_HoldCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_ResumeCall=_UC_SDK_ResumeCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_ForwardCall=_UC_SDK_ForwardCall@8")

//视频呼叫
#pragma comment(linker, "/EXPORT:UC_SDK_HangupVideoCall=_UC_SDK_HangupVideoCall@0")
#pragma comment(linker, "/EXPORT:UC_SDK_MakeVideoCall=_UC_SDK_MakeVideoCall@40")
#pragma comment(linker, "/EXPORT:UC_SDK_AcceptVideoCall=_UC_SDK_AcceptVideoCall@40")
#pragma comment(linker, "/EXPORT:UC_SDK_RejectVideoCall=_UC_SDK_RejectVideoCall@0")

//语音会议
#pragma comment(linker, "/EXPORT:UC_SDK_InviteMemberInCall=_UC_SDK_InviteMemberInCall@8")
#pragma comment(linker, "/EXPORT:UC_SDK_DeleteMemberInCall=_UC_SDK_DeleteMemberInCall@8")
#pragma comment(linker, "/EXPORT:UC_SDK_ModifyMemberStatusInCall=_UC_SDK_ModifyMemberStatusInCall@12")

//设备管理
#pragma comment(linker, "/EXPORT:UC_SDK_MuteMic=_UC_SDK_MuteMic@0")
#pragma comment(linker, "/EXPORT:UC_SDK_UnMuteMic=_UC_SDK_UnMuteMic@0")
#pragma comment(linker, "/EXPORT:UC_SDK_MuteSpker=_UC_SDK_MuteSpker@0")
#pragma comment(linker, "/EXPORT:UC_SDK_UnMuteSpker=_UC_SDK_UnMuteSpker@0")
#pragma comment(linker, "/EXPORT:UC_SDK_GetMicLevel=_UC_SDK_GetMicLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetMicLevel=_UC_SDK_SetMicLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetSpkerLevel=_UC_SDK_GetSpkerLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetSpkerLevel=_UC_SDK_SetSpkerLevel@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetMicDevList=_UC_SDK_GetMicDevList@16")
#pragma comment(linker, "/EXPORT:UC_SDK_GetSpeakerDevList=_UC_SDK_GetSpeakerDevList@16")
#pragma comment(linker, "/EXPORT:UC_SDK_GetVideoDevList=_UC_SDK_GetVideoDevList@16")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCurrentMicDev=_UC_SDK_GetCurrentMicDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCurrentSpeakerDev=_UC_SDK_GetCurrentSpeakerDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_GetCurrentVideoDev=_UC_SDK_GetCurrentVideoDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCurrentMicDev=_UC_SDK_SetCurrentMicDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCurrentSpeakerDev=_UC_SDK_SetCurrentSpeakerDev@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCurrentVideoDev=_UC_SDK_SetCurrentVideoDev@4")

//历史记录
#pragma comment(linker, "/EXPORT:UC_SDK_QueryCallHistory=_UC_SDK_QueryCallHistory@20")
#pragma comment(linker, "/EXPORT:UC_SDK_InsertCallHistory=_UC_SDK_InsertCallHistory@16")
#pragma comment(linker, "/EXPORT:UC_SDK_ClearCallHistroy=_UC_SDK_ClearCallHistroy@4")
#pragma comment(linker, "/EXPORT:UC_SDK_QueryConvHistory=_UC_SDK_QueryConvHistory@16")
#pragma comment(linker, "/EXPORT:UC_SDK_InsertConvHistory=_UC_SDK_InsertConvHistory@16")
#pragma comment(linker, "/EXPORT:UC_SDK_InsertConvHistoryPart=_UC_SDK_InsertConvHistoryPart@12")
#pragma comment(linker, "/EXPORT:UC_SDK_ClearConvHistroy=_UC_SDK_ClearConvHistroy@0")
#pragma comment(linker, "/EXPORT:UC_SDK_QueryHisConvPartByID=_UC_SDK_QueryHisConvPartByID@20")
#pragma comment(linker, "/EXPORT:UC_SDK_DeleteCallHistory=_UC_SDK_DeleteCallHistory@4")
#pragma comment(linker, "/EXPORT:UC_SDK_DeleteConvHistory=_UC_SDK_DeleteConvHistory@4")

//话机联动
#pragma comment(linker, "/EXPORT:UC_SDK_GetPhoneJointDevType=_UC_SDK_GetPhoneJointDevType@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetPhoneJointDevType=_UC_SDK_SetPhoneJointDevType@4")

//通讯录查找
#pragma comment(linker, "/EXPORT:UC_SDK_GetUCAccount=_UC_SDK_GetUCAccount@8")

//事件回调
#pragma comment(linker, "/EXPORT:UC_SDK_SetLoginEventCB=_UC_SDK_SetLoginEventCB@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetStatusChangedCB=_UC_SDK_SetStatusChangedCB@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetCallEventCallBack=_UC_SDK_SetCallEventCallBack@12")
#pragma comment(linker, "/EXPORT:UC_SDK_SetVideoCallEventCallBack=_UC_SDK_SetVideoCallEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetConfMemEventCallBack=_UC_SDK_SetConfMemEventCallBack@4")
#pragma comment(linker, "/EXPORT:UC_SDK_SetPhoneJointEventCallBack=_UC_SDK_SetPhoneJointEventCallBack@4")

//打开portal
#pragma comment(linker, "/EXPORT:UC_SDK_OpenPortal=_UC_SDK_OpenPortal@4")

#endif



//初始化
int __UC_SDK_CALL UC_SDK_Init(void)
{
	SetUnhandledExceptionFilter(GPTUnhandledExceptionFilter);

	//初始化日志
	(void)eSDKLog::getCategoryInstance();

	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	(void)UCEventMgr::Instance();
	UCRegManager::Instance().Init();
	UCConfigMgr::Instance().Init();
	UCCallManager::Instance().Init();
	UCContactMgr::Instance().Init();
	UCHistoryMgr::Instance().Init();
	(void)UCDeviceMgr::Instance();
	

	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;
}

//去初始化
int __UC_SDK_CALL UC_SDK_UnInit()
{	
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	UCCallManager::Instance().Uninit();
	UCContactMgr::Instance().Uninit();
	UCHistoryMgr::Instance().Uninit();
	UCConfigMgr::Instance().Uninit();	
	UCRegManager::Instance().Uninit();	

	UCEventMgr::Destroy();
	UCCallManager::Destroy();
	UCContactMgr::Destroy();
	UCHistoryMgr::Destroy();
	UCConfigMgr::Destroy();
	UCRegManager::Destroy();
	UCDeviceMgr::Destroy();

	DEBUG_LOG() << "--- LEAVE";
	eSDKLog::destroyInstance();	
	return UC_SDK_Success;
}

//通过用户名和密码登录
int __UC_SDK_CALL UC_SDK_SignInByPWD(const char* account, const char* pwd, const char* serverUrl,const char* langID)
{
	DEBUG_LOG() << "--- ENTER";
	
	if(NULL == account || NULL ==pwd || NULL == serverUrl || NULL == langID)
	{
		ERROR_LOG() << "Null Pointer";
		return UC_SDK_InvalidPara;
	}
	if( 0==strlen(account) || 0==strlen(pwd) || 0==strlen(serverUrl) || 0 ==strlen(langID))
	{
		ERROR_LOG() << "para is invalid";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM3(account,serverUrl,langID);

	std::string strAccount(account);
	std::string strPWD(pwd);
	std::string strUrl(serverUrl);
	std::string strLangID(langID);
	int iRet = UCRegManager::Instance().SignInByPWD(strAccount,strPWD,strUrl,strLangID);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//登出
int __UC_SDK_CALL UC_SDK_SignOut()
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG();
	int iRet = UCRegManager::Instance().SignOut();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//增加呼叫成员
int __UC_SDK_CALL UC_SDK_AddCallMember(int _memberType,const char* _member)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if(NULL == _member)
	{
		ERROR_LOG() << "phoneNum is null";
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_member))
	{
		ERROR_LOG() << "phoneNum is empty";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM2(_member,_memberType);

	if(UC_ACCOUNT == _memberType)
	{
		std::string strAccount = _member;
		Contact contact;
		if (UC_SDK_Success == UCContactMgr::Instance().getContactByAccount(strAccount,contact))
		{
			int iRet = UCCallManager::Instance().InsertUCMember(contact.uri_);
			DEBUG_LOG() << "--- LEAVE";
			return iRet;
		}
		ERROR_LOG() << "Find Uri Error!";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_FindUriErr;
	}
	else if (UC_IPPHONE == _memberType)
	{
		std::string phone = _member;
		(void)UCCallManager::Instance().InsertPhoneMember(phone);
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_Success;
	}
	return UC_SDK_InvalidPara;
}

int __UC_SDK_CALL UC_SDK_GetUCAccount(const char* phoneNum,char _UCAcc[STRING_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if(NULL == phoneNum)
	{
		ERROR_LOG() << "phoneNum is null.";
		return UC_SDK_NotFound;
	}
	INFO_PARAM1(phoneNum);

	Contact conct;
	int iRet = UCContactMgr::Instance().getContactByPhoneNum(phoneNum,conct);	
	if(UC_SDK_Success != iRet)
	{
		WARN_LOG() << "Get UC Member failed.";
	}
	else
	{
		ctk::MemSet(_UCAcc,0,STRING_LENGTH);
		std::string ucAcc = conct.ucAcc_;
		ctk::MemCopy(_UCAcc,ucAcc.c_str(),(ucAcc.size()<(STRING_LENGTH)) ? (ucAcc.size()) : (STRING_LENGTH-1) );	
		INFO_PARAM1(ucAcc);
	}
	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

//发起呼叫
int __UC_SDK_CALL UC_SDK_MakeCall()
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCCallManager::Instance().MakeCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//通话保持
int __UC_SDK_CALL UC_SDK_HoldCall()
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	int iRet = UCCallManager::Instance().HoldCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//通话恢复
int __UC_SDK_CALL UC_SDK_ResumeCall()
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	int iRet = UCCallManager::Instance().ResumeCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//呼叫前转
int __UC_SDK_CALL UC_SDK_ForwardCall(int iMemberType,const char* pMember)
{
	DEBUG_LOG() << "--- ENTER";
	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	if (NULL == pMember)
	{
		ERROR_LOG() << "phoneNum is null pointer.";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM2(iMemberType, pMember);
	if (0 == strlen(pMember))
	{
		ERROR_LOG() << "phoneNum is empty.";
		return UC_SDK_InvalidPara;
	}
	if (UC_ACCOUNT != iMemberType && UC_IPPHONE != iMemberType)
	{
		ERROR_LOG() << "memberType invalid.";
		return UC_SDK_InvalidPara;
	}

	std::string strMember = pMember;
	int iRet = UCCallManager::Instance().ForwardCall((EM_MemberType)iMemberType,strMember);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//结束通话
int __UC_SDK_CALL UC_SDK_HangupCall()
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG();
	int iRet = UCCallManager::Instance().HangupCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//结束视频通话
int __UC_SDK_CALL UC_SDK_HangupVideoCall()
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG();
	int iRet = UCCallManager::Instance().HangupVideoCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//接听呼叫
int __UC_SDK_CALL UC_SDK_AcceptCall()
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG();
	int iRet = UCCallManager::Instance().AcceptCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//接听呼叫
int __UC_SDK_CALL UC_SDK_AcceptVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
									int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight)
{
	DEBUG_LOG() << "--- ENTER";
	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	INFO_PARAM5(localHWnd, localLeft, localTop, localWidth, localHeight);
	INFO_PARAM5(remoteHWnd, remoteLeft, remoteTop, remoteWidth, remoteHeight);

	STVideoWindow stLocalWnd;
	stLocalWnd.hWnd = localHWnd;
	stLocalWnd.left = localLeft;
	stLocalWnd.top = localTop;
	stLocalWnd.width = localWidth;
	stLocalWnd.height = localHeight;

	STVideoWindow stRemoteWnd;
	stRemoteWnd.hWnd = remoteHWnd;
	stRemoteWnd.left = remoteLeft;
	stRemoteWnd.top = remoteTop;
	stRemoteWnd.width = remoteWidth;
	stRemoteWnd.height = remoteHeight;

	int iRet = UCCallManager::Instance().AcceptVideoCall(stLocalWnd,stRemoteWnd);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//拒绝呼叫
int __UC_SDK_CALL UC_SDK_RejectCall()
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG();
	int iRet = UCCallManager::Instance().RejectCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//拒绝视频呼叫
int __UC_SDK_CALL UC_SDK_RejectVideoCall()
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG();
	int iRet = UCCallManager::Instance().RejectVideoCall();
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//二次拨号
int __UC_SDK_CALL UC_SDK_SendDTMF(char tone)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCCallManager::Instance().SendDTMF(tone);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//麦克风静音
int __UC_SDK_CALL UC_SDK_MuteMic(void)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	
	int iRet = UCDeviceMgr::Instance().MuteMic();

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//麦克风取消静音
int __UC_SDK_CALL UC_SDK_UnMuteMic(void)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().UnMuteMic();

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//获取麦克风音量
int __UC_SDK_CALL UC_SDK_GetMicLevel(int& level)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().GetMicLevel(level);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}
//设置麦克风音量
int __UC_SDK_CALL UC_SDK_SetMicLevel(int level)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM1(level);

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().SetMicLevel(level);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}
//扬声器静音
int __UC_SDK_CALL UC_SDK_MuteSpker(void)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().MuteSpeaker();

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}
//扬声器取消静音
int __UC_SDK_CALL UC_SDK_UnMuteSpker(void)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().UnMuteSpeaker();

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}
//获取扬声器音量
int __UC_SDK_CALL UC_SDK_GetSpkerLevel(int& level)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().GetSpeakerLevel(level);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
	
}
//设置扬声器音量
int __UC_SDK_CALL UC_SDK_SetSpkerLevel(int level)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM1(level);

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	int iRet = UCDeviceMgr::Instance().SetSpeakerLevel(level);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

//发起视频呼叫或者将当前语音呼叫升级为视频呼叫
int __UC_SDK_CALL UC_SDK_MakeVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
									   int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM5(localHWnd, localLeft, localTop, localWidth, localHeight);
	INFO_PARAM5(remoteHWnd, remoteLeft, remoteTop, remoteWidth, remoteHeight);

	//校验入参
	if (0 == localHWnd || 0 == remoteHWnd)
	{
		ERROR_LOG() << "localHWnd or remoteHWnd is 0";
		return UC_SDK_Failed;
	}

	STVideoWindow stLocalWnd;
	stLocalWnd.height = localHeight;
	stLocalWnd.width = localWidth;
	stLocalWnd.top = localTop;
	stLocalWnd.left = localLeft;
	stLocalWnd.hWnd = localHWnd;	

	STVideoWindow stRemoteWnd;	
	stRemoteWnd.height = remoteHeight;
	stRemoteWnd.width = remoteWidth;
	stRemoteWnd.top = remoteTop;
	stRemoteWnd.left = remoteLeft;
	stRemoteWnd.hWnd = remoteHWnd;

	int iRet = UCCallManager::Instance().MakeVideoCall(stLocalWnd,stRemoteWnd);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//语音会议中邀请成员
int __UC_SDK_CALL UC_SDK_InviteMemberInCall(int _memberType,const char* pAccount)
{
	DEBUG_LOG() << "--- ENTER";	

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == pAccount)
	{
		ERROR_LOG() << "pAccount is null pointer.";
		return UC_SDK_InvalidPara;
	}
	if (0 == strlen(pAccount))
	{
		ERROR_LOG() << "pAccount is empty.";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM2(_memberType,pAccount);

	std::string strAccount = pAccount;
	int iRet = UCCallManager::Instance().InviteMemberInCall((EM_MemberType)_memberType,strAccount);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//语音会议中删除成员
int __UC_SDK_CALL UC_SDK_DeleteMemberInCall(int _memberType,const char* pAccount)
{
	DEBUG_LOG() << "--- ENTER";	

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	
	if (NULL == pAccount)
	{
		ERROR_LOG() << "pAccount is null pointer";
		return UC_SDK_InvalidPara;
	}
	if (0 == strlen(pAccount))
	{
		ERROR_LOG() << "pAccount is empty.";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM2(_memberType,pAccount);

	std::string strAccount = pAccount;
	int iRet = UCCallManager::Instance().DeleteMemberInCall((EM_MemberType)_memberType,strAccount);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//包括语音会议中断开某成员的语音，语音会议中重新呼叫某成员，语音会议中对某成员静音，对某成员取消静音4种。
int __UC_SDK_CALL UC_SDK_ModifyMemberStatusInCall(int operateType,int memberType,const char* pAccount)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}
	
	if (NULL == pAccount)
	{
		ERROR_LOG() << "pAccount is null.";
		return UC_SDK_InvalidPara;
	}
	if(operateType < EndCallMember || operateType > UnMuteMember)
	{
		ERROR_LOG() << "invalid operateType.";
		return UC_SDK_InvalidPara;
	}
	if(memberType < UC_ACCOUNT || memberType > UC_IPPHONE)
	{
		ERROR_LOG() << "invalid memberType.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM3(operateType,memberType,pAccount);

	std::string strAccount = pAccount;
	int iRet = UCCallManager::Instance().ModifyMemberStatusInCall((EM_ConvnerOperateType)operateType, (EM_MemberType)memberType,strAccount);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//获取麦克风设备列表
int __UC_SDK_CALL UC_SDK_GetMicDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM4(_fromIndex,_toIndex,_size,devList);
	if (NULL == devList || 0>_fromIndex || _fromIndex>_toIndex || 0>=_size)
	{
		ERROR_LOG() << "Invalid Param";
		return UC_SDK_InvalidPara;
	}

	int queryMicSize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STDeviceListParam)+(unsigned int)(queryMicSize-1)*sizeof(STDeviceParam));
	if(_size != iSize)
	{
		ERROR_LOG() << "alloc memory invalid.";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCDeviceMgr::Instance().GetMicDevList(_fromIndex,_toIndex,devList);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//获取扬声器设备列表
int __UC_SDK_CALL UC_SDK_GetSpeakerDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM4(_fromIndex,_toIndex,_size,devList);
	if (NULL == devList || 0>_fromIndex || _fromIndex>_toIndex || 0>=_size)
	{
		ERROR_LOG() << "Invalid Param";
		return UC_SDK_InvalidPara;
	}

	int querySpeakerSize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STDeviceListParam)+(unsigned int)(querySpeakerSize-1)*sizeof(STDeviceParam));
	if(_size != iSize)
	{
		ERROR_LOG() << "alloc memory invalid.";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCDeviceMgr::Instance().GetSpeakerDevList(_fromIndex,_toIndex,devList);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//获取视频设备列表
int __UC_SDK_CALL UC_SDK_GetVideoDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM4(_fromIndex,_toIndex,_size,devList);
	if (NULL == devList || 0>_fromIndex || _fromIndex>_toIndex || 0>=_size)
	{
		ERROR_LOG() << "Invalid Param";
		return UC_SDK_InvalidPara;
	}

	int queryVideoSize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STDeviceListParam)+((unsigned int)(queryVideoSize-1))*sizeof(STDeviceParam));
	if(_size != iSize)
	{
		ERROR_LOG() << "alloc memory invalid.";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCDeviceMgr::Instance().GetVideoDevList(_fromIndex,_toIndex,devList);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//获取当前麦克风设备
int __UC_SDK_CALL UC_SDK_GetCurrentMicDev(STDeviceParam* device)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == device)
	{
		ERROR_LOG() << "device is null pointer.";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM1(device);
	int iRet = UCDeviceMgr::Instance().GetCurrentMicDev(device);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//获取当前扬声器设备
int __UC_SDK_CALL UC_SDK_GetCurrentSpeakerDev(STDeviceParam* device)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == device)
	{
		ERROR_LOG() << "device is null pointer.";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM1(device);
	int iRet = UCDeviceMgr::Instance().GetCurrentSpeakerDev(device);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//获取当前视频设备
int __UC_SDK_CALL UC_SDK_GetCurrentVideoDev(STDeviceParam* device)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	if (NULL == device)
	{
		ERROR_LOG() << "device is null pointer.";
		return UC_SDK_InvalidPara;
	}
	INFO_PARAM1(device);
	int iRet = UCDeviceMgr::Instance().GetCurrentVideoDev(device);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//设置当前麦克风设备
int __UC_SDK_CALL UC_SDK_SetCurrentMicDev(int index)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM1(index);
	if (index < 0)
	{
		ERROR_LOG() << "index is less than 0";
		return UC_SDK_InvalidPara;
	}
	int iRet = UCDeviceMgr::Instance().SetCurrentMicDev(index);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//设置当前扬声器设备
int __UC_SDK_CALL UC_SDK_SetCurrentSpeakerDev(int index)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM1(index);
	if (index < 0)
	{
		ERROR_LOG() << "index is less than 0";
		return UC_SDK_InvalidPara;
	}
	int iRet = UCDeviceMgr::Instance().SetCurrentSpeakerDev(index);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}
//设置当前视频设备
int __UC_SDK_CALL UC_SDK_SetCurrentVideoDev(int index)
{
	DEBUG_LOG() << "--- ENTER";

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	INFO_PARAM1(index);
	if (index < 0)
	{
		ERROR_LOG() << "index is less than 0";
		return UC_SDK_InvalidPara;
	}
	int iRet = UCDeviceMgr::Instance().SetCurrentVideoDev(index);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//设置登录回调
int __UC_SDK_CALL UC_SDK_SetLoginEventCB(ClientSignInNotifyCB _loginEventCB)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(_loginEventCB);

	if (NULL == _loginEventCB)
	{
		ERROR_LOG() << "Null Pointer";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCRegManager::Instance().SetLoginEventCB(_loginEventCB);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//设置状态回调（登陆前必须调用）
int __UC_SDK_CALL UC_SDK_SetStatusChangedCB(StatusChangedCB _statusEventCB)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(_statusEventCB);

	if (NULL == _statusEventCB)
	{
		ERROR_LOG() << "Null Pointer";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCRegManager::Instance().SetStatusEventCB(_statusEventCB);
	
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

//设置呼叫事件回调
int __UC_SDK_CALL UC_SDK_SetCallEventCallBack(AVSessionClosedCB _AVSessClosedCB,
											  AVSessionConnectedCB _AVSessConnCB,
											  AVSessAddedCB _AVSessAddedCB)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM3(_AVSessClosedCB,_AVSessConnCB,_AVSessAddedCB);

	if (NULL == _AVSessClosedCB || NULL == _AVSessConnCB || NULL == _AVSessAddedCB)
	{
		ERROR_LOG() << "CallBack Function is NULL";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCCallManager::Instance().SetCallEventCB(_AVSessClosedCB,_AVSessConnCB,_AVSessAddedCB);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_SetVideoCallEventCallBack(VideoCallEventCB _callEventCallBack)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(_callEventCallBack);

	if (NULL == _callEventCallBack)
	{
		ERROR_LOG() << "CallBack Function is NULL";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCCallManager::Instance().SetCallEventCB(_callEventCallBack);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}
int __UC_SDK_CALL UC_SDK_SetConfMemEventCallBack(ConfMemberEventCB confMemEventCallBack)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(confMemEventCallBack);

	if (NULL == confMemEventCallBack)
	{
		ERROR_LOG() << "confMemEventCallBack Function is NULL";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCCallManager::Instance().SetConfMemEventCB(confMemEventCallBack);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

int __UC_SDK_CALL UC_SDK_QueryCallHistory(int _callType,  int _fromIndex, int _toIndex, STCallHistroyData* _queryResult,int _size)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM4(_callType,_fromIndex,_toIndex,_size);
	if(NULL == _queryResult)
	{
		ERROR_LOG() << "_queryResult is NULL.";
		return UC_SDK_InvalidPara;
	}

	if(_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG() << "query para is invalid.";
		return UC_SDK_InvalidPara;
	}

	int querySize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STCallHistroyData)+(unsigned int)(querySize-1)*sizeof(STCallHistroyItem));
	if(_size != iSize)
	{
		ERROR_LOG() << "memory size is invalid.";
		return UC_SDK_InvalidPara;
	}	

	int iRet = UCHistoryMgr::Instance().QueryCallHistory(_callType,_fromIndex,_toIndex,_queryResult);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

int __UC_SDK_CALL UC_SDK_ClearCallHistroy(int _callType)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM1(_callType);

	int iRet = UCHistoryMgr::Instance().ClearCallHistory(_callType);

	DEBUG_LOG() << "--- LEAVE";

	return iRet;

}

int __UC_SDK_CALL UC_SDK_InsertCallHistory(int _CallType,const char* _account,const char* _name,int _duration)
{
	DEBUG_LOG() << "--- ENTER";
	if(NULL == _account)
	{
		ERROR_LOG() << "account is NULL.";
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_account))
	{
		ERROR_LOG() << "account length is 0.";
		return UC_SDK_InvalidPara;
	}
	if(NULL == _name)
	{
		ERROR_LOG() << "name is NULL.";
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_name))
	{
		ERROR_LOG() << "name length is 0.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM4(_CallType,_account,_name,_duration);

	int iRet = UCHistoryMgr::Instance().InsertCallHistory(_CallType,_account,_name,_duration);

	DEBUG_LOG() << "--- LEAVE";

	return iRet;

}

int __UC_SDK_CALL UC_SDK_QueryConvHistory(int _fromIndex,int _toIndex,STConvHistroyData* _result,int _size)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM3(_fromIndex,_toIndex,_size);

	if(NULL == _result)
	{
		ERROR_LOG() << "_queryResult is NULL.";
		return UC_SDK_InvalidPara;
	}

	if(_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG() << "query para is invalid.";
		return UC_SDK_InvalidPara;
	}

	int querySize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STConvHistroyData)+(unsigned int)(querySize-1)*sizeof(STConvHistroyItem));
	if(_size != iSize)
	{
		ERROR_LOG() << "memory size is invalid.";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCHistoryMgr::Instance().QueryConvHistory(_fromIndex,_toIndex,_result);

	DEBUG_LOG() << "--- LEAVE";

	return iRet;

}
int __UC_SDK_CALL UC_SDK_QueryHisConvPartByID(const char* _convID,int _fromIndex,int _toIndex,STConfPartData* _result,int _size)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM3(_fromIndex,_toIndex,_size);

	if(NULL == _convID)
	{
		ERROR_LOG() << "convID is null.";
		return UC_SDK_InvalidPara;
	}

	if(0 == strlen(_convID))
	{
		ERROR_LOG() << "convID is empty.";
		return UC_SDK_InvalidPara;
	}

	if(NULL == _result)
	{
		ERROR_LOG() << "_queryResult is NULL.";
		return UC_SDK_InvalidPara;
	}

	if(_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG() << "query para is invalid.";
		return UC_SDK_InvalidPara;
	}

	int querySize = (_toIndex-_fromIndex)+1;	
	int iSize = (int)(sizeof(STConfPartData)+(unsigned int)(querySize-1)*sizeof(STConfPartItem));
	if(_size != iSize)
	{
		ERROR_LOG() << "memory size is invalid.";
		return UC_SDK_InvalidPara;
	}

	int iRet = UCHistoryMgr::Instance().QueryHisConvPartByID(_convID,_fromIndex,_toIndex,_result);


	DEBUG_LOG() << "--- Leave";

	return iRet;
}

int __UC_SDK_CALL UC_SDK_ClearConvHistroy()
{
	DEBUG_LOG() << "--- ENTER";

	INFO_LOG();

	int iRet = UCHistoryMgr::Instance().ClearConvHistory();

	DEBUG_LOG() << "--- LEAVE";

	return iRet;
}

int __UC_SDK_CALL UC_SDK_InsertConvHistory(const char* _leaderAccount,const char* _leaderName,int _duration,char _historyID[STRING_LENGTH])
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _leaderAccount)
	{
		ERROR_LOG() << "leaderAccount is NULL.";
		return UC_SDK_InvalidPara;
	}

	if(NULL == _leaderName)
	{
		ERROR_LOG() << "leaderName is NULL.";
		return UC_SDK_InvalidPara;
	}

	std::string strHisID = eSDKTool::CreateGuidStr();
	if("" == strHisID)
	{
		ERROR_LOG() << "creat strHisID failed";

		return UC_SDK_Failed;
	}

	INFO_PARAM3(_leaderAccount,_leaderName,_duration);

	int iRet = UCHistoryMgr::Instance().InsertConvHistory(strHisID,_leaderAccount,_leaderName,_duration);

	if(UC_SDK_Success == iRet)
	{
		ctk::MemSet(_historyID,0,STRING_LENGTH);
		ctk::MemCopy(_historyID,strHisID.c_str(),(strHisID.size()<(STRING_LENGTH)) ? (strHisID.size()) : (STRING_LENGTH-1) );
	}

	DEBUG_LOG() << "--- LEAVE";

	return iRet;
}

int __UC_SDK_CALL UC_SDK_InsertConvHistoryPart(const char* _historyConvID,const char* _partAccount,const char* _partName)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _historyConvID)
	{
		ERROR_LOG() << "historyConvID is NULL.";
		return UC_SDK_InvalidPara;
	}

	if(0 == strlen(_historyConvID))
	{
		ERROR_LOG() << "historyConvID size is 0.";
		return UC_SDK_InvalidPara;

	}

	if(NULL == _partAccount)
	{
		ERROR_LOG() << "partAccount is NULL.";
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_partAccount))
	{
		ERROR_LOG() << "partAccount size is 0.";
		return UC_SDK_InvalidPara;

	}

	if(NULL == _partName)
	{
		ERROR_LOG() << "partName is NULL.";
		return UC_SDK_InvalidPara;
	}
	if(0 == strlen(_partName))
	{
		ERROR_LOG() << "partName size is 0.";
		return UC_SDK_InvalidPara;

	}

	INFO_PARAM3(_historyConvID,_partAccount,_partName);

	int iRet = UCHistoryMgr::Instance().InsertConvHistoryPart(_historyConvID,_partAccount,_partName);

	DEBUG_LOG() << "--- LEAVE";

	return iRet;
}

int __UC_SDK_CALL UC_SDK_DeleteCallHistory(int iRcdID)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(iRcdID);

	int iRet = UCHistoryMgr::Instance().DeleteCallHistory(iRcdID);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_DeleteConvHistory(const char* _pConvID)
{
	DEBUG_LOG() << "--- ENTER";
	if(NULL == _pConvID)
	{
		ERROR_LOG() << "invalid  ConvID.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM1(_pConvID);

	std::string strConvID(_pConvID);
	int iRet = UCHistoryMgr::Instance().DeleteConvHistory(strConvID);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_GetPhoneJointDevType(int& _iDevType)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM1(_iDevType);

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotLogin;
	}


	int iRet = UCConfigMgr::Instance().GetPhoneJointDevType(_iDevType);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_SetPhoneJointDevType(int _iDevType)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(_iDevType);
	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}

	
	int iRet = UCConfigMgr::Instance().SetPhoneJointDevType(_iDevType);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_SetPhoneJointEventCallBack(PhoneJointEventCB pjEventCallBack)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(pjEventCallBack);
	int iRet = UCConfigMgr::Instance().SetPhoneJointEventCB(pjEventCallBack);
	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_OpenPortal(int _type)
{
	DEBUG_LOG() << "--- ENTER";

	INFO_PARAM1(_type);
	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		return UC_SDK_NotLogin;
	}	

	int iRet = UCConfigMgr::Instance().OpenPortal(_type);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

int __UC_SDK_CALL UC_SDK_PubSelfStatus(int _Status,const char* _Desc)
{
	DEBUG_LOG() << "--- ENTER";
	INFO_PARAM1(_Status);

	if(UC_SDK_Success != UCRegManager::Instance().CheckSignStatus())
	{
		ERROR_LOG() << "Publish self status failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_NotLogin;
	}

	if(_Status < Offline || _Status > NoDisturb)
	{
		ERROR_LOG() << "invalid  status.";
		return UC_SDK_InvalidPara;
	}
	if(NULL == _Desc)
	{
		ERROR_LOG() << "invalid  Desc.";
		return UC_SDK_InvalidPara;
	}

	std::string strDesc(_Desc);
	int iRet = UCRegManager::Instance().PubSelfStatus((ContactAvailability)_Status,strDesc);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

int __UC_SDK_CALL UC_SDK_GetContactStatus(int _AccountType,const char* _Account,int& _Status)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _Account)
	{
		ERROR_LOG() << "account is NULL.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM2(_AccountType,_Account);

	//非UC账户直接设置为离线
	if(UC_ACCOUNT != _AccountType)
	{
		_Status = Offline;
		INFO_LOG() << _Account << " is Offline.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_Success;
	}

	std::string strAccount(_Account);
	int iRet = UCRegManager::Instance().GetContactStatus(strAccount,_Status);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}

int __UC_SDK_CALL UC_SDK_GetContactInfo(const char* _Account,STContact* _pContactInfo)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _Account)
	{
		ERROR_LOG() << "account is NULL.";
		return UC_SDK_InvalidPara;
	}

	if(NULL == _pContactInfo)
	{
		ERROR_LOG() << "_pContactInfo is NULL.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM1(_Account);

	std::string strAccount(_Account);
	int iRet = UCRegManager::Instance().GetContactInfo(strAccount,*_pContactInfo);


	DEBUG_LOG() << "--- LEAVE";
	return iRet;



}

int __UC_SDK_CALL UC_SDK_SubscribeStatus(const char* _Account)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == _Account)
	{
		ERROR_LOG() << "account is NULL.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM1(_Account);
	std::string strAccount(_Account);

	Contact _contact;	
	if (UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount, _contact))
	{
		ERROR_LOG() << "getContact by Account failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_FindUriErr;
	}

	std::string strUri = _contact.uri_;
	int iRet = UCRegManager::Instance().SubscribeStatus(strUri);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;
}

int __UC_SDK_CALL UC_SDK_UnSubscribeStatus(const char* account)
{
	DEBUG_LOG() << "--- ENTER";

	if(NULL == account)
	{
		ERROR_LOG() << "account is NULL.";
		return UC_SDK_InvalidPara;
	}

	INFO_PARAM1(account);
	std::string strAccount(account);

	Contact cont_;	
	if (UC_SDK_Success != UCContactMgr::Instance().getContactByAccount(strAccount, cont_))
	{
		ERROR_LOG() << "getContact by Account failed.";
		DEBUG_LOG() << "--- LEAVE";
		return UC_SDK_FindUriErr;
	}

	std::string strUri = cont_.uri_;
	int iRet = UCRegManager::Instance().DisSubscribeStatus(strUri);

	DEBUG_LOG() << "--- LEAVE";
	return iRet;

}


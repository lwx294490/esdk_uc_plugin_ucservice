#ifndef _UC_CALL_MGR_H_
#define _UC_CALL_MGR_H_

#include "UCSDKObserver.h"

//呼叫管理
class UCCallManager
{
public:
	UCCallManager(void);
	~UCCallManager(void);
public:
	static inline UCCallManager& Instance()
	{
		return *ctk::Singleton_T<UCCallManager>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCCallManager>::destroy();
	}
public:
	void Init(void);
	void Uninit(void);
public:
	int InsertUCMember(const std::string& _ucUri);//插入UC成员
	int InsertPhoneMember(const std::string& _phone);//插入电话成员
	int MakeCall(void);
	int HoldCall(void);
	int ResumeCall(void);
	int MakeVideoCall(const STVideoWindow& stLocalWnd,const STVideoWindow& stRemoteWnd);
	int HangupCall(void);
	int HangupVideoCall(void);
	int AcceptCall(void);
	int AcceptVideoCall(const STVideoWindow& stLocalWnd,const STVideoWindow& stRemoteWnd);
	int RejectCall(void);
	int RejectCall(const std::string& conversationID);
	int RejectVideoCall(void);
	int SendDTMF(char tone);
	int ForwardCall(EM_MemberType iMemberType, const std::string& strMember);
	
	int SetCallEventCB(AVSessionClosedCB _aVSessionClosedCallBack,
							  AVSessionConnectedCB _aVSessionConnectedCallBack,
							  AVSessAddedCB _aVSessAddedCallBack);
	int SetCallEventCB(VideoCallEventCB _callEventCallBack)const;
	int SetConfMemEventCB(ConfMemberEventCB _confmemberEventCB)const;
	void ConectConfSignal(conversation::Conversation* pConversation);
	void DisConectConfSignal(conversation::Conversation* pConversation)const;
	void ConectVideoSignal(conversation::AVSession* pAVSess);
	void DisConectVideoSignal(conversation::AVSession* pAVSess)const;

	//会议
public:
	int InviteMemberInCall(EM_MemberType _memberType,const std::string& strAccount);
	int DeleteMemberInCall(EM_MemberType _memberType,const std::string& strAccount);
	int ModifyMemberStatusInCall(EM_ConvnerOperateType operateType, EM_MemberType _memberType,const std::string& strAccount);
	int UpdateConvMember(const std::string&,EM_MemStatusInCall);
	int ClearConvMember(void);
	int ClearConvID(void);
	int ClearCallMember(void);
	void ShowConvMember(conversation::Conversation* _pConv);
	bool GetConvStarted()const;
private:
	conversation::AVSession* GetAVSession();
	conversation::InstantMsgSession* GetIMSession();
	conversation::AVSession* AddAVSession();
	conversation::Conversation* GetConversation();	
	int GetMemberInCall(conversation::Conversation* pConversation,const std::string& strUri,Contact& _contact);
	int CreateTempGroup();
	
private:	
	typedef std::set<std::string> CallList;	
	CallList m_MemUriList;//成员Uri列表
	CallList m_MemPhoneList;//成员phone列表

	typedef std::map<std::string,EM_MemStatusInCall> ConvMemberMap;
	ConvMemberMap m_ConvMemberMap;

	ctk::Mutex m_mtx;//操作会议成员的锁
	ctk::Mutex m_ConvMutex;//操作会议成员的锁
	bool isConfStart;		//会议已经开始
	CallEvent m_CallEvent;//呼叫事件
	ConfEvent m_ConferenceEvent;
	VideoChannelEvent m_VideoEvent;
public:
	std::string m_ConversationID;
	ConversationMgr* m_pConvMgr;
	static UCSDKObserver	m_UCSDKObserver;
	static AVSessionClosedCB OnAVSessionClosedCB;			//呼叫断开回调函数指针
	static AVSessionConnectedCB OnAVSessionConnectedCB;		//连接成功回调函数指针
	static AVSessAddedCB OnAVSessAddedCB;					//新呼叫连接回调函数指针
	static ConfMemberEventCB OnConfMemberEventCB;
	static VideoCallEventCB OnVideoCallEventCB;
public:
	ConversationMgr* GetConvMgr(void)
	{
		return m_pConvMgr;
	}
	const std::string& GetConvID(void)const
	{
		return m_ConversationID;
	}
	void SetConvID(std::string ConvID_)
	{
		m_ConversationID = ConvID_;
	}
};

#endif



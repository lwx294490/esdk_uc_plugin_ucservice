#ifndef _UC_CALL_MGR_H_
#define _UC_CALL_MGR_H_

#include "UCSDKObserver.h"

//���й���
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
	int InsertUCMember(const std::string& _ucUri);//����UC��Ա
	int InsertPhoneMember(const std::string& _phone);//����绰��Ա
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

	//����
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
	CallList m_MemUriList;//��ԱUri�б�
	CallList m_MemPhoneList;//��Աphone�б�

	typedef std::map<std::string,EM_MemStatusInCall> ConvMemberMap;
	ConvMemberMap m_ConvMemberMap;

	ctk::Mutex m_mtx;//���������Ա����
	ctk::Mutex m_ConvMutex;//���������Ա����
	bool isConfStart;		//�����Ѿ���ʼ
	CallEvent m_CallEvent;//�����¼�
	ConfEvent m_ConferenceEvent;
	VideoChannelEvent m_VideoEvent;
public:
	std::string m_ConversationID;
	ConversationMgr* m_pConvMgr;
	static UCSDKObserver	m_UCSDKObserver;
	static AVSessionClosedCB OnAVSessionClosedCB;			//���жϿ��ص�����ָ��
	static AVSessionConnectedCB OnAVSessionConnectedCB;		//���ӳɹ��ص�����ָ��
	static AVSessAddedCB OnAVSessAddedCB;					//�º������ӻص�����ָ��
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



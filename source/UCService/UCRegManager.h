#ifndef _UC_REG_MGR_H_
#define _UC_REG_MGR_H_


//ע�����
class UCRegManager
{
public:
	UCRegManager(void);
	~UCRegManager(void);
public:
	static inline UCRegManager& Instance()
	{
		return *ctk::Singleton_T<UCRegManager>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCRegManager>::destroy();
	}
private:
	ctk::Mutex m_RegMutex;//����ע�����ָ������������ʼ���ͷǳ�ʼ�����߳����ݲ�һ��
	uc::model::UCClient* m_pUCClient;
	RegEvent m_RegEvent;
public:
	uc::model::UCSelf* m_pSelf;
	uc::model::ContactSubscription*  m_pSubscribeMgr;	
	static ClientSignInNotifyCB OnClientSignInNotifyCB;
	static StatusChangedCB OnStatusChangedCB;
public:
	void Init(void);
	void Uninit(void);
	void InitSubscribe(void);
	void UnInitSubscribe(void);
	int SignInByPWD(const std::string& _account,const std::string& _pwd,const std::string& _serverUrl,const std::string& _langID);//ʹ�������½
	int SignOut(void);
	int SetLoginEventCB(ClientSignInNotifyCB _loginEventCB);
	int SetStatusEventCB(StatusChangedCB _statusEventCB);
	int PubSelfStatus(ContactAvailability _state,const::string& _desc);
	int SubscribeStatus(const std::string& _strUri);//����״̬
	int DisSubscribeStatus(const std::string& _strUri);//ȥ����״̬
	int NotifyStatus(const Contact& _contact,ContactAvailability _state,const std::string& _desc);//�ϱ���ϵ��״̬
	int CheckSignStatus(void);//����Ƿ��¼
	int GetContactStatus(const std::string& _account,int& _status);
	int GetContactInfo(const std::string& _account,STContact& _Contact);
	int GetSigninErrorDesc(const std::string _para,std::string& _errordesc);
	
};

#endif



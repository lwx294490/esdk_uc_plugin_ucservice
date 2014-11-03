#ifndef _UC_CONFIG_H
#define _UC_CONFIG_H

class UCConfigMgr : public ctk::ThreadOwner
{
public:
	UCConfigMgr(void);
	~UCConfigMgr(void);
	static inline UCConfigMgr& Instance()
	{
		return *ctk::Singleton_T<UCConfigMgr>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCConfigMgr>::destroy();
	}
protected:
	virtual void onThreadExit(ctk::Thread* _thr);
private:
	uc::model::UCSelf* m_pUCSelf;
	uc::model::conversation::ConversationMgr* m_pConvMgr;
	std::string m_ConfigPath;
public:
	void Init(void);
	void Uninit(void);
	int GetPhoneJointDevType(int& _iDevType);//��ȡ���������豸����
	int SetPhoneJointDevType(int _iDevType);//���û��������豸����
	int SetPhoneJointEventCB(PhoneJointEventCB _EventCB)const;//���û���������Ϣ�ص�
	void ConectPhoneJointSignal();
	void DisConectPhoneJointSignal();
	int OpenPortal(int);
public:
	PhoneJointEvent m_phoneJointEvent;	//������������
	static PhoneJointEventCB m_OnPJEventCB;

private:
	//�����¼�߳�
	class SSOClient : public ctk::SimpleThread
	{
	private:
		SSOClient():ctk::SimpleThread(NULL,"SSO"),m_PortalType(0)
		{
		}
	public:
		SSOClient(ctk::ThreadOwner* _owner):ctk::SimpleThread(_owner, "SSO"),m_PortalType(0)
		{
		}
		void SetPortalType(int _type)
		{
			m_PortalType = _type;
		}

	protected:
		virtual void run();
	private:
		int m_PortalType;

	};
	ctk::Handle<SSOClient> m_pSSOClient;
};

#endif

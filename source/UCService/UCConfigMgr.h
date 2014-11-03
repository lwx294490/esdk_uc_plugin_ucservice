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
	int GetPhoneJointDevType(int& _iDevType);//获取话机联动设备类型
	int SetPhoneJointDevType(int _iDevType);//设置话机联动设备类型
	int SetPhoneJointEventCB(PhoneJointEventCB _EventCB)const;//设置话机联动消息回调
	void ConectPhoneJointSignal();
	void DisConectPhoneJointSignal();
	int OpenPortal(int);
public:
	PhoneJointEvent m_phoneJointEvent;	//话机联动设置
	static PhoneJointEventCB m_OnPJEventCB;

private:
	//单点登录线程
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

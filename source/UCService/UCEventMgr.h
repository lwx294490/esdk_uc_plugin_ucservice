#ifndef _UC_EVENT_MGR_
#define _UC_EVENT_MGR_

class UCEventMgr : public ctk::ThreadOwner
{
public:
	//�²����ϲ��׵��¼����ͣ��������ϲ����
	enum EventType
	{
		REG_EVENT=0,			//ע����֪ͨ
		CALL_CONNECT_EVENT,		//���н�ͨ�¼�
		CALL_CLOSE_EVENT,		//���н����¼�
		CALL_INCOMING_EVENT,	//�������¼�
		CONV_EVENT,				//�����е��¼�
		VIDEO_EVENT,			//��Ƶ���е��¼�
		PJ_NOTIFY_EVENT,		//�����������ý��֪ͨ�¼�
		RejectNewCall_EVENT,	//������Զ��ܾ��������¼�
		PUB_PJ_EVENT,			//������������״̬�¼�
		CONTACT_STATUS_EVENT	//״̬�¼�
	};
	static inline UCEventMgr& Instance()
	{
		return *ctk::Singleton_T<UCEventMgr>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCEventMgr>::destroy();
	}

	UCEventMgr();
	~UCEventMgr();
	void WaitAgentStart() const;//�ȴ��߳�����
public:
	void NotifyStatusEvent(const std::string& _strPara);
	void NotifyPubPJEvent(const std::string& _strPara);
	void NotifyCallCloseEvent(const std::string& _strPara) ;
	void NotifyCallConnectedEvent(const std::string& _strPara) ;
	void NotifyVideoEvent(const std::string& _strPara) ;
	void NotifyCallIncomingEvent(const std::string& _strPara) ;
	void NotifyConvMemEvent(const std::string& _strPara) ;
	void NotifyPJEvent(const std::string& _strPara) ;
	void NotifyRejectNewCallEvent(const std::string& _strPara) ;
protected:
	virtual void onThreadExit(ctk::Thread* _thr);
private:

	//�¼�������
	class EventAgent : public ctk::SimpleThread
	{
	private:
		EventAgent():ctk::SimpleThread(NULL,"event"),m_EventPara(""),m_eventType(REG_EVENT)
		{
		}
	public:
		EventAgent(ctk::ThreadOwner* _owner):ctk::SimpleThread(_owner, "event"),m_EventPara(""),m_eventType(REG_EVENT)
		{
		}
		void SetEventPara(EventType _eventType,const std::string& _strPara);
	protected:
		virtual void run();
	public:		
		bool OnNotifyEvent(void);
		void NotifyCallClosed(void) const;
		void NotifyCallConnect(void) const;
		void NotifyCallIncoming(void) const;
		void NotifyConv(void) const;
		void NotifyVideo(void) const;
		void NotifyPhoneJointCB(void) const;
		void NotifyRejectNewCall(void) const;
		void NotifyPublishPJ(void) const;
		void NotifyContactStatus(void) const;
	private:
		std::string m_EventPara;//�¼�����
		EventType m_eventType;		
	};
	ctk::Handle<EventAgent> m_pAgent;

};


#endif



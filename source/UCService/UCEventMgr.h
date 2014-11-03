#ifndef _UC_EVENT_MGR_
#define _UC_EVENT_MGR_

class UCEventMgr : public ctk::ThreadOwner
{
public:
	//下层向上层抛的事件类型，不包含上层调用
	enum EventType
	{
		REG_EVENT=0,			//注册结果通知
		CALL_CONNECT_EVENT,		//呼叫接通事件
		CALL_CLOSE_EVENT,		//呼叫结束事件
		CALL_INCOMING_EVENT,	//新来电事件
		CONV_EVENT,				//会议中的事件
		VIDEO_EVENT,			//视频呼叫的事件
		PJ_NOTIFY_EVENT,		//话机联动设置结果通知事件
		RejectNewCall_EVENT,	//来电后自动拒绝新来电事件
		PUB_PJ_EVENT,			//发布话机联动状态事件
		CONTACT_STATUS_EVENT	//状态事件
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
	void WaitAgentStart() const;//等待线程启动
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

	//事件代理类
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
		std::string m_EventPara;//事件参数
		EventType m_eventType;		
	};
	ctk::Handle<EventAgent> m_pAgent;

};


#endif



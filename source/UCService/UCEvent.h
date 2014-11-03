#ifndef _UC_EVENT_
#define _UC_EVENT_

class RegEvent :public has_slots<sigslot::multi_threaded_local>
{
public:
	//Sign In Signal
	void OnSignInNotify(UCClient::SignInState _state, std::string _reason);
	//StatusChange Signal
	void OnStatusChanged(ContactAvailability _state,std::string _desc,const Contact& _contact, std::string _param);
	//sip reg
	void OnSipRegNotify(int);
};

class CallEvent :public has_slots<sigslot::multi_threaded_local>
{
public:
	void OnCallRing(conversation::Conversation* _pConv,std::string _remoreuri);
	void OnCallClosed(conversation::Conversation* _pConv,  conversation::sMsgAVSessionClosedParam& _avParam);
	void OnCallConnected(conversation::Conversation* _pConv);
	void OnCallIncoming(conversation::Conversation* _pConv,conversation::sAudioVideoParam& _param);	
};

//�������󣬻����Ա��״̬֪ͨ�źŴ�����
class ConfEvent: public has_slots<sigslot::multi_threaded_local>
{
public:
	//���鷢���ߴ���IM��ʱȺʱ�յ����¼�
	void OnConvIMConnected(conversation::Conversation* _conv);

	//�����Ա״̬�仯ʱ���յ����¼�
	void OnConvStatusChanged(conversation::Conversation* _conv, int _chgtype, std::string _name);


	void OnConvAllowSpk(conversation::Conversation*, conversation::Participant _sess); 
	void OnConvForbidSpk(conversation::Conversation*, conversation::Participant _sess); 
	void OnConvCurSpker(conversation::Conversation*, std::string _spkerUri);
	void OnConvNumChanged(conversation::Conversation* _conv,
		std::vector<std::string> _kicklist,
		std::vector<std::string> _addlist);
	void OnConvDelSucc(conversation::Conversation* _conv,const std::string _parti);
	void OnConvRequestToSpeak(conversation::Conversation* _conv,const std::string _parti,bool bUnmute);
	void OnInstantSessMerged(conversation::Conversation* _conv,conversation::Conversation* _convmerged);
	void OnMuteAllAttender(conversation::Conversation* _conv,bool bSuc);
	void OnSetVideoSource(conversation::Conversation* _conv,const std::string _parti);
};

//��Ƶͨ��״̬
class VideoChannelEvent: public has_slots<sigslot::multi_threaded_local>
{
public:
	void OnChannelStateChanged(conversation::avchannel::ChannelState _state, 
		conversation::Session* _pSess);
};

//��������״̬
class PhoneJointEvent: public has_slots<sigslot::multi_threaded_local>
{
public:
	void OnPhoneJointRelated(int);
};


#endif


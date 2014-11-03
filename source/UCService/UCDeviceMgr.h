#ifndef _UC_DEVICEMGR_H_
#define _UC_DEVICEMGR_H_

class UCDeviceMgr
{
public:
	UCDeviceMgr(void);
	~UCDeviceMgr(void);
public:
	static inline UCDeviceMgr& Instance()
	{
		return *ctk::Singleton_T<UCDeviceMgr>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCDeviceMgr>::destroy();
	}
public:
	void Init(void);
	void Uninit(void);
public:
	uc::model::device::SpeakerDev* GetSpkDevice(void);
public:
	//ˢ���豸����
	void UpdateDevCfg(void);
	//��˷����
	int MuteMic()const;
	int UnMuteMic()const;
	int GetMicLevel(int& level)const;
	int SetMicLevel(int level)const;
	//����������
	int MuteSpeaker()const;
	int UnMuteSpeaker()const;
	int GetSpeakerLevel(int& level)const;
	int SetSpeakerLevel(int level)const;
	//��ȡ��˷��豸�б�
	int GetMicDevList(int _fromIndex, int _toIndex, STDeviceListParam* devList);
	//��ȡ�������豸�б�
	int GetSpeakerDevList(int _fromIndex, int _toIndex, STDeviceListParam* devList);
	//��ȡ��Ƶ�豸�б�
	int GetVideoDevList(int _fromIndex, int _toIndex, STDeviceListParam* devList);
	//��ȡ��ǰ��˷��豸
	int GetCurrentMicDev(STDeviceParam* device)const;
	//��ȡ��ǰ�������豸
	int GetCurrentSpeakerDev(STDeviceParam* device)const;
	//��ȡ��ǰ��Ƶ�豸
	int GetCurrentVideoDev(STDeviceParam* device)const;
	//���õ�ǰ��˷��豸
	int SetCurrentMicDev(int index);
	//���õ�ǰ�������豸
	int SetCurrentSpeakerDev(int index);
	//���õ�ǰ��Ƶ�豸
	int SetCurrentVideoDev(int index);

public:
	uc::model::device::DeviceMgr* m_pDevMgr;
};

#endif



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
	//刷新设备配置
	void UpdateDevCfg(void);
	//麦克风管理
	int MuteMic()const;
	int UnMuteMic()const;
	int GetMicLevel(int& level)const;
	int SetMicLevel(int level)const;
	//扬声器管理
	int MuteSpeaker()const;
	int UnMuteSpeaker()const;
	int GetSpeakerLevel(int& level)const;
	int SetSpeakerLevel(int level)const;
	//获取麦克风设备列表
	int GetMicDevList(int _fromIndex, int _toIndex, STDeviceListParam* devList);
	//获取扬声器设备列表
	int GetSpeakerDevList(int _fromIndex, int _toIndex, STDeviceListParam* devList);
	//获取视频设备列表
	int GetVideoDevList(int _fromIndex, int _toIndex, STDeviceListParam* devList);
	//获取当前麦克风设备
	int GetCurrentMicDev(STDeviceParam* device)const;
	//获取当前扬声器设备
	int GetCurrentSpeakerDev(STDeviceParam* device)const;
	//获取当前视频设备
	int GetCurrentVideoDev(STDeviceParam* device)const;
	//设置当前麦克风设备
	int SetCurrentMicDev(int index);
	//设置当前扬声器设备
	int SetCurrentSpeakerDev(int index);
	//设置当前视频设备
	int SetCurrentVideoDev(int index);

public:
	uc::model::device::DeviceMgr* m_pDevMgr;
};

#endif



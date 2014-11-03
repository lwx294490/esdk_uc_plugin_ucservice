#include "StdAfx.h"
#include "UCDeviceMgr.h"
#include "UCRegManager.h"

//媒体设置
const std::string SETTING_MEDIA_AUDIOINPUTDEVICE = "AudioInputDevice";
const std::string SETTING_MEDIA_AUDIOOUTPUTDEVICE = "AudioOutputDevice";
const std::string SETTING_MEDIA_VIDEODEVICE = "VideoDevice";

UCDeviceMgr::UCDeviceMgr(void):m_pDevMgr(NULL)
{
}

UCDeviceMgr::~UCDeviceMgr(void)
{
	m_pDevMgr = NULL;
}

void UCDeviceMgr::Init(void)
{
	uc::model::UCClient* pUCClient = UCClient::GetClient();
	if(NULL == pUCClient)
	{
		ERROR_LOG() << "m_pUCClient is NULL.";
		return;
	}
	m_pDevMgr = pUCClient->DeviceManager;
	if(NULL != m_pDevMgr)
	{
		if(!m_pDevMgr->Init())
		{
			WARN_LOG() << "Init Device Failed.";
		}		
	}

	return;
	
}
void UCDeviceMgr::Uninit(void)
{
	if(NULL == m_pDevMgr)
	{
		ERROR_LOG() << "m_pDevMgr is NULL.";
		return;
	}
	if(!m_pDevMgr->Uninit())
	{
		WARN_LOG() << "UnInit Device Failed.";
	}
	m_pDevMgr = NULL;
}
uc::model::device::SpeakerDev* UCDeviceMgr::GetSpkDevice(void)
{
	if(NULL == m_pDevMgr)
	{
		ERROR_LOG() << "m_pDevMgr is NULL.";
		return NULL;
	}
	return m_pDevMgr->activespkerdev;
}//lint !e1762  SpeakerDev在外部需要修改
void UCDeviceMgr::UpdateDevCfg(void)
{
	if(NULL == UCRegManager::Instance().m_pSelf)
	{
		ERROR_LOG() << "Self is NULL.";
		return;
	}
	if(NULL == m_pDevMgr)
	{
		ERROR_LOG() << "m_pDevMgr is NULL.";
		return;
	}

	//获取麦克风设备
	std::string microDevName("");
	UCRegManager::Instance().m_pSelf->simplecfg_.GetUserConfig(SETTING_MEDIA_AUDIOINPUTDEVICE,microDevName);	
	if (!microDevName.empty())
	{
		unsigned int micCount = m_pDevMgr->micdevlist.size();
		for (unsigned int i = 0; i < micCount; ++i)
		{
			std::string & devname = m_pDevMgr->micdevlist[i]->name;
			if (microDevName == devname)
			{
				INFO_LOG() << "current selected audio input device: [" <<  i << "] " << eSDKTool::utf82unicode(devname);
				m_pDevMgr->SetAudioCaptureDev(i);
				break;
			}
		}
	}

	//获取扬声器设备
	std::string spkerDevName("");
	UCRegManager::Instance().m_pSelf->simplecfg_.GetUserConfig(SETTING_MEDIA_AUDIOOUTPUTDEVICE,spkerDevName);	
	if (!spkerDevName.empty())
	{
		unsigned int spkerCount = m_pDevMgr->speakerdevlist.size();
		for (unsigned int i = 0; i < spkerCount; ++i)
		{
			std::string & devname = m_pDevMgr->speakerdevlist[i]->name;
			if (spkerDevName == devname)
			{
				INFO_LOG() << "current selected audio output device: [" <<  i << "] " << eSDKTool::utf82unicode(devname);
				m_pDevMgr->SetAudioPlayDev(i);
				break;
			}
		}
	}

	//获取视频设备
	std::string videoDevName("");
	UCRegManager::Instance().m_pSelf->simplecfg_.GetUserConfig(SETTING_MEDIA_VIDEODEVICE,videoDevName);	
	if (!videoDevName.empty())
	{
		unsigned int videoCount = m_pDevMgr->videodevlist.size();
		for (unsigned int i = 0; i < videoCount; ++i)
		{
			std::string & devname = m_pDevMgr->videodevlist[i]->name;
			if (videoDevName == devname)
			{
				INFO_LOG() << "current selected video device: [" <<  i << "] " << eSDKTool::utf82unicode(devname);
				m_pDevMgr->SetVideoCaptureDev(i);
			}
		}
	}

	return;
}

int UCDeviceMgr::MuteMic()const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activemicdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activemicdev is null pointer.";
		return UC_SDK_Failed;
	}

	if(!m_pDevMgr->activemicdev->Mute())
	{
		WARN_LOG() << "Mute Failed.";
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;

}
int UCDeviceMgr::UnMuteMic()const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activemicdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activemicdev is null pointer.";
		return UC_SDK_Failed;
	}

	if(!m_pDevMgr->activemicdev->UnMute())
	{
		WARN_LOG() << "UnMute Failed.";
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCDeviceMgr::GetMicLevel(int& level)const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activemicdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activemicdev is null pointer.";
		return UC_SDK_Failed;
	}

	level =  m_pDevMgr->activemicdev->GetVolume();
	return UC_SDK_Success;

}
int UCDeviceMgr::SetMicLevel(int level)const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activemicdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activemicdev is null pointer.";
		return UC_SDK_Failed;
	}

	if(!m_pDevMgr->activemicdev->SetVolume(level))
	{
		WARN_LOG() << "SetVolume Failed.";
		return UC_SDK_Failed;
	}
	return UC_SDK_Success;
}

int UCDeviceMgr::MuteSpeaker()const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activespkerdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activespkerdev is null pointer.";
		return UC_SDK_Failed;
	}

	if(!m_pDevMgr->activespkerdev->Mute())
	{
		WARN_LOG() << "Mute Failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}
int UCDeviceMgr::UnMuteSpeaker()const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activespkerdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activespkerdev is null pointer.";
		return UC_SDK_Failed;
	}

	if(!m_pDevMgr->activespkerdev->UnMute())
	{
		WARN_LOG() << "UnMute Failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}
int UCDeviceMgr::GetSpeakerLevel(int& level)const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activespkerdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activespkerdev is null pointer.";
		return UC_SDK_Failed;
	}

	level = m_pDevMgr->activespkerdev->GetVolume();

	return UC_SDK_Success;

}
int UCDeviceMgr::SetSpeakerLevel(int level)const
{
	if(NULL == m_pDevMgr || NULL == m_pDevMgr->activespkerdev)
	{
		ERROR_LOG() << "m_pDevMgr or m_pDevMgr->activespkerdev is null pointer.";
		return UC_SDK_Failed;
	}

	if(!m_pDevMgr->activespkerdev->SetVolume(level))
	{
		WARN_LOG() << "SetVolume Failed.";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;

}

//获取麦克风设备列表
int UCDeviceMgr::GetMicDevList(int _fromIndex, int _toIndex, STDeviceListParam* micDevList)
{
	//UC_SDK_GetMicDevList()调用GetMicDevList()前，已经对入参数值和字节大小进行判断。这里仅进行简单判断
	if (NULL == m_pDevMgr || NULL == micDevList)
	{
		ERROR_LOG() << "m_pDevMgr or devList is null pointer";
		return UC_SDK_NullPtr;
	}
	if (_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG() << "_fromIndex < 0 or _toIndex < 0 or fromIndex > toIndex";
		return UC_SDK_InvalidPara;
	}
	
	micDevList->iTotal = (int)m_pDevMgr->micdevlist.size();
	if(0 == micDevList->iTotal)
	{
		INFO_LOG() << "micDevList size is 0";
		return UC_SDK_Success;
	}
	if(_fromIndex >= micDevList->iTotal)
	{
		ERROR_LOG() << "_fromIndex >= m_pDevMgr->micdevlist.size()";
		return UC_SDK_InvalidPara;
	}
	if (_toIndex > micDevList->iTotal-1)
	{
		_toIndex = micDevList->iTotal-1;
	}
	micDevList->iFrom = _fromIndex;
	micDevList->iTo = _toIndex;

	for (int i=_fromIndex; i<=_toIndex; i++)
	{
		uc::model::device::MicDev* pMicDev = m_pDevMgr->micdevlist[(unsigned int)i];
		if (NULL == pMicDev)
		{
			ERROR_LOG() << "m_pDevMgr->micdevlist[i] is null pointer.";
			return UC_SDK_Failed;
		}

		int index = i-_fromIndex;

		std::string name = eSDKTool::utf82unicode(pMicDev->name);
		ctk::MemSet(micDevList->deviceList[index].name,0,STRING_LENGTH);
		ctk::MemCopy(micDevList->deviceList[index].name,name.c_str(),(name.size()<(STRING_LENGTH)) ? (name.size()) : (STRING_LENGTH-1));
		ctk::MemSet(micDevList->deviceList[index].deviceId,0,STRING_LENGTH);
		ctk::MemCopy(micDevList->deviceList[index].deviceId,pMicDev->deviceId.c_str(),(pMicDev->deviceId.size()<(STRING_LENGTH)) ? (pMicDev->deviceId.size()) : (STRING_LENGTH-1));		

		micDevList->deviceList[index].index = pMicDev->index;
		micDevList->deviceList[index].iscertified = (int)pMicDev->iscertified;
		micDevList->deviceList[index].isactive = (int)pMicDev->isactive;
		micDevList->deviceList[index].type = (int)pMicDev->type;
	}

	return UC_SDK_Success;
}
//获取扬声器设备列表
int UCDeviceMgr::GetSpeakerDevList(int _fromIndex, int _toIndex, STDeviceListParam* speakerDevList)
{
	//UC_SDK_GetSpeakerDevList()调用GetSpeakerDevList()前，已经对入参数值和字节大小进行判断。这里仅进行简单判断
	if (NULL == m_pDevMgr || NULL == speakerDevList)
	{
		ERROR_LOG() << "m_pDevMgr or devList is null pointer";
		return UC_SDK_NullPtr;
	}
	if (_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG() << "_fromIndex < 0 or _toIndex < 0 or fromIndex > toIndex";
		return UC_SDK_InvalidPara;
	}

	speakerDevList->iTotal = (int)m_pDevMgr->speakerdevlist.size();
	if(0 == speakerDevList->iTotal)
	{
		INFO_LOG() << "speakerDevList size is 0";
		return UC_SDK_Success;
	}
	if (_fromIndex >= speakerDevList->iTotal)
	{
		ERROR_LOG() << "_fromIndex >= m_pDevMgr->speakerdevlist.size()";
		return UC_SDK_InvalidPara;
	}
	if (_toIndex > speakerDevList->iTotal-1)
	{
		_toIndex = speakerDevList->iTotal-1;
	}
	speakerDevList->iFrom = _fromIndex;
	speakerDevList->iTo = _toIndex;

	for (int i=_fromIndex; i<=_toIndex; i++)
	{
		uc::model::device::SpeakerDev* pSpeakerDev = m_pDevMgr->speakerdevlist[(unsigned int)i];
		if (NULL == pSpeakerDev)
		{
			ERROR_LOG() << "m_pDevMgr->speakerdevlist[i] is null pointer.";
			return UC_SDK_Failed;
		}

		int index = i-_fromIndex;

		std::string name = eSDKTool::utf82unicode(pSpeakerDev->name);
		ctk::MemSet(speakerDevList->deviceList[index].name,0,STRING_LENGTH);
		ctk::MemCopy(speakerDevList->deviceList[index].name,name.c_str(),(name.size()<(STRING_LENGTH)) ? (name.size()) : (STRING_LENGTH-1));
		ctk::MemSet(speakerDevList->deviceList[index].deviceId,0,STRING_LENGTH);
		ctk::MemCopy(speakerDevList->deviceList[index].deviceId,pSpeakerDev->deviceId.c_str(),(pSpeakerDev->deviceId.size()<(STRING_LENGTH)) ? (pSpeakerDev->deviceId.size()) : (STRING_LENGTH-1));

		speakerDevList->deviceList[index].index = pSpeakerDev->index;
		speakerDevList->deviceList[index].iscertified = (int)pSpeakerDev->iscertified;
		speakerDevList->deviceList[index].isactive = (int)pSpeakerDev->isactive;
		speakerDevList->deviceList[index].type = (int)pSpeakerDev->type;
	}

	return UC_SDK_Success;
}
//获取视频设备列表
int UCDeviceMgr::GetVideoDevList(int _fromIndex, int _toIndex, STDeviceListParam* videoDevList)
{
	//UC_SDK_GetVideoDevList()调用GetVideoDevList()前，已经对入参数值和字节大小进行判断。这里仅进行简单判断
	if (NULL == m_pDevMgr || NULL == videoDevList)
	{
		ERROR_LOG() << "m_pDevMgr or devList is null pointer";
		return UC_SDK_NullPtr;
	}
	if (_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG() << "_fromIndex < 0 or _toIndex < 0 or fromIndex > toIndex";
		return UC_SDK_InvalidPara;
	}

	videoDevList->iTotal = (int)m_pDevMgr->videodevlist.size();
	if(0 == videoDevList->iTotal)
	{
		INFO_LOG() << "videoDevList size is 0";
		return UC_SDK_Success;
	}
	if (_fromIndex >= videoDevList->iTotal)
	{
		ERROR_LOG() << "_fromIndex >= m_pDevMgr->videodevlist.size()";
		return UC_SDK_InvalidPara;
	}
	if (_toIndex > videoDevList->iTotal-1)
	{
		_toIndex = videoDevList->iTotal-1;
	}
	videoDevList->iFrom = _fromIndex;
	videoDevList->iTo = _toIndex;

	for (int i=_fromIndex; i<=_toIndex; i++)
	{
		uc::model::device::VideoDev* pVideoDev = m_pDevMgr->videodevlist[(unsigned int)i];
		if (NULL == pVideoDev)
		{
			ERROR_LOG() << "m_pDevMgr->videodevlist[i] is null pointer.";
			return UC_SDK_Failed;
		}

		int index = i-_fromIndex;

		std::string name = eSDKTool::utf82unicode(pVideoDev->name);
		ctk::MemSet(videoDevList->deviceList[index].name,0,STRING_LENGTH);
		ctk::MemCopy(videoDevList->deviceList[index].name,name.c_str(),(name.size()<(STRING_LENGTH)) ? (name.size()) : (STRING_LENGTH-1));
		ctk::MemSet(videoDevList->deviceList[index].deviceId,0,STRING_LENGTH);
		ctk::MemCopy(videoDevList->deviceList[index].deviceId,pVideoDev->deviceId.c_str(),(pVideoDev->deviceId.size()<(STRING_LENGTH)) ? (pVideoDev->deviceId.size()) : (STRING_LENGTH-1));

		videoDevList->deviceList[index].index = pVideoDev->index;
		videoDevList->deviceList[index].iscertified = (int)pVideoDev->iscertified;
		videoDevList->deviceList[index].isactive = (int)pVideoDev->isactive;
		videoDevList->deviceList[index].type = (int)pVideoDev->type;
	}

	return UC_SDK_Success;
}
//获取当前麦克风设备
int UCDeviceMgr::GetCurrentMicDev(STDeviceParam* device)const
{
	if (NULL == m_pDevMgr || NULL == device)
	{
		ERROR_LOG() << "m_pDevMgr or device is null pointer";
		return UC_SDK_NullPtr;
	}
	
	uc::model::device::MicDev* pActiveMicDev = m_pDevMgr->activemicdev;
	if (NULL == pActiveMicDev)
	{
		ERROR_LOG() << "m_pDevMgr->activemicdev is null pointer";
		return UC_SDK_Failed;
	}


	std::string name = eSDKTool::utf82unicode(pActiveMicDev->name);
	ctk::MemSet(device->name,0,STRING_LENGTH);
	ctk::MemCopy(device->name,name.c_str(),(name.size()<(STRING_LENGTH)) ? (name.size()) : (STRING_LENGTH-1));
	ctk::MemSet(device->deviceId,0,STRING_LENGTH);
	ctk::MemCopy(device->deviceId,pActiveMicDev->deviceId.c_str(),(pActiveMicDev->deviceId.size()<(STRING_LENGTH)) ? (pActiveMicDev->deviceId.size()) : (STRING_LENGTH-1));

	device->index = pActiveMicDev->index;
	device->iscertified = pActiveMicDev->iscertified;
	device->isactive = pActiveMicDev->isactive;
	device->type = pActiveMicDev->type;

	return UC_SDK_Success;
}
//获取当前扬声器设备
int UCDeviceMgr::GetCurrentSpeakerDev(STDeviceParam* device)const
{
	if (NULL == m_pDevMgr || NULL == device)
	{
		ERROR_LOG() << "m_pDevMgr or device is null pointer";
		return UC_SDK_NullPtr;
	}

	uc::model::device::SpeakerDev* pActiveSpeakerDev = m_pDevMgr->activespkerdev;
	if (NULL == pActiveSpeakerDev)
	{
		ERROR_LOG() << "m_pDevMgr->activespkerdev is null pointer";
		return UC_SDK_Failed;
	}


	std::string name = eSDKTool::utf82unicode(pActiveSpeakerDev->name);
	ctk::MemSet(device->name,0,STRING_LENGTH);
	ctk::MemCopy(device->name,name.c_str(),(name.size()<(STRING_LENGTH)) ? (name.size()) : (STRING_LENGTH-1));
	ctk::MemSet(device->deviceId,0,STRING_LENGTH);
	ctk::MemCopy(device->deviceId,pActiveSpeakerDev->deviceId.c_str(),(pActiveSpeakerDev->deviceId.size()<(STRING_LENGTH)) ? (pActiveSpeakerDev->deviceId.size()) : (STRING_LENGTH-1));	

	device->index = pActiveSpeakerDev->index;
	device->iscertified = pActiveSpeakerDev->iscertified;
	device->isactive = pActiveSpeakerDev->isactive;
	device->type = pActiveSpeakerDev->type;

	return UC_SDK_Success;
}
//获取当前视频设备
int UCDeviceMgr::GetCurrentVideoDev(STDeviceParam* device)const
{
	if (NULL == m_pDevMgr || NULL == device)
	{
		ERROR_LOG() << "m_pDevMgr or device is null pointer";
		return UC_SDK_NullPtr;
	}

	uc::model::device::VideoDev* pActiveVideoDev = m_pDevMgr->activevideodev;
	if (NULL == pActiveVideoDev)
	{
		ERROR_LOG() << "m_pDevMgr->activevideodev is null pointer";
		return UC_SDK_Failed;
	}


	std::string name = eSDKTool::utf82unicode(pActiveVideoDev->name);
	ctk::MemSet(device->name,0,STRING_LENGTH);
	ctk::MemCopy(device->name,name.c_str(),(name.size()<(STRING_LENGTH)) ? (name.size()) : (STRING_LENGTH-1));
	ctk::MemSet(device->deviceId,0,STRING_LENGTH);
	ctk::MemCopy(device->deviceId,pActiveVideoDev->deviceId.c_str(),(pActiveVideoDev->deviceId.size()<(STRING_LENGTH)) ? (pActiveVideoDev->deviceId.size()) : (STRING_LENGTH-1));

	device->index = pActiveVideoDev->index;
	device->iscertified = pActiveVideoDev->iscertified;
	device->isactive = pActiveVideoDev->isactive;
	device->type = pActiveVideoDev->type;

	return UC_SDK_Success;
}
//设置当前麦克风设备
int UCDeviceMgr::SetCurrentMicDev(int index)
{
	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "m_pDevMgr is null pointer";
		return UC_SDK_NullPtr;
	}
	if (index < 0 || index >= (int)m_pDevMgr->micdevlist.size())
	{
		return UC_SDK_InvalidPara;
	}
	if (!m_pDevMgr->SetAudioCaptureDev((unsigned int)index))
	{
		INFO_PARAM1(index);
		ERROR_LOG() << "SetAudioCaptureDev failed.";
		return UC_SDK_Failed;
	}

	if(NULL == UCRegManager::Instance().m_pSelf)
	{
		ERROR_LOG() << "m_pSelf is NULL.";
		return UC_SDK_NullPtr;
	}

	UCRegManager::Instance().m_pSelf->simplecfg_.SaveUserConfig(SETTING_MEDIA_AUDIOINPUTDEVICE,m_pDevMgr->micdevlist[(unsigned int)index]->name);

	return UC_SDK_Success;
}
//设置当前扬声器设备
int UCDeviceMgr::SetCurrentSpeakerDev(int index)
{
	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "m_pDevMgr is null pointer";
		return UC_SDK_NullPtr;
	}
	if (index < 0 || index >= (int)m_pDevMgr->speakerdevlist.size())
	{
		return UC_SDK_InvalidPara;
	}
	if (!m_pDevMgr->SetAudioPlayDev((unsigned int)index))
	{
		INFO_PARAM1(index);
		ERROR_LOG() << "SetAudioPlayDev failed.";
		return UC_SDK_Failed;
	}

	if(NULL == UCRegManager::Instance().m_pSelf)
	{
		ERROR_LOG() << "m_pSelf is NULL.";
		return UC_SDK_NullPtr;
	}
	UCRegManager::Instance().m_pSelf->simplecfg_.SaveUserConfig(SETTING_MEDIA_AUDIOOUTPUTDEVICE,m_pDevMgr->speakerdevlist[(unsigned int)index]->name);

	return UC_SDK_Success;
}
//设置当前视频设备
int UCDeviceMgr::SetCurrentVideoDev(int index)
{
	if (NULL == m_pDevMgr)
	{
		ERROR_LOG() << "m_pDevMgr is null pointer";
		return UC_SDK_NullPtr;
	}
	if (index < 0 || index >= (int)m_pDevMgr->videodevlist.size())
	{
		return UC_SDK_InvalidPara;
	}
	if (!m_pDevMgr->SetVideoCaptureDev((unsigned int)index))
	{
		INFO_PARAM1(index);
		ERROR_LOG() << "SetVideoCaptureDev failed.";
		return UC_SDK_Failed;
	}

	if(NULL == UCRegManager::Instance().m_pSelf)
	{
		ERROR_LOG() << "m_pSelf is NULL.";
		return UC_SDK_NullPtr;
	}
	UCRegManager::Instance().m_pSelf->simplecfg_.SaveUserConfig(SETTING_MEDIA_VIDEODEVICE,m_pDevMgr->videodevlist[(unsigned int)index]->name);

	return UC_SDK_Success;
}



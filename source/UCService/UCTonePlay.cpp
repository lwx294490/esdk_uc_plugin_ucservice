#include "StdAfx.h"
#include "UCTonePlay.h"
#include "UCDeviceMgr.h"

UCTonePlay::UCTonePlay(void)
{
	eSDKTool::getCurrentPath(m_curPath);
}

UCTonePlay::~UCTonePlay(void)
{
}

int UCTonePlay::StartPlayIncomingCall(void) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG() << "StartPlayIncomingCall()";
	uc::model::device::SpeakerDev* spker = UCDeviceMgr::Instance().GetSpkDevice();
	if(NULL == spker)
	{
		ERROR_LOG() << "spker is null point";
		return UC_SDK_Failed;
	}
	if(!spker->BeginPlayFile(m_curPath+"\\audio\\In.wav",true,-1))
	{
		ERROR_LOG() << "BeginPlayFile Failed";
		return UC_SDK_Failed;
	}
	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;

}
int UCTonePlay::EndPlay(void) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG() << "EndPlay()";
	uc::model::device::SpeakerDev* spker = UCDeviceMgr::Instance().GetSpkDevice();
	if(NULL == spker)
	{
		ERROR_LOG() << "spker is null point";
		return UC_SDK_Failed;
	}
	if(!spker->StopPlayFile(-1))
	{
		ERROR_LOG() << "StopPlayFile Failed";
		return UC_SDK_Failed;
	}
	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;
}
//²¥·Å»ØÁåÒô
int UCTonePlay::StartPlayRingBack(void) const
{
	DEBUG_LOG() << "--- ENTER";
	INFO_LOG() << "StartPlayRingBack()";
	uc::model::device::SpeakerDev* spker = UCDeviceMgr::Instance().GetSpkDevice();
	if(NULL == spker)
	{
		ERROR_LOG() << "spker is null point";
		return UC_SDK_Failed;
	}
	if(!spker->BeginPlayFile(m_curPath+"\\audio\\RingBack.wav",true,-1))
	{
		ERROR_LOG() << "BeginPlayFile Failed";
		return UC_SDK_Failed;
	}
	DEBUG_LOG() << "--- LEAVE";
	return UC_SDK_Success;

}

int UCTonePlay::PlayDTMFTone(char tone)const
{
	uc::model::device::SpeakerDev* spker = UCDeviceMgr::Instance().GetSpkDevice();
	if(NULL == spker)
	{
		ERROR_LOG() << "spker is null point";
		return UC_SDK_Failed;
	}

	switch (tone)
	{
	case '0':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\0.wav",false,-1);
		}
		break;
	case '1':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\1.wav",false,-1);
		}
		break;
	case '2':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\2.wav",false,-1);
		}
		break;
	case '3':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\3.wav",false,-1);
		}
		break;
	case '4':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\4.wav",false,-1);
		}
		break;
	case '5':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\5.wav",false,-1);
		}
		break;
	case '6':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\6.wav",false,-1);
		}
		break;
	case '7':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\7.wav",false,-1);
		}
		break;
	case '8':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\8.wav",false,-1);
		}
		break;
	case '9':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\9.wav",false,-1);
		}
		break;
	case '#':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\Jin.wav",false,-1);
		}
		break;
	case '*':
		{
			spker->BeginPlayFile(m_curPath+"\\audio\\Key\\Xin.wav",false,-1);
		}
		break;
	default:
		ERROR_LOG() << "error tone";
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}


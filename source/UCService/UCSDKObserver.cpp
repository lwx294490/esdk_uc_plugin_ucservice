#include "StdAfx.h"
#include "UCSDKObserver.h"
#include "UCCallManager.h"

bool UCSDKObserver::OnNotification(void* _item)
{
	if(NULL == _item)
	{
		return false;
	}

	ConversationMgr* pConvMgr = UCCallManager::Instance().GetConvMgr();
	if(NULL == pConvMgr)
	{
		return false;
	}

	if(pConvMgr->HandleConversationNotify(_item))
	{
		return true;
	}
	else
	{
		return false;
	}	
}

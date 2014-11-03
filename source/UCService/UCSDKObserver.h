#ifndef _TEST_OBSERVER_H
#define _TEST_OBSERVER_H

//m_ObTest为界面实现类，实现SDK抛到上层的消息在单线程处理
class UCSDKObserver :public ConversationUiObserver
{
public:
	UCSDKObserver()
	{
	}
	virtual bool OnNotification(void* _item);
};

#endif



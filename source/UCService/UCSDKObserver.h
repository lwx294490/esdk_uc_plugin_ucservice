#ifndef _TEST_OBSERVER_H
#define _TEST_OBSERVER_H

//m_ObTestΪ����ʵ���࣬ʵ��SDK�׵��ϲ����Ϣ�ڵ��̴߳���
class UCSDKObserver :public ConversationUiObserver
{
public:
	UCSDKObserver()
	{
	}
	virtual bool OnNotification(void* _item);
};

#endif



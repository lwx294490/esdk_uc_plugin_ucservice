// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//
#ifndef _STDAFX_HEAD_
#define _STDAFX_HEAD_

#include "targetver.h"

//����UC APIͷ�ļ�����--start
#include "ctk/ctk.h"
#include "hwuc/HWUC.h"
#include "history/history.h"
using namespace uc::model; 
using namespace uc::model::conversation;
using namespace uc::model::device;
using namespace uc::model::historydata;
using namespace sigslot;
using namespace std;
//����UC APIͷ�ļ�����--end

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

//#include "vld.h"

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "UCSDK.h"
#include "UCEvent.h"
#include "UnhandledExceptionFilter.h"
#include "eSDKLog.h"
#include "eSDKTool.h"

#endif




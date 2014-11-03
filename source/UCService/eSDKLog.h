#ifndef _ESDKLOG_H
#define _ESDKLOG_H

#include "log4cpp.h"
//lint -e773
//�˴��꺯�����ܼ�����
//������־���𣬴�ӡ�������
#define DEBUG_LOG() eSDKLog::getCategoryInstance().debugStream()  << "{" << __FUNCTION__ << "} "
#define INFO_LOG()  eSDKLog::getCategoryInstance().infoStream()   << "{" << __FUNCTION__ << "} "
#define WARN_LOG()  eSDKLog::getCategoryInstance().warnStream()   << "{" << __FUNCTION__ << "} "
#define ERROR_LOG() eSDKLog::getCategoryInstance().errorStream()  << "{" << __FUNCTION__ << "} "
#define END_LOG()	eSDKLog::destroyInstance()

#define EXP1(param1) #param1 << " = " << (param1)
#define EXP2(param1, param2) \
	EXP1(param1) << ", " << EXP1(param2)
#define EXP3(param1, param2, param3) \
	EXP2(param1, param2) << ", " << EXP1(param3)
#define EXP4(param1, param2, param3, param4) \
	EXP3(param1, param2, param3) << ", " << EXP1(param4)
#define EXP5(param1, param2, param3, param4, param5) \
	EXP4(param1, param2, param3, param4) << ", " << EXP1(param5)
#define EXP6(param1, param2, param3, param4, param5, param6) \
	EXP5(param1, param2, param3, param4, param5) << ", " << EXP1(param6)

//��������ӡinfo������־�����6������
#define INFO_PARAM0() INFO_LOG()
#define INFO_PARAM1(param1) \
	INFO_PARAM0() << EXP1(param1)
#define INFO_PARAM2(param1, param2) \
	INFO_PARAM0() << EXP2(param1, param2)
#define INFO_PARAM3(param1, param2, param3) \
	INFO_PARAM0() << EXP3(param1, param2, param3)
#define INFO_PARAM4(param1, param2, param3, param4) \
	INFO_PARAM0() << EXP4(param1, param2, param3, param4)
#define INFO_PARAM5(param1, param2, param3, param4, param5) \
	INFO_PARAM0() << EXP5(param1, param2, param3, param4, param5)
#define INFO_PARAM6(param1, param2, param3, param4, param5, param6) \
	INFO_PARAM0() << EXP6(param1, param2, param3, param4, param5, param6)

//��������ӡdebug������־�����6������
#define DEBUG_PARAM0() DEBUG_LOG()
#define DEBUG_PARAM1(param1) \
	DEBUG_PARAM0() << EXP1(param1)
#define DEBUG_PARAM2(param1, param2) \
	DEBUG_PARAM0() << EXP2(param1, param2)
#define DEBUG_PARAM3(param1, param2, param3) \
	DEBUG_PARAM0() << EXP3(param1, param2, param3)
#define DEBUG_PARAM4(param1, param2, param3, param4) \
	DEBUG_PARAM0() << EXP4(param1, param2, param3, param4)
#define DEBUG_PARAM5(param1, param2, param3, param4, param5) \
	DEBUG_PARAM0() << EXP5(param1, param2, param3, param4, param5)
#define DEBUG_PARAM6(param1, param2, param3, param4, param5, param6) \
	DEBUG_PARAM0() << EXP6(param1, param2, param3, param4, param5, param6)
//lint +e773

//��־�����ļ�
#define CONFIG_FILE			"UCServiceLog_config.ini"

//��־�ļ�
#define LOG_FILE			"UCService.log"

//Ĭ����־Ŀ¼
#define LOG_DIRECTORY		"log"

//��־��ʽ"%d���� %t�߳�id %p���ȼ� %m��Ϣ %n���з�"
#define LOG_PATTERN			"[%d][%-5t][%5p]-%m%n"

//��־ʵ����
#define LOG_INSTANCE		"UCService"

//֧�ֵ���־����
enum LOGLEVEL
{
	DEBUG_LEVEL = 0,
	INFO_LEVEL,
	WARN_LEVEL,
	ERROR_LEVEL
};

//��־��
class eSDKLog
{
public:	
	static log4cpp::Category& getCategoryInstance();
	static void destroyInstance();
private:
	eSDKLog(void);
	~eSDKLog(void);
	int loadConfig();				//������־����
	int loadLog4cpp() const;		//����Log4cpp
	int setLog4CppLevel() const;	//����Log4cpp����־����
	int m_LogLevel;	
	static eSDKLog* m_Instance;
	
};

#endif



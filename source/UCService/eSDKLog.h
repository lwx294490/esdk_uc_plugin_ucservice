#ifndef _ESDKLOG_H
#define _ESDKLOG_H

#include "log4cpp.h"
//lint -e773
//此处宏函数不能加括号
//四种日志级别，打印简短描述
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

//带参数打印info级别日志，最多6个参数
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

//带参数打印debug级别日志，最多6个参数
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

//日志配置文件
#define CONFIG_FILE			"UCServiceLog_config.ini"

//日志文件
#define LOG_FILE			"UCService.log"

//默认日志目录
#define LOG_DIRECTORY		"log"

//日志格式"%d日期 %t线程id %p优先级 %m消息 %n换行符"
#define LOG_PATTERN			"[%d][%-5t][%5p]-%m%n"

//日志实例名
#define LOG_INSTANCE		"UCService"

//支持的日志级别
enum LOGLEVEL
{
	DEBUG_LEVEL = 0,
	INFO_LEVEL,
	WARN_LEVEL,
	ERROR_LEVEL
};

//日志类
class eSDKLog
{
public:	
	static log4cpp::Category& getCategoryInstance();
	static void destroyInstance();
private:
	eSDKLog(void);
	~eSDKLog(void);
	int loadConfig();				//加载日志配置
	int loadLog4cpp() const;		//加载Log4cpp
	int setLog4CppLevel() const;	//设置Log4cpp的日志级别
	int m_LogLevel;	
	static eSDKLog* m_Instance;
	
};

#endif



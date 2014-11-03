#include "StdAfx.h"
#include "eSDKTool.h"
#include <io.h>
#include <direct.h>

eSDKLog* eSDKLog::m_Instance = NULL;

eSDKLog::eSDKLog(void):m_LogLevel(INFO_LEVEL)
{
}
eSDKLog::~eSDKLog(void)
{
	try
	{
		log4cpp::Category& logCategory = log4cpp::Category::getInstance(LOG_INSTANCE);
		logCategory.infoStream() << "==============log end==============";
		log4cpp::Category::shutdown();
	}
	catch (...)
	{
	}
}
int eSDKLog::loadLog4cpp() const
{
	/*lint -save -e429*/
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern(LOG_PATTERN);
	std::string logPath;
	eSDKTool::getCurrentPath(logPath);
	logPath.append("\\");
	logPath.append(LOG_DIRECTORY);

	//create dir
	(void)_mkdir(logPath.c_str());

	logPath.append("\\");
	logPath.append(LOG_FILE);

	log4cpp::RollingFileAppender* rollfileAppender = new log4cpp::RollingFileAppender(LOG_INSTANCE,logPath);//logPath必须使用绝对路径
	rollfileAppender->setLayout(pLayout);
	log4cpp::Category& logCategory = log4cpp::Category::getInstance(LOG_INSTANCE);
	logCategory.setAdditivity(false); 
	logCategory.addAppender(rollfileAppender);
	return 0;
	/*lint -restore*/
}
int eSDKLog::setLog4CppLevel() const
{
	log4cpp::Category& logCategory = log4cpp::Category::getInstance(LOG_INSTANCE);
	switch (m_LogLevel)
	{
	case INFO_LEVEL:
		{
			logCategory.setPriority(log4cpp::Priority::INFO);
			break;
		}
	case DEBUG_LEVEL:
		{
			logCategory.setPriority(log4cpp::Priority::DEBUG);
			break;
		}
	case WARN_LEVEL:
		{
			logCategory.setPriority(log4cpp::Priority::WARN);
			break;
		}
	case ERROR_LEVEL:
		{
			logCategory.setPriority(log4cpp::Priority::ERROR);
			break;
		}
	default:
		{
			logCategory.setPriority(log4cpp::Priority::INFO);
		}
	}

	return 0;
}

int eSDKLog::loadConfig()
{	
	std::string logConfigPath;
	eSDKTool::getCurrentPath(logConfigPath);
	logConfigPath.append("\\");
	logConfigPath.append(CONFIG_FILE);

	const int LENGTH = 10;
	char tchValue[LENGTH] = {0};
	(void)::GetPrivateProfileStringA("UCService","loglevel","",tchValue,LENGTH-1,logConfigPath.c_str());
	
	std::string strLogLevel(tchValue);
	if(0 == strLogLevel.compare("info"))
	{
		m_LogLevel = INFO_LEVEL;
	}
	else if(0 == strLogLevel.compare("warning"))
	{
		m_LogLevel = WARN_LEVEL;
	}
	else if(0 == strLogLevel.compare("error"))
	{
		m_LogLevel = ERROR_LEVEL;
	}
	else if(0 == strLogLevel.compare("debug"))
	{
		m_LogLevel = DEBUG_LEVEL;
	}
	else
	{
		m_LogLevel = INFO_LEVEL;
	}

	return m_LogLevel;
}
log4cpp::Category& eSDKLog::getCategoryInstance()
{
	if(NULL == m_Instance)
	{
		m_Instance = new eSDKLog();
		(void)m_Instance->loadConfig();
		(void)m_Instance->loadLog4cpp();
		(void)m_Instance->setLog4CppLevel();
		log4cpp::Category& root = log4cpp::Category::getInstance(LOG_INSTANCE);
		root.infoStream() << "==============log start============";
	}

	log4cpp::Category& logCategory = log4cpp::Category::getInstance(LOG_INSTANCE);
	return logCategory;
}

void eSDKLog::destroyInstance()
{
	if(m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}



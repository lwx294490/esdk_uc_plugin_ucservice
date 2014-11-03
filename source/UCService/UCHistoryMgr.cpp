//lint -e864
#include "StdAfx.h"
#include "UCHistoryMgr.h"

UCHistoryMgr::UCHistoryMgr(void):m_pHisMgr(NULL)
{
}

UCHistoryMgr::~UCHistoryMgr(void)
{
	m_pHisMgr = NULL;
}
void UCHistoryMgr::Init(void)
{
	m_pHisMgr = HistoryManager::Instance();
}
void UCHistoryMgr::Uninit(void)
{
	m_pHisMgr = NULL;
}
int UCHistoryMgr::QueryCallHistory(int _CallType,int _FromIndex,int _toIndex, STCallHistroyData* _queryResult)const
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}
	if(NULL == _queryResult)
	{
		ERROR_LOG() << "queryResult is NULL";
		return UC_SDK_NullPtr;
	}

	INFO_PARAM2(_CallType,_queryResult);

	if(_FromIndex > _toIndex)
	{
		ERROR_LOG() << "index is invalid";
		return UC_SDK_InvalidPara;
	}

	CallType type_= CALL_ALL;
	int iRet = ConvertCallType(_CallType,type_);
	if(UC_SDK_Success != iRet)
	{
		ERROR_LOG() << "CallType is invalid";
		return iRet;
	}

	//查询所有
	std::vector<historydata::Record> lstCall;
	_queryResult->iTotal =  m_pHisMgr->FilterCallRecords(lstCall, -1, 0,type_);	
	if(0 >= _queryResult->iTotal)
	{
		INFO_LOG() << "Total Size is " << _queryResult->iTotal;
		return UC_SDK_Success;
	}
	if(_queryResult->iTotal < _FromIndex)
	{
		WARN_LOG() << "FromIndex is too large";
		return UC_SDK_InvalidPara;
	}

	lstCall.clear();
	int iSize = _queryResult->iTotal;
	(void)m_pHisMgr->FilterCallRecords(lstCall, 0, iSize,type_);
	_queryResult->iTotal = (int)lstCall.size();
	_queryResult->iFrom = _FromIndex;
	if(_toIndex > _queryResult->iTotal )
	{
		_queryResult->iTo = _queryResult->iTotal-1;
	}
	else
	{
		_queryResult->iTo = _toIndex;
	}
	
	std::reverse(lstCall.begin(), lstCall.end());
	unsigned int resultSize = (unsigned int)(_queryResult->iTo-_queryResult->iFrom) + 1;	
	for(unsigned int i=0;i<resultSize;++i)
	{
		historydata::Record recd = lstCall.at((i+(unsigned int)_FromIndex));

		//duration
		_queryResult->stCallHistory[i].duration = recd.duration;

		//calltype
		if(recd.sent)
		{
			_queryResult->stCallHistory[i].callType = HISTORY_CALL_DIALED;
		}
		else
		{
			if(recd.duration > -1)
			{
				_queryResult->stCallHistory[i].callType = HISTORY_CALL_ANSWERED;
			}
			else
			{
				_queryResult->stCallHistory[i].callType = HISTORY_CALL_MISSED;
			}			
		}

		//recordID
		_queryResult->stCallHistory[i].recordID = (int)recd.recordId;

		//starttime
		_queryResult->stCallHistory[i].startTime.year = recd.date.year;
		_queryResult->stCallHistory[i].startTime.month = recd.date.month;
		_queryResult->stCallHistory[i].startTime.day = recd.date.day;
		_queryResult->stCallHistory[i].startTime.hour = recd.time.hour;
		_queryResult->stCallHistory[i].startTime.minute = recd.time.minute;
		_queryResult->stCallHistory[i].startTime.second = recd.time.second;

		//callname
		ctk::MemSet(_queryResult->stCallHistory[i].CallName,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stCallHistory[i].CallName,recd.peerName.c_str(),(recd.peerName.size()<(STRING_LENGTH)) ? (recd.peerName.size()) : (STRING_LENGTH-1));

		//account
		std::string account = recd.peerId;
		ctk::MemSet(_queryResult->stCallHistory[i].ucAccount,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stCallHistory[i].ucAccount,account.c_str(),(account.size()<(STRING_LENGTH)) ? (account.size()) : (STRING_LENGTH-1));

		//callNum，这里使用peerId，是因为当记录创建时，如果是IPphone呼叫就会创建号码
		std::string bindNum = recd.peerId;
		ctk::MemSet(_queryResult->stCallHistory[i].CallNum,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stCallHistory[i].CallNum,bindNum.c_str(),(bindNum.size()<(STRING_LENGTH)) ? (bindNum.size()) : (STRING_LENGTH-1));


	}
	return UC_SDK_Success;
}

int UCHistoryMgr::ClearCallHistory(int _CallType)const
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}

	CallType sdkCalltype_= CALL_ALL;

	int iRet = ConvertCallType(_CallType,sdkCalltype_);
	if(UC_SDK_Success != iRet)
	{
		ERROR_LOG() << "_CallType is invalid";
		return iRet;
	}	

	m_pHisMgr->RemoveCallRecords(sdkCalltype_);

	return UC_SDK_Success;
}

int UCHistoryMgr::QueryConvHistory(int _FromIndex,int _toIndex,STConvHistroyData* _queryResult)
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}
	if(NULL == _queryResult)
	{
		ERROR_LOG() << "queryResult is NULL";
		return UC_SDK_NullPtr;
	}

	INFO_PARAM3(_FromIndex,_toIndex,_queryResult);

	if(_FromIndex > _toIndex)
	{
		ERROR_LOG() << "index is invalid";
		return UC_SDK_InvalidPara;
	}

	//先查总数
	std::vector<historydata::Record> lstTempGroup;	
	_queryResult->iTotal = m_pHisMgr->FilterMeetingRecords(lstTempGroup);
	if(0 >= _queryResult->iTotal)
	{
		return UC_SDK_Success;
	}

	//再查所有
	lstTempGroup.clear();
	int iSize = _queryResult->iTotal;
	(void)m_pHisMgr->FilterMeetingRecords(lstTempGroup,0,iSize);
	
	//翻转，设置查找的范围
	std::reverse(lstTempGroup.begin(), lstTempGroup.end());
	_queryResult->iTotal = (int)lstTempGroup.size();
	_queryResult->iFrom = _FromIndex;
	if(_toIndex > _queryResult->iTotal )
	{
		_queryResult->iTo = _queryResult->iTotal-1;
	}
	else
	{
		_queryResult->iTo = _toIndex;
	}

	//去除需要返回的部分
	unsigned int uiresultSize = (unsigned int)(_queryResult->iTo-_queryResult->iFrom) + 1;	
	for(unsigned int i=0;i<uiresultSize;++i)
	{
		historydata::Record rcd = lstTempGroup.at((i+(unsigned int)_FromIndex));
		historydata::Conversation cvs;
		bool bRet = m_pHisMgr->GetConversationByConversationId(cvs,rcd.cvsId);
		if(!bRet)
		{
			WARN_LOG() << "GetConversationByConversationId [" << rcd.cvsId <<"] failed.";
			continue;
		}
		std::string stdParts = cvs.participants;
		std::vector<std::string> strList;
		eSDKTool::SplitString(stdParts,strList);

		_queryResult->stConvHistory[i].partcipantNum = (int)strList.size();
		_queryResult->stConvHistory[i].duration = rcd.duration;

		_queryResult->stConvHistory[i].startTime.year = rcd.date.year;
		_queryResult->stConvHistory[i].startTime.month = rcd.date.month;
		_queryResult->stConvHistory[i].startTime.day = rcd.date.day;
		_queryResult->stConvHistory[i].startTime.hour = rcd.time.hour;
		_queryResult->stConvHistory[i].startTime.minute = rcd.time.minute;
		_queryResult->stConvHistory[i].startTime.second = rcd.time.second;


		ctk::MemSet(_queryResult->stConvHistory[i].convID,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stConvHistory[i].convID,cvs.cvsId.c_str(),(cvs.cvsId.size()<(STRING_LENGTH)) ? (cvs.cvsId.size()) : (STRING_LENGTH-1));
		ctk::MemSet(_queryResult->stConvHistory[i].compereAccount,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stConvHistory[i].compereAccount,cvs.originator.c_str(),(cvs.originator.size()<(STRING_LENGTH)) ? (cvs.originator.size()) : (STRING_LENGTH-1));
		ctk::MemSet(_queryResult->stConvHistory[i].compereName,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stConvHistory[i].compereName,cvs.originator.c_str(),(cvs.originator.size()<(STRING_LENGTH)) ? (cvs.originator.size()) : (STRING_LENGTH-1));

	}
	
	return UC_SDK_Success;
}

int UCHistoryMgr::QueryHisConvPartByID(const std::string& _convID,int _FromIndex,int _toIndex,STConfPartData* _queryResult)
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}
	if(NULL == _queryResult)
	{
		ERROR_LOG() << "queryResult is NULL";
		return UC_SDK_NullPtr;
	}

	INFO_PARAM4(_convID,_FromIndex,_toIndex,_queryResult);

	if(_FromIndex > _toIndex)
	{
		ERROR_LOG() << "index is invalid";
		return UC_SDK_InvalidPara;
	}

	historydata::Conversation conv;
	bool bRet = m_pHisMgr->GetConversationByConversationId(conv,_convID);
	if(!bRet)
	{
		ERROR_LOG() << "convID is not existed";
		return UC_SDK_Failed;
	}

	std::string strPart = conv.participants;

	std::vector<std::string> strList;
	eSDKTool::SplitString(strPart,strList);

	unsigned int iSize = strList.size();
	_queryResult->partNum = (int)iSize;

	for(unsigned int i = 0;i<iSize;++i)
	{
		ctk::MemSet(_queryResult->stConfPart[i].partAccount,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stConfPart[i].partAccount,strList.at(i).c_str(),(strList.at(i).size()<(STRING_LENGTH)) ? (strList.at(i).size()) : (STRING_LENGTH-1));
		ctk::MemSet(_queryResult->stConfPart[i].partName,0,STRING_LENGTH);
		ctk::MemCopy(_queryResult->stConfPart[i].partName,strList.at(i).c_str(),(strList.at(i).size()<(STRING_LENGTH)) ? (strList.at(i).size()) : (STRING_LENGTH-1));
	}

	return UC_SDK_Success;
}

int UCHistoryMgr::ClearConvHistory()
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}
	
	std::vector<historydata::Conversation> listConv;
	m_pHisMgr->GetTempGroupConversations(listConv);
	unsigned int uiSize = listConv.size();
	for(unsigned int i=0;i<uiSize;++i)
	{
		//清除最近会话
		listConv.at(i).DeleteRecentRecord();
		//清除会话
		m_pHisMgr->RemoveConversationById(listConv.at(i).cvsId);
		m_pHisMgr->RemoveRecordsByConversationId(listConv.at(i).cvsId);
	}

	m_pHisMgr->RemoveRecordsByRecordType(RECORD_MEETING);
	return UC_SDK_Success;
}

int UCHistoryMgr::ConvertCallType(int _CallType,CallType& _sdkCallType)const
{
	switch (_CallType)
	{
	case HISTORY_CALL_ALL:
		{
			_sdkCallType = CALL_ALL;
			break;
		}
	case HISTORY_CALL_ANSWERED:
		{
			_sdkCallType = CALL_ANSWERED;
			break;
		}
	case HISTORY_CALL_MISSED:
		{
			_sdkCallType = CALL_MISSED;
			break;
		}
	case HISTORY_CALL_DIALED:
		{
			_sdkCallType = CALL_DIALED;
			break;
		}
	default:
		{
			return UC_SDK_InvalidPara;
		}
	}
	return UC_SDK_Success;
}

int UCHistoryMgr::InsertCallHistory(int _CallType,const std::string& _account,const std::string& _name,int _duration)
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}

	//获取开始时间
	historydata::Date startdate;
	historydata::Time starttime;
	if(0 > _duration)
	{
		eSDKTool::GetStartTime(startdate,starttime,0);
	}
	else
	{
		eSDKTool::GetStartTime(startdate,starttime,(unsigned int)_duration);
	}
	//增加到历史记录
	historydata::Conversation historyConv;
	m_pHisMgr->CreateSingleConversation(historyConv,_account,startdate,starttime);

	historydata::Record rcd;
	if(_CallType == HISTORY_CALL_DIALED)
	{
		historyConv.CreateOutgoingCallRecord(rcd, startdate, starttime, _account,_name);
		rcd.ModifyDuration(_duration);
		return UC_SDK_Success;
	}
	else if(_CallType == HISTORY_CALL_ANSWERED)
	{
		historyConv.CreateIncommingCallRecord(rcd, startdate, starttime, _account,_name);
		rcd.ModifyDuration(_duration);
		return UC_SDK_Success;
	}
	else if(_CallType == HISTORY_CALL_MISSED)
	{
		historyConv.CreateIncommingCallRecord(rcd, startdate, starttime, _account,_name);
		return UC_SDK_Success;
	}

	ERROR_LOG() << "callType is invalid";
	return UC_SDK_InvalidPara;
}

int UCHistoryMgr::InsertConvHistory(const std::string& _convID,const std::string& _leaderAccount,const std::string& _leaderName,int duration)
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}

	INFO_PARAM3(_convID,_leaderAccount,duration);
	//获取开始时间
	historydata::Date startdate;
	historydata::Time starttime;
	if(0 > duration)
	{
		eSDKTool::GetStartTime(startdate,starttime,0);
	}
	else
	{
		eSDKTool::GetStartTime(startdate,starttime,(unsigned int)duration);
	}
	//增加到历史记录
	historydata::Conversation historyConv;
	bool bRet = m_pHisMgr->CreateTempGroupConversation(historyConv,_convID,_convID,"Default Chat",startdate,starttime,_leaderAccount,_leaderName);
	if(!bRet)
	{
		ERROR_LOG() << "insert conv history failed.";
		return UC_SDK_Failed;
	}
	historydata::Record rcd;
	historyConv.CreateIncommingCallRecord(rcd,startdate,starttime,_leaderAccount,_leaderName);
	historyConv.SetParticipants("");
	rcd.ModifyDuration(duration);

	return UC_SDK_Success;
}
int UCHistoryMgr::InsertConvHistoryPart(const std::string& _historyID,
						  const std::string& _partAccount,
						  const std::string& _partName)
{
	if(NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}

	INFO_PARAM3(_historyID,_partAccount,_partName);

	historydata::Conversation historyConv;
	bool bRet = m_pHisMgr->GetConversationByConversationId(historyConv,_historyID);
	if(!bRet)
	{
		ERROR_LOG() << "historyId is inexistent.";
		return UC_SDK_Failed;
	}
	std::string strPart = historyConv.participants;
	strPart.append(_partAccount);
	strPart.append(",");
	historyConv.SetParticipants(strPart);
	return UC_SDK_Success;
}

int UCHistoryMgr::DeleteCallHistory( int ircdID)const
{
	if (NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}

	if (ircdID < 0)	
	{
		ERROR_LOG() << "ircdID is invalid";
		return UC_SDK_InvalidPara;
	}

	(void)m_pHisMgr->RemoveRecordsByRecordId((historydata::RecordId)ircdID);

	return UC_SDK_Success;
}
int UCHistoryMgr::DeleteConvHistory(std::string strConvID)const
{
	if (NULL == m_pHisMgr)
	{
		ERROR_LOG() << "pHisMgr is NULL";
		return UC_SDK_NullPtr;
	}

	if (strConvID.empty())	
	{
		ERROR_LOG() << "iIndex is invalid";
		return UC_SDK_InvalidPara;
	}

	(void)m_pHisMgr->RemoveConversationById(strConvID);
	(void)m_pHisMgr->RemoveRecordsByConversationId(strConvID);

	return UC_SDK_Success;
}

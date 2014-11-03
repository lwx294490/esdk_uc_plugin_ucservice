#ifndef _UC_HISTORY_MGR_H
#define _UC_HISTORY_MGR_H

class UCHistoryMgr
{
public:
	UCHistoryMgr(void);
	~UCHistoryMgr(void);
public:
	static inline UCHistoryMgr& Instance()
	{
		return *ctk::Singleton_T<UCHistoryMgr>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCHistoryMgr>::destroy();
	}
public:
	void Init(void);
	void Uninit(void);
public:
	int QueryCallHistory(int _CallType,int _FromIndex,int _toIndex,STCallHistroyData* _queryResult)const;
	int ClearCallHistory(int _CallType)const;
	int QueryConvHistory(int _FromIndex,int _toIndex,STConvHistroyData* _queryResult);
	int QueryHisConvPartByID(const std::string& _groupurl,int _FromIndex,int _toIndex,STConfPartData* _queryResult);
	int ClearConvHistory();
public:
	int InsertCallHistory(int _CallType,const std::string& _url,const std::string& _name,int _duration);
	int InsertConvHistory(const std::string& _convID,
								const std::string& _leaderAccount,
								const std::string& _leaderName,
								int duration);
	int InsertConvHistoryPart(const std::string& _convID,
									const std::string& _partAccount,
									const std::string& _partName);
public:
	int DeleteCallHistory(int ircdID)const;
	int DeleteConvHistory(std::string strConvID)const;
private:
	int ConvertCallType(int _CallType,CallType& _sdkCallType)const;//×ª»»ºô½ÐÀàÐÍ
private:
	HistoryManager* m_pHisMgr;
};

#endif



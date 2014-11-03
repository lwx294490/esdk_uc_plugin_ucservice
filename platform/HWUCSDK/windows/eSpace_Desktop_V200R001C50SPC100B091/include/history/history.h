/******************************************************************************
* Huawei Enterprise Communication API
* device.h
* Author :	Huawei
* Description :  History record related API.
* Create Time:	2011-7-02	16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :	2011-7-02 1.00	First version
******************************************************************************/

#pragma once

#include "history/HistoryAutoLink.h"

namespace uc {
  namespace model {
    namespace historydata {

struct HISTORY_API Date
{
  int year;
  int month;
  int day;

  Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {}
  std::string ToString() const;
  bool FromString(const std::string & str);

  bool operator==(const Date & date) const
  {
    return year == date.year && month == date.month && day == date.day;
  }

};

struct HISTORY_API Time
{
  int hour;
  int minute;
  int second;

  Time(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) {}
  std::string ToString() const;
  bool FromString(const std::string & str);

  bool operator==(const Time & date)
  {
    return hour == date.hour && minute == date.minute && second == date.second;
  }
};

enum RecordType
{
  RECORD_CHAT, 
  RECORD_SMS, 
  RECORD_FILE, 
  RECORD_OFFLINEFILE, 
  RECORD_CHAT_SMS_FILE = 4, // 暂时没有用，仅作为查询的类型参数
  RECORD_SYSTEM = 5, 
  RECORD_VOICEMSG = 6, 
  RECORD_VIDEOMSG = 7,
  RECORD_MEETING = 9,
  RECORD_CALL = 10, 
  RECORD_MEMBER = 100, 
  RECORD_RECORDING = 101, 
};

// conversation type
enum CvsType
{
  CVS_SINGLE, 
  CVS_FIXEDGROUP, 
  CVS_TEMPGROUP, 
  CVS_DISCUSSGROUP,
  CVS_SYSTEM, 
  CVS_MEETING, 
};

// call type
enum CallType
{
  CALL_ALL, 
  CALL_MISSED, 
  CALL_ANSWERED, 
  CALL_DIALED, 
};

typedef long long RecordId;

class HISTORY_API Record
{
public:
  int recordType; // enum RecordType
  std::string msgId;
  RecordId recordId;

  int cvsType; // enum CvsType
  std::string cvsId; // staff uri or fixed group id or (temp group) conversation id

  std::string peerId;
  std::string peerName; // peer name or peer number (for call)
  bool sent; // sent or received ?

  Date date;
  Time time;
  int duration; // -1 : missed call, chat, ...

  bool read; // Has chat been read or is it a missed call ?
  bool important; // is it important ?

  std::string body; // with format info
  std::string text; // no format info, pure text

  int recordFlag;

  Record(int record_type = -1, int cvs_type = -1);

public:
  bool MarkRead() { return SetRead(true); }
  bool ClearRead() { return SetRead(false); }
  bool MarkImportant() { return SetImportant(true); }
  bool ClearImportant() { return SetImportant(false); }
  bool DeleteRecentRecord();
private:
  bool SetRead(bool set);
  bool SetImportant(bool set);

public:
  bool ModifyDuration(int duration);
  bool ModifyBody(const std::string & bd);
  bool ModifyText(const std::string & tx);
  bool ModifyFlag(int record_flag);

public:
  bool IsMissedCall() const {
    return RECORD_CALL == recordType && -1 == duration;
  }

}; // struct Record

class HISTORY_API Conversation
{
public:
  int cvsType; // enum CvsType
  std::string cvsId;

  std::string groupId;
  std::string groupName;
  std::string originator;
  std::string participants;

  Date date;
  Time time;

  bool hided;

  Conversation() 
    : cvsType(-1), hided(false)
  {
  }

public:
  bool MarkHided() { return SetHided(true); }
  bool ClearHided() { return SetHided(false); }
  bool DeleteRecentRecord() const ;

private:
  bool SetHided(bool set);

public:
  // compute indirectly
  int GetImportant();
  int GetUnreadChat();

  int MarkRead();
  int ClearImportant();

public:
    int QueryUnreadCount() const;
    int QueryUnreadCallCount() const;
  int QueryImportantCount();
  int GetImportantRecords(std::vector<Record> & records) const;

public:
  bool SetParticipants(const std::string & part);
  bool SetConversationName(const std::string & newname);

public:
  bool CreateRecvChatRecord(Record & record, 
    const std::string & body, const std::string & text, 
    const Date & date, const Time & time, 
    const std::string & peer_id, const std::string & peer_name) const;
  bool CreateSentChatRecord(Record & record, 
    const std::string & body, const std::string & text, 
    const Date & date, const Time & time) const;
public:
  bool CreateIncommingCallRecord(Record & record, 
    const Date & date, const Time & time, 
    const std::string & peer_id, const std::string & peer_name) const;
  bool CreateOutgoingCallRecord(Record & record, 
    const Date & date, const Time & time, 
    const std::string & peer_id, const std::string & peer_name) const;
public:
  bool CreateRecvSMSRecord(Record & record, 
    const std::string & body, const Date & date, const Time & time, 
    const std::string & peer_id, const std::string & peer_name) const;
  bool CreateSentSMSRecord(Record & record, 
    const std::string & body, const Date & date, const Time & time, 
    const std::string & peer_id, const std::string & peer_name) const;
public:
  bool CreateRecvFileRecord(Record & record, 
    const std::string & body, const Date & date, const Time & time, 
    const std::string & peer_id, const std::string & peer_name, bool isOffline = false) const;
  bool CreateSentFileRecord(Record & record, 
    const std::string & body, const Date & date, const Time & time) const;
public:
  bool CreateSystemRecord(Record & record, 
    const std::string & peer_id, const std::string & body, 
    const Date & date, const Time & time) const;
public:
  bool CreateVoiceMessageRecord(Record & record, 
    const std::string & peer_id, const std::string & body, 
    const Date & date, const Time & time) const;
public:
  bool CreateMemberRecord(Record & record, 
    const std::string & body, const Date & date, const Time & time) const;
public:
  bool CreateRecordingRecord(Record & record, 
    const std::string & body, const Date & date, const Time & time) const;
private:
  bool CreateRecord(Record & record, int record_type, 
    const std::string & peer_id, const std::string & peer_name, bool sent, 
    const Date & date, const Time & time, 
    const std::string & body, const std::string & text = "") const;

public:
  bool GetLastUnreadMissedCallRecord(Record & record) const;

public:
  int GetAllRecords(std::vector<Record> & records) const;
  int GetAllChatRecords(std::vector<Record> & records) const;
  int GetAllCallRecords(std::vector<Record> & records) const;
  int GetAllFileTransferRecords(std::vector<Record> & records) const;
  int GetAllRecordsByRecordType(std::vector<Record> & records, int record_type) const;
  int GetChatRecordsByRecordType(std::vector<Record> & records) const;
  int GetRecordsBetweenDate(std::vector<Record> & records, 
    const Date & beginDate, const Date & endDate); // [beginDate, endDate)

public:
    int MarkMsgIdRead();
    int MarkMsgIdDeleting();
    std::string GetLastMsgIds();
    int RemoveMsgIds();
}; // struct Conversation

class HISTORY_API HistoryManager
{
public:
  static HistoryManager * Instance();
  static void Destroy();

  virtual std::string GetSystemMessageCvsId() const = 0;
  virtual std::string GetVoiceMessageCvsId() const = 0;

public:
  // create db file and tables
  virtual void InitializeHistoryData() = 0;
  virtual void FinalizeHistoryData() = 0;

  // clear db tables
  virtual bool ClearHistoryData() = 0;

public:
  // conversation creation
  virtual bool CreateSingleConversation(Conversation & cvs, 
    const std::string & peer_id, 
    const Date & date, const Time & time) = 0;
  virtual bool CreateFixedGroupConversation(Conversation & cvs, 
    const std::string & creator, const std::string & group_id, 
    const std::string & group_uri, const std::string & group_name, 
    const Date & date, const Time & time) = 0;
  virtual bool CreateDiscussGroupConversation(Conversation & cvs, 
      const std::string & cvs_id, 
      const std::string & group_id, const std::string & group_name, 
      const Date & date, const Time & time, 
      const std::string & orig, const std::string & pati) = 0;
  virtual bool CreateTempGroupConversation(Conversation & cvs, 
    const std::string & cvs_id, 
    const std::string & group_id, const std::string & group_name, 
    const Date & date, const Time & time, 
    const std::string & orig, const std::string & pati) = 0;
  virtual bool CreateSystemConversation(Conversation & cvs, 
    const Date & date, const Time & time) = 0;
  virtual bool CreateVoiceMessageConversation(Conversation & cvs, 
    const Date & date, const Time & time) = 0;

public: // get single record or conversation
  // result with no conversation information
  virtual bool GetRecordByRecordId(
    Record & record, const RecordId & recordId) = 0;

  virtual bool GetRecordAndConversationByRecordId(
    Record & record, Conversation & cvs, const RecordId & recordId) = 0;

public: // system conversation
  virtual bool GetSystemConversation(Conversation & cvs) = 0;
  virtual bool GetVoiceMessageConversation(Conversation & cvs) = 0;
  virtual bool GetConversationByConversationId(
    Conversation & cvs, const std::string & cvsId) = 0;

  virtual int GetSingleConversations(
    std::vector<Conversation> & conversations) = 0;
  virtual int GetFixedGroupConversations(
    std::vector<Conversation> & conversations) = 0;
  virtual int GetTempGroupConversations(
    std::vector<Conversation> & conversations) = 0;

  virtual int GetDiscussGroupConversation(
	std::vector<Conversation> & conversatios) = 0;

  virtual int GetAllConversations(
    std::vector<Conversation> & conversations) = 0;

public: // recent query
  // recent conversations

  virtual int QueryUnreadAll(std::vector<Record> & conversations) = 0;

  virtual int GetRecentConversations(int maxLimit, 
    std::vector<Conversation> & recentConversations, 
    std::vector<Record> & lastRecords, 
    std::vector<Record> & lastUnreadMissedCalls) = 0;

public:
  // history conversation id(s), arranged in date
  typedef std::pair<Date, std::vector<std::string> > DateConversation;
  typedef std::vector<DateConversation> DateConversations;
  // chat (sms, file) history
  virtual int GetHistoryChatConversations(
    DateConversations & dateConversations) const = 0;
  virtual bool GetChatConversationByConversationIdAndDate(
    Conversation & cvs, const std::string & cvsId, const Date & date) = 0;

  // history record id(s), arranged in date
  typedef std::pair<Date, std::vector<RecordId> > DateRecord;
  typedef std::vector<DateRecord> DateRecords;
  // call history
  virtual int GetHistoryCallRecords(DateRecords & dateRecords) const = 0;
  // system notification history
  virtual int GetHistorySystemRecords(DateRecords & dateRecords) const = 0;

  // history conversations/records by date
  virtual int GetHistoryChatConversationsBetweenDate(
    std::vector<Conversation> & conversations, 
    const Date & beginDate, const Date & endDate) const = 0;

public: // 历史记录管理器各种条件删选（分页）
  // startIndex: <0 不指定偏移位置；>=0 指定偏移位置
  // amount: <0 返回所有结果；=0 仅返回结果数目；>0 指定结果数目
  virtual int FilterChatSmsFileRecords(std::vector<Record> & records, 
    int startIndex = -1, int amount = -1, 
    const std::string & cvsId = "", const std::string & key = "", 
    const Date & beginDate = Date(), const Date & endDate = Date()) const = 0;
  virtual int FilterSmsRecords(std::vector<Record> & records, 
    int startIndex = -1, int amount = -1, 
    const std::string & cvsId = "", const std::string & key = "", 
    const Date & beginDate = Date(), const Date & endDate = Date()) const = 0;
  virtual int FilterCallRecords(std::vector<Record> & records, 
    int startIndex = -1, int amount = -1, 
    CallType callType = CALL_ALL, int reservedInt1 = 0) const = 0;
  virtual int FilterMeetingRecords(std::vector<Record> & records, 
    int startIndex = -1, int amount = -1) const = 0;
  virtual int FilterSystemRecords(std::vector<Record> & records, 
    int startIndex = -1, int amount = -1) const = 0;
  virtual int FilterRecordingRecords(std::vector<Record> & records, 
    int startIndex = -1, int amount = -1) const = 0;

public: // 查询某记录在会话所有记录的位置
  virtual int GetRecordIndex(
    const RecordId & recordId, const std::string & cvsId) = 0;

  virtual int GetPreRecordsByRecordId(std::vector<Record> & records, const RecordId& recordId, 
      const std::string& cvsId, const int limitcount) = 0;

public: // count query
  virtual int QueryUnreadCount() const = 0;
  virtual int QueryConversationCountBetweenDate(
    const Date & beginDate, const Date & endDate) const = 0; // [beginDate, endDate)

public: // remove operations
  virtual int RemoveRecordsByRecordId(const RecordId & recordId) const = 0;
  virtual int RemoveRecordsByRecordType(int recordType) const = 0;
  virtual int RemoveRecordsByConversationId(const std::string & cvsId) const = 0;

  virtual int RemoveCallRecords(CallType callType = CALL_ALL) const = 0;

  virtual int RemoveHistoryChatRecords() const = 0;
  virtual int RemoveHistoryChatRecordsByConversationIdAndDate(
    const std::string cvsId, const Date & date) const = 0;

  virtual int RemoveHistoryChatRecordsByConversationId(const std::string cvsId) const = 0;

  virtual int RemoveHistoryMemberRecordsByConversationId(const std::string cvsId) const = 0;

  virtual int RemoveHistoryCallRecords() const = 0;
  virtual int RemoveHistorySystemRecords() const = 0;

  virtual int RemoveRecentConversationById(const std::string & cvsId) const = 0;
  virtual int RemoveConversationById(const std::string & cvsId) const = 0;

}; // class HistoryManager

    } // namespace historydata
  } // namespace model
} // namespace uc

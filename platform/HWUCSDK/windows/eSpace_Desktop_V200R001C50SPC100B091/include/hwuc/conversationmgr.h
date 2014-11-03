/******************************************************************************
* Huawei Enterprise Communication API
* group.h
* Author :  Huawei
* Description :  Group related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma  once

namespace uc {
  namespace model {

class UCClient;
struct UCBookConfInfo;

    namespace conversation {

        enum APPCLASSLAYER_API FileTransferFunctionType
        {
            TRANS_IM_P2P,
            TRANS_GROUP_SHARESPACE,
        };
/**
* \brief ConversationUiObserver
* \note The ConversationUiObserver class is the interface exposed to UI
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API ConversationUiObserver
{
public:
  virtual bool OnNotification(void* _item) = 0;
};

/**
* \brief ConversationMgr
* \note The ConversationMgr class maintains all conversation(including outgoing and incoming)
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API ConversationMgr
{
public:
  enum CallExType
  {
      RegisterDNDType,
      UnRegisterDNDType,
      RegisterCallWaitType,
      UnRegisterCallWaitType
  };

  ConversationMgr(uc::model::UCClient* _cli = NULL)
    : client(_cli), observer(NULL)
  {
  }

  virtual ~ConversationMgr()
  {

  }

  /**
  * \brief supplied to UI for notification handling
  * \param[in]  msg item
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  virtual bool HandleConversationNotify(void* _item) = 0;

  /**
  * \brief init conversation manager
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  virtual bool Init() = 0;
  virtual bool Uninit() = 0;

  /**
  * \brief create a new conversation
  * \param[in]  N/A
  * \param[out] N/A
  * \return  conversation: if success, generate an identifier for new conversation
  */
  virtual Conversation* AddConversation() = 0;

  /**
  * \brief remove an exist conversation
  * \param[in]  _sess: Conversation need to be deleted 
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  virtual bool RemoveConversation(const std::string& _identifier) = 0;

  /**
  * \brief remove an exist conversation.just for discussgroup
  * \param[in]  _sess: Conversation need to be deleted 
  * \param[in]  bIsExitGroup: exit from discussgroup or not
  * \param[out] N/A
  * \return  true: success; false: failed
  */
  virtual bool RemoveDiscussGroupConversation(const std::string& _identifier, bool bIsExitGroup) = 0;

  /**
  * \brief get an exist conversation
  * \param[in]  Conversation identifier 
  * \param[out] N/A
  * \return  true: conversation pointer; false: NULL
  */
  virtual Conversation* GetConversation(const std::string& _identifier) = 0;

  virtual ctk::SharedPtr<Conversation> GetConversationSafe(const std::string& _identifier) = 0;

  virtual Conversation* GetConversationByProperty(ConversationProperty _type, const std::string& _value) = 0;

  virtual Conversation* GetConvByImTargetUri(const std::string& _targetUri) = 0;

  virtual Conversation* GetConvByFixedGroupId(const std::string& _groupId) = 0;

  /**
  * \brief get an exist conversation has specified contact
  * \param[in]  _contact 
  * \param[out] N/A
  * \return  true: conversation pointer; false: NULL
  */
  virtual Conversation* GetConversationByContact(const uc::model::Contact& _contact) = 0;

  /**
  * \brief Get count of exist conversation with AVSession
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true or false
  */
  virtual int GetAVSessionConvCount() = 0;
  /**
  * \brief Get count of exist conference conversation with AVSession count
  * \param[in]  N/A
  * \param[out] N/A
  * \return count of conference with AVSession 
  */
  virtual int GetConfAVSessionConvCount() = 0;

  /**
  * \brief Get count of exist conversation with AVSession except onhold
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true or false
  */
  virtual int GetAVSessionConvCountExceptOnhold() = 0;

  /**
  * \brief Check if exist conversation with AVSession and AVSession is conference
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true or false
  */
  virtual bool HasConfAVSessionConv() = 0;

  /**
  * \brief Check if exist conversation with AVSession and AVSession is connecting
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true or false
  */
  virtual Session* GetConnectingAVSession() = 0;

  /**
  * \brief Get connected AVSession 
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true or false
  */
  virtual Session* GetConnectedAVSession() = 0;

  /**
  * \brief create a new conversation for conference
  * \note  Reserved for future use
  * \param[in]  _confurl  conference quick link
  * \param[out] N/A
  * \return  conversation: if success, generate an identifier for new conversation
  */
  virtual Conversation* JoinConference(const std::string& _confurl) = 0;

  /**
  * \brief get current file transfer count 
  * \param[in]  _confurl  conference quick link
  * \param[out] N/A
  * \return  total trans count
  */
  virtual int GetCurrentFileTransCount() = 0;

  /**
  * \brief disconnect with UI observer
  * \param[in]  N/A
  * \param[out] N/A
  * \return  total trans count
  */
  virtual void DisconObserver() = 0;

  /*fixgroup share space manager, bad in here, need to optimize*/
  virtual void ReSetShareSpace() = 0;
  virtual int GetShareSpaceCurrentFileTransCount() = 0;
  virtual bool Upload(const std::string& _groupId, const FixedGroupShareSpaceFile& cFile, std::string &_sessionId) = 0;
  virtual bool Download(const std::string& _groupId, const FixedGroupShareSpaceFile& cFile, std::string &_sessionId) = 0;
  virtual bool Delete(const std::string& _groupId, const FixedGroupShareSpaceFile& cFile,  std::string &_sessionId) = 0;
  virtual bool Cancel(const FixedGroupShareSpaceFile& cFile, const std::string& _sessionId) = 0;
  virtual bool List(const std::string _groupId, std::string _pageNum, std::string _pageSize,
      std::string _pageOffset) = 0;

public:
  uc::model::UCClient* client;   //!< uc client instance

  ConversationUiObserver* observer;  //!< ui observer for handling notification

  /**
  * \brief new instant session has been added signal.
  *        temp group has been created for UE
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnInstantSessAdded(uc::model::conversation::Conversation* _con); 
  */
  sigslot::signal1<Conversation*> InstantSessAdded;

  /**
  * \brief new audio/video session has been added signal.
  *        incoming audio/video call for UE
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAvSessAdded(uc::model::conversation::Conversation* _con); 
  */
  sigslot::signal2<Conversation*, sAudioVideoParam&> AVSessAdded;

  /**
  * \brief be kicked from the instant session.
  *        1. end conversation; 2. all incoming session has ended
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnInstantSessRemoved(uc::model::conversation::Conversation* _con); 
  */
  sigslot::signal1<Conversation*> InstantSessRemoved;

  sigslot::signal3<std::string, const sFileTransParam&, FileTransferFunctionType> FileReceived;
  sigslot::signal2< std::string, sImMsgItem& >  InstantMessageReceived;
  sigslot::signal2<std::string, sMsgSendResultParam>   instantMessageSendResult;
  sigslot::signal2<std::string, const sSmsParam&> SmsReceived;

  sigslot::signal1<const sSysMsgItem&> SystemMsgReceived;

  sigslot::signal2<int, uc::model::UCBookConfInfo&> BookConfBcReceived;

  sigslot::signal2<std::string, bool> ReloginReceived;

  /**
  * \brief AV session receive ring notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionRinged(uc::model::conversation::Conversation* _con, std::string _remoreuri);
  */
  sigslot::signal2<Conversation*, std::string> AVSessionRinged;

  /**
  * \brief AV session receive closed notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionClosed(uc::model::conversation::Conversation* _con, std:;string _reason); 
  */
  sigslot::signal2<Conversation*, sMsgAVSessionClosedParam&> AVSessionClosed;

  /**
  * \brief AV session receive connected notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAVSessionConnected(uc::model::conversation::Conversation* _con); 
  */
  sigslot::signal1<Conversation*> AVSessionConnected;

    /**
  * \brief Phone Joint related notification
  *        UI need to implement has_slots<> and connect to the signal.
  */
  sigslot::signal1<int> AVPhoneJointRelated;

  sigslot::signal1<Conversation*> AVPhoneJointReferToLocalConf;

  sigslot::signal2 <Conversation*, std::string> AVPhoneAddConfMemberReq;

  sigslot::signal1 <Conversation*> AVPhoneCreateConfReq;
    /**
  * \brief receive ACB Refer notification
  *        UI need to implement has_slots<> and connect to the signal.
  */
  sigslot::signal1<std::string> AVACBReferNotifyReceived;

  /**
  * \brief Occurs when group participants changed
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void ConvGroupMemberChanged(uc::model::conversation::Conversation* _conv, 
  *                             std::vector<std::string> _kicklist, std::vector<std::string> _addlist); 
  */
  sigslot::signal3<Conversation*, std::vector<std::string>, std::vector<std::string> > ConvGroupMemberChanged;

  /**
  * \brief receive ACB ReservedFailure notification
  *        UI need to implement has_slots<> and connect to the signal.
  */
  sigslot::signal2<std::string, bool> AVReservedResult;

    /**
  * \brief AV session receive 181 forward notification
  *        UI need to implement has_slots<> and connect to the signal.
  */
  sigslot::signal2<Conversation*, std::string> AVSessionForward;

  sigslot::signal1<sSoftConsoleCallQueueParam> SoftConsoleCallQueueResult_;

  sigslot::signal3<std::string,  std::vector<FixedGroupShareSpaceFile>, std::string> FixGroupShareSpaceFileListResult;
  sigslot::signal2<std::string,  std::string> FixGroupShareSpaceFileDeleteResult;
  sigslot::signal2<CallExType, bool> CallExCodeRes;

  sigslot::signal2<Conversation*, std::string> ReferNotify;
  sigslot::signal2<Conversation*, std::string> PeerNumChangeNotify;
};

    }
  }
}

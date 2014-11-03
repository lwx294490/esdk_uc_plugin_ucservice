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

#pragma once

namespace uc {
  namespace model {
    namespace conversation {

// ! An enum
/** \brief  Participant conf state
*/
const std::string PART_CONFSTATE_NEEDREFER = "10";
const std::string PART_CONFSTATE_INVITING = "1";
const std::string PART_CONFSTATE_HANGUP = "4";
const std::string PART_CONFSTATE_INCONF = "5";
const std::string PART_CONFSTATE_QUIT = "6";
const std::string PART_CONFSTATE_INHOLD = "7";

enum ParticipantState
{
  stateInviting = 1,
  stateHangup = 4,
  stateInconf = 5,
  stateQuit = 6,
  stateInHold = 7,
  stateNeedreffer = 10,
};
// ! An enum
/** \brief  Participant aduio state
*/
const std::string PART_AUDIO_MUTED = "1";
const std::string PART_AUDIO_UNMUTED = "0";
const std::string PART_TEMPGROUPMEMBER_DND = "1";

enum MuteState
{
  unmuteState,
  muteState,
  requestToSpeak,
};

// ! An enum
/** \brief  Participant access audio session type
*/
const std::string PART_AUDIO_BY_MOBILE = "1";
const std::string PART_AUDIO_BY_FIXEDNUM = "2";

const std::string PART_AUDIO_CURSPEAKER = "1"; 

// ! An enum
/** \brief  participant property
*/
enum ParticipantProperty
{
  PartIsMergedConf,  /*!< merged conf member type */
  ParIsLeader,       /*!< The participant is a leader of the conversation. */
  ParIsConfLeader,   /*!< The participant is a leader of the conference. */
  ParIsAnonymous,    /*!< The participant is an anonymous user. */
  PartConfState,     /*!< The participant's state in current conference*/
  PartIsMuted,       /*!< The participant is muted now */
  PartAudioRight,    /*!< audio right that the participant has*/
  PartAudioDevType,  /*!< participant use which device type to enter the audio*/
  ParIsCurSpeaker,   /*!< participant is current speaker*/
  PartDeviceType,     /*!< The participant's deveice type of convergent conference:PC/2G/TP*/
  PartMediaType,     /*!< The participant's media type of convergent conference:Audio/Video*/
  PartIsdndType,     /*!< 由于是dnd用户而未真正接入会话，却依然显示的成员。*/
  PartOldConfState,  /*!< 记录上次刷新的状态，用于比较，如果没有变化不刷新界面*/
  PartReserved1,     /*!< reserved for future use*/
};

/**
* \brief Participant
* \note The Participant class represents attendee of the Conversation
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API Participant
{
public:

    Participant():bIsRemove(false)
  {
  }

  Participant(const Participant& _part)
  {
    this->contact_ = _part.contact_;
    this->propmap_  = _part.propmap_;
    this->bIsRemove = false;
  }

  ~Participant()
  {

  }

  Participant& operator = (const Participant& par)
  {
    if (&par != this)
    {
      this->contact_ = par.contact_;
      this->propmap_  = par.propmap_;
    }

    return *this;
  }

  uc::model::Contact contact_;   //!< participant detail info

  bool bIsRemove;//IPT2.2数据会议中与会者被移除为true，退出为false

  typedef std::map<ParticipantProperty, std::string> _ParPropMap;
  _ParPropMap propmap_;

};

    }
  }
}

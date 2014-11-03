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
    namespace conversation {

class Session;

namespace avchannel {

  // ! An enum
  /** \brief  audio/video media stream direction
  */
  enum MediaStreamDirection
  {
    InvalidMediaDir = 0,
    MediaSend,
    MediaReceive,
    MediaSendReceive,
  };

  // ! An enum
  /** \brief  audio/video channel state
  */
  enum ChannelState
  {
    ChannelConnecting,   /*!<  channel is establishing*/
    ChannelReceive,      /*!<  channel direction is receive only*/
    ChannelSend,         /*!<  channel direction is send only*/
    ChannelSendReceive,  /*!<  channel direction is send/receive*/
    ChannelInActive,     /*!<  channel is inactive*/
    ChannelSwitching,
  };

  enum ChannelEvent
  {
      ChannelSwitchToPcOk,
      ChannelSwitchToPcFailed,
      ChannelSwitchToPhoneOk,
      ChannelSwitchToPhoneFailed,
      ChannelUnknownEvent,
  };

  /**
  * \brief Channel
  * \note The Channel class controls media stream.
  * \author  y00135380
  * \version 1.0.0  initial version
  */
  class APPCLASSLAYER_API Channel
  {
  public:

    Channel(ChannelState state = ChannelInActive);

    Channel(ChannelState state,uc::model::conversation::Session* ownsession );

    /**
    * \brief Resume channel
    *        It's used for Resume a holded channel
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Start() = 0;

    /**
    * \brief Hold channel
    *        It's used for hold an established channel
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Stop() = 0;

    virtual bool Switch() = 0;


    virtual ChannelState GetChannelState() const;


    virtual void SetChannelState(const ChannelState state);


    virtual uc::model::conversation::Session* GetOwnSession();


    virtual void SetOwnSession(uc::model::conversation::Session* const sess);


  public:

    ChannelState state_;  /*!< Current channel state*/

    uc::model::conversation::Session* session_;  /*!< Session that this channel belongs to*/

  public:

    /**
    * \brief Occurs when the channel state changes
    *        UI need to implement has_slots<> and connect to the signal.
    *        Like this:  void OnChannelStateChanged(uc::model::conversation::avchannel::ChannelState _state, uc::model::conversation::Session* _pSess); 
    */
    sigslot::signal2<ChannelState, uc::model::conversation::Session*> ChannelStateChanged;  

    sigslot::signal2<ChannelEvent, uc::model::conversation::Session*> ChannelEventOccur;  
  };

  /**
  * \brief Audio Channel
  * \note The Channel class controls audio media stream.
  * \author  y00135380
  * \version 1.0.0  initial version
  */
  class APPCLASSLAYER_API AudioChannel: public Channel
  {
  public:
    /**
    * \brief Send DTMF event
    * \param[in]  _tones dtmf event string
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    bool SendDTMF(const std::string& _tones);

    /**
    * \brief See the reference of Channel
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Start();

    /**
    * \brief See the reference of Channel
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Stop();

    virtual bool Switch();
  };

  /**
  * \brief VideoWindow
  * \note The Channel class controls media channel.
  * \author  y00135380
  * \version 1.0.0  initial version
  */
  struct APPCLASSLAYER_API VideoWindow
  {
  public:
    VideoWindow()
      : wnd_(NULL)
      , height_(0)
      , width_(0)
      , left_(0)
      , top_(0)
    {

    }
#ifdef WIN32
    HWND wnd_;   //!< render window
#else
    void* wnd_;  //!< render window
#endif
    int height_; //!< render window height
    int width_;  //!< render window width
    int left_;   //!< render window left corner
    int top_;    //!< render window top corner
    std::string defaultimg_;
  };

  /**
  * \brief Video Channel
  * \note The Channel class controls video media stream.
  * \author  y00135380
  * \version 1.0.0  initial version
  */
  class APPCLASSLAYER_API VideoChannel: public Channel
  {
  public:
    /**
    * \brief See the reference of Channel
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Start();

    /**
    * \brief See the reference of Channel
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Stop();

    virtual bool Switch();

    /**
    * \brief Change video channel's VideoWindow parameter
    * \param[in]  N/A
    * \param[out] N/A
    * \return  true: success; false: failed
    */ 
    virtual bool Update();

  public:
    VideoWindow localwnd_;   //!< local video render window
    VideoWindow remotewnd_;  //!< remote video render window
  };

      }
    }
  }
}

/******************************************************************************
* Huawei Enterprise Communication API
* ecsclient.h
* Author :  Huawei
* Description :  UCSelf and UCClient related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once


namespace uc {
    namespace model {

        // ! An enum
        /** \brief  permission field definition
        */
        enum APPCLASSLAYER_API PermissionType
        {
            AbbDial,                 //缩位拨号    01 
            PwdCallLimit,
            CallLimit,               //呼叫限制       03
            LostCallNotifySms,       //未接来电转短信  04    
            BlackWhiteList,          //黑白名单   05   
            Ctd,                     //点击呼叫   06
            CallAllNewSev,           //撤销所有业务  07
            OneNum,                  //一号通  08
            CallDeflection,          //呼叫偏转  09
            RemoteReg,               //远程注册  10
            MainNum,                 //企业总机  11
            Attendant,               //话务员  12
            SecretarySev,            //秘书业务  13
            SecretaryStationSev,     //秘书台  14
            Clir,                    //主叫线识别限制  15
            ClirOverride,            //主叫线识别限制逾越  16
            Clip,                    //主叫线识别显示  17
            DisplayUsrName,          //主叫显示姓名  18
            CallerId,                //被叫来电显示  19
            AnonymousCallReject,     //匿名呼叫拒绝  20
            GroupPickUp,             //同组代答  21
            DesignatePick,           //指定代答  22
            AlarmClock,              //闹钟业务  23
            Acb,                     //自动回叫业务  24
            Recording,               //录音  25
            CallTransfer,            //呼叫转接  26
            CallPark,                //呼叫驻留  27
            CallWait,                //呼叫等待  28
            CallHold,                //呼叫保持  29
            DisRinging,              //区别振铃  30
            BargeInsert,             //强插  31
            BargeDisconnect,         //强拆  32
            BargeOverride,           //强替  33
            BargeMonitor,            //监听  34
            NightService,            //夜服功能  35
            DoNotDisturb,            //免打扰  36
            ThreePartyConf,          //三方通话  37
            CallForwardUnCondi,      //无条件转移  38
            CallForwardOnBusy,       //遇忙转移  39
            CallForwardOnReply,      //无应答转移  40
            CallForwardOffline,      //离线转移  41
            ForwarVoimailBoxUnCon,   //无条件转语音邮箱  42
            ForwarVoimailBoxBusy,    //遇忙转语音邮箱  43
            ForwarVoimailBoxNoReply, //无应答转语音邮箱  44
            ForwarFaxMailBoxUnCon,   //无条件转传真  45
            ForwarOnCon,             //条件转移  46
            ForwarVoiMailBoxOffline, //离线转语音邮箱  47
            HuntingGroup,            //Hunting寻呼  48
            VipList,                 //私人列表  49
            FaxMail,                 //语音传真  50
            DataConf,                //多媒体会议  51
            FileTrans,               //文件传输  52
            VideoCall,               //视频通话功能  53
            VoiceConf,               //语音会议  54
            EnterBussBook,           //企业地址簿   55
            PersonBook,              //个人地址簿  56
            Sms,                     //短信功能  57
            Mms,                     //彩信功能  58
            IM,                      //即时消息  59
            TurnPhone,               //一键转接  60
            VoiceCall,               //音频通话功能  61
            CreateGroup,             //创建群组  62
            DeptNotificaton,         //部门通知  63
            GroupMessage,            //群发消息  64

            VideoConf = 79,          //视频会议  79
            DenyForwarding = 81,     //呼叫前转拒绝
            FwdIntelligence,         //智能前转
            FollowMe,                //Follow Me
            Immediate2Voicemail,     //语音邮箱即时转
            DoPhoneJoint ,           //话机联动  86

            LBS = 88,                //LBS
            Intercom,                //对讲机
            Mobility,                //IP话机移动
            CallLog = 91,                 //呼叫日志以及漫游聊天记录 92

            MsgWaiting = 96,         //留言灯
            HotLine,                 //热线

            MaliciousCallTrace = 98,  //恶意呼叫
            SNR = 99,                //Single Number Reach
            Presence,               //状态呈现
            ExchangeStatus,          //Exchange状态同步

            FixGroupShareSpaceFunFlag  = 109, //110群共享

            OffLineFileTranslate = 110,//第111位离线文件传输
            VisualVoiceMail = 111,
            //CampOnBusy = 113,//114无缝忙转 zhangxuewen删除，IMS里CampOnBusy用26位来一起控制
            SrvCallRecordPermission = 113, //漫游呼叫记录 114
            UnknownPermission = 200,
        };

        enum APPCLASSLAYER_API FeatureType //特性位
        {
            NoDisturbFeature = 2,  //免打扰是否开启
            FPwdCallLimit = 6,
            CallWaitFeature = 7,    //呼叫等待是否开启

            FCallForwardUnCon = 9,
            FCallForwardOnBusy,
            FCallForwardOnNoReply,
            FCallForwardOffline,

            FCallForward2VoicemailAll,
            FCallForward2VoicemailOnBusy,
            FCallForward2VoicemailOnNoReply,
            FCallForward2VoicemailOffline
        };

        // ! An enum
        /** \brief  playing ringtone type definition
        */
        enum APPCLASSLAYER_API RingType
        {
            ContactRing = 0,
            GroupRing,
            InsideRing,
            OutsideRing,
            CallbackRing,
            SystemRing,
            IMMsgRing,
            SysMsgRing
        };

        /**
        * \brief OnlineConfig
        * \note The OnlineConfig class is used for reminder when user login
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API OnlineConfig
        {
        public:
            int GetOnlineTipsList(std::vector<std::string>& _list) const;
            int SaveOnlineTipsList(const std::vector<std::string>& _list) const;
        };

        class APPCLASSLAYER_API SMSSignatureConfig
        {
        public:
            int GetSMSSignatureList(std::vector<std::string>& _list) const;
            int SaveSMSSignatureList(const std::vector<std::string>& _list) const;
        };

        class APPCLASSLAYER_API TransferNumberConfig
        {
        public:
            int GetNumberList(std::vector<std::string>& _list) const;
            int SaveNumberList(const std::vector<std::string>& _list) const;
            bool AddNumber(const std::string & number) const;
        };

        /**
        * \brief RingToneConfig
        * \note The RingToneConfig class is used for playing ringtone when new call arrives
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API RingToneConfig
        {
        public:
            bool SaveContactGroupRing(
                const std::string& _id, const std::string& _ringtone) const;
            bool SaveGlobalRing(const int _type, const std::string& _ringtone) const;
            bool GetContactGroupRing(
                const std::string &_id, std::string& _ringtone) const;
            void GetGlobalRing(const int _type, std::string& _ringtone) const;
            bool RemoveContactGroupRing(const std::string& _id) const;
        };

        /**
        * \brief StringItem
        * \note The StringItem class is used for storing quick (auto) reply messages
        * \author  c00161520
        * \version 1.0.0  initial version
        */
        typedef long long IDType;
        struct APPCLASSLAYER_API StringItem
        {
            IDType id;
            std::string content;

            StringItem() : id(0) {}
        };

        /**
        * \brief QuickReplyConfig
        * \note The QuickReplyConfig class is used for storing quick reply messages
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API ReplyConfig
        {
        public:
            int SaveQuickReplyList(const std::vector<StringItem> & _list) const;
            bool AddQuickReply(StringItem & strItem) const;
            bool UpdateQuickReply(const StringItem & strItem) const;
            bool RemoveQuickReply(const IDType & id) const;
            int ClearQuickReply() const;
            int GetQuickReplyList(std::vector<StringItem> & strItems) const;

        public:
            int SaveAutoReplyList(const std::vector<StringItem> & _list) const;
            bool AddAutoReply(StringItem & strItem) const;
            bool UpdateAutoReply(const StringItem & strItem) const;
            bool RemoveAutoReply(const IDType & id) const;
            int ClearAutoReply() const;
            int GetAutoReplyList(std::vector<StringItem> & strItems) const;
        };

        /**
        * \brief SimpleConfig
        * \note The SimpleConfig class is used for UI to store simple key/value pair config
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API SimpleConfig
        {
        public:
            bool GetUserConfig(
                const std::string & _strkey, std::string & _strValue) const;
            bool SaveUserConfig(
                const std::string & _strkey, const std::string & _strValue) const;
        };

        /**
        * \brief   用户自定义状态
        * \note    目前支持忙碌和离开两个大类，小类别用户自己定义
        * \author  liwenwqing 217212 20121226
        * \version 1.0.0  initial version
        */
        typedef long long UserDefineStateID;
        struct APPCLASSLAYER_API UserDefineStateDateType
        {
            UserDefineStateID userDefineStateId;  //主键，递增
            std::string strParentState;           //自定义状态所属的大类，目前支持忙碌和离开两个大类 liwenwqing 217212 20121226
            std::string strChildStateContent;     //用户自定义状态内容
        };

        class APPCLASSLAYER_API UserDefineStateConfig
        {
        public:
            /*************************************************************/
            /*
            /* 函数作用：获得某一大类的用户自定义状态，比如忙碌作为父状态
            /* 参数    ：
            /*          [in ]_strParentState 父类状态
            /*          [out]vectorUserDefineState_ 所有子类的状态
            /*
            /* 备注： 目前支持忙碌和离开两类状态下可以自定义状态
            /*
            /*************************************************************/
            int GetUserDefineStateByParentState(const std::string & _strParentState, std::vector<UserDefineStateDateType> & vectorUserDefineState_) const;

            /*************************************************************/
            /*
            /* 函数作用：增加一个用户自定义状态
            /* 参数    ：
            /*          [out]UserDefineStateId_ 新增加的状态ID值，
            /*               在数据库中是自增的主键
            /*          [in ]_strParentState 父状态
            /*          [in ]_strStateContent 用户自定义的状态
            /*
            /* 返回值： ture表示插入成功，false表示插入失败
            /*
            /* 备注： 插入后，用户要得到刚刚插入的主键，以便删除该记录
            /*
            /*************************************************************/
            bool AddOneUserDefineState(int &UserDefineStateId_, const std::string & _strParentState, const std::string & _strStateContent) const;

            /*************************************************************/
            /*
            /* 函数作用：通过主键（状态id）删除用户自定义状态
            /* 参数    ：
            /*          [in ]_userDefineStateId 状态id，在数据库中是自增的
            /*
            /* 返回值： ture表示删除成功，false表示删除失败
            /*
            /*************************************************************/
            bool DeleteOneUserDefineState(const UserDefineStateID _userDefineStateId) const;

        };

        struct APPCLASSLAYER_API WorkspacePanel
        {
            std::string name;
            std::string url;
            std::string image;
            std::string type;
        };

        /**
        * \brief WorkspaceConfig
        * \note The WorkspaceConfig class is used for manage user workspace panels
        * \author  c00161520
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API WorkspaceConfig
        {
        public:
            int SaveWorkspaceList(const std::vector<WorkspacePanel> & panels) const;
            bool AddWorkspace(const WorkspacePanel & panel) const;
            bool RemoveWorkspace(const std::string & name) const;
            int ClearWorkspace() const;
            bool GetWorkspace(const std::string & name, WorkspacePanel panel) const;
            int GetWorkspaceList(std::vector<WorkspacePanel> & panels) const;
            int GetWorkspaceListByType(const std::string & type, 
                std::vector<WorkspacePanel> & panels) const;

        };

        // ! An enum
        /** \brief  Booked conference related push messages
        */
        enum APPCLASSLAYER_API BookConfCnType
        {
            BOOKCONF_CNCREATE = 0,
            BOOKCONF_CNMODIFY,
            BOOKCONF_CNCANCEL,

            BOOKCONF_CNUNKNOWN,
        };

        struct APPCLASSLAYER_API UCBookConfInfo
        {
            std::string topic;  //!< conf subject
            std::string meetingtime;  //!< conf time
            std::string convener; //!< conf convener
            std::string convenername; //!< convener name
            std::vector<std::string> attendeelist;    //!< conf member list
            std::string accessnum;    //!< conf access number
            std::string securitycode;    //!< conf security number
            std::string iscycle;    //!< whether it's a cycle conf
            std::string startdate;    //!< conf start date
            std::string validityperiod;    //!< conf duration period
            std::string content;         //!< conf content
            std::string chairmanpwd;  //!< chairman password
            std::string partmanpwd;  //!< participant password
            std::string recordcode;  //!< conf record code
            std::string funcbits;    //!< conf funcbits 
            std::string mediaBits;  //!< media type,1:audio 2:video 3:data ,exm 001 only have data media
            ctk::int16 confType;    //!< conference type, 0instant 1booking 2cycle 3persistent
            std::string confid;      //!< conf id
            std::string confStyle;    //!< conf Style

            UCBookConfInfo() : confType(-1) {}
        };
        std::ostream & operator<<(std::ostream & _os, 
            const uc::model::UCBookConfInfo & bookConf);   

        /**
        * \brief Voice mail query condition
        * \note The VoiceMsgQuery class is used for conditional query
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API VoiceMsgQuery
        {
            std::string prevId;
            int pagecount;
            int ordertype;
        };

        /**
        * \brief conference query condition
        * \note The BookConferenceQuery class is used for conditional query
        * \author  z00214359
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API BookConferenceQuery
        {
            int pagesize;
            int currentpage;
        };

        /**
        * \brief UCVoiceMailMsg
        * \note The UCVoiceMailMsg class is used for Voice Mail
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API UCVoiceMailMsg
        {
            std::string voiceid;  //!< 留言消息ID
            std::string voicetype;     //!< 留言类型
            std::string src;      //!< 留言者号码
            std::string srcname;  //!< 留言者姓名
            std::string time;     //!< 留言时间
            ctk::Int32  duration; //!< 留言时长
            std::string  status;   //!< 留言状态
            std::string  importance; //!< 留言重要性
            std::string  sensity;    //!< 留言私密性
            std::string voicecode;  //!< 留言提取号码
        };
        std::ostream & operator<<(std::ostream & _os, 
            const uc::model::UCVoiceMailMsg & _msg); 

        // ! An enum

        /** \brief  record msgtype define
        */
        enum APPCLASSLAYER_API SrvRecordMsgType
        {
            InvalidRcdType = 0,
            P2PRcdype, //1点对点消息
            GroupRcdType, //2群组消息
            SystemRcdType, //3系统消息
            DeptNtfRcdType, //4部门通知
            MeetingNtfRcdType, //5会议通知
            SysAndMeetingNtfRcdType, //6系统和会议通知
        };

        /**
        * \brief UCSrvRecord
        * \note The UCSrvRecord class is used for server record history
        * \author  l00193975
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API SrvRecord
        {
            std::string id; //!< 消息记录ID
            SrvRecordMsgType msgtype; //!<消息类型
            std::string name;
            std::string sender; //!< 消息发送方
            std::string recver; //!< 消息接收方
            std::string msgtime; //!< 消息时间
            std::string subject;
            std::string msgsvctype;
            std::string content; //!<消息内容
            std::string encodetype; //!<消息编码格式
        };

        enum CallHistoryType  //Added by z65727 [2013/12/7]
        {
            emAllCall = 0,		//全部
            emMissedCall,		//未接
            emReceivedCall,	//已接
            emPlacedCall		//呼出
        };

        struct APPCLASSLAYER_API SrvCallRecord //Added by z65727 [2013/12/7]
        {
            long long id; //!< 消息记录ID
            std::string Callee; //!< 主叫号码
            std::string Caller; //!< 被叫号码
            std::string StartTime; //!< 呼叫开始时间
            int CallDuration; //!< 呼叫持续时间(s)
            CallHistoryType emType; //!< 呼叫类型：0 All;1 Missed;2 Received;3 Placed
        };

        std::ostream & operator<<(std::ostream &  _os, const uc::model::SrvRecord & _rcd);

        /**
        * \brief profile of current user
        * \note get value from ecs::ecsdata::UserProfile
        * \author  c00161520
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API SelfProfile
        {
            std::string profilepath_;    //!< user data path
            std::string headimagepath_;  //!< Cached image header file path
            std::string imagefilepath_;  //!< cached image in im message
            std::string receivefilepath_;  //!< file transfer
            std::string recordfilepath_;  //!< record files
            std::string portaladdr;      //!< Personal PORTAL address
            std::string portaladdrback;      //!< Backup Personal PORTAL address
            std::string confportal;      //!< Main conf PORTAL address
            std::string confportalback;  //!< Bakup conf PORTAL address
            std::string confaccesscodelist; //!< access code list of conferences
            std::string cscfdomain; //!< cscf domain
            std::string cscfdomainname; //!< cscf domain name
            std::string contrycode; //!< contry code
            std::string token;      //!< token

            std::map<std::string, std::string> callexcodelist;  //!< Extended call business code

            int curcenter;               //!< Real center belongs to: 0 South ; 1 North
            int retrytimes;		           //!< Remaining retry times
            int maxretrytimes;		       //!< max retry times 
            int maxcontact;              //!< Max allowed contact count
            int firstlogin;              //!< Whether first login
            int voiceMailFlg;
            int holdtimeout;        //!< callhold time
            std::string zone;            //!< user zone
            std::string netLocation;     //!< network location: 1 internal network, 2 external network

            std::map<std::string, std::string> pluginconfigs_;  //plugin params fetched from the server

            std::string corpId;
            std::string lastLoginTime;              //!< Last login time
            std::string voicemailaccesscode;
            std::string mailboxnum;                 // voice mail box number
            std::string lastLocation;          //!< Last login Location
            std::string snrnum;               //一键转接号码
            std::string featurelist;          //业务特性列表
            std::vector<std::string> sensewordlist; //!< sensible words list

            bool bPhoneUser; //是否联动用户
            bool bPhoneJoint; //是否已经开启联动
            bool bInputStatus; //!< Whether you notify your input status
            int corenetdeploymodel; //!< 0: uap ; 1: ims ; 2: ims+ats;
            int selfcalllimittype;
            bool bCallWaitOpen;
            std::string faxresponseurl;
            std::string passwordlimit;
            SelfProfile() 
                : curcenter(-1), retrytimes(-1), maxretrytimes(-1), maxcontact(-1), firstlogin(-1),selfcalllimittype(0)
                , holdtimeout(0), corenetdeploymodel(1)
            {
                bInputStatus = false;
                bPhoneUser = false;
                bPhoneJoint = false;
                bCallWaitOpen = false;
                voiceMailFlg = 0;
            }
            ~SelfProfile() {}
        };

        /**
        * \brief vip list item
        * \note get value from ecs::ecsdata::UserProfile
        * \author  c00161520
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API PrivateListItem
        {
            std::string bindNo;   //<! bind number
            std::string name;     //<! vip name
            std::string reserve;  //<! not used
        };

        struct APPCLASSLAYER_API ACBItem
        {
        public:
            std::string callee_;  //!< auto call back number
            int time_;    //!< call back time
        };

        class APPCLASSLAYER_API ACBConfig
        {
        public:
            int GetACBLineNum() const;
            int GetACBList(std::vector<ACBItem> & acblist) const;
            void SetACBList(const std::vector<ACBItem> & acblist);

            sigslot::signal1<std::string> ACBNotify_;
        };

        class APPCLASSLAYER_API CallForwardConfig
        {
        public:
            std::string ControlCFU;
            std::string FwdUnconNum;
            std::string FwdNoAnsNum;
            std::string FwdBusyNum;
            std::string FwdOfflineNum;
            bool bFwdUnconToVoiceMail;
            bool bFwdNoAnsToVoiceMail;
            bool bFwdBusyToVoiceMail;
            bool bFwdOfflineToVoiceMail;
        };

        class APPCLASSLAYER_API FixedGroupCreateConfig
        {
        public:
            int maxGroupCreateLimit;            //个人可创建的最大群组数
            int maxGroupMemeberLimit;           //群组内最大成员数
        };

        class APPCLASSLAYER_API BossSecConfig
        {
        public:
            int GetIdentity() const;
            bool IsShareLine(int lineindex) const;
        };

        struct APPCLASSLAYER_API LBSLocationInfo
        {
            ctk::String locationId;
            bool isLeaf;
            ctk::String locationName;
        };

        enum BUSINESS_PROPERITY_TYPE
        {
            BUSINESS_PARK_INSESSION,
        };

        class APPCLASSLAYER_API BusinessDescription
        {
        public:
            typedef std::set<BUSINESS_PROPERITY_TYPE> _Properity;

            BusinessDescription(){}
            virtual ~BusinessDescription(){}

            virtual bool HasProperity(const BUSINESS_PROPERITY_TYPE _properity) = 0;
            virtual void GetProerity(_Properity &_properities) = 0;
        };
        /**
        * \brief UCSelf
        * \note The UCSelf class is the Self detailed information manipulation class
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API UCSelf
        {
        public:
            enum PubContactInfoType
            {
                Availability,
                CustomStatusDesc,
                Position, 
                Location, 
                AVTool, 
                Signature,
                HeadImage,
                CallDeviceDesc,
                Invalid, 
            };

            virtual ~UCSelf()
            {
            }

            virtual bool Init() = 0;

            virtual bool Uninit() = 0;

            /**
            * \brief Judge if we have the specified featrueFlag
            * \param[in]  featrue type
            * \param[out] N/A
            * \return  true:  has featrue ; false: Otherwise 
            */
            virtual bool HasFeatrueFlag(FeatureType _type) = 0;

            /**
            * \brief Judge if we have the specified permission
            * \param[in]  permission type
            * \param[out] N/A
            * \return  true:  has permission ; false: Otherwise 
            */
            virtual bool HasPermission(PermissionType _type) = 0;

            /**
            * \brief Judge if we have the Sip Reg OK state
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  has sip Reg OK state ; false: Otherwise 
            */
            virtual bool GetSipRegOk() = 0;

            /**
            * \brief Check Is DND Ring-off Mode
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  has permission ; false: Otherwise 
            */
            virtual bool CheckIsDNDRingOffMode() = 0;


            /**
            * \brief Publish self information.
            *        Include status/signature/headimage etc.
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool PublishSelfInformation(const std::map<PubContactInfoType, std::string>& _values) = 0;

            /**
            * \brief Sync Self information from local db.
            *        Include status/signature/head image etc.
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool RefreshSelfInfo() = 0;

            /**
            * \brief Get self related booked conference list
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool GetBookConfList(const BookConferenceQuery& _cond,std::vector<UCBookConfInfo>& _list,unsigned int* conferencecount) = 0;

            /**
            * \brief Get current user profile value
            * \param[in]  
            * \param[out] _profile: user profile
            * \return  true:  Success ; false: Failed 
            */
            virtual bool RefreshSelfProfile() = 0;
            virtual SelfProfile & GetProfile() = 0;
            virtual std::string GetProfilePath() const = 0;  /*< assign user profile storage path*/
            virtual int GetSrvRecord(const std::string& userId, 
                const std::string& startTime, const std::string& endTime, 
                int msgType, int pageNum, int pageSize, int amount, 
                std::vector<uc::model::SrvRecord>& _rcdList) = 0;

            /***
            * \brief  Save the Call Forward Config to local store                                                             * \param[in]  
            * \param[out]
            * \return
            */
            virtual void PersistCallForwardConfig() = 0;

            /**
            * \brief Get current user call forward config
            * \param[in]  
            * \param[out]
            * \return
            */
            virtual void RefreshCallForwardConfig() = 0;

            /**
            * \brief 从服务器AA获取呼叫记录
            * \param[in] nCurrentPage，页面上指定的当前页
            * \param[in] nCallType, 呼叫类型 uc::model::historydata::CallType
            * \param[in] nPerPageCount, 每页查询的数目
            * \param[out] lstCall: 获取的一页呼叫记录
            * \param[out] uRecordCount: 获取的一页记录数目
            * \return  呼叫记录总条数 
            *  added by zhangxuewen 65727
            */
            virtual bool GetSrvCallRecord(const unsigned int nCurrentPage, const unsigned int nCallType, 
                const unsigned int nPerPageCount, unsigned int &uRecordCount, std::vector<uc::model::SrvCallRecord> &lstCall)=0;

            /**
            * \brief Del call log list from server
            * \param[in]  _targetnum   filtered target number
            * \param[in]  _list  call log list
            * \param[out] call log list
            * \return  true: success; false: failed
            */
            virtual bool DelCallLog(const std::string& _targetnum, const std::vector<std::string> _list) = 0;

            /**
            * \brief Get current user's private vip list
            * \param[in]  
            * \param[out] _list: private vip list
            * \return  number of private vips
            */
            virtual int GetPrivateList(std::vector<PrivateListItem> & _list) = 0;
            virtual int SetPrivateList(const std::vector<PrivateListItem> & _list) = 0;

            /**
            * \brief Get voice mail message list
            * \param[in]  N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool GetVoiceMsgList(const VoiceMsgQuery& _cond, std::vector<UCVoiceMailMsg>& _list) = 0;

            /**
            * \brief Forward voice mail message to specified target
            * \param[in]  _id  voice message id
            * \param[in]  _target  target number
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool ForwardVoiceMsg(const std::string& _id, const std::string& _target) = 0;

            /**
            * \brief delete voice mail messages
            * \param[in]  _list  voice message id list
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool DelVoiceMsg(const std::string& _id, const std::string& _delType) = 0;
            /**
            * \brief Get messages of specified type
            * \param[in]  _msgtype: message type
            * \param[out] N/A
            * \return  0 success
            */
            virtual int GetUnreadList(int _msgtype) = 0;

            /*
            *beacuse of Asynchronous getting unread messages, restarting GetUnreadList need to reset first.
            */
            virtual void ResetUnreadList() = 0;

            /**
            * \brief Send fax to UMS
            * \param[in]  _target   target fax number
            * \param[in]  _filepath fax file path
            * \param[out] N/A
            * \return  current fax session related fax id 
            */
            virtual int SendFax(const std::string sender, const std::string _target, const std::string _filepath, std::string &strRsp) = 0;

            virtual void GetLinkageNum(std::string &_number) = 0;

            /**
            * \brief Get Location based services information from AA
            * \param[in]  fullNumber   user account number
            * \param[in]  locationID tree parent id (equals -1 if root)
            * \param[in]  _refresh if true, get lbs information directly from AA.
            * \param[out]  _lbsinfo all children of some parent id.
            * \return   true:  Success ; false: Failed 
            */
            virtual bool GetLBSOneLevelInformationFromAA(const std::string &locationID, 
                std::vector<uc::model::LBSLocationInfo> &_lbsinfo) = 0;

            /**
            * \brief set user's current location based services information to AA
            * \param[in]  fullNumber   user account number
            * \param[in]  userLocation user's current location.
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool SetLBSInformation(const std::string &userLocation) = 0;

            virtual bool UpdateCallConfig(int regCallWait) = 0;

            virtual bool GetUserImage(const std::string & _imageId) = 0;
            virtual bool NotifyDispatchMsg(bool _bNotify) = 0;
            virtual void SetReloginToken(bool _isHeartbeatTimeout) = 0;
            virtual void StopHeartbeatThread() = 0;
            virtual void GetBindPhoneNumList(std::vector<std::string>& bindPhoneNumList) = 0;
        public:
            uc::model::Contact selfInfo;  /*!< Self detailed information*/
            uc::model::ContactAvailability selfStatus;  /*!< Self status */
            std::string selfStatusDesc;   /*!< Self status description */        

            OnlineConfig onlinecfg_;     /*!< online tips config*/
            SMSSignatureConfig smsSigncfg_;     /*!< sms signature config*/
            TransferNumberConfig transferNumCfg_; /*!< transfer number history list*/
            RingToneConfig ringtonecfg_; /*!< ring tone of incoming call config*/
            ReplyConfig quickreplycfg_; /*!< quick reply config*/
            SimpleConfig simplecfg_;     /*< value/pair simple config*/ 
            ACBConfig acbConfig_; /*< auto call back config*/
            UserDefineStateConfig userDefineStateConfig_; /**/
            CallForwardConfig callforwardConfig_;
            FixedGroupCreateConfig fixedGroupConfig_;
            uc::model::BusinessDescription *bussiness_;

        public:
            sigslot::signal2<int,int> VoiceMessageNotify_;

            /**
            * \brief Fax send result notify
            *        UI need to implement has_slots<> and connect to the signal.
            *        Like this:  void OnFaxSendResNotify();
            * \param[in]  std::string faxid
            * \param[in]  int  send result
            * \param[out] N/A
            * \return   
            */
            sigslot::signal2<std::string, int>  FaxSendResNotify_;
            sigslot::signal1<int> ReloginMsgNotify_;

            /**
            * \brief User Image changed notification
            *        UI need to implement has_slots<> and connect to the signal.
            *        Like this:  void OnUserImageChgedNotify_();
            * \param[in]  N/A
            * \param[out] N/A
            * \return   
            */
            sigslot::signal1<std::string> UserImageChangeNotify_;

        };

        /**
        * \brief LoginListItem
        * \note The LoginListItem struct represents user login information;
        * \author  c00161520
        * \version 1.0.0  initial version
        */
        struct APPCLASSLAYER_API LoginListItem
        {
            std::string account;  /*< login account */
            std::string password; /*< login password */
            std::string datetime; /*< login date and time */
            bool rememberPwd;
            bool autoLogin;

            bool usesvn1;         /* use svn or not ? */
            bool usesvn2;         /* use svn or not ? */
            std::string svnacc1;  /* first svn account */
            std::string svnacc2;  /* first svn account */
            uc::model::PasswordWrapper svnpsw1;  /* first svn pasword */
            uc::model::PasswordWrapper svnpsw2;  /* first svn pasword */
        };

        /**
        * \brief SystemConfig
        * \note The SystemConfig class is used for UI to store login list
        * \author  c00161520
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API SystemConfig
        {
        public:
            bool Initilize() const;
            bool Finalize() const;

            int GetLoginList(std::vector<LoginListItem> & items) const;
            bool UpdateLoginList(
                const std::string & account, const std::string & password, 
                bool rememberPwd, bool autoLogin) const;
            bool UpdateRememberPwd(const std::string & account, bool rememberPwd) const;
            bool UpdateAutoLogin(const std::string & account, bool autoLogin) const;
            bool DeleteAccount(const std::string & account) const;

            bool UpdateSVNConfig(
                const std::string & account, bool usesvn1, 
                const std::string & svnacc1, const std::string & svnpsw1,
                bool usesvn2, 
                const std::string & svnacc2, const std::string & svnpsw2) const;

            bool GetSysConfig(
                const std::string & _strkey, std::string & _strValue) const;
            bool SaveSysConfig(
                const std::string & _strkey, const std::string & _strValue) const;
            //是否用svn登录，给IM的会议组件使用，true表示是svn登录的，liwenqing 217212 20130106
            bool GetIsSvnLogin();
            bool SetIsSvnLogin(bool _bIsSvnLogin = false);

        private:
            static bool m_bIsSvnLogin; 
        };

        /**
        * \brief UCClient
        * \note The UCClient class is the basis for all Huawei UC2.0 API functionality
        * \author  y00135380
        * \version 1.0.0  initial version
        */
        class APPCLASSLAYER_API UCClient
        {
        public:
            enum SignInState
            {
                Client_Uninited,
                Client_SignedFailed,
                Client_SigningIn,
                Client_SignedIn,
                Client_KickedOut,
                Client_Invalid
            };

            UCClient();
            virtual ~UCClient();

            /**
            * \brief Initialize the uc system
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool Init() = 0;

            /**
            * \brief Initialize the uc system
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool UnInit() = 0;

            virtual bool GetUpdateAddress(
                const std::string & ip, int port, const std::string account) = 0;

            /**
            * \brief Sign in the uc system
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool SignIn(bool bIsNeedRegister = true) = 0;

            /**
            * \brief Sign Out the uc system
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool SignOut(bool bIsNeedUnregister = true) = 0;

            /**
            * \brief sip unregister -- eServer Interface
            * \param[in]  N/A
            * \param[out] N/A
            * \return  true:  Success ; false: Failed 
            */
            virtual bool SipUnregister() = 0;

            /**
            * \brief Get the UC client class instance
            * \param[in]  N/A
            * \param[out] N/A
            * \return  UCClient 
            */
            static UCClient* GetClient();
            static void ReleaseClient();

            void SetSoftConsole(bool bConsole) { is_softconsole_ = bConsole; }
            bool GetSoftConsole() { return is_softconsole_; }

            void SetConsoleSearchStrategy(int _search_strategy) { search_strategy_ = _search_strategy; }
            int GetConsoleSearchStrategy() { return search_strategy_; }

        public:
            bool is_softconsole_;
            int search_strategy_;
            uc::model::UCSelf* Self;     /*!< Self privacy */
            uc::model::ContactMgr* ContactManager;   /*!< Personal addressbook manager*/
            uc::model::ContactSubscription* ContactSubManager;  /*!< Contact presence subscription manager*/
            uc::model::FavouriteMgr* FavouriteManager;  /*!< My favourite manager*/

            uc::model::device::DeviceMgr* DeviceManager;   /*!< Audio/Video device manager*/

            uc::model::conversation::ConversationMgr* ConvManager;  /*!< IM/Call/Conference conversation manager*/

            uc::model::SignInConfig SignConfig;  /*!< Sign in param configuration*/
            uc::model::SystemConfig SysConfig; /*!< System config interface */
            uc::model::EntAddrbookMgr EntAddrbookManager_;  /*!< Enterprise addressbook manager*/

            /**
            * \brief User Permission changed notification
            *        UI need to implement has_slots<> and connect to the signal.
            *        Like this:  void OnPermissionChgedNotify_();
            * \param[in]  N/A
            * \param[out] N/A
            * \return   
            */
            sigslot::signal0<> PermissionChgedNotify_;

            /**
            * \brief User CallForward changed notification
            *        UI need to implement has_slots<> and connect to the signal.
            *        Like this:  void OnCallForwardChgedNotify_();
            * \param[in]  N/A
            * \param[out] N/A
            * \return   
            */
            sigslot::signal0<> CallServiceSettingChgedNotify_;

            /**
            * \brief client signin result notify Signal
            *        UI need to implement has_slots<> and connect to the signal.
            *        Like this:  void OnStateChanged(uc::model::UCClient::SignInState _state, std::string);
            * \param[in]  N/A
            * \param[out] N/A
            * \return   
            */
            sigslot::signal2<SignInState, std::string> SignInNotify_;
            sigslot::signal1<std::string> GetUpdateAddrNotify_;
            sigslot::signal1<int> PubResultNotify_;

            sigslot::signal1<int> DNDNotify_;
			sigslot::signal0<> VoiceRightChangeNotify_;
            sigslot::signal1<int> SipOkNotify_;
        };

        static const std::string SIGNINSIP_OK = "signin_sipok";
        static const std::string SIGNINFAIL_GETUPDATE = "getupdate"; // aa:AAresult
        static const std::string SIGNINFAIL_AA = "aa"; // aa:AAresult
        static const std::string SIGNINFAIL_CONTACT = "contact";
        static const std::string SIGNINFAIL_SIP = "sip";
        static const std::string SIGNINFAIL_SIP_408 = "sip408";
        static const std::string SIGNINFAIL_SIP_KICKOUT = "sipkickout";
        static const std::string SIGNINFAIL_SIP_PAUSEOFFLINE = "pauseoffline";
        static const std::string SIGNINFAIL_PROFILE = "profile";
        static const std::string SIGNINFAIL_HEARTBEAT = "heartbeat_timeout";

        static const std::string SIGNIN_NOK = "signin";
        static const std::string SIGNOUT_OK = "signout";
        static const std::string SIGNOUT_FAILED = "signoutfailed";

        static const std::string SIGNINFAIL_NOIP = "noip";
        static const std::string SIGNINFAIL_HASIP = "hasip";

    }
}

#ifndef _UC_SDK_H_
#define _UC_SDK_H_


const int STRING_LENGTH = 100;//所有对外字符串固定长度

const char ERROR_PWD[STRING_LENGTH]			= "error pwd";			//密码不正确
const char EMPTY_PWD[STRING_LENGTH]			= "empty pwd";			//密码为空
const char ACC_NOT_EXISTED[STRING_LENGTH]	= "account not existed";//账号不存在
const char ACC_LOCKED[STRING_LENGTH]		= "locked";				//账号已锁定
const char ACC_ERROR[STRING_LENGTH]			= "account error";		//账号错误
const char NEED_CHANGEPWD[STRING_LENGTH]	= "need change pwd";	//需要更换密码
const char TIME_OUT[STRING_LENGTH]			= "timeout";			//超时
const char NEED_NEW_VERSION[STRING_LENGTH]	= "need new version";	//需要下载新版本才允许登录
const char NEED_ACTIVE[STRING_LENGTH]		= "need active";		//用户未激活
const char NORMAL_ERROR[STRING_LENGTH]		= "normal error";		//登陆一般失败
const char ACC_KICKED[STRING_LENGTH]		= "sipkickout";			//用户被踢
const char LOGOUT_OK[STRING_LENGTH]			= "log out ok";			//用户成功注销

// 对外接口返回码
enum EM_UCServiceRetvCode
{
	UC_SDK_Success				=	0,			//成功
	UC_SDK_InvalidPara			=	1,			//不合法的参数
	UC_SDK_Failed				=	2,			//失败
	UC_SDK_NotInit				=	3,			//未初始化
	UC_SDK_NullPtr				=	4,			//空指针
	UC_SDK_FindUriErr			=	5,			//查找用户uri错误
	UC_SDK_NotHaveCallTarget	=	6,			//没有呼叫对象
	UC_SDK_InTempGroupNow		=	7,			//已经在TempGroup内
	UC_SDK_NotFound				=	8,			//没有找到
	UC_SDK_NoRight				=	9,			//没有权限
	UC_SDK_NotLogin				=	10			//未成功登录
};

//登录结果通知类型，只有1和3使用
enum EM_SignInState
{
	UC__SignedFailed		=	1,
	UC__SignedIn			=	3
};

//状态类型
enum EM_StatusType
{
	UC_Offline		=	0,	//离线
	UC_Online		=	1,	//在线
	UC_Hide			=	2,	//隐身
	UC_Busy			=	3,	//忙碌
	UC_Leave		=	4,	//忙碌
	UC_NoDisturb	=	5	//免打扰
};

//成员类型
enum EM_MemberType
{
	UC_ACCOUNT	=	0,	//UC账户
	UC_IPPHONE	=	1	//IPPHONE
};

//话机联动类型
enum EM_PhoneJointType
{
	PC_Device		=0,	//PC作为通讯设备
	IPPhone_Device	=1	//ip话机作为通讯设备
};
//话机联动通知状态
enum EM_PhoneJointStatusType
{
	STATUS_START_SUCC    = 0, //开启联动成功
	STATUS_START_FAILED  = 1, //开启联动失败
	STATUS_STOP_SUCC     = 2, //取消联动成功
	STATUS_STOP_FAILED   = 3, //取消联动失败
	STATUS_ONLINE        = 4, //IPPhone在线
	STATUS_OFFLINE       = 5, //IPPhone离线
	STATUS_OFFHOOK       = 6  //IPPhone摘机
};

//打开页面的类型
enum EM_PortalType
{
	SelfMgr_Portal			=	0,	//个人管理页面
	BookConf_Portal			=	1	//预定会议页面
};

//主席操作权限
enum EM_ConvnerOperateType
{
	EndCallMember			=	0,	//结束某成员的通话
	ReInviteMember			=	1,	//重新呼叫某成员
	MuteMember				=	2,	//对某成员静音
	UnMuteMember			=	3	//对某成员取消静音
};

//会议中的成员状态
enum EM_MemStatusInCall
{
	CONF_MEM_INVITING		=	0,	//正在呼叫某成员
	CONF_MEM_HANGUP			=	1,	//某成员挂断
	CONF_MEM_INCONF			=	2,	//正在会议中
	CONF_MEM_QUIT			=	3,	//成员离开
	CONF_MEM_MUTE			=	4,	//成员被静音
	CONF_MEM_UnMute			=	5,	//成员被取消静音
	CONF_MEM_SPK			=	6,	//成员在说话
	CONF_MEM_ADD			=	7,	//新增成员
	CONF_MEM_DEL			=	8	//成员被删除
};

//视频Call状态
enum EM_VideoCallStatus
{
	CALL_VIDEO_REQ			=	0,	//视频呼叫请求
	CALL_VIDEO_CONNECTED	=	1,	//视频呼叫接通
	CALL_VIDEO_CLOSE		=	2	//视频呼叫未接通或者关闭
};

//单人呼叫历史记录类型
enum EM_CallHistoryType
{	
	HISTORY_CALL_MISSED		=	0,	//未接电话
	HISTORY_CALL_ANSWERED	=	1,	//已接通话
	HISTORY_CALL_DIALED		=	2,	//已拨通话
	HISTORY_CALL_ALL		=	3	//全部通话
};



// 对外提供的数据结构和回调函数接口
typedef struct
{
	char id_[STRING_LENGTH];				//!< id
	char uri_[STRING_LENGTH];				//!< sip uri
	char fullUri_[STRING_LENGTH];			//!< sip full uri
	char ucAcc_[STRING_LENGTH]; //!< account
	char staffNo_[STRING_LENGTH]; //!< staff no
	char name_[STRING_LENGTH]; //!< name
	char nickName_[STRING_LENGTH];//!< nick name
	char qpinyin_[STRING_LENGTH];//!< name fullpinyin
	char spinyin_[STRING_LENGTH];//!< name simplepinyin
	char homePhone_[STRING_LENGTH];//!< home phone
	char officePhone_[STRING_LENGTH];//!< office phone
	char officePhone2_[STRING_LENGTH];//!< office phone2
	char mobile_[STRING_LENGTH];//!< mobile phone
	char otherPhone_[STRING_LENGTH];//!< other phone
	char otherPhone2_[STRING_LENGTH];//!< other phone2
	char address_[STRING_LENGTH];//!< address
	char email_[STRING_LENGTH];//!< email
	char duty_[STRING_LENGTH];//!< duty
	char fax_[STRING_LENGTH];//!< fax
	char gender_[STRING_LENGTH];//!< gender
	char corpName_[STRING_LENGTH];//!< enterprise name
	char deptName_[STRING_LENGTH];//!< dept name
	char webSite_[STRING_LENGTH];//!< web site
	char desc_[STRING_LENGTH];//!< description
	char zip_[STRING_LENGTH];//!< zip
	char signature_[STRING_LENGTH]; //!< signature
	char imageID_[STRING_LENGTH];//!< head image id
	char position_[STRING_LENGTH];//!< 
	char location_[STRING_LENGTH];//!< 
	char tzone_[STRING_LENGTH];//!< contact time zone
	char avtool_[STRING_LENGTH];//!< avaliable device (mic/speaker/camera)
	char device_[STRING_LENGTH];//!< contact device type
	char terminalType_[STRING_LENGTH];//!< contact type
	char ipphone1_[STRING_LENGTH];//!< bind ipphone1 number
	char ipphone2_[STRING_LENGTH];//!< bind ipphone2 number
	int flow_;//!< mark contact status in the group(just used for fixedgroup)
} STContact;

typedef struct 
{   
	int chatType;
	char origin[STRING_LENGTH];
	char target[STRING_LENGTH];
	char content[300];
	char rcv_time[STRING_LENGTH];
	char name[STRING_LENGTH];
	char msgid[STRING_LENGTH];
} STImMsgItem;

typedef struct
{
	int iTotal;
	STContact stContact[1];
} STContactList;

typedef struct   
{
	char callerUri_[STRING_LENGTH];			//对方号码
	char AVSessionId_[STRING_LENGTH];  
	char reason_[STRING_LENGTH];			//错误码
} STMsgAVSessionClosedParam;

typedef struct
{
	char ucAcc[STRING_LENGTH];
	int isvideo_;				//1表示视频， 0表示不是视频
	int callMode;				//1表示IPPHone，0表示软终端呼出
	int AccountType;			//1表示IPPhone，0表示UcAccount
} STAudioVideoParam;

typedef struct   
{
	int left;       
	int top;  
	int width;
	int height;
	int hWnd;						//窗口句柄
} STVideoWindow;

typedef struct  
{
	char name[STRING_LENGTH];       /*!< device name*/
	char deviceId[STRING_LENGTH];   /*!< device id*/
	int index;						/*!< device no*/
	int iscertified;				/*!< if device is verified by Huawei Corp.*/
	int isactive;					/*!< if device is active*/
	int type;						/*!< 设备类型*/
} STDeviceParam;

typedef struct
{
	int iTotal;						//总共数目
	int iFrom;						//开始索引
	int iTo;						//结束索引
	STDeviceParam deviceList[1];
} STDeviceListParam;

//会议参数
typedef struct
{
	char ucAcc[STRING_LENGTH];
	int memStatus;			//参考EM_MemStatusInCall的定义
	int memType;			//参考EM_MemberType的定义
} STConfParam;

//呼叫参数
typedef struct
{
	char ucAcc[STRING_LENGTH];
	int callStatus;			//参考EM_VideoCallStatus的定义
}STVideoCallParam;		

//历史记录
typedef struct
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}STTime;

typedef struct
{
	char CallNum[STRING_LENGTH];	//绑定号
	char CallName[STRING_LENGTH];	//名称
	char ucAccount[STRING_LENGTH];	//UC账户
	STTime startTime;				//开始时间
	int duration;					// -1 :表示未接来电
	int callType;					//calltype
	int recordID;					//recordID
}STCallHistroyItem;

typedef struct
{
	int iTotal;
	int iFrom;
	int iTo;
	STCallHistroyItem stCallHistory[1];
}STCallHistroyData;

typedef struct
{
	char convID[STRING_LENGTH];				//会议ID
	char compereName[STRING_LENGTH];		//主持人名称
	char compereAccount[STRING_LENGTH];		//主持人账户
	STTime startTime;						//开始时间
	int duration;							// -1 :表示未接来电
	int partcipantNum;						//参与者个数
}STConvHistroyItem;

typedef struct
{
	int iTotal;
	int iFrom;
	int iTo;
	STConvHistroyItem stConvHistory[1];
}STConvHistroyData;

typedef struct
{
	char partName[STRING_LENGTH];//与会者名称
	char partAccount[STRING_LENGTH];//与会者账户
}STConfPartItem;

typedef struct
{
	int partNum;//与会者个数
	STConfPartItem stConfPart[1];
}STConfPartData; 

// 回调函数指针定义
typedef void (CALLBACK *ClientSignInNotifyCB)(int _state,const char* _reason);	//_state的取值参考枚举类型EM_SignInState
typedef void (CALLBACK *StatusChangedCB)(int _state, const STContact& _contact);//_state的取值参考枚举类型EM_StatusType
typedef void (CALLBACK *AVSessionClosedCB)(const STMsgAVSessionClosedParam& _avParam);
typedef void (CALLBACK *AVSessionConnectedCB)(void);
typedef void (CALLBACK *AVSessAddedCB)(const STAudioVideoParam& _avParam);
typedef void (CALLBACK *ConfMemberEventCB)(const STConfParam& _avParam);
typedef void (CALLBACK *VideoCallEventCB)(const STVideoCallParam& _callParam);
typedef void (CALLBACK *PhoneJointEventCB)(int _state);							//_state的取值参考枚举类型EM_PhoneJointStatusType
#endif




#ifndef _UC_SDK_H_
#define _UC_SDK_H_


const int STRING_LENGTH = 100;//���ж����ַ����̶�����

const char ERROR_PWD[STRING_LENGTH]			= "error pwd";			//���벻��ȷ
const char EMPTY_PWD[STRING_LENGTH]			= "empty pwd";			//����Ϊ��
const char ACC_NOT_EXISTED[STRING_LENGTH]	= "account not existed";//�˺Ų�����
const char ACC_LOCKED[STRING_LENGTH]		= "locked";				//�˺�������
const char ACC_ERROR[STRING_LENGTH]			= "account error";		//�˺Ŵ���
const char NEED_CHANGEPWD[STRING_LENGTH]	= "need change pwd";	//��Ҫ��������
const char TIME_OUT[STRING_LENGTH]			= "timeout";			//��ʱ
const char NEED_NEW_VERSION[STRING_LENGTH]	= "need new version";	//��Ҫ�����°汾�������¼
const char NEED_ACTIVE[STRING_LENGTH]		= "need active";		//�û�δ����
const char NORMAL_ERROR[STRING_LENGTH]		= "normal error";		//��½һ��ʧ��
const char ACC_KICKED[STRING_LENGTH]		= "sipkickout";			//�û�����
const char LOGOUT_OK[STRING_LENGTH]			= "log out ok";			//�û��ɹ�ע��

// ����ӿڷ�����
enum EM_UCServiceRetvCode
{
	UC_SDK_Success				=	0,			//�ɹ�
	UC_SDK_InvalidPara			=	1,			//���Ϸ��Ĳ���
	UC_SDK_Failed				=	2,			//ʧ��
	UC_SDK_NotInit				=	3,			//δ��ʼ��
	UC_SDK_NullPtr				=	4,			//��ָ��
	UC_SDK_FindUriErr			=	5,			//�����û�uri����
	UC_SDK_NotHaveCallTarget	=	6,			//û�к��ж���
	UC_SDK_InTempGroupNow		=	7,			//�Ѿ���TempGroup��
	UC_SDK_NotFound				=	8,			//û���ҵ�
	UC_SDK_NoRight				=	9,			//û��Ȩ��
	UC_SDK_NotLogin				=	10			//δ�ɹ���¼
};

//��¼���֪ͨ���ͣ�ֻ��1��3ʹ��
enum EM_SignInState
{
	UC__SignedFailed		=	1,
	UC__SignedIn			=	3
};

//״̬����
enum EM_StatusType
{
	UC_Offline		=	0,	//����
	UC_Online		=	1,	//����
	UC_Hide			=	2,	//����
	UC_Busy			=	3,	//æµ
	UC_Leave		=	4,	//æµ
	UC_NoDisturb	=	5	//�����
};

//��Ա����
enum EM_MemberType
{
	UC_ACCOUNT	=	0,	//UC�˻�
	UC_IPPHONE	=	1	//IPPHONE
};

//������������
enum EM_PhoneJointType
{
	PC_Device		=0,	//PC��ΪͨѶ�豸
	IPPhone_Device	=1	//ip������ΪͨѶ�豸
};
//��������֪ͨ״̬
enum EM_PhoneJointStatusType
{
	STATUS_START_SUCC    = 0, //���������ɹ�
	STATUS_START_FAILED  = 1, //��������ʧ��
	STATUS_STOP_SUCC     = 2, //ȡ�������ɹ�
	STATUS_STOP_FAILED   = 3, //ȡ������ʧ��
	STATUS_ONLINE        = 4, //IPPhone����
	STATUS_OFFLINE       = 5, //IPPhone����
	STATUS_OFFHOOK       = 6  //IPPhoneժ��
};

//��ҳ�������
enum EM_PortalType
{
	SelfMgr_Portal			=	0,	//���˹���ҳ��
	BookConf_Portal			=	1	//Ԥ������ҳ��
};

//��ϯ����Ȩ��
enum EM_ConvnerOperateType
{
	EndCallMember			=	0,	//����ĳ��Ա��ͨ��
	ReInviteMember			=	1,	//���º���ĳ��Ա
	MuteMember				=	2,	//��ĳ��Ա����
	UnMuteMember			=	3	//��ĳ��Աȡ������
};

//�����еĳ�Ա״̬
enum EM_MemStatusInCall
{
	CONF_MEM_INVITING		=	0,	//���ں���ĳ��Ա
	CONF_MEM_HANGUP			=	1,	//ĳ��Ա�Ҷ�
	CONF_MEM_INCONF			=	2,	//���ڻ�����
	CONF_MEM_QUIT			=	3,	//��Ա�뿪
	CONF_MEM_MUTE			=	4,	//��Ա������
	CONF_MEM_UnMute			=	5,	//��Ա��ȡ������
	CONF_MEM_SPK			=	6,	//��Ա��˵��
	CONF_MEM_ADD			=	7,	//������Ա
	CONF_MEM_DEL			=	8	//��Ա��ɾ��
};

//��ƵCall״̬
enum EM_VideoCallStatus
{
	CALL_VIDEO_REQ			=	0,	//��Ƶ��������
	CALL_VIDEO_CONNECTED	=	1,	//��Ƶ���н�ͨ
	CALL_VIDEO_CLOSE		=	2	//��Ƶ����δ��ͨ���߹ر�
};

//���˺�����ʷ��¼����
enum EM_CallHistoryType
{	
	HISTORY_CALL_MISSED		=	0,	//δ�ӵ绰
	HISTORY_CALL_ANSWERED	=	1,	//�ѽ�ͨ��
	HISTORY_CALL_DIALED		=	2,	//�Ѳ�ͨ��
	HISTORY_CALL_ALL		=	3	//ȫ��ͨ��
};



// �����ṩ�����ݽṹ�ͻص������ӿ�
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
	char callerUri_[STRING_LENGTH];			//�Է�����
	char AVSessionId_[STRING_LENGTH];  
	char reason_[STRING_LENGTH];			//������
} STMsgAVSessionClosedParam;

typedef struct
{
	char ucAcc[STRING_LENGTH];
	int isvideo_;				//1��ʾ��Ƶ�� 0��ʾ������Ƶ
	int callMode;				//1��ʾIPPHone��0��ʾ���ն˺���
	int AccountType;			//1��ʾIPPhone��0��ʾUcAccount
} STAudioVideoParam;

typedef struct   
{
	int left;       
	int top;  
	int width;
	int height;
	int hWnd;						//���ھ��
} STVideoWindow;

typedef struct  
{
	char name[STRING_LENGTH];       /*!< device name*/
	char deviceId[STRING_LENGTH];   /*!< device id*/
	int index;						/*!< device no*/
	int iscertified;				/*!< if device is verified by Huawei Corp.*/
	int isactive;					/*!< if device is active*/
	int type;						/*!< �豸����*/
} STDeviceParam;

typedef struct
{
	int iTotal;						//�ܹ���Ŀ
	int iFrom;						//��ʼ����
	int iTo;						//��������
	STDeviceParam deviceList[1];
} STDeviceListParam;

//�������
typedef struct
{
	char ucAcc[STRING_LENGTH];
	int memStatus;			//�ο�EM_MemStatusInCall�Ķ���
	int memType;			//�ο�EM_MemberType�Ķ���
} STConfParam;

//���в���
typedef struct
{
	char ucAcc[STRING_LENGTH];
	int callStatus;			//�ο�EM_VideoCallStatus�Ķ���
}STVideoCallParam;		

//��ʷ��¼
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
	char CallNum[STRING_LENGTH];	//�󶨺�
	char CallName[STRING_LENGTH];	//����
	char ucAccount[STRING_LENGTH];	//UC�˻�
	STTime startTime;				//��ʼʱ��
	int duration;					// -1 :��ʾδ������
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
	char convID[STRING_LENGTH];				//����ID
	char compereName[STRING_LENGTH];		//����������
	char compereAccount[STRING_LENGTH];		//�������˻�
	STTime startTime;						//��ʼʱ��
	int duration;							// -1 :��ʾδ������
	int partcipantNum;						//�����߸���
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
	char partName[STRING_LENGTH];//���������
	char partAccount[STRING_LENGTH];//������˻�
}STConfPartItem;

typedef struct
{
	int partNum;//����߸���
	STConfPartItem stConfPart[1];
}STConfPartData; 

// �ص�����ָ�붨��
typedef void (CALLBACK *ClientSignInNotifyCB)(int _state,const char* _reason);	//_state��ȡֵ�ο�ö������EM_SignInState
typedef void (CALLBACK *StatusChangedCB)(int _state, const STContact& _contact);//_state��ȡֵ�ο�ö������EM_StatusType
typedef void (CALLBACK *AVSessionClosedCB)(const STMsgAVSessionClosedParam& _avParam);
typedef void (CALLBACK *AVSessionConnectedCB)(void);
typedef void (CALLBACK *AVSessAddedCB)(const STAudioVideoParam& _avParam);
typedef void (CALLBACK *ConfMemberEventCB)(const STConfParam& _avParam);
typedef void (CALLBACK *VideoCallEventCB)(const STVideoCallParam& _callParam);
typedef void (CALLBACK *PhoneJointEventCB)(int _state);							//_state��ȡֵ�ο�ö������EM_PhoneJointStatusType
#endif




//lint -e1784
#ifndef _CESDK_UCSERVICE_H
#define _CESDK_UCSERVICE_H
#include "UCSDK.h"
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ESDK_UCSERVICE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ESDK_UCSERVICE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ESDK_UCSERVICE_EXPORTS
#define ESDK_UCSERVICE_API __declspec(dllexport)
#else
#define ESDK_UCSERVICE_API __declspec(dllimport)
#endif

#ifdef WIN32
#define __UC_SDK_CALL __stdcall
#else
#define __UC_SDK_CALL
#endif



#ifdef __cplusplus
extern "C"
{
#endif


	/**
	 *初始化
	 * 
	 *该函数用于初始化数据
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆前先初始化
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_Init(void);

	/**
	 *去初始化
	 * 
	 *该函数用于去初始化数据
	 *
	 *@return		0成功
	 *@return		非0失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnInit(void);

	/**
	 *登录
	 * 
	 *该函数用于使用账号和密码登陆
	 *
	 *@param[in]	account			账号
	 *@param[in]	pwd				密码
	 *@param[in]	serverUrl		登录地址，格式为10.10.10.10:8081
	 *@param[in]	langID			运行的语言，英文一般为1033，中文一般为2052
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆前先初始化
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SignInByPWD(const char* account, const char* pwd, const char* serverUrl,const char* langID);
	/**
	 *登出
	 * 
	 *该函数用于注销登陆
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SignOut(void);

	/**
	 *增加呼叫成员
	 * 
	 *该函数用于设置发起呼叫的目标用户
	 *
	 *@param[in]	memberType		成员类型，参考枚举类型EM_MemberType
	 *@param[in]	member			UC账号或者ipphone
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	当同时呼叫多个用户时，请重复调用多次，然后调用发起呼叫接口
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_AddCallMember(int memberType,const char* member);

	/**
	 *查询呼叫成员
	 * 
	 *该函数用于查询呼叫成员的账户
	 *	 
	 *@param[in]	phoneNum		号码，一串数字
	 *@param[out]	_UCAcc			UC成员账户名称
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	增加账户时，先查询此用户是否存在对应的UC账户
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetUCAccount(const char* phoneNum,char _UCAcc[STRING_LENGTH]);

	/**
	 *发起呼叫
	 * 
	 *该函数用于发起账户呼叫
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	呼叫前先增加呼叫成员
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MakeCall(void);

	/**
	 *通话保持
	 * 
	 *该函数用于通话保持
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_HoldCall(void);

	/**
	 *通话恢复
	 * 
	 *该函数用于通话恢复
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ResumeCall(void);

	/**
	 *呼叫前转
	 * 
	 *该函数用于呼叫前转
	 *
	 *@param[in]	iMemberType		成员类型，参考枚举类型EM_MemberType
	 *@param[in]	pMember			UC账号或者IPPhone号码
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ForwardCall(int iMemberType,const char* pMember);

	/**
	 *结束通话
	 * 
	 *该函数用于结束通话释放conversation，释放UC_SDK_InsertMember增加的成员
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	主动挂断通话时调用（对方挂断时会自动调用释放资源）
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_HangupCall(void);

	/**
	 *结束视频通话
	 * 
	 *该函数用于结束视频通话，保留语音通话
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	主动挂断视频通话时调用（）
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_HangupVideoCall(void);

	/**
	 *接听呼叫
	 * 
	 *该函数用于接听呼叫
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_AcceptCall(void);

	/**
	 *接听视频呼叫
	 * 
	 *该函数用于接听视频呼叫
	 *
	 *@param[in]	localHWnd		本地视频播放窗口的句柄
	 *@param[in]	localLeft		本地视频播放窗口的X坐标
	 *@param[in]	localTop		本地视频播放窗口的Y坐标
	 *@param[in]	localWidth		本地视频播放窗口的宽度
	 *@param[in]	localHeight		本地视频播放窗口的高度
	 *@param[in]	remoteHWnd		对方视频播放窗口的句柄
	 *@param[in]	remoteLeft		对方视频播放窗口的X坐标
	 *@param[in]	remoteTop		对方视频播放窗口的Y坐标
	 *@param[in]	remoteWidth		对方视频播放窗口的宽度
	 *@param[in]	remoteHeight	对方视频播放窗口的高度
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_AcceptVideoCall(
		int localHWnd, 	int localLeft, int localTop, int localWidth, int localHeight,
		int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight);

	/**
	 *拒绝呼叫
	 * 
	 *该函数用于拒绝呼叫
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_RejectCall(void);

	/**
	 *拒绝呼叫
	 * 
	 *该函数用于拒绝视频呼叫
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/

	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_RejectVideoCall(void);

	/**
	 *二次拨号
	 * 
	 *该函数用于二次拨号接口，支持“0 1 2 3 4 5 6 7 8 9 \* \#”等12个字符
	 *
	 *@param[in]	tone	拨号字符
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SendDTMF(char tone);

	/**
	 *麦克风静音
	 * 
	 *该函数用于麦克风静音
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MuteMic(void);

	/**
	 *麦克风取消静音
	 * 
	 *该函数用于麦克风取消静音
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnMuteMic(void);

	/**
	 *获取麦克风音量
	 * 
	 *该函数用于获取麦克风音量
	 *
	 *@param[out]	level		麦克风音量
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetMicLevel(int& level);

	/**
	 *设置麦克风音量
	 * 
	 *该函数用于设置麦克风音量
	 *
	 *@param[in]	level		麦克风音量
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetMicLevel(int level);

	/**
	 *扬声器静音
	 * 
	 *该函数用于扬声器静音
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MuteSpker(void);

	/**
	 *扬声器取消静音
	 * 
	 *该函数用于扬声器取消静音
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnMuteSpker(void);

	/**
	 *获取扬声器音量
	 * 
	 *该函数用于获取麦克风音量
	 *
	 *@param[out]	level		扬声器音量
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetSpkerLevel(int& level);

	/**
	 *设置扬声器音量
	 * 
	 *该函数用于设置扬声器音量
	 *
	 *@param[in]	level		扬声器音量
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetSpkerLevel(int level);

	/**
	 *发起视频呼叫或者将当前语音呼叫升级为视频呼叫
	 * 
	 *该函数用于发起视频呼叫或者将当前语音呼叫升级为视频呼叫
	 *
	 *@param[in]	localHWnd		本地视频播放窗口的句柄
	 *@param[in]	localLeft		本地视频播放窗口的X坐标
	 *@param[in]	localTop		本地视频播放窗口的Y坐标
	 *@param[in]	localWidth		本地视频播放窗口的宽度
	 *@param[in]	localHeight		本地视频播放窗口的高度
	 *@param[in]	remoteHWnd		对方视频播放窗口的句柄
	 *@param[in]	remoteLeft		对方视频播放窗口的X坐标
	 *@param[in]	remoteTop		对方视频播放窗口的Y坐标
	 *@param[in]	remoteWidth		对方视频播放窗口的宽度
	 *@param[in]	remoteHeight	对方视频播放窗口的高度
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	句柄的值必须正确
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MakeVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
															int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight);


	/**
	 *语音会议中邀请成员
	 * 
	 *该函数用于语音会议中邀请成员
	 *
	 *@param[in]	memberType_		账户类型，参考枚举类型EM_MemberType
	 *@param[in]	pAccount		账号
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InviteMemberInCall(int memberType_,const char* pAccount);

	/**
	 *语音会议中删除成员
	 * 
	 *该函数用于语音会议中删除成员
	 *
	 *@param[in]	memberType_		账号类型，参考枚举类型EM_MemberType
	 *@param[in]	pAccount		账号
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_DeleteMemberInCall(int memberType_,const char* pAccount);

	/**
	 *包括语音会议中断开某成员的语音，语音会议中重新呼叫某成员，语音会议中对某成员静音，对某成员取消静音4种。
	 * 
	 *该函数用于包括语音会议中断开某成员的语音，语音会议中重新呼叫某成员，语音会议中对某成员静音，对某成员取消静音4种。
	 *
	 *@param[in]	operateType		操作类型，参考枚举类型EM_ConvnerOperateType
	 *@param[in]	memberType_		账号类型，参考枚举类型EM_MemberType
	 *@param[in]	pAccount		UC账号
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ModifyMemberStatusInCall(int operateType,int memberType_,const char* pAccount);

	/**
	 *获取麦克风设备列表
	 * 
	 *该函数用于获取麦克风设备列表
	 *
	 *@param[in] _fromIndex		开始索引
	 *@param[in] _toIndex		结束索引
	 *@param[in] _size			结构体大小
	 *@param[out] devList		设备列表
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	[_fromIndex, _toIndex], 包含_fromIndex, _toIndex
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetMicDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList);

	/**
	 *获取扬声器设备列表
	 * 
	 *该函数用于获取扬声器设备列表
	 *
	 *@param[in] _fromIndex		开始索引
	 *@param[in] _toIndex		结束索引
	 *@param[in] _size			结构体大小
	 *@param[out] devList		设备列表
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	[_fromIndex, _toIndex], 包含_fromIndex, _toIndex
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetSpeakerDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList);

	/**
	 *获取视频设备列表
	 * 
	 *该函数用于获取视频设备列表
	 *
	 *@param[in] _fromIndex		开始索引
	 *@param[in] _toIndex		结束索引
	 *@param[in] _size			结构体大小
	 *@param[out] devList		设备列表
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	[_fromIndex, _toIndex], 包含_fromIndex, _toIndex
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetVideoDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList);

	/**
	 *获取当前麦克风设备
	 * 
	 *该函数用于获取当前麦克风设备
	 *
	 *@param[out] device		当前麦克风设备
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetCurrentMicDev(STDeviceParam* device);

	/**
	 *获取当前扬声器设备
	 * 
	 *该函数用于获取当前扬声器设备
	 *
	 *@param[out] device		当前扬声器设备
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetCurrentSpeakerDev(STDeviceParam* device);

	/**
	 *获取当前视频设备
	 * 
	 *该函数用于获取当前视频设备
	 *
	 *@param[out] device		当前视频设备
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetCurrentVideoDev(STDeviceParam* device);

	/**
	 *设置当前麦克风设备
	 * 
	 *该函数用于设置当前麦克风设备
	 *
	 *@param[in] index			设备索引
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCurrentMicDev(int index);

	/**
	 *设置当前扬声器设备
	 * 
	 *该函数用于设置当前扬声器设备
	 *
	 *@param[in] index			设备索引
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCurrentSpeakerDev(int index);

	/**
	 *设置当前视频设备
	 * 
	 *该函数用于设置当前视频设备
	 *
	 *@param[in] index			设备索引
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	暂无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCurrentVideoDev(int index);

	/**
	 *设置登录回调
	 * 
	 *该函数用于设置登录回调函数
	 *
	 *@param[in]	loginEventCB_	登陆回调函数指针
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆前必须调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetLoginEventCB(ClientSignInNotifyCB loginEventCB_);

	/**
	 *设置状态回调
	 * 
	 *该函数用于设置状态回调函数
	 *
	 *@param[in]	statusChangedCallBack	状态回调函数指针
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆前必须调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetStatusChangedCB(StatusChangedCB statusChangedCallBack);

	/**
	 *设置呼叫事件回调
	 * 
	 *该函数用于设置呼叫事件回调函数
	 *
	 *@param[in]	aVSessionClosedCallBack		通话结束事件回调函数指针
	 *@param[in]	aVSessionConnectedCallBack	通话连接事件回调函数指针
	 *@param[in]	aVSessAddedCallBack			收到呼叫事件回调函数指针
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆后立即调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCallEventCallBack(AVSessionClosedCB aVSessionClosedCallBack,
																	AVSessionConnectedCB aVSessionConnectedCallBack,
																	AVSessAddedCB aVSessAddedCallBack);

	/**
	 *设置视频呼叫事件回调
	 * 
	 *该函数用于设置视频呼叫事件回调函数
	 *
	 *@param[in]	callEventCallBack		视频通话事件回调函数指针
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆后立即调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetVideoCallEventCallBack(VideoCallEventCB callEventCallBack);

	/**
	 *设置会议中事件回调
	 * 
	 *该函数用于设置会议中成员状态变化事件回调
	 *
	 *@param[in] confMemEventCallBack
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	送到连接成功函数返回后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetConfMemEventCallBack(ConfMemberEventCB confMemEventCallBack);

	/**
	 *查询单人呼叫历史记录
	 * 
	 *该函数查询单人呼叫历史记录
	 *
	 *@param[in] _callType		历史记录类型，参考枚举类型EM_CallHistoryType
	 *@param[in] _fromIndex		开始序列号，从0开始
	 *@param[in] _toIndex		结束序列号，不能小于_fromIndex
	 *@param[out] _result		查询结果存放结构体
	 *@param[out] _size			指针_result所指内存的大小
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	送到连接成功函数返回后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_QueryCallHistory(int _callType, int _fromIndex,int _toIndex,STCallHistroyData* _result,int _size);


	/**
	 *清除单人呼叫历史记录
	 * 
	 *该函数清除单人呼叫历史记录
	 *
	 *@param[in] _callType	历史记录类型，参考枚举类型EM_CallHistoryType
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	送到连接成功函数返回后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ClearCallHistroy(int _callType);

	/**
	 *插入呼叫历史记录
	 * 
	 *该函数用于插入呼叫历史记录
	 *
	 *@param[in] _callType	历史记录类型，参考枚举类型EM_CallHistoryType
	 *@param[in] _account	账户
	 *@param[in] _name		姓名
	 *@param[in] _duration	呼叫持续时间单位为秒，未接通的呼叫要求值为-1，
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InsertCallHistory(int _callType,const char* _account,const char* _name,int _duration);


	/**
	 *查询会议历史记录
	 * 
	 *该函数会议历史记录
	 *
	 *@param[in] _fromIndex		开始序列
	 *@param[in] _toIndex		结束序列
	 *@param[out] _result		返回的会议历史记录结果
	 *@param[out] _size			指针_result所指内存的大小
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_QueryConvHistory(int _fromIndex,int _toIndex,STConvHistroyData* _result,int _size);

	/**
	 *查询一条会议历史记录的参与者
	 * 
	 *该函数用于查询一条会议历史记录的参与者
	 *
	 *@param[in] _convID		会议历史记录ID，由UC_SDK_QueryConvHistory接口查询出来
	 *@param[in] _fromIndex		开始序列
	 *@param[in] _toIndex		结束序列
	 *@param[out] _result		返回的结果存放地址
	 *@param[out] _size			指针_result所指内存的大小
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	调用UC_SDK_QueryConvHistory后，会获取到_convID，然后可以调用UC_SDK_QueryHisConvPartByID
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_QueryHisConvPartByID(const char* _convID,int _fromIndex,int _toIndex,STConfPartData* _result,int _size);


	/**
	 *清除会议历史记录
	 * 
	 *该函数清除会议历史记录
	 *
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ClearConvHistroy(void);

	/**
	 *插入会议历史记录
	 * 
	 *该函数用于插入会议历史记录
	 *
	 *@param[in] _leaderAccount	主持人账户
	 *@param[in] _leaderName	主持人姓名	
	 *@param[in] _duration		会议持续时间
	 *@param[out] _historyID	会议历史记录ID
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InsertConvHistory(const char* _leaderAccount,const char* _leaderName,int _duration,char _historyID[STRING_LENGTH]);

	/**
	 *插入会议历史记录的与会人
	 * 
	 *该函数用于插入会议历史记录的与会人
	 *
	 *@param[in] _partAccount	与会者账户
	 *@param[in] _partName		与会者姓名
	 *@param[in] _historyConvID	会议历史记录ID，调用UC_SDK_InsertConvHistory生成
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	调用UC_SDK_InsertConvHistory后，获取到_historyConvID，然后可以调用UC_SDK_InsertConvHistoryPart插入成员
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InsertConvHistoryPart(const char* _historyConvID,const char* _partAccount,const char* _partName);

	/**
	 *删除一条呼叫记录
	 * 
	 *该函数用于删除一条呼叫记录
	 *
	 *@param[in] _iRcdID			删除记录索引ID,参考结构体类型STCallHistroyItem
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_DeleteCallHistory(int _iRcdID);

	/**
	 *删除一条会议记录
	 * 
	 *该函数用于删除一条会议记录
	 *
	 *@param[in] _pConvID			删除会议历史记录的ID
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_DeleteConvHistory(const char* _pConvID);

	/**
	 *获取话机联动设备类型
	 * 
	 *该函数用于获取话机联动设备类型
	 *
	 *@param[out] _iDevType			联动设备类型，参考枚举类型EM_PhoneJointType
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetPhoneJointDevType(int& _iDevType);

	/**
	 *设置话机联动设备类型
	 * 
	 *该函数用于设置话机联动设备类型
	 *
	 *@param[in] _iDevType			联动设备类型，参考枚举类型EM_PhoneJointType
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	无
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetPhoneJointDevType(int _iDevType);

	/**
	 *设置话机联动事件回调
	 * 
	 *该函数用于设置话机联动事件回调函数
	 *
	 *@param[in]	pjEventCallBack		话机联动事件回调函数指针
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆后立即调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetPhoneJointEventCallBack(PhoneJointEventCB pjEventCallBack);

	/**
	 *单点登录个人管理平台或者预约会议页面
	 * 
	 *该函数用于单点登录个人管理平台或者预约会议页面
	 *
	 *@param[in]	_type		打开页面的类型，参考枚举类型EM_PortalType
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆后立即调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_OpenPortal(int _type);

	/**
	 *发布状态
	 * 
	 *该函数用于发布个人状态
	 *
	 *@param[in]	_Status		状态	 
	 *@param[in]	_Desc		状态描述
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登陆后立即调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_PubSelfStatus(int _Status,const char* _Desc);

	/**
	 *获取联系人状态
	 * 
	 *该函数用于获取联系人个人状态
	 *
	 *@param[in]	_AccountType 联系人账户类型	 
	 *@param[in]	_Account	联系人账户	 
	 *@param[out]	_Status		状态
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登录成功后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetContactStatus(int _AccountType,const char* _Account,int& _Status);

	/**
	 *获取联系人信息
	 * 
	 *该函数用于获取联系人信息
	 *
	 *@param[in]	_Account	联系人账户	 
	 *@param[out]	_pContactInfo		联系人的信息
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登录成功后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetContactInfo(const char* _Account,STContact* _pContactInfo);

	/**
	 *订阅某个联系人状态
	 * 
	 *该函数用于订阅某个联系人状态
	 *
	 *@param[in]	_Account	联系人账户	 
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登录成功后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SubscribeStatus(const char* _Account);

	/**
	 *取消订阅某个联系人状态
	 * 
	 *该函数用于取消订阅某个联系人状态
	 *
	 *@param[in]	_Account	联系人账户	 
	 *@return		0	成功
	 *@return		非0	失败（参考错误返回码）
	 *@attention	登录成功后调用
	 *@par			无
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnSubscribeStatus(const char* _Account);


#ifdef __cplusplus
}
#endif 


#endif



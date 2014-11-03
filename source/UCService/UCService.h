//lint -e1784
#ifndef _CESDK_UCSERVICE_H
#define _CESDK_UCSERVICE_H
#include "UCSDK.h"
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ESDK_UCSERVICE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ESDK_UCSERVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
	 *��ʼ��
	 * 
	 *�ú������ڳ�ʼ������
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½ǰ�ȳ�ʼ��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_Init(void);

	/**
	 *ȥ��ʼ��
	 * 
	 *�ú�������ȥ��ʼ������
	 *
	 *@return		0�ɹ�
	 *@return		��0ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnInit(void);

	/**
	 *��¼
	 * 
	 *�ú�������ʹ���˺ź������½
	 *
	 *@param[in]	account			�˺�
	 *@param[in]	pwd				����
	 *@param[in]	serverUrl		��¼��ַ����ʽΪ10.10.10.10:8081
	 *@param[in]	langID			���е����ԣ�Ӣ��һ��Ϊ1033������һ��Ϊ2052
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½ǰ�ȳ�ʼ��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SignInByPWD(const char* account, const char* pwd, const char* serverUrl,const char* langID);
	/**
	 *�ǳ�
	 * 
	 *�ú�������ע����½
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SignOut(void);

	/**
	 *���Ӻ��г�Ա
	 * 
	 *�ú����������÷�����е�Ŀ���û�
	 *
	 *@param[in]	memberType		��Ա���ͣ��ο�ö������EM_MemberType
	 *@param[in]	member			UC�˺Ż���ipphone
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��ͬʱ���ж���û�ʱ�����ظ����ö�Σ�Ȼ����÷�����нӿ�
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_AddCallMember(int memberType,const char* member);

	/**
	 *��ѯ���г�Ա
	 * 
	 *�ú������ڲ�ѯ���г�Ա���˻�
	 *	 
	 *@param[in]	phoneNum		���룬һ������
	 *@param[out]	_UCAcc			UC��Ա�˻�����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�����˻�ʱ���Ȳ�ѯ���û��Ƿ���ڶ�Ӧ��UC�˻�
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetUCAccount(const char* phoneNum,char _UCAcc[STRING_LENGTH]);

	/**
	 *�������
	 * 
	 *�ú������ڷ����˻�����
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����ǰ�����Ӻ��г�Ա
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MakeCall(void);

	/**
	 *ͨ������
	 * 
	 *�ú�������ͨ������
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_HoldCall(void);

	/**
	 *ͨ���ָ�
	 * 
	 *�ú�������ͨ���ָ�
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ResumeCall(void);

	/**
	 *����ǰת
	 * 
	 *�ú������ں���ǰת
	 *
	 *@param[in]	iMemberType		��Ա���ͣ��ο�ö������EM_MemberType
	 *@param[in]	pMember			UC�˺Ż���IPPhone����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ForwardCall(int iMemberType,const char* pMember);

	/**
	 *����ͨ��
	 * 
	 *�ú������ڽ���ͨ���ͷ�conversation���ͷ�UC_SDK_InsertMember���ӵĳ�Ա
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�����Ҷ�ͨ��ʱ���ã��Է��Ҷ�ʱ���Զ������ͷ���Դ��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_HangupCall(void);

	/**
	 *������Ƶͨ��
	 * 
	 *�ú������ڽ�����Ƶͨ������������ͨ��
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�����Ҷ���Ƶͨ��ʱ���ã���
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_HangupVideoCall(void);

	/**
	 *��������
	 * 
	 *�ú������ڽ�������
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_AcceptCall(void);

	/**
	 *������Ƶ����
	 * 
	 *�ú������ڽ�����Ƶ����
	 *
	 *@param[in]	localHWnd		������Ƶ���Ŵ��ڵľ��
	 *@param[in]	localLeft		������Ƶ���Ŵ��ڵ�X����
	 *@param[in]	localTop		������Ƶ���Ŵ��ڵ�Y����
	 *@param[in]	localWidth		������Ƶ���Ŵ��ڵĿ��
	 *@param[in]	localHeight		������Ƶ���Ŵ��ڵĸ߶�
	 *@param[in]	remoteHWnd		�Է���Ƶ���Ŵ��ڵľ��
	 *@param[in]	remoteLeft		�Է���Ƶ���Ŵ��ڵ�X����
	 *@param[in]	remoteTop		�Է���Ƶ���Ŵ��ڵ�Y����
	 *@param[in]	remoteWidth		�Է���Ƶ���Ŵ��ڵĿ��
	 *@param[in]	remoteHeight	�Է���Ƶ���Ŵ��ڵĸ߶�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_AcceptVideoCall(
		int localHWnd, 	int localLeft, int localTop, int localWidth, int localHeight,
		int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight);

	/**
	 *�ܾ�����
	 * 
	 *�ú������ھܾ�����
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_RejectCall(void);

	/**
	 *�ܾ�����
	 * 
	 *�ú������ھܾ���Ƶ����
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/

	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_RejectVideoCall(void);

	/**
	 *���β���
	 * 
	 *�ú������ڶ��β��Žӿڣ�֧�֡�0 1 2 3 4 5 6 7 8 9 \* \#����12���ַ�
	 *
	 *@param[in]	tone	�����ַ�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SendDTMF(char tone);

	/**
	 *��˷羲��
	 * 
	 *�ú���������˷羲��
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MuteMic(void);

	/**
	 *��˷�ȡ������
	 * 
	 *�ú���������˷�ȡ������
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnMuteMic(void);

	/**
	 *��ȡ��˷�����
	 * 
	 *�ú������ڻ�ȡ��˷�����
	 *
	 *@param[out]	level		��˷�����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetMicLevel(int& level);

	/**
	 *������˷�����
	 * 
	 *�ú�������������˷�����
	 *
	 *@param[in]	level		��˷�����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetMicLevel(int level);

	/**
	 *����������
	 * 
	 *�ú�����������������
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MuteSpker(void);

	/**
	 *������ȡ������
	 * 
	 *�ú�������������ȡ������
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnMuteSpker(void);

	/**
	 *��ȡ����������
	 * 
	 *�ú������ڻ�ȡ��˷�����
	 *
	 *@param[out]	level		����������
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetSpkerLevel(int& level);

	/**
	 *��������������
	 * 
	 *�ú���������������������
	 *
	 *@param[in]	level		����������
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetSpkerLevel(int level);

	/**
	 *������Ƶ���л��߽���ǰ������������Ϊ��Ƶ����
	 * 
	 *�ú������ڷ�����Ƶ���л��߽���ǰ������������Ϊ��Ƶ����
	 *
	 *@param[in]	localHWnd		������Ƶ���Ŵ��ڵľ��
	 *@param[in]	localLeft		������Ƶ���Ŵ��ڵ�X����
	 *@param[in]	localTop		������Ƶ���Ŵ��ڵ�Y����
	 *@param[in]	localWidth		������Ƶ���Ŵ��ڵĿ��
	 *@param[in]	localHeight		������Ƶ���Ŵ��ڵĸ߶�
	 *@param[in]	remoteHWnd		�Է���Ƶ���Ŵ��ڵľ��
	 *@param[in]	remoteLeft		�Է���Ƶ���Ŵ��ڵ�X����
	 *@param[in]	remoteTop		�Է���Ƶ���Ŵ��ڵ�Y����
	 *@param[in]	remoteWidth		�Է���Ƶ���Ŵ��ڵĿ��
	 *@param[in]	remoteHeight	�Է���Ƶ���Ŵ��ڵĸ߶�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�����ֵ������ȷ
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_MakeVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
															int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight);


	/**
	 *���������������Ա
	 * 
	 *�ú����������������������Ա
	 *
	 *@param[in]	memberType_		�˻����ͣ��ο�ö������EM_MemberType
	 *@param[in]	pAccount		�˺�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InviteMemberInCall(int memberType_,const char* pAccount);

	/**
	 *����������ɾ����Ա
	 * 
	 *�ú�����������������ɾ����Ա
	 *
	 *@param[in]	memberType_		�˺����ͣ��ο�ö������EM_MemberType
	 *@param[in]	pAccount		�˺�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_DeleteMemberInCall(int memberType_,const char* pAccount);

	/**
	 *�������������жϿ�ĳ��Ա���������������������º���ĳ��Ա�����������ж�ĳ��Ա��������ĳ��Աȡ������4�֡�
	 * 
	 *�ú������ڰ������������жϿ�ĳ��Ա���������������������º���ĳ��Ա�����������ж�ĳ��Ա��������ĳ��Աȡ������4�֡�
	 *
	 *@param[in]	operateType		�������ͣ��ο�ö������EM_ConvnerOperateType
	 *@param[in]	memberType_		�˺����ͣ��ο�ö������EM_MemberType
	 *@param[in]	pAccount		UC�˺�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ModifyMemberStatusInCall(int operateType,int memberType_,const char* pAccount);

	/**
	 *��ȡ��˷��豸�б�
	 * 
	 *�ú������ڻ�ȡ��˷��豸�б�
	 *
	 *@param[in] _fromIndex		��ʼ����
	 *@param[in] _toIndex		��������
	 *@param[in] _size			�ṹ���С
	 *@param[out] devList		�豸�б�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	[_fromIndex, _toIndex], ����_fromIndex, _toIndex
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetMicDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList);

	/**
	 *��ȡ�������豸�б�
	 * 
	 *�ú������ڻ�ȡ�������豸�б�
	 *
	 *@param[in] _fromIndex		��ʼ����
	 *@param[in] _toIndex		��������
	 *@param[in] _size			�ṹ���С
	 *@param[out] devList		�豸�б�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	[_fromIndex, _toIndex], ����_fromIndex, _toIndex
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetSpeakerDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList);

	/**
	 *��ȡ��Ƶ�豸�б�
	 * 
	 *�ú������ڻ�ȡ��Ƶ�豸�б�
	 *
	 *@param[in] _fromIndex		��ʼ����
	 *@param[in] _toIndex		��������
	 *@param[in] _size			�ṹ���С
	 *@param[out] devList		�豸�б�
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	[_fromIndex, _toIndex], ����_fromIndex, _toIndex
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetVideoDevList(int _fromIndex, int _toIndex, int _size, STDeviceListParam* devList);

	/**
	 *��ȡ��ǰ��˷��豸
	 * 
	 *�ú������ڻ�ȡ��ǰ��˷��豸
	 *
	 *@param[out] device		��ǰ��˷��豸
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetCurrentMicDev(STDeviceParam* device);

	/**
	 *��ȡ��ǰ�������豸
	 * 
	 *�ú������ڻ�ȡ��ǰ�������豸
	 *
	 *@param[out] device		��ǰ�������豸
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetCurrentSpeakerDev(STDeviceParam* device);

	/**
	 *��ȡ��ǰ��Ƶ�豸
	 * 
	 *�ú������ڻ�ȡ��ǰ��Ƶ�豸
	 *
	 *@param[out] device		��ǰ��Ƶ�豸
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetCurrentVideoDev(STDeviceParam* device);

	/**
	 *���õ�ǰ��˷��豸
	 * 
	 *�ú����������õ�ǰ��˷��豸
	 *
	 *@param[in] index			�豸����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCurrentMicDev(int index);

	/**
	 *���õ�ǰ�������豸
	 * 
	 *�ú����������õ�ǰ�������豸
	 *
	 *@param[in] index			�豸����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCurrentSpeakerDev(int index);

	/**
	 *���õ�ǰ��Ƶ�豸
	 * 
	 *�ú����������õ�ǰ��Ƶ�豸
	 *
	 *@param[in] index			�豸����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCurrentVideoDev(int index);

	/**
	 *���õ�¼�ص�
	 * 
	 *�ú����������õ�¼�ص�����
	 *
	 *@param[in]	loginEventCB_	��½�ص�����ָ��
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½ǰ�������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetLoginEventCB(ClientSignInNotifyCB loginEventCB_);

	/**
	 *����״̬�ص�
	 * 
	 *�ú�����������״̬�ص�����
	 *
	 *@param[in]	statusChangedCallBack	״̬�ص�����ָ��
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½ǰ�������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetStatusChangedCB(StatusChangedCB statusChangedCallBack);

	/**
	 *���ú����¼��ص�
	 * 
	 *�ú����������ú����¼��ص�����
	 *
	 *@param[in]	aVSessionClosedCallBack		ͨ�������¼��ص�����ָ��
	 *@param[in]	aVSessionConnectedCallBack	ͨ�������¼��ص�����ָ��
	 *@param[in]	aVSessAddedCallBack			�յ������¼��ص�����ָ��
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½����������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetCallEventCallBack(AVSessionClosedCB aVSessionClosedCallBack,
																	AVSessionConnectedCB aVSessionConnectedCallBack,
																	AVSessAddedCB aVSessAddedCallBack);

	/**
	 *������Ƶ�����¼��ص�
	 * 
	 *�ú�������������Ƶ�����¼��ص�����
	 *
	 *@param[in]	callEventCallBack		��Ƶͨ���¼��ص�����ָ��
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½����������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetVideoCallEventCallBack(VideoCallEventCB callEventCallBack);

	/**
	 *���û������¼��ص�
	 * 
	 *�ú����������û����г�Ա״̬�仯�¼��ص�
	 *
	 *@param[in] confMemEventCallBack
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�͵����ӳɹ��������غ����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetConfMemEventCallBack(ConfMemberEventCB confMemEventCallBack);

	/**
	 *��ѯ���˺�����ʷ��¼
	 * 
	 *�ú�����ѯ���˺�����ʷ��¼
	 *
	 *@param[in] _callType		��ʷ��¼���ͣ��ο�ö������EM_CallHistoryType
	 *@param[in] _fromIndex		��ʼ���кţ���0��ʼ
	 *@param[in] _toIndex		�������кţ�����С��_fromIndex
	 *@param[out] _result		��ѯ�����Žṹ��
	 *@param[out] _size			ָ��_result��ָ�ڴ�Ĵ�С
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�͵����ӳɹ��������غ����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_QueryCallHistory(int _callType, int _fromIndex,int _toIndex,STCallHistroyData* _result,int _size);


	/**
	 *������˺�����ʷ��¼
	 * 
	 *�ú���������˺�����ʷ��¼
	 *
	 *@param[in] _callType	��ʷ��¼���ͣ��ο�ö������EM_CallHistoryType
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	�͵����ӳɹ��������غ����
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ClearCallHistroy(int _callType);

	/**
	 *���������ʷ��¼
	 * 
	 *�ú������ڲ��������ʷ��¼
	 *
	 *@param[in] _callType	��ʷ��¼���ͣ��ο�ö������EM_CallHistoryType
	 *@param[in] _account	�˻�
	 *@param[in] _name		����
	 *@param[in] _duration	���г���ʱ�䵥λΪ�룬δ��ͨ�ĺ���Ҫ��ֵΪ-1��
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InsertCallHistory(int _callType,const char* _account,const char* _name,int _duration);


	/**
	 *��ѯ������ʷ��¼
	 * 
	 *�ú���������ʷ��¼
	 *
	 *@param[in] _fromIndex		��ʼ����
	 *@param[in] _toIndex		��������
	 *@param[out] _result		���صĻ�����ʷ��¼���
	 *@param[out] _size			ָ��_result��ָ�ڴ�Ĵ�С
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_QueryConvHistory(int _fromIndex,int _toIndex,STConvHistroyData* _result,int _size);

	/**
	 *��ѯһ��������ʷ��¼�Ĳ�����
	 * 
	 *�ú������ڲ�ѯһ��������ʷ��¼�Ĳ�����
	 *
	 *@param[in] _convID		������ʷ��¼ID����UC_SDK_QueryConvHistory�ӿڲ�ѯ����
	 *@param[in] _fromIndex		��ʼ����
	 *@param[in] _toIndex		��������
	 *@param[out] _result		���صĽ����ŵ�ַ
	 *@param[out] _size			ָ��_result��ָ�ڴ�Ĵ�С
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����UC_SDK_QueryConvHistory�󣬻��ȡ��_convID��Ȼ����Ե���UC_SDK_QueryHisConvPartByID
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_QueryHisConvPartByID(const char* _convID,int _fromIndex,int _toIndex,STConfPartData* _result,int _size);


	/**
	 *���������ʷ��¼
	 * 
	 *�ú������������ʷ��¼
	 *
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_ClearConvHistroy(void);

	/**
	 *���������ʷ��¼
	 * 
	 *�ú������ڲ��������ʷ��¼
	 *
	 *@param[in] _leaderAccount	�������˻�
	 *@param[in] _leaderName	����������	
	 *@param[in] _duration		�������ʱ��
	 *@param[out] _historyID	������ʷ��¼ID
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InsertConvHistory(const char* _leaderAccount,const char* _leaderName,int _duration,char _historyID[STRING_LENGTH]);

	/**
	 *���������ʷ��¼�������
	 * 
	 *�ú������ڲ��������ʷ��¼�������
	 *
	 *@param[in] _partAccount	������˻�
	 *@param[in] _partName		���������
	 *@param[in] _historyConvID	������ʷ��¼ID������UC_SDK_InsertConvHistory����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	����UC_SDK_InsertConvHistory�󣬻�ȡ��_historyConvID��Ȼ����Ե���UC_SDK_InsertConvHistoryPart�����Ա
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_InsertConvHistoryPart(const char* _historyConvID,const char* _partAccount,const char* _partName);

	/**
	 *ɾ��һ�����м�¼
	 * 
	 *�ú�������ɾ��һ�����м�¼
	 *
	 *@param[in] _iRcdID			ɾ����¼����ID,�ο��ṹ������STCallHistroyItem
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_DeleteCallHistory(int _iRcdID);

	/**
	 *ɾ��һ�������¼
	 * 
	 *�ú�������ɾ��һ�������¼
	 *
	 *@param[in] _pConvID			ɾ��������ʷ��¼��ID
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_DeleteConvHistory(const char* _pConvID);

	/**
	 *��ȡ���������豸����
	 * 
	 *�ú������ڻ�ȡ���������豸����
	 *
	 *@param[out] _iDevType			�����豸���ͣ��ο�ö������EM_PhoneJointType
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetPhoneJointDevType(int& _iDevType);

	/**
	 *���û��������豸����
	 * 
	 *�ú����������û��������豸����
	 *
	 *@param[in] _iDevType			�����豸���ͣ��ο�ö������EM_PhoneJointType
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetPhoneJointDevType(int _iDevType);

	/**
	 *���û��������¼��ص�
	 * 
	 *�ú����������û��������¼��ص�����
	 *
	 *@param[in]	pjEventCallBack		���������¼��ص�����ָ��
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½����������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SetPhoneJointEventCallBack(PhoneJointEventCB pjEventCallBack);

	/**
	 *�����¼���˹���ƽ̨����ԤԼ����ҳ��
	 * 
	 *�ú������ڵ����¼���˹���ƽ̨����ԤԼ����ҳ��
	 *
	 *@param[in]	_type		��ҳ������ͣ��ο�ö������EM_PortalType
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½����������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_OpenPortal(int _type);

	/**
	 *����״̬
	 * 
	 *�ú������ڷ�������״̬
	 *
	 *@param[in]	_Status		״̬	 
	 *@param[in]	_Desc		״̬����
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��½����������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_PubSelfStatus(int _Status,const char* _Desc);

	/**
	 *��ȡ��ϵ��״̬
	 * 
	 *�ú������ڻ�ȡ��ϵ�˸���״̬
	 *
	 *@param[in]	_AccountType ��ϵ���˻�����	 
	 *@param[in]	_Account	��ϵ���˻�	 
	 *@param[out]	_Status		״̬
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��¼�ɹ������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetContactStatus(int _AccountType,const char* _Account,int& _Status);

	/**
	 *��ȡ��ϵ����Ϣ
	 * 
	 *�ú������ڻ�ȡ��ϵ����Ϣ
	 *
	 *@param[in]	_Account	��ϵ���˻�	 
	 *@param[out]	_pContactInfo		��ϵ�˵���Ϣ
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��¼�ɹ������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_GetContactInfo(const char* _Account,STContact* _pContactInfo);

	/**
	 *����ĳ����ϵ��״̬
	 * 
	 *�ú������ڶ���ĳ����ϵ��״̬
	 *
	 *@param[in]	_Account	��ϵ���˻�	 
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��¼�ɹ������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_SubscribeStatus(const char* _Account);

	/**
	 *ȡ������ĳ����ϵ��״̬
	 * 
	 *�ú�������ȡ������ĳ����ϵ��״̬
	 *
	 *@param[in]	_Account	��ϵ���˻�	 
	 *@return		0	�ɹ�
	 *@return		��0	ʧ�ܣ��ο����󷵻��룩
	 *@attention	��¼�ɹ������
	 *@par			��
	**/
	ESDK_UCSERVICE_API int __UC_SDK_CALL UC_SDK_UnSubscribeStatus(const char* _Account);


#ifdef __cplusplus
}
#endif 


#endif



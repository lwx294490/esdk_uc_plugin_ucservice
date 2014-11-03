/******************************************************************************
* Huawei Enterprise Communication API
* siginconfig.h
* Author :  Huawei
* Description :  SignInConfig related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

namespace uc {
  namespace model {

// ! An enum
/** \brief  signinmode definition
*/
enum  SignInMode
{
  DomainAccount = 0,
  AccountAndPwd,
  FingerPrint,
  ByTicket = 4, //��񶨵�4�����Ҹ�
};

// ! An enum
/** \brief  signin privacy definition
*/
enum SignInType
{
  PublicComputer = 0,
  PrivateComputer,
};

// ! An enum
/** \brief  signin center definition
*/
enum SignInCenter
{
  Server1 = 0,
  Server2,
};

enum AATunnelType
{
    AA_CONNECTION_HTTP,
    AA_CONNECTION_HTTPS,
};
/**
* \brief PasswordWrapper
* \note The PasswordWrapper class is the password stored in ram with certain encrypt algorithm.
* \author  k00191387
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API PasswordWrapper
{
public:
	PasswordWrapper();
	~PasswordWrapper();
	PasswordWrapper(const PasswordWrapper &p);
	PasswordWrapper(const std::string &p);
	PasswordWrapper &operator=(const std::string &p);
	PasswordWrapper &operator=(const PasswordWrapper &p);
	operator std::string () const;
	std::string encryptText() const;
	void setEncryptText(const std::string &text);
private:
	int ToPwd(const std::string text, std::string &out) const ;
	int GetPwd(const std::string text, std::string &res) const ;

	std::string m_pwdEncryptText;
};
/**
* \brief SignInConfig
* \note The SignInConfig class is the signin configuration collection manager class.
* \author  y00135380
* \version 1.0.0  initial version
*/
#ifdef __APPLE__
      typedef void* HWND;
#endif
      
struct APPCLASSLAYER_API SignInConfig
{
public:

    SignInConfig():
      aaTunnelType(AA_CONNECTION_HTTP),
      siteID(Server1),
      svntunnel(false),
      svnDestroyTunnel(false)
    {
        autosign = false;
        initStatus = InvalidStatus;
        saveacc = false;
        savepwd = false;
        signinmode = AccountAndPwd;
        signintype = PrivateComputer;
		svnLoginDlgHwnd = NULL;
    }

  std::string account;  /*!< SignIn account*/
  uc::model::PasswordWrapper pwd;              /*!< SignIn password*/
  std::string internalurl;  /*!< Internal server address*/
  std::string internalsurl;     /*!< Internal secure server address*/
  std::string externalurl;  /*!< External server address*/
  std::string externalsurl;     /*!< External secure server address*/
  SignInCenter siteID;      /*!< SignIn center*/

  /* �Ƿ�ʹ��svn��¼������ */
  bool svntunnel;               /*!< Whether use svn channel for sigin*/
  bool svnDestroyTunnel;        /*!< Whether destroy svn channel*/
  std::string svnServerIp;      /*!< Secure Server IP*/
  std::string svnServerIpPort;  /*!< Secure Server IP Port*/
  std::string svnacc;   /*!< Secure channel account*/
  std::string svnpwd;   /*!< Secure channel password*/
  HWND svnLoginDlgHwnd;

  std::string lang;     /*!< Current using language*/
  std::string ver;      /*!< Current client version*/

  bool saveacc;   /*!< Whether saving account*/
  bool savepwd;   /*!< Whether saving password*/
  bool autosign;  /*!< Whether auto sign in next time*/

  SignInMode signinmode;  /*!< Sign in mode*/
  SignInType signintype;  /*!< Sign in type*/

  ContactAvailability initStatus; /*!< Sign in initial status*/
  std::string initDesc; /*!< Sign in initial sub-status*/
  std::string ticket; /*!< ticket value when use a usb ticket to login*/
  int aaTunnelType;
};

enum SignInAAResult /* ��Ҫ������sdk_msg_login.h �еĶ��屣��һ�� */
{
    LOGIN_SUCCESS = 0,           /*!<  ��½�ɹ�*/
    LOGIN_FAILED,                /*!< ��½һ��ʧ��*/
    LOGIN_PASSWORD_ERROR,        /*!<  ���벻��ȷ*/
    LOGIN_ACCOUNT_DONOT_EXIST,   /*!< �˺Ų�����*/
    LOGIN_ACCOUNT_ALREADY_LOGIN, /*!< ���˺��ѵ�¼*/
    LOGIN_ACCOUNT_LOCK,          /*!< �˺������� */
    LOGIN_NEED_NEWVERSION,       /*!< ��Ҫ�����°汾�������¼ */
    LOGIN_NEED_ACTIVE,           /*!< �û�δ���� */
    LOGIN_TIMEOUT,               /*!< ��ʱ */
    LOGIN_ABORT,                 /*!< ���� */
    LOGIN_PWDNULL,               /*!< ����Ϊ�� */
    LOGIN_ACCOUNT_ERROR,         /*!< �˺Ŵ��� */
    LOGIN_NEED_CHANGE_PASSWORD,   /*!< ��Ҫ�������� */
    LOGIN_DOMAIN_GET_UCACCOUNT_FAILED,
    LOGIN_THIRDPART_AA_FAILED,
    LOGIN_BAD_PARAM,
    LOGIN_EXTENSION_SYSTEM,
    LOGIN_EXTENSION_TICKET_EXPIRE,
    LOGIN_EXTENSION_TICKET_NOT_EXIST,
    LOGIN_EXTENSION_TICKET_FORBIDDEN,
    LOGIN_EXTENSION_TICKET_AUTH_WRONG,
    LOGIN_EXTENSION_OVER_FLOW_CONTROL,
    LOGIN_EXTENSION_FLOW_CONTROL_EXCEPTION,
    LOGIN_SERVICE_UNAVAILABLE,      /*!< 503 service unavailable */
    LOGIN_DOWNLOAD_CA_FAIL,         /*!< download cert failed */
};

  }
}

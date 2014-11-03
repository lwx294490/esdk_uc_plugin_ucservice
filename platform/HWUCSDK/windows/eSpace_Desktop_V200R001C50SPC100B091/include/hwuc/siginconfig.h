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
  ByTicket = 4, //规格定的4，勿乱改
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

  /* 是否使用svn登录及参数 */
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

enum SignInAAResult /* 重要：请与sdk_msg_login.h 中的定义保持一致 */
{
    LOGIN_SUCCESS = 0,           /*!<  登陆成功*/
    LOGIN_FAILED,                /*!< 登陆一般失败*/
    LOGIN_PASSWORD_ERROR,        /*!<  密码不正确*/
    LOGIN_ACCOUNT_DONOT_EXIST,   /*!< 账号不存在*/
    LOGIN_ACCOUNT_ALREADY_LOGIN, /*!< 此账号已登录*/
    LOGIN_ACCOUNT_LOCK,          /*!< 账号已锁定 */
    LOGIN_NEED_NEWVERSION,       /*!< 需要下载新版本才允许登录 */
    LOGIN_NEED_ACTIVE,           /*!< 用户未激活 */
    LOGIN_TIMEOUT,               /*!< 超时 */
    LOGIN_ABORT,                 /*!< 放弃 */
    LOGIN_PWDNULL,               /*!< 密码为空 */
    LOGIN_ACCOUNT_ERROR,         /*!< 账号错误 */
    LOGIN_NEED_CHANGE_PASSWORD,   /*!< 需要更换密码 */
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

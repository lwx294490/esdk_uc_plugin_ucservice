#ifndef _UCCONTACT_H
#define _UCCONTACT_H

class UCContactMgr
{
public:
	UCContactMgr(void);
	~UCContactMgr(void);
public:
	static inline UCContactMgr& Instance()
	{
		return *ctk::Singleton_T<UCContactMgr>::instance(CTK_CURRENT);
	}
	static inline void Destroy()
	{
		ctk::Singleton_T<UCContactMgr>::destroy();
	}
public:
	void Init(void);
	void Uninit(void);
	int getContactByUri(const std::string& _uri, Contact& _contact);
	int getContactByAccount(const std::string& _account, Contact& _contact);
	int getContactByPhoneNum(const std::string& _phone, Contact& _contact);
private:
	ContactMgr* m_pContactMgr;			//个人通讯录管理
	EntAddrbookMgr* m_pEntContactMgr;	//企业通讯录管理
};

#endif



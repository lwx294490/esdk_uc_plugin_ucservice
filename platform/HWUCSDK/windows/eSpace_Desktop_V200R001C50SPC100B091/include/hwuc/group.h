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

class Contact;

// ! An enum
/** \brief  group type definition
*/
enum APPCLASSLAYER_API GroupType
{
  CustomGroupType,
  FixedGroupType,
  FavoriteGroupType,
  DiscussGroupType
};

/**
* \brief Group
* \note The Group class is the basis of different group.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API Group
{
public:
  Group()
    :name_(""), id_(""), type_(-1), readonly_(false)
  {
  }

  virtual ~Group()
  {
  }

  /**
  * \brief Remove contact from current group(custom group/fixed group)
  * \param[in]  Contact
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual bool RemoveContact(const Contact& _contact) const = 0;

  /**
  * \brief Modify group(custom group/fixed group) name
  * \param[in]  Contact
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual bool Rename(const std::string& _name) = 0;

  /**
  * \brief Get group(custom group/fixed group) member list
  * \param[in]  N/A
  * \param[out] Contact list
  * \return  true:  success ; false: failed 
  */
  virtual bool GetContactlist(std::vector<Contact>& _contactlist) = 0;

public:
  std::string name_;  /*!< group name*/
  std::string id_;    /*!< group id*/
  int type_;          /*!< group type*/
  bool readonly_;     /*!< if group is readonly*/
};

/**
* \brief CustomGroup
* \note The CustomGroup class is private group create by user.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API CustomGroup: public Group
{
public:
  CustomGroup()
  {
    type_ = CustomGroupType;
    indexno_ = -1;
  }

  virtual bool AddContact(uc::model::Contact& _contact);
  virtual bool RemoveContact(const uc::model::Contact& _contact) const;
  virtual bool Rename(const std::string& _name);
  virtual bool GetContactlist(std::vector<Contact>& _contactlist);

  /**
  * \brief Move Up the CustomGroup
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool MoveUp();

  /**
  * \brief Move Down the CustomGroup
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool MoveDown();

public:
  int indexno_;    /*!< group index no*/
};

class APPCLASSLAYER_API FixedGroupConfig
{
public:
  enum PreferenceFlagType
  {
    MsgTips,    //!< notify user the messages
    CountTips,  //!< notify user the count of messages
    NoTips,     //!< do not notify user
  };

  std::string id_;        //!< group id
  std::string uri_;       //!< group uri
  int preFlag_;           //!< user preference config flag of this group
  int msgCount_;          //!< number of im message of this group

  FixedGroupConfig(const std::string & id, const std::string & uri) 
    : id_(id), uri_(uri), preFlag_(MsgTips), msgCount_(0)
  {
  }

  /**
  * \brief Change fixed group preference flag
  * \note  use value of  PreferenceFlagType
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool ChangePreferenceFlag(int preFlag);

  /**
  * \brief Change fixed group message count
  * \note  use value of  PreferenceFlagType
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool ChangeMsgCount(int msgCount);
};


enum APPCLASSLAYER_API FixedGroupAttributeType
{
    ATTRIBUTE_FIRST = 0,

    SHARE_SPACE_TOTAL_SIZE,
    SHARE_SPACE_SINGLE_FILE_SIZE,
    SHARE_SPACE_SPARE_SIZE,

    //must be the last.
    ATTRIBUTE_TOTAL_NUM,
};

/**
* \brief FixedGroup
* \note The FixedGroup class is fixed group create by owner(self or other user).
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API FixedGroup: public Group
{
public:
  enum
  {
    KickedFromFixedGroup = 0,
    FixedGroupDismissed,
  };

  FixedGroup()
  {
    type_ = FixedGroupType;
    capacity_ = 50; //default equals to 50
    needpermit_ = "true"; //default need owner permit
  }

  virtual int AddContact(uc::model::Contact& _contact);
  virtual bool RemoveContact(const uc::model::Contact& _contact) const;
  virtual bool Rename(const std::string& _name);
  virtual bool GetContactlist(std::vector<Contact>& _contactlist);
  virtual int GetContactFlow(const std::string & _uri);

  /**
  * \brief check if the contact is in the group
  * \note  
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool IsHasContact(const std::string& _uri);

  /**
  * \brief Change fixed group basic information
  * \note  Just can be done by group owner
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool ChangeGroupInfo() const;

  /**
  * \brief Change fixed group Owner
  * \note  Just can be done by current group owner
  * \param[in]  New owner
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  int ChangeGroupOwner(const Contact& _owner);

  /**
  * \brief Update fixed group contactlist from server
  * \param[in]  N/A
  * \param[out] Contact list
  * \return  true:  success ; false: failed 
  */ 
  bool Refresh(std::vector<Contact>& _contactlist);
  bool Refresh(bool sync_ = true);

  /**
  * \brief Be invoked when receiving group invitation and user accept to join the group
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool AcceptInvitation() const;

  /**
  * \brief Be invoked when receiving group invitation and user reject to join the group
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool RejectInvitation() const;

  /**
  * \brief Be invoked when receiving group joining request and owner accept the request
  * \param[in]  Contact who wants to join the group
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool AcceptJoinReq(const uc::model::Contact& _contact) const;

  /**
  * \brief Be invoked when receiving group joining request and owner reject the request
  * \param[in]  Contact who wants to join the group
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool RejectJoinReq(const uc::model::Contact& _contact) const;

  /**
  * \brief add or update the config object of this group
  * \param[in]  group id and uri of config object will be set automatically
  * \param[out] the config object of this group
  * \return  true:  success ; false: failed 
  */ 
  bool AddConfig(FixedGroupConfig & config, int preFlag, int msgCount) const;

  /**
  * \brief remove the config object of this group
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */ 
  bool RemoveConfig() const;

  /**
  * \brief get the config object of this group
  * \param[in]  group id and uri of config object will be set automatically
  * \param[out] the config object of this group
  * \return  true : this group has been configed in db; false : no config
  */ 
  bool GetConfig(FixedGroupConfig & config) const;


  virtual bool GetAttribute(FixedGroupAttributeType _type, std::string &_value);

  virtual bool SetAttribute(FixedGroupAttributeType _type, std::string _newValue);

public:
  std::string creator_;    //!< group creator
  std::string uri_;        //!< group uri
  std::string groupno_;    //!< group no
  std::string desc_;       //!< group description
  std::string bulletin_;   //!< group bulletin

  std::string owneruri_;   //!< group owner(can be different with creator)

  int capacity_;           //!< group max members
  std::string needpermit_; //!< if group needs permit by owner

  std::string sspaceTotalSize_; //!< 群共享空间总容量
  std::string sspaceSpareSize_; //!< 群共享空间剩余空间大小
  std::string sspaceSingleFileLimiteSize_; //!< 群共享空间单个文件大小限制
};

/**
* \brief FixedGroup
* \note The FavoriteGroup class is the group contains favorite contact
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API FavoriteGroup: public Group
{
public:
  FavoriteGroup()
  {
    type_ = FavoriteGroupType;
  }

  virtual bool AddContact(uc::model::Contact& _contact);
  virtual bool RemoveContact(const uc::model::Contact& _contact) const;
  virtual bool Rename(const std::string& _name);
  virtual bool GetContactlist(std::vector<Contact>& _contactlist);
};

class APPCLASSLAYER_API DiscussGroup: public Group
{
public:
	DiscussGroup() : capacity_(0)
	{
		type_ = DiscussGroupType;
	}

	virtual bool AddContact(uc::model::Contact& _contact);
	virtual bool RemoveContact(const uc::model::Contact& _contact) const;
	virtual bool Rename(const std::string& _name);
	virtual bool GetContactlist(std::vector<Contact>& _contactlist);

	bool Refresh(bool sync = true);
	bool Refresh(std::vector<Contact>& _contactlist);

public:
    std::string groupid_;//!< group id
    std::string groupuri;//!< group uri
    std::string creator_;//!< group creator
    std::string owner_; //!< group owner
    int capacity_;           //!< group max members
    std::string needpermit_; //!< if group needs permit by owner
};

  }
}

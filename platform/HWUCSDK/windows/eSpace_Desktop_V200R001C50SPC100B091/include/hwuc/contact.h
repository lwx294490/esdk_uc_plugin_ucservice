/******************************************************************************
* Huawei Enterprise Communication API
* contact.h
* Author :  Huawei
* Description :  Contact and ContactMgr related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma  once

namespace uc {
  namespace model {

class Group;
class CustomGroup;
class FavoriteGroup;
class FixedGroup;
class DiscussGroup;
// ! An enum
/** \brief  conversation type definition
*/
enum APPCLASSLAYER_API SessionType
{
  Invalid = 0,
  InstantMessage = 1,
  AudioVideo,
  DataSharing,
  CallExBusiness,
  Reserved1,
  Reserved2,
};

// ! An enum
/** \brief  addressbook search field definition
*/
enum SearchFields
{
  AddrSearch_Uri = 0,
  AddrSearch_Account,
  AddrSearch_StaffNo,
  AddrSearch_Name,
  AddrSearch_NickName,
  AddrSearch_HomePhone,
  AddrSearch_OfficePhone,
  AddrSearch_Mobile,
  AddrSearch_OtherPhone,
  AddrSearch_Address,
  AddrSearch_Email,
  AddrSearch_Duty,
  AddrSearch_Fax,
  AddrSearch_DeptName,
  AddrSearch_All,
};

// ! An enum
/** \brief  addressbook search options
*/
enum SearchOptions
{
  MatchWholeWords,
  FuzzyMatch,
};

// ! An enum
/** \brief  Contact login device type
*/
const std::string CONTACT_PC_DEVICE = "p";
const std::string CONTACT_MOBILE_DEVICE = "m";

/**
* \brief Contact
* \note The Contact class is the detailed user information class
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API Contact
{
public:
  /**
  * \brief Modify contact
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool Modify() const;

  /**
  * \brief Get user self define head image
  * \param[in]  N/A
  * \param[out] N/A
  * \return  head image file path
  */
  std::string GetHeadImagePath(bool grey = false) const;

  /**
  * \brief Move Contact from one group to another
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool MoveToGroup(const uc::model::Group& _src, const uc::model::Group& _target);

  /**
  * \brief Add Contact to a group
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool AddToGroup(const uc::model::Group& _target) const;

  /**
  * \brief Remove Contact from a group
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool RemoveFromGroup(const uc::model::Group& _target) const;

  /**
  * \brief Change Contact from original group to target group
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool RemoveFromOneToAnotherGroup(std::string &oldGroupID, std::string &newGroupID) const;

  /**
  * \brief Judge if we can started related session
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool CanStartSession(SessionType _type);

  /**
  * \brief Judge if we can move Contact from one group to another
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  bool CanMoveToGroup(const uc::model::Group& _src, const uc::model::Group& _target);

  /**
  * \brief query custom groups that this contact belongs to
  * \param[in]  N/A
  * \param[out] _groups: custom groups
  * \return  number of groups
  */
  int GetCustomGroups(std::vector<uc::model::CustomGroup> & _groups);

  bool IsFavourite() const;

public:
  std::string id_;        //!< id
  std::string uri_;       //!< sip uri
  std::string fullUri_;   //!< sip full uri
  std::string ucAcc_;     //!< account
  std::string staffNo_;   //!< staff no
  std::string videoStatus_; //!< video status

  std::string name_;      //!< name
  std::string nickName_;  //!< nick name

  std::string qpinyin_;   //!< name fullpinyin
  std::string spinyin_;   //!< name simplepinyin

  std::string homePhone_;   //!< home phone
  std::string officePhone_; //!< office phone
  std::string officePhone2_; //!< office phone2
  std::string officePhone3_; //!< office phone2
  std::string officePhone4_; //!< office phone2
  std::string officePhone5_; //!< office phone2
  std::string officePhone6_; //!< office phone2
  std::string mobile_;      //!< mobile phone
  std::string otherPhone_;  //!< other phone
  std::string otherPhone2_; //!< other phone2
  std::string address_;     //!< address

  std::string email_;     //!< email
  std::string duty_;      //!< duty
  std::string fax_;       //!< fax
  std::string gender_;    //!< gender

  std::string corpName_;  //!< enterprise name
  std::string deptName_;  //!< dept name
  std::string webSite_;   //!< web site
  std::string desc_;      //!< description
  std::string zip_;       //!< zip

  std::string signature_; //!< signature
  std::string imageID_;   //!< head image id
  std::string position_;  //!< 
  std::string location_;  //!< 
  std::string tzone_;     //!< contact time zone
  std::string avtool_;    //!< avaliable device (mic/speaker/camera)
  std::string device_;    //!< contact device type
  std::string terminalType_; //!< contact type
  std::string ipphone1_;  //!< bind ipphone1 number
  std::string ipphone2_;  //!< bind ipphone2 number
  std::string ipphone3_;
  std::string ipphone4_;
  std::string ipphone5_;
  std::string ipphone6_;
  std::string dummy_; 
  std::string modifyTime_;
  std::string state_; 
  int flow_;              //!< mark contact status in the group(just used for fixedgroup)

public:
    std::string callDevice_; //!< calling device when call contact's some no.
    std::string type_;       //!< contact's type, for special use.


public:
    Contact():flow_(-1){}
};

/**
* \brief ContactMgr
* \note The ContactMgr class is the private contact collection manager class.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API ContactMgr
{
public:
  typedef std::vector<Contact> _Contacts;

  virtual ~ContactMgr() {}

  virtual bool Init() = 0;
  virtual bool Uninit() = 0;

  virtual bool AddCustomGroup(CustomGroup& _grp) = 0;

  virtual bool AddFavoriteGroup(FavoriteGroup& _grp) = 0;

  virtual bool RemoveCustomGroup(const CustomGroup& _grp) = 0;

  virtual bool RemoveFavoriteGroup(const FavoriteGroup& _grp) = 0;

  virtual bool RefreshContactByBindNo(const std::string& _bindno, Contact& _contact, int* perrcode = NULL) = 0;
  virtual bool RefreshContactByUri(const std::string& _uri, Contact& _contact, int* perrcode = NULL) = 0;
  virtual bool RefreshContactByAccount(const std::string& _acc, Contact& _contact) = 0;
  virtual bool RefreshContactById(const std::string& _id, Contact& _contact) = 0;
  //just for IPT
  virtual bool RefreshContactByEmail(const std::string& _email, Contact& _contact) = 0;

  virtual bool RemoveContactById(const std::string & _id) = 0;

  // query local only
  virtual bool HasContact(const std::string & uri) = 0;
  virtual bool GetContactByUri(const std::string& _uri, Contact& _contact, bool refresh = false, int* perrcode = NULL) = 0;
  virtual bool GetContactByAccount(const std::string& _acc, Contact& _contact) = 0;
  virtual bool GetContactById(const std::string& _id, Contact& _contact) = 0;
  virtual bool GetContactByPhoneNum(const std::string& _phonenum, Contact& _contact) = 0;
  virtual bool GetContactByPhoneNumAndName(const std::string& _phonenum, const std::string& _name, Contact& _contact) = 0;
  virtual bool GetContactByFullUri(const std::string& _fulluri, Contact& _contact) = 0;

  //Just for IPT
  virtual bool GetContactByEmail(const std::string& _email, Contact& _contact) = 0;

  virtual bool SearchContact(const std::string& _condition, SearchFields _field, 
    SearchOptions _options, _Contacts& _contactlist) = 0;
  virtual bool GetAllContactlist(std::vector<Contact>& _contactlist) = 0;

  virtual bool GetCustomGrouplist(std::vector<CustomGroup>& _grouplist) = 0;

  virtual bool GetCustomGroupById(const std::string& _id, CustomGroup& _group) = 0;

  virtual bool RefreshFixedGrouplist(std::vector<FixedGroup>& _grouplist) = 0;
  virtual bool GetFixedGrouplist(std::vector<FixedGroup>& _grouplist) = 0;
  virtual bool GetFixedGroupByUri(const std::string& _groupuri, FixedGroup& _group) = 0;
  virtual bool GetFixedGroupByID(const std::string& _groupid, FixedGroup& _group) = 0;

  /**
  * \brief Add a new fixed group
  * \param[in]  _grp: fixed group info
  * \param[out] N/A
  * \return  0:  success ; 1: failed; 2: too many groups
  */
  virtual int AddFixedGroup(FixedGroup & _grp) = 0;
  virtual bool RemoveFixedGroup(const uc::model::FixedGroup & _grp) = 0;
  virtual bool SearchFixedGroup(
    const std::string& groupNo, const std::string& groupName, 
    int offset, int count, 
    std::vector<uc::model::FixedGroup> & _grouplist) = 0;

  virtual int  AddDiscussGroup(DiscussGroup& _group) = 0;
  virtual bool RemoveDiscussGroup(const DiscussGroup& _group) = 0;
  virtual bool GetDiscussGrouplist(std::vector<DiscussGroup>& _grouplist) = 0;
  virtual bool GetDiscussGroupByID(const std::string& _groupid, uc::model::DiscussGroup& _group) = 0;
  virtual bool RefreshDiscussGroupList(std::vector<DiscussGroup>& _grouplist) = 0;

public:  
  /**
  * \brief Receive Fixed Group invitation
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnGroupInvitation_(const uc::model::FixedGroup _group, std::string inviteruri, std::string invitername);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal4<const uc::model::FixedGroup &, std::string, std::string, std::string> FixedGroupInvitation_;
  
  /**
  * \brief Group owner receive Fixed Group invitation result notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnGroupInvitationRes(const uc::model::FixedGroup _group, std::string invitername, int result);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal3<const uc::model::FixedGroup &, std::string, int> FixedGroupInvitationRes_;

  /**
  * \brief Receive Fixed Group dismissed or being kicked from Fixed Group notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnLeaveFromFixedGroup(const uc::model::FixedGroup _group, int reason);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal2<const uc::model::FixedGroup &, int> LeaveFromFixedGroup_;

  sigslot::signal1<const uc::model::FixedGroup &> RefreshFixedGroupResult_;

  /**
  * \brief Receive joining Fixed Group request
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnJoinFixedGroupRequset(const uc::model::FixedGroup _group, std::string inviteruri, std::string invitername);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal3<const uc::model::FixedGroup &, std::string, std::string> JoinFixedGroupRequset_;

  /**
  * \brief requestor receive join fixed group response result
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnJoinFixedGroupRes(const uc::model::FixedGroup _group, std::string invitername, int result);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal3<const uc::model::FixedGroup &, std::string, int> JoinFixedGroupRes_;

  /**
  * \brief Receive Fixed Group member added notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnMemberAdded(const uc::model::FixedGroup _group, uc::model::Contact _contact);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal2<const uc::model::FixedGroup &, uc::model::Contact &> MemberAdded_;

  /**
  * \brief Receive Fixed Group member removed notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnMemberRemoved(const uc::model::FixedGroup _group, uc::model::Contact _contact);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal2<const uc::model::FixedGroup &, uc::model::Contact &> MemberRemoved_;

  /**
  * \brief Receive Fixed Group member really flow changed notifcation
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnMemberFlowChanged(const uc::model::FixedGroup _group, uc::model::Contact _contact);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal2<const uc::model::FixedGroup &, uc::model::Contact &> MemberFlowChanged_;

  /**
  * \brief Receive Fixed Group member really flow changed notifcation
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnMemberFlowChanged(const uc::model::FixedGroup _group, uc::model::Contact _contact);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal2<const uc::model::FixedGroup &, uc::model::Contact &> GroupOwnerChanged_;

  /**
  * \brief Receive Fixed Group info changed notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnFixedGroupInfoChanged(const uc::model::FixedGroup _group);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal1<const uc::model::FixedGroup &> FixedGroupInfoChanged_;

    /**
  * \brief Receive Incre Contacts changed notification
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnIncreContactsChanged(std::string);
  * \param[in]  N/A
  * \param[out] N/A
  * \return   
  */
  sigslot::signal1<std::string> IncreContactsChanged_;
};

// ! An enum
/** \brief  online status definition
*/
enum ContactAvailability
{
  Offline = 0,
  Online,
  Hide,
  Busy,
  Leave,
  NoDisturb,
  InvalidStatus,
};

typedef std::pair<uc::model::Contact, uc::model::ContactAvailability> ContactStatus;

/**
* \brief Dept
* \note The Dept class is the enterprise department class.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API Dept
{
public:
  typedef std::vector<ContactStatus> _ContactStatuses;

  Dept():deptlevel_(0){}

  /**
  * \brief Search the contacts in current or its sub-branch
  * \param[in]  N/A
  * \param[out] N/A
  * \return  contact list
  */
  bool SearchContact( int deptlevel, int offset, int count, int ordertype
    , int & recamount, _ContactStatuses & _contactlist
    /*, SearchFields _field, SearchOptions _options*/) const;

  bool SendBroadcastMessage(
    const std::string & subject, const std::string & text) const;

  std::string deptname_;  /*!< dept name*/
  std::string deptID_;    /*!< dept ID*/
  std::string parentID_;  /*!< parent dept ID*/
  int         deptlevel_; /*!< dept level*/
};

/**
* \brief EntAddrbookMgr
* \note The EntAddrbookMgr class is basis of the enterprise addressbook manager.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API EntAddrbookMgr
{
public:
  typedef std::vector<ContactStatus> _ContactStatuses;
  typedef std::vector<Dept> _Depts;

  EntAddrbookMgr():lastoffset_(0),recamount_(0){}
  /**
  * \brief Search the contacts in current enterprise addressbook
  * \param[in]  N/A
  * \param[out] N/A
  * \return contact list
  */
  bool SearchContact(
    std::string _condition, std::string deptid, bool querysubdept
    , int offset, int count, int ordertype, int & recamount, 
    _ContactStatuses & _contactlist, int searchtype = 0
    /*, SearchFields _field, SearchOptions _options*/) const;

  bool SearchContactAssist(
      std::string _condition, std::string deptid, bool querysubdept
      , int offset, int count, int ordertype, int & recamount, 
      _ContactStatuses & _contactlist) const;

  void GetRootDept(Dept & rootDept) const;

  /**
  * \brief Get sub branches of the specified parent branch
  * \param[in]  N/A
  * \param[out] N/A
  * \return department list
  */
  void GetSubDeptList(std::string _parentId, _Depts & depts) const;

    /**
  * \brief Get status of the enterprise staffs
  * \param[in]  accountList:the account list
  * \param[out] N/A
  * \return department list
  */
  void GetEntStaffStatus(const std::list<std::string> &accountList) const;

  mutable int lastoffset_;      //!< Previous unconditional search offset
  mutable int recamount_;       //!< Previous unconditional search totalcount
  mutable _ContactStatuses lastcache_;  //!< Previous unconditional search staff cache

  typedef ctk::Mutex _Mutex;
  _Mutex mtx_;
};

  } // namespace model
} // namespace uc

/******************************************************************************
* Huawei Enterprise Communication API
* contactsubscription.h
* Author :  Huawei
* Description :  ContactSubscription related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

namespace uc {
  namespace model {

/**
* \brief ContactSubscription
* \note The ContactSubscription class manager all contacts subscription
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API ContactSubscription
{
public:
  virtual ~ContactSubscription() {}

  /**
  * \brief Init contact presence subscription
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual bool Init() = 0;
  virtual bool Uninit() = 0;

  /**
  * \brief get the specified contact status
  * \param[in]  contact uri
  * \param[out] ContactAvailability description
  * \param[out] contact device type
  * \return  ContactAvailability and 
  */
  virtual ContactAvailability GetContactStatus(
    const std::string& _uri) = 0;
  virtual ContactAvailability GetContactStatus(
    const std::string& _uri, std::string& _desc) = 0;
  virtual ContactAvailability GetContactStatus(
	  const std::string& _uri, std::string& _desc, std::string& device_) = 0;
 
  virtual ContactAvailability GetContactExchangeStatus(const std::string& _uri) = 0;
  virtual void GetContactVideoStatus(
            const std::string& _uri, std::string& _videostatus) = 0;

  virtual std::string GetContactDevice(const std::string& _uri) = 0;

  /**
  * \brief subscribe contact presence
  * \param[in]  contact uri
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual bool AddSubContact(const std::string& _uri) = 0;

  /**
  * \brief remove from sub contact
  * \param[in]  contact uri
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual void RemoveSubContact(const std::string& _uri) = 0;

  virtual void ClearSubList() = 0;

  virtual void GetSubList(std::vector<std::string> &subContactList) = 0;
  /**
  * \brief check if we have sub this user
  * \param[in]  contact uri
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual bool HasSubContact(const std::string& _uri) = 0;

  /**
  * \brief Init sub contact list with friend list
  * \param[in]  N/A
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual void InitSubContactlist() = 0;

  /**
  * \brief subscribe contacts presence
  * \param[in]  contact uri
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual void AddSubContact(std::vector<std::string>& _uri) = 0;

  /**
  * \brief remove from sub contacts
  * \param[in]  contact uri
  * \param[out] N/A
  * \return  true:  success ; false: failed 
  */
  virtual void RemoveSubContact(std::vector<std::string>& _uri) = 0;

public:
  /**
  * \brief Contact state changed Signal
  *        UI need to implement has_slots<> and connect to the signal.
  *        Like this:  void OnAvailabilityChanged(uc::model::UCClient::ContactAvailability _state, 
  *                          std::string _desc, uc::model::Contact _contact);
  */
  sigslot::signal4<uc::model::ContactAvailability, std::string, const uc::model::Contact&, std::string> UserAvailabilityChanged_;

  sigslot::signal2<std::string, std::map<std::string, uc::model::ContactAvailability> > GroupStatusChanged_;

  sigslot::signal3<std::string, std::string, std::string > UserMainIdentityRebind_;
};

  }
}

/******************************************************************************
* Huawei Enterprise Communication API
* Author :	Huawei
* Description :  authorization related API.
* Create Time:	2013-09-12	16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :	2013-09-12 1.00	First version
******************************************************************************/

#pragma once

#include "auth/authAutoLink.h"

namespace uc {
  namespace model {
    namespace auth {

        enum AuthType
        {
            AUTH_TYPE_AA = 1,
            AUTH_TYPE_Ticket,
            AUTH_TYPE_PKI,
            AUTH_TYPE_SmartCard,
            AUTH_TYPE_BiometricDevice,
            AUTH_TYPE_UNKNOWN,
        };

        class AUTH_API AuthManager
        {
        public:
            //Singleton
            static AuthManager * Instance();
            static void Destroy();
        public:
           /**
            * \brief get the ticket for authorization
            * \param[in]  N/A
            * \param[out] _ticket : the ticket.
            * \return   AuthType
            */
            virtual AuthType GetTicket(std::string &_ticket) = 0;
           /**
            * \brief get server address when authorization is AUTH_TYPE_Ticket
            * \param[in]  N/A
            * \param[out] _ipAddress : the ip address(v4 & v6).
            * \param[out] _port : the port.
            * \return   bool indicates success or failed
            */
            virtual bool GetServer(std::string &_ipAddress, std::string &_port) = 0;
        };

    } // namespace auth
  } // namespace model
} // namespace uc

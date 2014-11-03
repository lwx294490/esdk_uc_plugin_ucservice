/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_ICMP_PING_H_
#define _Z_CTK_ICMP_PING_H_

#include "ctk/base.h"

namespace ctk {

    class PingImpl; 

    //author: zhangkui 00108466
    class CTK_API Ping
    {
        PingImpl* impl_;

    public:
        Ping();
        ~Ping();

        bool open();

        void close();

        /**
        * \brief 
        * \param[in]  _remote 对端IP地址 //
        * \param[out]  _costTime ping花费时间，单位ms //
        * \param[in]  _waitTimeout ping超时返回直接，单位s //
        * \return 返回值 //
        */
        bool sendAndWait(const ctk::String& _remote, ctk::int64* _costTime, ctk::int32 _waitTimeout = 1000);
    };

} // end of namespace ctk

#endif //_Z_CTK_ICMP_PING_H_


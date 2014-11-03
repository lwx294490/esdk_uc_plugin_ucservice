/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TCP_SERVER_H_
#define _Z_CTK_TCP_SERVER_H_

#include "ctk/tcp/tcp_common.h"

namespace ctk {

    namespace tcp { class ServerImpl; }

    class CTK_API TcpServer
    {
        tcp::ServerImpl* impl_;

    public:
        TcpServer();
        ~TcpServer();

        bool open(const TcpAddr& _svrAddr, TcpCallbackPtr _cb, int _buffSize=65535);

        void close();

        bool send(const TcpAddr& _peerAddr, ctk::rcistr _buf, int _waitSeconds=-1);

        ctk::uint16 getLocalPort() const;

    };

} // end of namespace ctk

#endif //_Z_CTK_TCP_SERVER_H_


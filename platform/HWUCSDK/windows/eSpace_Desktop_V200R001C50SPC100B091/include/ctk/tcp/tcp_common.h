/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TCP_COMMON_H_
#define _Z_CTK_TCP_COMMON_H_

#include <ctk/base.h>
#include <ctk/util/util_type.h>
#include <ctk/base/interface.h>
#include <ctk/pml/pml_stream.h>
#include <ctk/mt/shared.h>
#include <ctk/mt/handle.h>

#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>

namespace ctk {

    struct CTK_API TcpAddr
    {
        ctk::String ip_;
        ctk::Uint16 port_;

        TcpAddr();
        TcpAddr(const ACE_INET_Addr& _addr);
        explicit TcpAddr(ctk::uint16 _port, ctk::rcistr _ip=ctk::istr());

        operator ACE_INET_Addr() const;

        void codec(ctk::pml::stream& _mps);

        bool operator==(const TcpAddr&) const;
        bool operator!=(const TcpAddr&) const;
        bool operator<(const TcpAddr&) const;

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const TcpAddr& _v);

    class CTK_API TcpCallback : virtual public Shared
    {
    public:
        virtual void onRecv(const ctk::TcpAddr& _peerAddr, const ctk::istr& _msg) = 0;
        virtual void onClose(const ctk::TcpAddr& _peerAddr) = 0;
    };
    typedef ctk::Handle<TcpCallback> TcpCallbackPtr;

} // end of namespace ctk

#endif // _Z_CTK_TCP_COMMON_H_


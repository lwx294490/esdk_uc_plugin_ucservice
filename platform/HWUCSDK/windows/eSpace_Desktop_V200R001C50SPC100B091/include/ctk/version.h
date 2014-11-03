/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_CLASS_H_
#define _Z_CTK_VERSION_CLASS_H_

#include "ctk/base.h"

namespace ctk {

    struct CTK_API Version
    {
        typedef const Version& _RCV;

        uint32 version_;
        uint32 patch_;

        explicit Version(uint32 _version=0, uint32 _patch=0);

        bool operator>(_RCV _v) const;
        bool operator<(_RCV _v) const;
        bool operator==(_RCV _v) const;
        bool operator>=(_RCV _v) const;
        bool operator<=(_RCV _v) const;
        bool operator!=(_RCV _v) const;

        void codec(ctk::pml::stream& _mps);
    };

    typedef const Version& RCVersion;

    CTK_API std::ostream& operator<<(std::ostream& _os, const Version& _v);

}

#endif // _Z_CTK_VERSION_CLASS_H_


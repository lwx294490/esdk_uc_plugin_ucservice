/*
 *  ctk_util_aes.h
 *  espace
 *
 *  Created by luyunhai 117629(3664)/huawei on 12-4-25.
 *  Copyright 2011-2012 Huawei Technologies Co., Ltd. All rights reserved.
 *
 */
#ifndef _CTK_UTIL_AES_H_
#define _CTK_UTIL_AES_H_

#include "ctk/base.h"

// AES crypt
namespace ctk
{
    class AesCipher;

    // AES CBC 128
    class CTK_API AES : private noncopyable
    {
        AesCipher* cipher_;

    public:
        AES(istr _key, istr _iv); // _key and _iv must be 16 bytes
        ~AES();

        void encrypt(istr _in, Bytes& _out);

        void decrypt(istr _in, Bytes& _out);

    }; // end of class AES
    
} // end of namespace ctk

#endif // _CTK_UTIL_AES_H_


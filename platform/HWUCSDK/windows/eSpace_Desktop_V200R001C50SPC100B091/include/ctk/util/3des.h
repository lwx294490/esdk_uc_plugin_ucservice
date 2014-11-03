/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_3DES_H_
#define _Z_CTK_UTIL_3DES_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

#if !defined(DES3_ED_FLAG)
#define DES3_ED_FLAG
#define des3_encrypt 0
#define des3_decrypt 1
#endif

namespace ctk {

//////////////////////////////////////////////////////////////////////////
/*
 unsigned char key[8] = {"doks"};
 unsigned char buff[8] = {"abcdef"};
 C3DES des;
 des.DoDES3(0,buff,key); //encrypt
 des.DoDES3(1,buff,key); //decrypt
*/
/* 3DES Class. */
class des3 
{
public:
    CTK_API static bool encode(rcistr _in, Bytes& _out, rcistr _key);
    CTK_API static bool decode(rcistr _in, Bytes& _out, rcistr _key);

private:
    bool DoDES3(uchar edFlag, rcistr _in, Bytes& _out, const uchar* pKey /*[8]*/);
    bool DoDES3(
        uchar edFlag, //EDFlag是加\脱密标志,0表示加密，1表示脱密 //
        uchar* databuf/*[8]*/, //DataBuf将被处理的明文或密文的缓冲区,并兼作输出缓冲区 //
        const uchar* keybuf/*[8]*/ //8byte的密钥缓冲区 //
    );
    inline void pro_key(void);
    inline void first_p(void);
    inline void expand_x(void);
    inline void fction(void);
    inline void make(bool FirstFlag);
    static const ulong sp0[64],sp1[64],sp2[64],sp3[64],sp4[64],sp5[64],sp6[64],sp7[64];
    static const uchar pc0[64],pc0_v[64],pc1[56],pc2[48],rotate[16],bytebit[8];
    static const ulong bigbyte[24],bigbyte1[32];
    uchar key[8],m[8],c[8],k[16][8],s_in[8],pc[64];
    uchar ed_flag;
    ulong x[2];
};

} // namespace ctk

#endif //_Z_CTK_UTIL_3DES_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_MD5_H_
#define _Z_CTK_UTIL_MD5_H_

#include <ctk/ctk_config.h>

#include <ctk/base/base_type_string.h>

extern "C"
{
struct md5_state_s;
}

namespace ctk
{

class CTK_API MD5
{
public:

    MD5();
    MD5(rcistr _data);
    ~MD5();

    void update(rcistr _data);
    void finish();

    void getDigest(String& _result) const;

private:

    md5_state_s* state_;
    unsigned char digest_[16];
};

} // namespace ctk

#endif //_Z_CTK_UTIL_MD5_H_


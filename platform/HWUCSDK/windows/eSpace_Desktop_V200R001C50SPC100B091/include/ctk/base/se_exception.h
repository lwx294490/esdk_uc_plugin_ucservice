/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_SE_EXCEPTION_H_
#define _Z_CTK_BASE_SE_EXCEPTION_H_

#include "ctk/ctk_config.h"

#include "ctk/base/exception.h"

namespace ctk
{

    class CTK_API SE_Exception : public std::exception
    {
        typedef std::exception _Super;

    private:
        uint se_;

        // address (win32)
        uint32 ebp_;
        uint32 eip_;

        std::string str_;

    public:
        SE_Exception( uint _n = 0, uint32 _ebp = 0, uint32 _eip = 0);
        ~SE_Exception() CTK_NOTHROW;

        uint getSeNumber() const;
        uint32 getEbp() const;
        uint32 getEip() const;

        virtual pcstr what() const CTK_NOTHROW;

        static void set_se_translator();

    };

}

#endif //_Z_CTK_BASE_SE_EXCEPTION_H_


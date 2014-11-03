/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_BMPUTIL_H_
#define _Z_CTK_UTIL_BMPUTIL_H_

#include "ctk/ctk_config.h"

#include "ctk/strings.h"

namespace ctk
{
    struct BmpInfo
    {
        uint16 width_;
        uint16 height_;
        uint16 bits_;

        BmpInfo(uint16 _width=0, uint16 _height=0, uint16 _bits=0)
            : width_(_width), height_(_height), bits_(_bits)
        {
        }
    };

    void packBmp24to15(istr _input, uint16 _biBitCount, StringBuffer& _output);

    void diffBmp15Data(istr _oldBuf, istr _newBuf, StringBuffer& _diffData);

    void compressBmp15Data(istr _input, StringBuffer& _output);

    void compressBmp15DiffData(istr _input, StringBuffer& _output);

}

#endif //_Z_CTK_UTIL_BMPUTIL_H_


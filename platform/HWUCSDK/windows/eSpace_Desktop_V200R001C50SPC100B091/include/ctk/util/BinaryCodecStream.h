/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_BINARYCODECSTREAM_H_
#define _Z_CTK_UTIL_BINARYCODECSTREAM_H_

#include "ctk/ctk_config.h"

#include "ctk/util/BinaryInStream.h"
#include "ctk/util/BinaryOutStream.h"

namespace ctk
{

    class BinaryCodecStream
    {
        bool encoding_;
        ctk::BinaryInStream bis_;
        ctk::BinaryOutStream bos_;

    public:
        BinaryCodecStream()
            : encoding_(true)
        {
        }
        BinaryCodecStream(ctk::istr _buf)
            : encoding_(false), bis_(_buf)
        {
        }

        void str(ctk::istr _buf)
        {
            bis_.str(_buf);
        }

        ctk::istr str() const // get output
        {
            return bos_.str();
        }

        template <class T>
        BinaryCodecStream& operator|(T& _v)
        {
            if (encoding_)
                bos_ << _v;
            else
                bis_ >> _v;
            return *this;
        }

    };

} // end of namespace ctk

#endif //_Z_CTK_UTIL_BINARYCODECSTREAM_H_


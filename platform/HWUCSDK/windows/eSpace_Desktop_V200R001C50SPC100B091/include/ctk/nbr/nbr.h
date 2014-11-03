/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// NBR(Nested Binary Representation)

#ifndef _Z_CTK_NBR_NBR_H_
#define _Z_CTK_NBR_NBR_H_

#include "ctk/ctk_config.h"

#include "ctk/nbr/stream.h"

#include "ctk/log/log_dumper.h"

namespace ctk {
namespace nbr {

   class BinaryCodecInterface : public ctk::Dumpable
   {
   public:
       virtual ~BinaryCodecInterface(){}
       virtual void encode(ctk::nbr::OutputStream& _os) const = 0;
       virtual void decode(ctk::nbr::InputStream& _is) = 0;
   };

} // end of namespace nbr
} // end of namespace ctk

#endif // !_Z_CTK_NBR_NBR_H_


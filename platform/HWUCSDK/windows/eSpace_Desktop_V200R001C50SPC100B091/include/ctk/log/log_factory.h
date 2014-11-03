/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_FACTORY_H_
#define _Z_CTK_LOG_FACTORY_H_

#include "ctk/ctk_config.h"

namespace ctk
{
    class CTK_API logger;
    class CTK_API dumper;

    class CTK_API logger_factory
    {
    public:
        static void create();
        static void destroy();

        static logger& instance(const std::string& _id);

    };

    struct LOGGER_FACTORY
    {
    };
    CTK_API ctk::dumper& operator<<(ctk::dumper& _os, const LOGGER_FACTORY& _v);

} // namespace ctk

#endif//_Z_CTK_LOG_FACTORY_H_


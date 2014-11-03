/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_CFG_CONFIG_FILE_H_
#define _Z_CTK_CFG_CONFIG_FILE_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/pml_stream.h"

namespace ctk
{
    const pcstr ECS_CLI_CFG_FILE = "ECS_CLI_CFG_FILE";

    class CTK_API ConfigFile
    {
        ctk::Boolean enable_;
        ctk::String config_;
        pml::stream mps_;
        const pml::stream mpsEmpty_;

        ctk::Uint32 codepage_;

    public:
        ConfigFile();

        ConfigFile& load(ctk::rcistr _cfgFile);

        ConfigFile& load();

        bool empty() const;

        const pml::stream& mps() const;

        static uint32 codepage();

        static ConfigFile& instance();
        
        static void destroy();

        ctk::dumper& dump(ctk::dumper& _os) const;

    };

}

#endif//_Z_CTK_CFG_CONFIG_FILE_H_


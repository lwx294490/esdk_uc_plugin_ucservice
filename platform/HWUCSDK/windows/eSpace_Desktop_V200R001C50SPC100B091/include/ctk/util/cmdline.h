/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

#ifndef _Z_CTK_CMDLINE_H_
#define _Z_CTK_CMDLINE_H_
 
#include "ctk/base.h"
#include "ctk/util/util_type.h"

#include "ctk/mt/thread.h"
#include "ctk/mt/threadUtil.h"
#include "ctk/mt/queue.h"

namespace ctk {

    class CTK_API CmdLineCallback : public ctk::Interface
    {
    public:
        virtual void onCmdLine(ctk::rcwstr _cmdline) = 0;
    };

    class CTK_API CmdLineThread : public ctk::SimpleThread
    {
        typedef ctk::SimpleThread _Super;

        ctk::Pointer<CmdLineCallback> cb_;
        ctk::Wstring prompt_;
        ctk::Boolean noprompt_;

    public:
        CmdLineThread(ctk::rcistr _name, CmdLineCallback* _cb, ctk::rciwstr _prompt);

    protected:
        virtual void onWork();

    };

    class CTK_API CmdLineQueue : public CmdLineCallback
    {
        typedef ctk::mt::queue<ctk::Wstring> _Queue;
        typedef ctk::Handle<CmdLineThread> _ThreadPtr;
        _Queue     queue_;
        _ThreadPtr thr_;

    public:
        bool open(ctk::rciwstr _prompt);

        void close();

        bool get(ctk::Wstring& _cmd, ctk::Time _waitTime);

    protected:
        void onCmdLine(ctk::rcwstr _cmdline);

    };

} //end of namespace ctk

#endif//_Z_CTK_CMDLINE_H_


/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_THREAD_COM_H_
#define _Z_CTK_THREAD_COM_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/thread.h"

#if CTK_WIN32

namespace ctk
{
    struct AutoSTA
    {
        AutoSTA();
        ~AutoSTA();
    };

    struct AutoMTA
    {
        AutoMTA();
        ~AutoMTA();
    };

    class CTK_API STAThread : public SimpleThread
    {
        typedef SimpleThread _Super;

    public:
        STAThread(ThreadOwner* _owner, pcstr _name)
            : _Super(_owner, _name)
        {
        }

    private:
        virtual void run_i();

    };
    typedef ctk::Handle<STAThread> STAThreadPtr;

    class CTK_API MTAThread : public SimpleThread
    {
        typedef SimpleThread _Super;

    public:
        MTAThread(ThreadOwner* _owner, pcstr _name)
            : _Super(_owner, _name)
        {
        }

    private:
        virtual void run_i();

    };
    typedef ctk::Handle<MTAThread> MTAThreadPtr;

} // end of namespace ctk

#endif // CTK_WIN32

#endif // _Z_CTK_THREAD_COM_H_


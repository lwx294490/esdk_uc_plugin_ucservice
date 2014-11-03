/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UOW_H_
#define _Z_CTK_UOW_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

#include "ctk/log/log_dumper.h"

namespace ctk
{
    class CTK_API CmdLine
    {
    public:
        typedef std::vector<String> _Args;

        CmdLine()
        {
            init(0, 0);
        }
        CmdLine(int _argc, ACE_TCHAR* _argv[])
        {
            init(_argc, _argv);
        }

        CmdLine& init(int _argc, ACE_TCHAR* _argv[]);

        Wstring& cmd()
        {
            return cmd_;
        }

        const Wstring& cmd() const
        {
            return cmd_;
        }

        _Args& args()
        {
            return args_;
        }

        const _Args& args() const
        {
            return args_;
        }

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        int argc_;
        ACE_TCHAR** argv_;

        Wstring cmd_;
        _Args args_;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const CmdLine& v)
    {
        return v.dump(os);
    }
    inline std::ostream& operator<<(std::ostream& os, const CmdLine& v)
    {
        return v.dump(os);
    }

    class CTK_API UnitOfWork
    {
    public:
        typedef UnitOfWork _Self;
        typedef CmdLine::_Args _Args;
        typedef std::list<UnitOfWork*> _Children;

        UnitOfWork(pcstr _name="", UnitOfWork* _parent=0);
        virtual ~UnitOfWork();

        int start();

        void stop(int _retval=0);
        void stopAll(int _retval=0);

        String path() const;

        virtual void on_init() = 0;
        virtual void on_loop() = 0;
        virtual void on_fini() = 0;

        virtual void run(rcstr CTK_NO_ARG(_cmd)){};

        bool running() const
        {
            return running_;
        }

        UnitOfWork* parent() const
        {
            return parent_;
        }

        UnitOfWork* root()
        {
            UnitOfWork* tmp = this;
            while(tmp->parent())
                tmp = tmp->parent();
            return tmp;
        }

        const String& name() const
        {
            return name_;
        }

        String& name()
        {
            return name_;
        }

        const CmdLine& cmdline() const
        {
            return cmdline_;
        }

        CmdLine& cmdline()
        {
            return cmdline_;
        }

        _Args& args()
        {
            return cmdline().args();
        }

        const _Args& args() const
        {
            return cmdline().args();
        }

    private:
        bool running_;
        int retval_;

        UnitOfWork* parent_;
        _Children children_;

        String name_;

        CmdLine cmdline_;
    };

    //class UowManager
    //{
    //};

    //class UowDemo : public UnitOfWork
    //{
    //};

    class CTK_API UowMain : public UnitOfWork
    {
    public:
        typedef UowMain _Self;
        typedef UnitOfWork _Super;

        UowMain(int _argc, ACE_TCHAR* _argv[]);

        virtual void on_init() { }
        virtual void on_loop() { }
        virtual void on_fini() { }

        rcstr argAt(size_type _i) const
        {
            if (args().size() > _i)
                return args()[_i];
            return emptyArg_;
        }

        rcstr argCurrent() const
        {
            return argAt(currArg_);
        }

        rcstr argNext() const
        {
            if (argLeft()>0)
                ++currArg_;
            return argCurrent();
        }

        size_type argCount() const
        {
            return (size_type)args().size();
        }

        size_type argLeft() const
        {
            return argCount() - currArg_;
        }

    private:
        String emptyArg_;
        mutable size_type currArg_;
    };

    class CTK_API main_uow
    {
    public:
        main_uow() : uow_(0) { }
        
        UnitOfWork* get() const { return uow_; }
        void set(UnitOfWork* _uow) { uow_ = _uow; }

        CTK_STATIC_FUN main_uow& instance();
    
    private:
        UnitOfWork* uow_;
    };

    CTK_API UnitOfWork& app();

}

#endif //_Z_CTK_UOW_H_


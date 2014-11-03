/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MT_TASK_H_
#define _Z_CTK_MT_TASK_H_

#include "ctk/ctk_config.h"

#include "ctk/mt/thread.h"

#include "ctk/mt/threadUtil.h"

#include "ctk/mt/queue.h"

#include "ctk/util.h"

namespace ctk {

    class TaskBase : public ctk::Shared
    {
    public:
        // 要执行的任务 //
        virtual void run() = 0;

        // 线程退出时要取消当前任务的执行 //
        virtual void onCancel() { }

        // 任务队列满时将最早的任务挤出去 //
        virtual void onRemove() { }

    };
    typedef ctk::Handle<TaskBase> TaskPtr;

    class Task
    {
        TaskPtr ptr_;

    public:
        Task(TaskPtr _ptr = 0)
            : ptr_(_ptr)
        {
        }

        void operator()()
        {
            TaskPtr p = ptr_;
            if (p)
                p->run();
        }

        void onCancel()
        {
            TaskPtr p = ptr_;
            if (p)
                p->onCancel();
        }

        void onRemove()
        {
            TaskPtr p = ptr_;
            if (p)
                p->onRemove();
        }

    };

    /*
     * 任务队列模型 //
     * 
     */
    template<class _Fo=Task, class _ParentThread=ctk::SimpleThread>
    class TaskQueue
    {
        class TaskThread : public _ParentThread
        {
            typedef _ParentThread _Super;

            TaskQueue& owner_;

            _Fo currentTask_;

            volatile bool taskActive_;

        public:
            TaskThread(istr _name, TaskQueue& _owner)
                : _Super(0, _name.data())
                , owner_(_owner)
                , taskActive_(false)
            {
            }

            void cancel()
            {
                onStop();
            }

        protected:
            bool onLoop()
            {
                if (owner_.q_.get(currentTask_))
                {
                    taskActive_ = true;
                    currentTask_();
                    taskActive_ = false;
                }
                return true;
            }

            void onStop()
            {
                if (taskActive_)
                    currentTask_.onCancel();
                else
                    owner_.q_.notifyAll();
            }

        };
        friend class TaskThread;

        typedef ctk::Handle<TaskThread> TaskThreadPtr;

        String name_;
        size_t numofThreads_;
        size_t limitedQueueSize_;

        ctk::mt::queue<_Fo> q_;

        ctk::vector<TaskThreadPtr> threads_;

    public:
        TaskQueue(rcstr _name, size_t _numofThreads = 1, size_t _limitedQueueSize = 0)
            : name_(_name), numofThreads_(_numofThreads), limitedQueueSize_(_limitedQueueSize)
        {
        }

        void open()
        {
            for (size_t i = 0; i < numofThreads_; ++i)
            {
                TaskThreadPtr pThread = ctk_new TaskThread(name_|"."|i, *this);
                pThread->startAndWait();
                threads_.push_back(pThread);
            }
        }

        void close()
        {
            for (size_t i = 0; i < threads_.size(); ++i)
            {
                ctk::stopThread(threads_[i]);
            }
        }

        void cancelAll()
        {
            while (q_.size() > 0)
            {
                _Fo tmp;
                if (q_.get(tmp))
                    tmp.onRemove();
            }

            for (size_t i = 0; i < threads_.size(); ++i)
            {
                if (threads_[i])
                    threads_[i]->cancel();
            }
        }

        void put(const _Fo& _v)
        {
            while (limitedQueueSize_ > 0 && q_.size() > (limitedQueueSize_ - 1))
            {
                _Fo tmp;
                if (q_.get(tmp))
                    tmp.onRemove();
            }

            q_.put(_v);
        }

    };

    template<class _Fo=Task, class _ParentThread=ctk::SimpleThread>
    class SimpleTask : public TaskQueue<_Fo, _ParentThread>
    {
        typedef TaskQueue<_Fo, _ParentThread> _Super;

    public:
        SimpleTask(istr _name)
            : _Super(_name, 1, 1)
        {
        }

    };

}

#endif // _Z_CTK_MT_TASK_H_


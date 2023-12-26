#pragma once
#include <DawnNet/Concurrency/Job.hpp>
#include <DawnNet/Concurrency/LockQueue.hpp>
#include <DawnNet/Concurrency/JobTimer.hpp>

namespace DawnNet
{
    /*------------------
        JobQueue
    ------------------*/

    class JobQueue : public std::enable_shared_from_this<JobQueue>
    {
    public:
        void DoAsync(CallbackType&& callback)
        {
            Push(ObjectPool<Job>::MakeShared(std::move(callback)));
        }

        template<typename T, typename Ret, typename... Args>
        void DoAsync(Ret(T::*memFunc)(Args...), Args... args)
        {
            std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
            Push(ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...));
        }

        void DoTimer(uint64 tickAfter, CallbackType&& callback)
        {
            JobRef job = ObjectPool<Job>::MakeShared(std::move(callback));
            GJobTimer->Reserve(tickAfter, shared_from_this(), job);
        }

        template<typename T, typename Ret, typename... Args>
        void DoAsync(uint64 tickAfter, Ret(T::* memFunc)(Args...), Args... args)
        {
            std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
            JobRef job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...);
            GJobTimer->Reserve(tickAfter, shared_from_this(), job);
        }

        void				ClearJob() { _jobs.Clear(); }

    public:
        void				Push(JobRef job, bool pushOnly = false);
        void				Execute();

    protected:
        LockQueue<JobRef>	_jobs;
        Atomic<int32>		_jobCount = 0;
    };
}
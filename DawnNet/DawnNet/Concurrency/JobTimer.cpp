#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/JobTimer.hpp>
#include <DawnNet/Concurrency/JobQueue.hpp>

namespace DawnNet
{
    /*-------------------
        JobTimer
    -------------------*/

    void JobTimer::Reserve(uint64 tickAfter, std::weak_ptr<JobQueue> owner, JobRef job)
    {
        const uint64 executeTick = XGetTickCount64() + tickAfter;
        JobData* jobData = ObjectPool<JobData>::Pop(owner, job);

        WRITE_LOCK;

        _items.push(TimerItem{ executeTick, jobData });
    }

    void JobTimer::Distribute(uint64 now)
    {
        // 한번에 1 쓰레드만 통과
        if (_distributing.exchange(true) == true)
            return;

        Vector<TimerItem> items;

        {
            WRITE_LOCK;

            while (_items.empty() == false)
            {
                const TimerItem& timerItem = _items.top();
                if (now < timerItem.executeTick)
                    break;

                items.push_back(timerItem);
                _items.pop();
            }
        }

        for (TimerItem& item : items)
        {
            if (JobQueueRef owner = item.jobData->owner.lock())
                owner->Push(item.jobData->job);

            ObjectPool<JobData>::Push(item.jobData);
        }

        // 끝났으면 붙여준다.
        _distributing.store(false);
    }

    void JobTimer::Clear()
    {
        WRITE_LOCK;

        while (_items.empty() == false)
        {
            const TimerItem& timerItem = _items.top();
            ObjectPool<JobData>::Push(timerItem.jobData);
            _items.pop();
        }
    }
}
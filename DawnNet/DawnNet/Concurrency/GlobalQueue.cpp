
#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/GlobalQueue.hpp>

namespace DawnNet
{
    /*------------------
        GlobalQueue
    ------------------*/

    GlobalQueue::GlobalQueue()
    {
    }

    GlobalQueue::~GlobalQueue()
    {
    }

    void GlobalQueue::Push(JobQueueRef jobQueue)
    {
        _jobQueues.Push(jobQueue);
    }

    JobQueueRef GlobalQueue::Pop()
    {
        return _jobQueues.Pop();
    }
}
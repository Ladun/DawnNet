
#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>
#include <DawnNet/Core/TLS.hpp>
#include <DawnNet/Core/Global.hpp>
#include <DawnNet/Concurrency/GlobalQueue.hpp>


namespace DawnNet
{

    /*------------------
        ThreadManager
    -------------------*/

    ThreadManager::ThreadManager()
    {
        // Main Thread
        InitTLS();
    }

    ThreadManager::~ThreadManager()
    {
        Join();
    }

    void ThreadManager::Launch(std::function<void(void)> callback)
    {
        LockGuard guard(_lock);

        _threads.push_back(std::thread([=]()
        {
            InitTLS();
            callback();
            DestroyTLS();
        }));
    }

    void ThreadManager::Join()
    {
        for (std::thread& t : _threads)
        {
            if (t.joinable())
                t.join();
        }

        _threads.clear();
    }

    void ThreadManager::InitTLS()
    {
        static Atomic<uint32> SThreadId = 1;
        LThreadId = SThreadId.fetch_add(1);
    }

    void ThreadManager::DestroyTLS()
    {
        std::cout << "DestoryTLS\n";
    }

    void ThreadManager::DoGlobalQueueWork()
    {
        while (true)
        {
            uint64 now = XGetTickCount64();
            if (now > LEndTickCount)
                break;

            JobQueueRef jobQueue = GGlobalQueue->Pop();
            if (jobQueue == nullptr)
                break;
            
            jobQueue->Execute();
        }
    }

    void ThreadManager::DistributeReservedJob()
    {
        const uint64 now = XGetTickCount64();

        GJobTimer->Distribute(now);
    }
    
    
} // namespace DawnNet
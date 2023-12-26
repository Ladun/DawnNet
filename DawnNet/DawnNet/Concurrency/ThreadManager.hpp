#pragma once

#include <thread>
#include <functional>

/*------------------
	ThreadManager
-------------------*/

namespace DawnNet
{
    class ThreadManager
    {
    public:
        ThreadManager();
        ~ThreadManager();

        void	Launch(std::function<void(void)> callback);
        void	Join();

        static void InitTLS();
        static void DestroyTLS();

        static void DoGlobalQueueWork();
        static void DistributeReservedJob();

    private:
        Mutex			    _lock;
        Vector<std::thread>	_threads;
    };
}
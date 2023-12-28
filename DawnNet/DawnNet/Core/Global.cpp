#include <DawnNet/pch.hpp>
#include <DawnNet/Core/Global.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>
#include <DawnNet/Concurrency/GlobalQueue.hpp>
#include <DawnNet/Concurrency/JobTimer.hpp>
#include <DawnNet/Memory/Memory.hpp>
#include <DawnNet/Buffer/SendBuffer.hpp>

namespace DawnNet
{
    ThreadManager*		GThreadManager = nullptr;
    Memory*				GMemory = nullptr;
    SendBufferManager*	GSendBufferManager = nullptr;
    GlobalQueue*		GGlobalQueue = nullptr;
    JobTimer*			GJobTimer = nullptr;

    class CoreGlobal
    {
    public:
        CoreGlobal()
        {
            GThreadManager = new ThreadManager();
            GMemory = new Memory();
            GSendBufferManager = new SendBufferManager();
            GGlobalQueue = new GlobalQueue();
            GJobTimer = new JobTimer();
        }

        ~CoreGlobal()
        {
            delete GThreadManager;
            delete GSendBufferManager;
            delete GGlobalQueue;
            delete GJobTimer;
            delete GMemory;
        }
    } GCoreGlobal;
}
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

    

    /*----------------
            Tick Count
    ------------------*/
    tick32_t XGetTickCount()
    {
        tick32_t tick = 0ul;
    
    #if defined(DN_PLATFORM_WINDOWS)
        tick = GetTickCount();
    #else
        struct timespec tp;
    
        clock_gettime(CLOCK_MONOTONIC, &tp);
    
        tick = (tp.tv_sec*1000ul) + (tp.tv_nsec/1000ul/1000ul);
    #endif
    
        return tick;
    }
    
    tick64_t XGetTickCount64()
    {
        tick64_t tick = 0ull;
    
    #if defined(DN_PLATFORM_WINDOWS)
        tick = GetTickCount64();
    #else
        struct timespec tp;
    
        clock_gettime(CLOCK_MONOTONIC, &tp);
    
        tick = (tp.tv_sec*1000ull) + (tp.tv_nsec/1000ull/1000ull);
    #endif
    
        return tick;
    }
}
#pragma once

namespace DawnNet
{
    extern class ThreadManager*		GThreadManager;
    extern class Memory*			GMemory;
    extern class SendBufferManager*	GSendBufferManager;
    extern class GlobalQueue*		GGlobalQueue;
    extern class JobTimer*			GJobTimer;

    // extern class DeadLockProfiler*	GDeadLockProfiler;
    // extern class DBConnectionPool*	GDBConnectionPool;
    // extern class ConsoleLog* GConsoleLogger;

 
    typedef unsigned long long int tick64_t;
    typedef unsigned long int tick32_t;
    
    tick32_t XGetTickCount();    
    tick64_t XGetTickCount64();
}
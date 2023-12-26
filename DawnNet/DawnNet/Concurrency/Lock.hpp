#pragma once

// TODO: Move to global header
#include <atomic>


namespace DawnNet
{
    /*---------------
        RW SpinLock
    ----------------*/

    /*--------------------------------------------
    [\\\\\\\\][\\\\\\\\][RRRRRRRR][RRRRRRRR]
    W : WriteFlag (Exclusive Lock Owner ThreadId)
    R : ReadFlag (Shared Lock Count)
    ---------------------------------------------*/


    // W -> R (o)
    // R -> W (x)

    class Lock
    {
        enum : uint32_t
        {
            ACQUIRE_TIMEOUT_TICK = 10000,
            MAX_SPIN_COUNT = 5000,
            WRITE_THREAD_MASK = 0xFFFF'0000,
            READ_COUNT_MASK = 0x0000'FFFF,
            EMPTY_FLAG = 0x0000'0000
        };

    public:
        void WriteLock(const char* name);
        void WriteUnlock(const char* name);
        void ReadLock(const char* name);
        void ReadUnlock(const char* name);

    private:
        std::atomic<uint32_t> _lockFlag = EMPTY_FLAG;
        uint16_t _writeCount = 0;
    };

    /*------------------------------
            Lock Guards
    ------------------------------*/

    class ReadLockGuard
    {
    public:
        ReadLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.ReadLock(name); }
        ~ReadLockGuard(){_lock.ReadUnlock(_name);}

    private:
        Lock& _lock;
        const char* _name;
    };

    class WriteLockGuard
    {
    public:
        WriteLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.WriteLock(name); }
        ~WriteLockGuard() { _lock.WriteUnlock(_name); }

    private:
        Lock& _lock;
        const char* _name;
    };
}
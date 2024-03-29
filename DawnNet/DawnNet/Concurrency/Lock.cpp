#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/Lock.hpp>
#include <DawnNet/Core/TLS.hpp>

namespace DawnNet
{
    void Lock::WriteLock(const char* name)
    {
        
        const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
        if(LThreadId == lockThreadId)
        {
            _writeCount++;
            return;
        }

        const int64 beginTick = XGetTickCount64();
        const uint32 desired = ((LThreadId << 16) & WRITE_THREAD_MASK);
        while(true)
        {
            for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
            {
                uint32 expected = EMPTY_FLAG;
                if (_lockFlag.compare_exchange_strong(OUT expected, desired))
                {
                    _writeCount++;
                    return;
                }
            }

            if(XGetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK )
            {
                std::cout << "LOCK_TIMEOUT " << LThreadId << '\n';
                DN_DEBUGBREAK();
            }
 
            std::this_thread::yield();
        }
    }
    
    void Lock::WriteUnlock(const char* name)
    {
        // ReadLock 을 풀기 전에는 WriteUnlock 불가능
        
        if((_lockFlag.load() & READ_COUNT_MASK) != 0 )
        {
            std::cout << "INVALID_UNLOCK_ORDER\n";
            DN_DEBUGBREAK();
        }      

        const int32 lockCount = --_writeCount;
        if (lockCount == 0)
            _lockFlag.store(EMPTY_FLAG);
    }

    void Lock::ReadLock(const char* name)
    {
        const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
        if (LThreadId == lockThreadId)
        {
            _lockFlag.fetch_add(1);
            return;
        }

        // 아무도 락을 소유하고 있지 않을 때 경합해서 공유 카운트를 올린다.
        const int64 beginTick = XGetTickCount64();
        while (true)
        {
            for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
            {
                uint32 expected = (_lockFlag.load() & READ_COUNT_MASK);
                if (_lockFlag.compare_exchange_strong(OUT expected, expected + 1))
                    return;
            }

            if(XGetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK )
            {
                std::cout << "LOCK_TIMEOUT " << LThreadId << '\n';
                DN_DEBUGBREAK();
            }

            std::this_thread::yield();
        }
    }

    void Lock::ReadUnlock(const char* name)
    {
        if((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
        {
            std::cout << "Multiple unlock\n";
            DN_DEBUGBREAK();
        }
    
    }
} // namespace DawnNet

#include <DawnNet/Core/Func.hpp>

namespace DawnNet
{

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
} // namespace DawnNet

#pragma once
#include <stack>
#include <cstdint>

namespace DawnNet
{
    extern thread_local uint32_t            LThreadId;
    extern thread_local uint64_t            LEndTickCount;


    extern thread_local std::stack<int32_t>	LLockStack;
    extern thread_local SendBufferChunkRef	LSendBufferChunk;
    // extern thread_local class JobQueue*		LCurrentJobQueue;
}
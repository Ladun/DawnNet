#include "LockFreeStack.hpp"

namespace DawnNet
{
    // void InitializeHead(SListHeader *header)
    // {
    //     header->alignment = 0;
    //     header->region = 0;
    // }

    // void PushEntrySList(SListHeader *header, SListEntry *entry)
    // {
    //     SListHeader expected = {};
    //     SListHeader desired = {};
        
    //     // 16 바이트 정렬
    //     desired.HeaderX64.next = (((uint64)entry) >> 4);

    //     while (true)
    //     {
    //         expected = *header;

    //         // 이 사이에 변경될 수 있다

    //         entry->next = (SListEntry*)(((uint64)expected.HeaderX64.next) << 4);
    //         desired.HeaderX64.depth = expected.HeaderX64.depth + 1;
    //         desired.HeaderX64.sequence = expected.HeaderX64.sequence + 1;

    //         if (::InterlockedCompareExchange128((int64*)header, desired.region, desired.alignment, (int64*)&expected) == 1)
    //             break;
    //     }
    // }

    // SListEntry *PopEntrySList(SListHeader *header)
    // {
    //     return nullptr;
    // }

} // namespace DawnNet

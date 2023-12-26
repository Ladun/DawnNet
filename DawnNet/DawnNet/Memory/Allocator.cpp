#include <DawnNet/pch.hpp>
#include <DawnNet/Memory/Allocator.hpp>
// #include "Memory.h"

namespace DawnNet
{
	void* BaseAllocator::Alloc(int32 size)
	{
		return ::malloc(size);
	}

	void BaseAllocator::Release(void* ptr)
	{
		::free(ptr);
	}

	/*-------------------------
			StompAllocator
	--------------------------*/

	void* StompAllocator::Alloc(int32 size)
	{
		const int64 pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;
		const int64 dataOffset = pageCount * PAGE_SIZE - size;
	#if defined(DN_PLATFORM_WINDOWS)
		void* baseAddress = ::VirtualAlloc(NULL, pageCount * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	#elif defined(DN_PLATFORM_LINUX)
		void* baseAddress = mmap(0, pageCount * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	#endif
		return static_cast<void*>(static_cast<int8*>(baseAddress) + dataOffset);
	}

	void StompAllocator::Release(void* ptr)
	{
		const int64 address = reinterpret_cast<int64>(ptr);
		const int64 baseAddress = address - (address % PAGE_SIZE);
	#if defined(DN_PLATFORM_WINDOWS)
		::VirtualFree(reinterpret_cast<void*>(baseAddress), 0, MEM_RELEASE);
	#elif defined(DN_PLATFORM_LINUX)
		const int64 pageCount = (address - baseAddress) / PAGE_SIZE + 1;
		munmap(reinterpret_cast<void*>(baseAddress), pageCount * PAGE_SIZE);
	#endif
	}

	/*-------------------------
			PoolAllocator
	--------------------------*/

	void* PoolAllocator::Alloc(int32 size)
	{
		return GMemory->Allocate(size);
	}

	void PoolAllocator::Release(void* ptr)
	{
		GMemory->Release(ptr);
	}
}
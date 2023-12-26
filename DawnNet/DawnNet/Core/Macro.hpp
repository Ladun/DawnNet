#pragma once

#define OUT
#define DN_PLATFORM_LINUX

#if defined(DN_PLATFORM_WINDOWS) 
#include <windows.h>
#else
#include <time.h>
#endif

/*----------------
		Func
------------------*/
#if defined(DN_PLATFORM_WINDOWS)
#define ALIGNED_MALLOC(size, alignment)	::_aligned_malloc(size, alignment)
#define ALIGNED_FREE(ptr) 				::_aligned_free(ptr)
#define ALIGNED_(x) __declspec(align(x))
#elif defined(DN_PLATFORM_LINUX)
#define ALIGNED_MALLOC(size, alignment) aligned_alloc(alignment, size)
#define ALIGNED_FREE(ptr)				free(ptr);
#define ALIGNED_(x) __attribute__ ((aligned(x)))
#endif


/*----------------
		Lock
------------------*/

#define USE_MANY_LOCKS(count)	Lock _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx], typeid(this).name());
#define READ_LOCK				READ_LOCK_IDX(0)
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx], typeid(this).name());
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

/*----------------
		Crash
------------------*/

#ifdef DN_DEBUG
	#if defined(DN_PLATFORM_WINDOWS)
		#define DN_DEBUGBREAK() std::cout << "raise!\n"; __debugbreak()
	#elif defined(DN_PLATFORM_LINUX)
		#include <signal.h>
		#define DN_DEBUGBREAK() std::cout << "raise!\n"; raise(SIGTRAP); 
	#endif
	#define DN_ENALBE_ASSERTS
#else
	#define DN_DEBUGBREAK()
#endif

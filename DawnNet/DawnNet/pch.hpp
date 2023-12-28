#pragma once

/* -------------
    standard include
---------------- */

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <functional>


/* -------------
    boost lib include
---------------- */

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/bind/bind.hpp>


/* -------------
    custom include
---------------- */

#include <DawnNet/Core/Types.hpp>
#include <DawnNet/Core/Error.hpp>
#include <DawnNet/Core/Func.hpp>
#include <DawnNet/Core/Global.hpp>
#include <DawnNet/Core/TLS.hpp>
#include <DawnNet/Core/Macro.hpp>
#include <DawnNet/Core/Container.hpp>

#if defined(DN_PLATFORM_WINDOWS)

#elif defined(DN_PLATFORM_LINUX)
#include <sys/mman.h>
#endif

#include <DawnNet/Concurrency/Lock.hpp>
#include <DawnNet/Memory/ObjectPool.hpp>
#include <DawnNet/Memory/Memory.hpp>
#include <DawnNet/Buffer/SendBuffer.hpp>
#include <DawnNet/Concurrency/JobQueue.hpp>

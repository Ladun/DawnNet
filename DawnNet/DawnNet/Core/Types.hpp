
#pragma once
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <boost/asio.hpp>

namespace DawnNet
{
    // Default data types
    using BYTE = unsigned char;
    using int8 = int32_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;
    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;
    using ErrCode = std::size_t;

    // Stl
    template<typename T>
    using Atomic = std::atomic<T>;
    using Mutex = std::mutex;
    using CondVar = std::condition_variable;
    using UniqueLock = std::unique_lock<std::mutex>;
    using LockGuard = std::lock_guard<std::mutex>;

    // Boost asio
	using SocketType = boost::asio::ip::tcp::socket;	
	using ResolverType = boost::asio::ip::tcp::resolver;
	using AcceptorType = boost::asio::ip::tcp::acceptor;
	using EndpointType = boost::asio::ip::tcp::endpoint;

    #define USING_SHARED_PTR(name) using name##Ref = std::shared_ptr<class name>;
    
    USING_SHARED_PTR(Session);
    USING_SHARED_PTR(PacketSession);
    USING_SHARED_PTR(Listener);
    USING_SHARED_PTR(ServerService);
    USING_SHARED_PTR(ClientService);
    USING_SHARED_PTR(SendBuffer);
    USING_SHARED_PTR(SendBufferChunk);
    USING_SHARED_PTR(Job);
    USING_SHARED_PTR(JobQueue);

} // namespace DawnNet

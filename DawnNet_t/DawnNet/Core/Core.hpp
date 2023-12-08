#pragma once

#include <shared_mutex>
#include <mutex>

#include <boost/asio.hpp>

namespace DawnNet
{

	template<typename T> 
	class Singleton
	{
	protected:
		Singleton() = default;
		virtual ~Singleton() = default;
		Singleton(const Singleton&) = delete;
		void operator=(const Singleton&) = delete;
	public:
		static T& Instance()
		{
			static T singleton;
			return singleton;
		}
	};

	using ReadLock = std::shared_lock<std::shared_mutex>;
	using WriteLock = std::unique_lock<std::shared_mutex>;

	// Redefine types;
    using Size = unsigned short;
	using SocketType = boost::asio::ip::tcp::socket;	
	using ResolverType = boost::asio::ip::tcp::resolver;
	using AcceptorType = boost::asio::ip::tcp::acceptor;
	using EndpointType = boost::asio::ip::tcp::endpoint;

	#pragma region Constant
	constexpr Size eSzPacketMax		= 0x3FFF;	// 한 패킷당 최대 사이즈
	#pragma endregion

	/**
		@brief 에러코드 타입
	*/
    using ErrCode = std::size_t;

	
}
#pragma once

#include <boost/asio.hpp>

#include <DawnNet/Core.hpp>


namespace DawnNet
{ 
	class IOContext : public Singleton<IOContext>
    {
	public:
		IOContext();
		~IOContext();

		ErrCode Run();
		void	Stop();
		void	Restart();

		template<typename THandler>
		auto BindExecutor(THandler&& handler)
		{
			return boost::asio::bind_executor(_strand, handler);
		}
		template<typename THandler>
		void Post(THandler&& handler)
		{
			return _ioContext.post(_strand, handler);
		}

		boost::asio::io_context& GetIOContext() { return _ioContext; }

	private:
		boost::asio::io_context			    _ioContext;
		boost::asio::io_context::strand	    _strand;
		boost::asio::io_context::work	    _work;
    };
}
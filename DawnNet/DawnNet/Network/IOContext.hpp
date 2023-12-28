#pragma once

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
			return boost::asio::bind_executor(m_Strand, handler);
		}
		template<typename THandler>
		void Post(THandler&& handler)
		{
			return m_IOContext.post(m_Strand, handler);
		}

		boost::asio::io_context& GetIOContext() { return m_IOContext; }

	private:
		boost::asio::io_context			    m_IOContext;
		boost::asio::io_context::strand	    m_Strand;
		boost::asio::io_context::work	    m_Work;
    };
}
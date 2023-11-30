#include <DawnNet/IOContext.hpp>

namespace DawnNet
{

	IOContext::IOContext() : m_IOContext(), m_Strand(m_IOContext), m_Work(m_IOContext)
	{
	}

	IOContext::~IOContext()
	{
	}

	ErrCode IOContext::Run()
	{
		return m_IOContext.run();
	}

	void IOContext::Stop()
	{
		m_IOContext.stop();
	}

	void IOContext::Restart()
	{
		m_IOContext.restart();
	}
}
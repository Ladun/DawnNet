#include <DawnNet/pch.hpp>
#include <DawnNet/Network/IOContext.hpp>

namespace DawnNet
{

	IOContext::IOContext() : _ioContext(), _strand(_ioContext), _work(_ioContext)
	{
	}

	IOContext::~IOContext()
	{
	}

	ErrCode IOContext::Run()
	{
		return _ioContext.run();
	}

	void IOContext::Stop()
	{
		_ioContext.stop();
	}

	void IOContext::Restart()
	{
		_ioContext.restart();
	}
}
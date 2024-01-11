
#include <DawnNet/pch.hpp>
#include <DawnNet/Network/Listner.hpp>
#include <DawnNet/Network/IOContext.hpp>
#include <DawnNet/Network/Service.hpp>

namespace DawnNet
{

    Listner::Listner(const EndpointType& endpoint) 
        :   _acceptor(IOContext::Instance().GetIOContext(), endpoint)
    {
		_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    }

    Listner::~Listner()
    {
        
    }


    bool Listner::StartAccept(ServerServiceRef service)
    {        
        // 새로운 클라이언트의 연결을 받기 위해 비동기적으로 accept 작업을 수행합니다.
        SessionRef newSession = service->CreateSession();

        // TODO: 여러 가지 상태를 여기서 세팅하고 실패하면 false로 반환 
        // 예를 들어서 현재 socket이 listen 상태인지 등등
        
        _acceptor.async_accept(newSession->Socket(),
            [this, ser=service, newSession](boost::system::error_code ec)
            {
                if (!ec)
                {
                    // SessionPtr new_session = session_factory_(std::move(socket));
                    newSession->Start();
                }
                else{
                    std::cout << "Fail to accept, error: "<< ec.message() <<"\n";
                }

                // 다음 클라이언트의 연결을 기다립니다.
                StartAccept(ser);
            });

        return true;
    }

    ErrCode Listner::Close()
    {
		boost::system::error_code aError;
		_acceptor.close(aError);
		return aError.value();
    }
}
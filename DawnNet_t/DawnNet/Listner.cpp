
#include <DawnNet/pch.hpp>
#include <DawnNet/Listner.hpp>
#include <DawnNet/Session.hpp>
#include <DawnNet/IOContext.hpp>

#include <iostream>


namespace DawnNet
{

    Listner::Listner(std::function<SessionPtr(SocketType)> sessionFactory,
                       const EndpointType& endpoint) :
        m_SessionFactory(sessionFactory), m_Acceptor(IOContext::Instance().GetIOContext(), endpoint)
    {

		m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        StartAccept();
    }

    Listner::~Listner()
    {
        
    }


    void Listner::StartAccept()
    {        
        // 새로운 클라이언트의 연결을 받기 위해 비동기적으로 accept 작업을 수행합니다.

        SocketType socket(IOContext::Instance().GetIOContext());
        SessionPtr newSession = m_SessionFactory(std::move(socket));
        
        m_Acceptor.async_accept(newSession->Socket(),
            [this, session=newSession.get()](boost::system::error_code ec)
            {
                if (!ec)
                {
                    // SessionPtr new_session = session_factory_(std::move(socket));
                    session->Start();
                    session->OnConnected();
                }
                else{
                    std::cout << "Fail to accept, error: "<< ec.message() <<"\n";
                }

                // 다음 클라이언트의 연결을 기다립니다.
                StartAccept();
            });
    }

    ErrCode Listner::Close()
    {
		boost::system::error_code aError;
		m_Acceptor.close(aError);
		return aError.value();
    }
}
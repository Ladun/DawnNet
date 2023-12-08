
#include <DawnNet/pch.hpp>
#include <DawnNet/Connector.hpp>
#include <DawnNet/IOContext.hpp>
#include <DawnNet/Error.hpp>

namespace DawnNet
{
    Connector::Connector(std::function<SessionPtr(SocketType)> sessionFactory,
                         const std::string& host, 
                         const std::string& port):
        m_SessionFactory(sessionFactory), 
        m_Resolver(IOContext::Instance().GetIOContext()), 
        m_Host(host), m_Port(port), m_Session()
    {

    }

    Connector::~Connector()
    {
    }

    ErrCode Connector::Connect()
    {        
        SocketType socket(IOContext::Instance().GetIOContext());

        ResolverType::iterator endpoint_iterator = m_Resolver.resolve(m_Host, m_Port);
        ResolverType::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        
        while(error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if(error)
            return eErrCodeHostNotFound;

        m_Session = m_SessionFactory(std::move(socket));
        m_Session->Start();
        m_Session->OnConnected();
        
        return 0;
    }
}
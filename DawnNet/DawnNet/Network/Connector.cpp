
#include <DawnNet/pch.hpp>
#include <DawnNet/Network/Connector.hpp>
#include <DawnNet/Network/IOContext.hpp>

namespace DawnNet
{
    Connector::Connector(std::function<SessionRef(SocketType)> sessionFactory,
                         const std::string& host, 
                         const std::string& port):
        _sessionFactory(sessionFactory), 
        _resolver(IOContext::Instance().GetIOContext()), 
        _host(host), _port(port), _session(nullptr)
    {

    }

    Connector::~Connector()
    {
    }

    ErrCode Connector::Connect()
    {        
        SocketType socket(IOContext::Instance().GetIOContext());

        ResolverType::iterator endpoint_iterator = _resolver.resolve(_host, _port);
        ResolverType::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        
        while(error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if(error)
            return ErrCodeHostNotFound;

        _session = _sessionFactory(std::move(socket));
        _session->Start();
        
        return 0;
    }
}

#include <DawnNet/pch.hpp>
#include <DawnNet/Network/Connector.hpp>
#include <DawnNet/Network/IOContext.hpp>
#include <DawnNet/Network/Service.hpp>

namespace DawnNet
{
    Connector::Connector(const std::string& host, 
                         const std::string& port):
        _resolver(IOContext::Instance().GetIOContext()), 
        _host(host), _port(port), _session(nullptr)
    {

    }

    Connector::~Connector()
    {
    }

    bool Connector::Connect(ClientServiceRef& service)
    {
        _session = service->CreateSession();

        ResolverType::iterator endpoint_iterator = _resolver.resolve(_host, _port);
        ResolverType::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        
        while(error && endpoint_iterator != end)
        {
            _session->Socket().close();
            _session->Socket().connect(*endpoint_iterator++, error);
        }
        if(error)
            return false;

        _session->Start();
        
        return true;
    }
}
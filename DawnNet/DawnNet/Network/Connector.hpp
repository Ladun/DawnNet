#pragma once

#include <DawnNet/Network/Session.hpp>
#include <cstring>

class ClientService;

namespace DawnNet
{
    class Connector
    {
    public:
        Connector(const std::string& host, 
                  const std::string& port);
        ~Connector();

        bool Connect(ClientServiceRef& service);

        Session* GetSession() const{
            return _session.get();
        }
    
    private:
        SessionRef _session;

        std::string _host;
        std::string _port;
        ResolverType _resolver;
    };
}
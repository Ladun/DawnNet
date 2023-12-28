#pragma once

#include <DawnNet/Network/Session.hpp>
#include <cstring>

namespace DawnNet
{
    class Connector
    {
    public:
        Connector(std::function<SessionRef(SocketType)> sessionFactory,
                  const std::string& host, 
                  const std::string& port);
        ~Connector();

        ErrCode Connect();

        Session* GetSession() const{
            return _session.get();
        }
    
    private:
        std::function<SessionRef(SocketType)> _sessionFactory;

        SessionRef _session;

        std::string _host;
        std::string _port;
        ResolverType _resolver;
    };
}
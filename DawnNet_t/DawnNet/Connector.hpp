#pragma once

#include <DawnNet/Core.hpp>
#include <DawnNet/Session.hpp>
#include <cstring>

namespace DawnNet
{
    class Connector
    {
    public:
        Connector(std::function<SessionPtr(SocketType)> sessionFactory,
                  const std::string& host, 
                  const std::string& port);
        ~Connector();

        ErrCode Connect();

        Session* GetSession() const{
            return m_Session.get();
        }
    
    private:
        std::function<SessionPtr(SocketType)> m_SessionFactory;

        SessionPtr m_Session;

        std::string m_Host;
        std::string m_Port;
        ResolverType m_Resolver;
    };
}
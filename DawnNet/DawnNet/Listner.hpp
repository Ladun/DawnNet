#pragma once

#include <functional>
#include <DawnNet/Session.hpp>


namespace DawnNet
{
    class Listner
    {
    public:
        Listner(std::function<SessionPtr(SocketType)> sessionFactory,
                 const EndpointType& endpoint);
        ~Listner();
        
        void StartAccept();
        ErrCode Close();


    private:
        std::function<SessionPtr(SocketType)> m_SessionFactory;
        AcceptorType m_Acceptor;

    };
}
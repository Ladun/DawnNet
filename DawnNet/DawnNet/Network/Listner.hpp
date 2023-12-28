#pragma once

#include <functional>
#include <DawnNet/Network/Session.hpp>


namespace DawnNet
{
    class Listner
    {
    public:
        Listner(std::function<SessionRef(SocketType)> sessionFactory,
                const EndpointType& endpoint);
        ~Listner();
        
        void StartAccept();
        ErrCode Close();


    private:
        std::function<SessionRef(SocketType)> _sessionFactory;
        AcceptorType _acceptor;

    };
}
#pragma once

#include <functional>
#include <DawnNet/Network/Session.hpp>

class ServerService;
 
namespace DawnNet
{
    class Listner
    {
    public:
        Listner(const EndpointType& endpoint);
        ~Listner();
        
        bool StartAccept(ServerServiceRef service);
        ErrCode Close();


    private:
        AcceptorType _acceptor;

    };
}
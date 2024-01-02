#pragma once

#include <DawnNet/DawnNet.hpp>

#include "../server.hpp"

namespace ld_server
{
    class ClientSession: public DawnNet::Session
    {
    public:
        ClientSession(DawnNet::SocketType socket, Server* server);
        ~ClientSession();

        void OnConnected() override;
        void OnSend(std::size_t sendSize) override;
        void OnDisconnected() override;


    private:
        Server* server_;
    };
}
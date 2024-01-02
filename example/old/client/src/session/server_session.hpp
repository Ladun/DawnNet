#pragma once

#include <DawnNet/DawnNet.hpp>
#include "../client.hpp"

namespace ld_client
{
    class ServerSession: public DawnNet::Session
    {
    public:
        ServerSession(DawnNet::SocketType socket, Client* client);
        ~ServerSession();

        void OnConnected() override;
        void OnSend(std::size_t sendSize) override;
        void OnDisconnected() override;

    private:
        Client* client_;
    };
}
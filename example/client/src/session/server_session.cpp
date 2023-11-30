
#include <iostream>

#include "server_session.hpp"

namespace ld_client
{
    ServerSession::ServerSession(DawnNet::SocketType socket, Client* client)
        : Session(std::move(socket)), client_(client)
    {

    }

    ServerSession::~ServerSession()
    {

    }

    void ServerSession::OnConnected()
    {
        std::cout << "Connect to " << m_Socket.remote_endpoint().address().to_string() << " \n";

    }
    void ServerSession::OnSend(std::size_t sendSize)
    {
        // std::cout << "Send size: " << sendSize << '\n';
    }
    
    void ServerSession::OnDisconnected() 
    {
        std::cout << "disconnected\n";

        client_->close();
    }
}
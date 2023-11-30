
#include <iostream>

#include "client_session.hpp"


namespace ld_server
{
    ClientSession::ClientSession(DawnNet::SocketType socket, Server* server)
        : Session(std::move(socket)), server_(server)
    {

    }

    ClientSession::~ClientSession()
    {

    }


    void ClientSession::OnConnected()
    {
        std::cout << m_Socket.remote_endpoint().address().to_string() << " connected\n";
    }

    void ClientSession::OnSend(std::size_t sendSize)
    {
        // std::cout << "Send size: " << sendSize << '\n';

    }
    void ClientSession::OnDisconnected() 
    {
        std::cout << "disconnected\n";

        server_->close();

    }
}
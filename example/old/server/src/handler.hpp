#pragma once

#include <iostream>

#include <DawnNet/DawnNet.hpp>
#include <custom_packet.hpp>

#include "session/client_session.hpp"
#include "server.hpp"



namespace ld_server
{

    DawnNet::ErrCode ChatPacketHandler(DawnNet::PacketHeader* header, DawnNet::Size pSize, DawnNet::Session* session, Server* server)
    {   
        auto packet = reinterpret_cast<net_packet::ChatPacket*>(header);

        // std::cout << "Packet ptr: " << packet << ", ";
        // std::cout << "Receive size: " << pSize << ", ";
        // std::cout << "Session ptr: " << session << ", ";
        // std::cout << "Server ptr: " << server << "\n";

        std::cout << "Receive [" << packet->nickname.data() <<"]:";
        std::cout << packet->message.data() <<"\n"; 

        server->broadcast(*packet, sizeof(*packet));
        return 0;
    }
}
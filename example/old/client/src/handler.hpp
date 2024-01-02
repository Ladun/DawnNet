#pragma once

#include <DawnNet/DawnNet.hpp>
#include "session/server_session.hpp"
#include "custom_packet.hpp"

namespace ld_client
{

    DawnNet::ErrCode ChatPacketHandler(DawnNet::PacketHeader* header, DawnNet::Size size, DawnNet::Session* session)
    {
        auto packet = reinterpret_cast<net_packet::ChatPacket*>(header);
        // auto ssession = reinterpret_cast<ServerSession*>(session);

        std::cout << "[" << packet->nickname.data() <<"]:";
        std::cout << packet->message.data() <<"\n";

        return 0;
    }
}
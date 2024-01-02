#pragma once

#include <DawnNet/DawnNet.hpp>

namespace net_packet
{
    enum class PacketCode: DawnNet::MessageNo
    {
        CHAT
    };

    class ChatPacket : public DawnNet::PacketHeader
    {
    public:
        ChatPacket() = default;
        ~ChatPacket() = default;

    public:
        std::array<char, 30> nickname;
        std::array<char, 992> message;
    };
}
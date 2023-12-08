#pragma once 

#include <DawnNet/Core.hpp>



namespace DawnNet
{
    using MessageNo = unsigned short;

    #pragma pack(push, 1)
    class PacketHeader
    {
    public:
        MessageNo _message{};        
    };
    #pragma pack(pop)

    // Packet header size
    constexpr Size ePacketHeaderSize = sizeof(PacketHeader);
}
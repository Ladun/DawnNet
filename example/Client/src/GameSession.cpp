#include <DawnNet/pch.hpp>
#include "GameSession.hpp"
#include "ServerPacketHandler.hpp"

void GameSession::OnConnected()
{
    // Protocol::C_LOGIN pkt;
    // auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
    // Send(sendBuffer);

    std::cout << "Connect to " << Socket().remote_endpoint().address().to_string() << " \n";

}

void GameSession::OnDisconnected()
{

    std::cout << "disconnected\n";
}

void GameSession::OnRecvPacket(BYTE *buffer, int32 len)
{
    DawnNet::PacketSessionRef session = GetPacketSessionRef();
    DawnNet::PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    ServerPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{
}

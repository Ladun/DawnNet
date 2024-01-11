#include <DawnNet/pch.hpp>
#include "GameSession.hpp"
#include "SessionManager.hpp"
#include "ClientPacketHandler.hpp"

void GameSession::OnConnected()
{
    SessionManager::Instance().Add(std::static_pointer_cast<GameSession>(shared_from_this()));
    std::cout << Socket().remote_endpoint().address().to_string() << " connected\n";
}

void GameSession::OnDisconnected()
{
    SessionManager::Instance().Remove(std::static_pointer_cast<GameSession>(shared_from_this()));
    std::cout << "disconnected\n";
}

void GameSession::OnRecvPacket(BYTE *buffer, int32 len)
{
    PacketSessionRef session = GetPacketSessionRef();
    DawnNet::PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    
    ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{
}

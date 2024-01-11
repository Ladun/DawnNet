
#include <DawnNet/pch.hpp>
#include "ClientPacketHandler.hpp"
#include "GameSession.hpp"
#include "SessionManager.hpp"

namespace DawnNet
{

	PacketHandlerFunc GPacketHandler[UINT16_MAX];

	// 직접 컨텐츠 작업자

	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		return false;
	}

	bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
	{
		
		return true;
	}

	bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
	{
		std::cout << pkt.nickname() << ": " << pkt.msg() << std::endl;

		Protocol::S_CHAT chatPkt;
		chatPkt.set_nickname(pkt.nickname());
		chatPkt.set_msg(pkt.msg());
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);

		SessionManager::Instance().BroadCast(sendBuffer);

		return true;
	}
}
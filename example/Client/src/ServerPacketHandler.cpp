#include <DawnNet/pch.hpp>
#include "ServerPacketHandler.hpp"

namespace DawnNet
{
	PacketHandlerFunc GPacketHandler[UINT16_MAX];

	// 직접 컨텐츠 작업자

	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		return false;
	}

	bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
	{
		return true;
	}

	bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
	{
		std::cout << pkt.nickname() << ": " << pkt.msg() << std::endl;
		return true;
	}
}
#include <iostream>
#include <memory>

#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>
#include <DawnNet/Network/Service.hpp>
#include <DawnNet/Network/IOContext.hpp>

#include "GameSession.hpp"
#include "ServerPacketHandler.hpp"

#include "Packet/Protocol.pb.h"


int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cerr << "Usage: client <nickname> <host> <port>\n";
        return 1;
    }

    ServerPacketHandler::Init();

    auto service = MakeShared<DawnNet::ClientService>(
        MakeShared<GameSession>,
        argv[2], argv[3]
    );

    if(!service->Start())
    {
        std::cerr << "service start error\n";
        return 1;
    }
    std::cout << "Client Start\n";


    for(int i = 0; i < 1; i++)
    {
        DawnNet::GThreadManager->Launch([](){

            // 원래는 ThreadManager로 관리를 해야 하지만, 
            // boost asio에서는 알아서 관리해주기 때문에 RUN만 함.

            DawnNet::IOContext::Instance().Run();
        });
    }

    Protocol::C_CHAT chatPkt;
    chatPkt.set_msg(std::string("Hello World!"));
    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);

    service->Broadcast(sendBuffer);      
    
    DawnNet::GThreadManager->Join();       
    std::cout << "Client End\n";
}
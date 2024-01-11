#include <iostream>
#include <memory>

#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>
#include <DawnNet/Network/Service.hpp>
#include <DawnNet/Network/Session.hpp>
#include <DawnNet/Network/IOContext.hpp>

#include "GameSession.hpp"
#include "ClientPacketHandler.hpp"

enum 
{
    WORKER_TICK=64
};


int main(int argc, char* argv[])
{

    ClientPacketHandler::Init();

    auto service = MakeShared<DawnNet::ServerService>(
        MakeShared<GameSession>,
        DawnNet::EndpointType(boost::asio::ip::tcp::v4(), 8888)
    );

    if(!service->Start())
    {
        std::cerr << "service start error\n";
        return 1;
    }
    std::cout << "Server Start\n";

    for(int i = 0; i < 4; i++)
    {
        DawnNet::GThreadManager->Launch([](){

            // 원래는 ThreadManager로 관리를 해야 하지만, 
            // boost asio에서는 알아서 관리해주기 때문에 RUN만 함.

            DawnNet::IOContext::Instance().Run();
        });
    }

    while(true)
    {

    }
    
    DawnNet::GThreadManager->Join();     
    std::cout << "Server End\n";
}
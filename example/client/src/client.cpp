
#include <iostream>

#include "client.hpp"
#include "handler.hpp"
#include "session/server_session.hpp"

#include "custom_packet.hpp"

namespace ld_client
{
    Client::Client(const std::string& nickname,
                     const std::string& host,
                     const std::string& port)
        :  connector_(
            [this](DawnNet::SocketType socket) -> DawnNet::SessionPtr
            {
                return std::make_shared<ServerSession>(std::move(socket), this);
            },
            host, port), nickname_(nickname), state_(State::NOT_INITIALIZED)
    {    
    }

    Client::~Client()
    {
        
    }

    DawnNet::ErrCode Client::init()
    {
        // add handler;
        
        DawnNet::MessageHandler::Instance().RegisterHandler(
            static_cast<DawnNet::MessageNo>(net_packet::PacketCode::CHAT),
            &ChatPacketHandler);

        state_ = State::INITIALIZED;
        return 0;
    }

    DawnNet::ErrCode Client::connect_and_run()
    {
        if(state_ == State::NOT_INITIALIZED)
            return eErrCodeNoInitialize;
            
        DawnNet::ErrCode err = connector_.Connect();
        if(err)
            return err;

        state_ = State::RUNNING;
        // Run io_context -> run program
        thread_ = std::thread{std::bind(&Client::__io_context_run, this)};
        
        // Custom update
        std::array<char, 992> msg;
        net_packet::ChatPacket packet{};
        memcpy(packet.nickname.data(), nickname_.data(), sizeof(nickname_.data()));
        while(true)
        {
            memset(msg.data(), '\0', msg.size());
            if(!std::cin.getline(msg.data(), 1024 - nickname_.size() - sizeof(DawnNet::PacketHeader)))
            {
                std::cin.clear();
            }

            if(state_ != State::RUNNING)
                break;

            memcpy(packet.message.data(), msg.data(), msg.size());
            
            connector_.GetSession()->Send(packet, sizeof(packet));            
        }
        thread_.join();

        return 0;
    }

    DawnNet::ErrCode Client::close()
    {
        
        DawnNet::IOContext::Instance().Stop();

        state_ = State::CLOSED;
        return 0;
    }

    void Client::__io_context_run()
    {
        try
        {
            DawnNet::IOContext::Instance().Run();
        } catch(std::exception& exception)
        {
            // TODO: log error;
        }
    }
}
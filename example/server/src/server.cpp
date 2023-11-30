

#include "server.hpp"
#include "handler.hpp"
#include "session/session_manager.hpp"

#include "custom_packet.hpp"


namespace ld_server
{
    Server::Server(int port)
        : listner_(
            [this](DawnNet::SocketType socket) -> DawnNet::SessionPtr
            {
                return SessionManager::Instance().generate(std::move(socket), this);
            }, DawnNet::EndpointType(boost::asio::ip::tcp::v4(), port)),
          thread_cnt_(0), is_init_(false)
    {
        thread_cnt_ = std::thread::hardware_concurrency() * 2;
    }

    Server::~Server()
    {
        
    }

    DawnNet::ErrCode Server::init()
    {

        // add handler;
        
        DawnNet::MessageHandler::Instance().RegisterHandler(
            static_cast<DawnNet::MessageNo>(net_packet::PacketCode::CHAT),
            std::bind(&ChatPacketHandler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, this));

        is_init_ = true;
        return 0;
    }

    DawnNet::ErrCode Server::run()
    {
        if(!is_init_)
            return eErrCodeNoInitialize;

        for (unsigned int index = 0; index < thread_cnt_; ++index)
        {
            thread_list_.emplace_back(std::thread{std::bind(&Server::__io_context_run, this)});

        }

        // Server loop add;


        for(auto& aThread: thread_list_)
        {
            aThread.join();
        }

        return 0;
    }

    DawnNet::ErrCode Server::close()
    {
        listner_.Close();

        DawnNet::IOContext::Instance().Stop();
        return 0;
    }

    void Server::broadcast(DawnNet::PacketHeader& packet, DawnNet::Size size)
    {
        for(const auto& [id, session] : SessionManager::Instance().get_session_list())
        {
            if(session->Socket().is_open())
            {
                session->Send(packet, size);
            }
        }
    }

    void Server::__io_context_run()
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
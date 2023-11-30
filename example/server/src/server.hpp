#pragma once

#include <DawnNet/DawnNet.hpp>

#include "session/session_manager.hpp"

namespace ld_server
{
    class Server
    {
    public:
        Server(int port);
        ~Server();

        DawnNet::ErrCode init();
        DawnNet::ErrCode run();
        DawnNet::ErrCode close();

        void broadcast(DawnNet::PacketHeader& packet, DawnNet::Size size);
    private:
        // template<typename PacketType>
        // void __send(/*session_id, data*/);
        void __io_context_run();

    private:
        bool is_init_;

        DawnNet::Listner listner_;

        unsigned int thread_cnt_;
        std::vector<std::thread> thread_list_;

    };
}
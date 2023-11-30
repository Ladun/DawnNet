#pragma once

#include <DawnNet/DawnNet.hpp>

namespace ld_client
{
    enum class State
    {
        NOT_INITIALIZED,
        INITIALIZED, 
        RUNNING,
        CLOSED
    };

    class Client
    {
    public:
        Client(const std::string& nickname,
                const std::string& host,
                const std::string& port);
        ~Client();

        DawnNet::ErrCode init();
        DawnNet::ErrCode connect_and_run();
        DawnNet::ErrCode close();
    
    private:

        void __io_context_run();

    private:
        State state_;

        std::string nickname_;
        
        std::thread thread_;
        DawnNet::Connector connector_;
    };
}
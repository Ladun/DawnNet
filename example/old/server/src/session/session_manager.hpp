#pragma once

#include <map>

#include <DawnNet/DawnNet.hpp>

namespace ld_server
{   
    class Server; 

    // TODO: Change to Thread-safe singleton
    class SessionManager : public DawnNet::Singleton<SessionManager>
    {
    public:
        SessionManager() = default;
        ~SessionManager() = default;

        DawnNet::SessionPtr generate(DawnNet::SocketType socket, Server* server);
        DawnNet::SessionPtr find(uint32_t id);
        void remove(DawnNet::SessionPtr session);

    public:
        std::map<uint32_t, DawnNet::SessionPtr>& get_session_list()
        {
            return session_list_;
        }

    private:
        std::shared_mutex mutex_;

        uint32_t session_id_;
        std::map<uint32_t, DawnNet::SessionPtr> session_list_;
        
    };
}
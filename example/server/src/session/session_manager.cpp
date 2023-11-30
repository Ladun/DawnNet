
#include "session_manager.hpp"
#include "client_session.hpp"

#include <iostream>

namespace ld_server
{
    DawnNet::SessionPtr SessionManager::generate(DawnNet::SocketType socket, Server* server)
    {
        DawnNet::WriteLock lock(mutex_);

        int session_id = ++session_id_;
        DawnNet::SessionPtr session = std::make_shared<ClientSession>(std::move(socket), server);
        session->SetID(session_id);

        session_list_.emplace(session_id, session);

        return session;
    }

    DawnNet::SessionPtr SessionManager::find(uint32_t id)
    {
        DawnNet::ReadLock lock(mutex_);
        auto iter = session_list_.find(id);
        if(iter == session_list_.end())
            return nullptr;

        return iter->second;
    }

    void SessionManager::remove(DawnNet::SessionPtr session)
    {
        DawnNet::WriteLock lock(mutex_);

    }

}
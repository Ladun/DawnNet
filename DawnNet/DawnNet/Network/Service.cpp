#include <DawnNet/pch.hpp>
#include <DawnNet/Network/Service.hpp>
#include <DawnNet/Network/Session.hpp>

namespace DawnNet
{
    Service::Service(SessionFactory sessionFactory)
        : _sessionFactory(sessionFactory)
    {
        
    }   

    Service::~Service()
    {

    }

    void Service::Broadcast(SendBufferRef sendBuffer)
    {
        READ_LOCK;
        for (const auto& session : _sessions)
        {
            session->Send(sendBuffer);
        }
    }

    SessionRef Service::CreateSession() 
    {
        SessionRef session = _sessionFactory();
        session->SetService(shared_from_this());

        return session;
    }

    void Service::AddSession(SessionRef session)
    {
        WRITE_LOCK;
        _sessions.insert(session);

    }

    void Service::ReleaseSession(SessionRef session)
    {
        WRITE_LOCK;
        _sessions.erase(session);
    }   

    ServerService::ServerService(SessionFactory sessionFactory,
                                 const EndpointType& endpoint)
        : Service(sessionFactory), _listner(endpoint)
    {
    }

    ServerService::~ServerService()
    {
        std::cout << "~ServerService\n";
    }

    bool ServerService::Start()
    {
	    ServerServiceRef service = std::static_pointer_cast<ServerService>(shared_from_this());
        if(!_listner.StartAccept(service))
            return false;

        return true;
    }

    ClientService::ClientService(SessionFactory sessionFactory, 
                                 const std::string& host, 
                                 const std::string& port)
        : Service(sessionFactory), _connector(host, port)
    {
    }

    ClientService::~ClientService()
    {
    }

    bool ClientService::Start()
    {
	    ClientServiceRef service = std::static_pointer_cast<ClientService>(shared_from_this());
        if(!_connector.Connect(service))
            return false;

        return true;
    }

} // DawnNet
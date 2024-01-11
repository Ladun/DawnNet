#pragma once

#include <DawnNet/Network/Connector.hpp>
#include <DawnNet/Network/Listner.hpp>

namespace DawnNet
{

    using SessionFactory = std::function<SessionRef(void)>;

    class Service : public std::enable_shared_from_this<Service>
    {
    public:
	    Service(SessionFactory sessionFactory);
        virtual ~Service();

        virtual bool    Start() = 0;

	    void			Broadcast(SendBufferRef sendBuffer);
        SessionRef      CreateSession();
        void			AddSession(SessionRef session);
        void			ReleaseSession(SessionRef session);


    protected:
        USE_LOCK;

        SessionFactory  _sessionFactory;
        Set<SessionRef> _sessions;
    };

    class ServerService : public Service
    {
    public:
        ServerService(SessionFactory sessionFactory,
                      const EndpointType& endpoint);
        virtual ~ServerService();

        virtual bool Start() override;

    private:
        Listner _listner;
    };
    
    class ClientService : public Service
    {
    public:
        ClientService(SessionFactory sessionFactory, 
                      const std::string& host, 
                      const std::string& port);
        virtual ~ClientService();

        virtual bool Start() override;
    private:
        Connector _connector;
    };
} // namespace DawnNet

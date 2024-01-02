#pragma once

namespace DawnNet
{

    class Service : public std::enable_shared_from_this<Service>
    {
    public:
	    Service(SessionFactory sessionFactory);
        virtual ~Service();

    protected:
        SessionFactory _sessionFactory;
    };
    
} // namespace DawnNet

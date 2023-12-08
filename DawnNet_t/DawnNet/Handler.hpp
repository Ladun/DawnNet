#pragma once

#include <map>
#include <functional>

#include <DawnNet/Core.hpp>
#include <DawnNet/PacketHeader.hpp>
#include <DawnNet/Error.hpp>


namespace DawnNet
{
    class MessageHandler : public Singleton<MessageHandler>
    {
    public:
        using HandlerType = std::function<ErrCode(PacketHeader*, Size, Session*)>;

    public:
        MessageHandler() = default;
        ~MessageHandler() = default;
        ErrCode RegisterHandler(MessageNo number, HandlerType&& handler)
        {
            auto result = m_HandlerList.emplace(number, handler);
            if (result.second == false)
                return eErrCodeAlreadyRegistered;

            return 0;
        }
	
        template<typename... TArgs>
        ErrCode Process(MessageNo number, TArgs... args)
        {
            auto iter = m_HandlerList.find(number);
            if (iter == m_HandlerList.end())
                return eErrCodeInvalidMessage;

            auto result = iter->second(args...);
            return result;
        }
        
    private:

        std::map<MessageNo, HandlerType> m_HandlerList;
    };
}
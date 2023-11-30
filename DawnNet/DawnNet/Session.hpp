#pragma once

#include <DawnNet/Core.hpp>
#include <DawnNet/Buffer.hpp>
#include <DawnNet/PacketHeader.hpp>

#include <boost/asio.hpp>


namespace DawnNet
{
    // 세션 클래스 정의
    constexpr Size eSzPacketMin = sizeof(BufferHeader);
    
    class Session : public std::enable_shared_from_this<Session>
    {
    public:
        Session(SocketType&& socket);
        virtual ~Session();

        void Start();
        ErrCode Send(PacketHeader& packet, Size size);
        void Send(char* buffer, int size);

    private:
        ErrCode Disconnect();    
        ErrCode RegisterRecv();
        ErrCode OnRecv(Size size);

    public:
        virtual void OnConnected() = 0;
        virtual void OnSend(std::size_t sendSize) = 0;
        virtual void OnDisconnected() = 0;

    public: 
        void SetID(uint32_t id) { m_id = id; }
        uint32_t GetID() const { return m_id; }
        SocketType& Socket()
        {
            return m_Socket;
        }

    protected:
        uint32_t m_id{};
        SocketType m_Socket;
        Buffer m_Buffer;
        Buffer m_SendBuffer;
        
    };
    using SessionPtr = std::shared_ptr<Session>;
}
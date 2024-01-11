#pragma once

#include <DawnNet/Buffer/RecvBuffer.hpp>


namespace DawnNet
{
    class Service;
        
    class Session : public std::enable_shared_from_this<Session>
    {        
        enum
        {
            BUFFER_SIZE = 0x10000, // 64kb
        };

    public:
        Session();
        virtual ~Session();

        void Start();
        void Send(SendBufferRef sendBuffer);
        void Disconnect();    

    private:
        void RegisterRecv();
        void ProcessRecv(int32 size);

        void RegisterSend();
        void ProcessSend(int32 size);

    public: 
        virtual void    OnConnected() = 0;
        virtual int32   OnRecv(BYTE* buffer, int32 len) = 0;
        virtual void    OnSend(int32 len) = 0;
        virtual void    OnDisconnected() = 0;

    public: 
        void SetID(uint32_t id) { _id = id; }
        uint32_t GetID() const { return _id; }

        void SetService(std::shared_ptr<Service> service) { _service = service; }
        std::shared_ptr<Service> GetService() { return _service.lock(); }

        SocketType& Socket() { return _socket; }
        bool IsConnected() { return _connected; }
	    SessionRef GetSessionRef() { return std::static_pointer_cast<Session>(shared_from_this()); }

    private:
        uint32_t                _id{};
        std::weak_ptr<Service>  _service;
        SocketType              _socket;
        Atomic<bool>            _connected = false;

    private:
        USE_LOCK

        // Recv
        RecvBuffer _recvBuffer;  

        // Send
        Queue<SendBufferRef> _sendQueue;    
	    Atomic<bool>		 _sendRegistered = false; 
    };

    /* -----------------
        Packet Session
    --------------------*/

    struct PacketHeader
    {
        uint16 size;
        uint16 id;
    };

    class PacketSession : public Session
    {
    public:
        PacketSession();
        virtual ~PacketSession();

        PacketSessionRef GetPacketSessionRef() { return std::static_pointer_cast<PacketSession>(shared_from_this()); }

    protected:
        virtual int32	OnRecv(BYTE* buffer, int32 len);
        virtual void	OnRecvPacket(BYTE* buffer, int32 len) = 0;

    };
}
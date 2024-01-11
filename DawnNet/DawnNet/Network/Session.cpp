
#include <DawnNet/pch.hpp>
#include <DawnNet/Network/Session.hpp>
#include <DawnNet/Network/IOContext.hpp>
#include <DawnNet/Network/Service.hpp>

namespace DawnNet
{

    Session::Session() 
        : _socket(IOContext::Instance().GetIOContext()), _recvBuffer(BUFFER_SIZE)
    {
        
    }

    Session::~Session()
    {
        std::cout << "~Session\n";
        _socket.close();
    }

    void Session::Start()
    {

	    _connected.store(true);

        GetService()->AddSession(GetSessionRef());

        OnConnected();

        RegisterRecv();
    }
    
    void Session::Disconnect()
    {
        if (_connected.exchange(false) == false)
            return;

        boost::system::error_code errCode;

        if(_socket.is_open())
            _socket.close(errCode);

        OnDisconnected();
        GetService()->ReleaseSession(GetSessionRef());
            
    }

    void Session::Send(SendBufferRef sendBuffer)
    {
        if (IsConnected() == false)
            return;

            
        bool registerSend = false;

        {
            WRITE_LOCK;

            _sendQueue.push(sendBuffer);

            if (_sendRegistered.exchange(true) == false)
                registerSend = true;
        }
        if(registerSend)
            RegisterSend();

    }

    void Session::RegisterRecv()
    {
        if(IsConnected() == false)
            return;

        int32 size      = _recvBuffer.FreeSize();
        BYTE* writePtr  = _recvBuffer.WritePos();

        // if(size < sizeof(PacketHeader) || _recvBuffer.GetBufferSize() < size) 
        // {
        //     Disconnect();
        //     return eErrCodeSesBufferFull;
        // }

        // Register read
        _socket.async_read_some(boost::asio::buffer(writePtr, size), IOContext::Instance().BindExecutor(
            [this](const boost::system::error_code& ec, std::size_t recvSize)
            {
                if(ec.value() != 0)
                {
                    std::cout << "Fail to recv, error: "<< ec.message() <<"\n";
                    Disconnect();
                    return;
                }

                // Processing recieved data
                ProcessRecv(static_cast<int32>(recvSize));
            }));
    }

    void Session::ProcessRecv(int32 recvSize)
    {
        if(recvSize == 0)
        {
            std::cout << "Faid on ProcessRecv, error: 'Recv 0'\n";
            Disconnect();
            return;
        }

        if(!_recvBuffer.OnWrite(recvSize))
        {
            std::cout << "Faid on ProcessRecv, error: 'OnWrite overflow'\n";
            Disconnect();
            return;
        }


        int32 dataSize      = _recvBuffer.DataSize();
        int32 processLen    = OnRecv(_recvBuffer.ReadPos(), dataSize);
        
        if (processLen < 0 || dataSize < processLen || 
            _recvBuffer.OnRead(processLen) == false)
        {
            std::cout << "Faid on ProcessRecv, error: 'OnRead overflow'\n";
            Disconnect();
            return;
        }
        
        _recvBuffer.Clean();        

        RegisterRecv();
    }

    void Session::RegisterSend()
    {
        if(IsConnected() == false)
            return;

        // Save send data to local variable
        Vector<SendBufferRef> sendBuffers;
        int32 writeSize = 0;
        {
            WRITE_LOCK;
            while (_sendQueue.empty() == false)
            {
                SendBufferRef sendBuffer = _sendQueue.front();

                writeSize += sendBuffer->WriteSize();

                _sendQueue.pop();
                sendBuffers.push_back(sendBuffer);
            }
        }

        // Make boost asio buffer
        Vector<boost::asio::mutable_buffer> buf;        
        for (SendBufferRef sendBuffer : sendBuffers)
        {
            buf.push_back(boost::asio::buffer(sendBuffer->Buffer(), sendBuffer->WriteSize()));
        }

        // Register send
         _socket.async_write_some(buf, IOContext::Instance().BindExecutor(
			[this](const boost::system::error_code& ec, std::size_t sendSize)
            {
                if(ec.value() != 0 || sendSize == 0)
                {
                    std::cout << "Fail to send, error: "<< ec.message() <<"\n";
                    Disconnect();
                }

                ProcessSend(sendSize);
                OnSend(sendSize);
            })
        );
    }


    void Session::ProcessSend(int32 size)
    {
        if (size == 0)
        {
            std::cout << "Faid on ProcessRecv, error: 'Send 0'\n";
            Disconnect();
            return;
        }

        OnSend(size);

        WRITE_LOCK;
        if (_sendQueue.empty())
            _sendRegistered.store(false);
        else
            RegisterSend();
    }

    /*-----------------
        Packet Session
    ------------------*/

    PacketSession::PacketSession()
        : Session()
    {
    }

    PacketSession::~PacketSession()
    {
    }

    // [size(2)][id(2)][data...][size(2)][id(2)][data...]
    int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
    {
        int32 processLen = 0;

        while (true)
        {
            int32 dataSize = len - processLen;
            // 최소한 헤더는 파싱할 수 있어야 한다.
            if (dataSize < sizeof(PacketHeader))
                break;

            PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
            // 헤더에 기록된 패킷 크기를 파싱할 수 있어야 한다.
            if (dataSize < header.size)
                break;

            // 패킷 조립 성공
            OnRecvPacket(&buffer[0], header.size);

            processLen += header.size;
        }

        return processLen;
    }
} // namespace DawnNet
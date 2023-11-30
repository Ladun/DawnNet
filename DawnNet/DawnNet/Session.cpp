
#include <DawnNet/pch.hpp>
#include <DawnNet/Session.hpp>
#include <DawnNet/Handler.hpp>
#include <DawnNet/IOContext.hpp>

namespace DawnNet
{

    Session::Session(SocketType&& socket) 
        : m_Socket(std::move(socket)), m_Buffer(eSzPacketMax), m_SendBuffer(eSzPacketMax)
    {
    }

    Session::~Session()
    {
        
    }

    void Session::Start()
    {
        RegisterRecv();
    }
    
    ErrCode Session::Disconnect()
    {
        boost::system::error_code errCode;

        OnDisconnected();

        if(m_Socket.is_open())
            m_Socket.close(errCode);

        return errCode.value();
    }

    ErrCode Session::Send(PacketHeader& packet, Size size)
    {
        // Add to buffer_
        m_SendBuffer.Clear();
        m_SendBuffer.Push(reinterpret_cast<char*>(&packet), size);

        Send(m_SendBuffer.GetReadPtr(), m_SendBuffer.GetUsingSize());
        return 0;
    }

    void Session::Send(char* buffer, int size)
    {
        m_Socket.async_write_some(boost::asio::mutable_buffer(buffer, size), IOContext::Instance().BindExecutor(
			[this](const boost::system::error_code& ec, std::size_t sendSize)
            {
                if(ec.value() != 0 || sendSize == 0)
                {
                    std::cout << "Fail to send, error: "<< ec.message() <<"\n";
                    Disconnect();
                }

                OnSend(sendSize);
            })
        );
    }

    ErrCode Session::RegisterRecv()
    {
        Size size       = m_Buffer.GetUsableSize();
        char* writePtr  = m_Buffer.GetWritePtr();

        if(size <  eSzPacketMin || m_Buffer.GetBufferSize() < size) 
        {
            Disconnect();
            return eErrCodeSesBufferFull;
        }

        m_Socket.async_read_some(boost::asio::mutable_buffer(writePtr, size), IOContext::Instance().BindExecutor(
            [this](const boost::system::error_code& ec, std::size_t recvSize)
            {
                
                if(ec.value() != 0)
                {
                    std::cout << "Fail to recv, error: "<< ec.message() <<"\n";
                    Disconnect();
                    return;
                }

                ErrCode errCode = OnRecv(static_cast<Size>(recvSize));
                if (errCode != 0)
                {
                    std::cout << "Fail on_recv, error: "<< errCode <<"\n";
                    Disconnect();
                    return;
                }

                RegisterRecv();
            }));
        
        return 0;
    }

    ErrCode Session::OnRecv(Size recvSize)
    {
        if(recvSize == 0)
        {
            return eErrCodeInvalidSize;
        }

        if(!m_Buffer.OnPush(recvSize))
        {
            return eErrCodeSessionBufferFull;
        }


        Size    size = 0;
        ErrCode result = 0;
        char*   data = m_Buffer.Front(size, result);
        if(result != 0)
            return result;

        while(data != nullptr && result == 0)
        {   
            if(size < sizeof(PacketHeader))
            {
                return eErrCodeInvalidSize;
            }

            PacketHeader* header = reinterpret_cast<PacketHeader*>(data);
            result = MessageHandler::Instance().Process(header->m_Message, header, size, this);
            if(result != 0)
                break;
            
            data = m_Buffer.Front(size, result);
        }
        if(result != 0)
            return result;

        m_Buffer.Pop();
        return 0;
    }

    
} // namespace DawnNet
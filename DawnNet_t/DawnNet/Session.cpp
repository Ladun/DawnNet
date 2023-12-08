
#include <DawnNet/pch.hpp>
#include <DawnNet/Session.hpp>
#include <DawnNet/Handler.hpp>
#include <DawnNet/IOContext.hpp>

namespace DawnNet
{

    Session::Session(SocketType&& socket) 
        : _socket(std::move(socket)), _buffer(eSzPacketMax), _sendBuffer(eSzPacketMax)
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

        if(_socket.is_open())
            _socket.close(errCode);

        return errCode.value();
    }

    ErrCode Session::Send(PacketHeader& packet, Size size)
    {
        // Add to buffer_
        _sendBuffer.Clear();
        _sendBuffer.Push(reinterpret_cast<char*>(&packet), size);

        Send(_sendBuffer.GetReadPtr(), _sendBuffer.GetUsingSize());
        return 0;
    }

    void Session::Send(char* buffer, int size)
    {
        _socket.async_write_some(boost::asio::mutable_buffer(buffer, size), IOContext::Instance().BindExecutor(
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
        Size size       = _buffer.GetUsableSize();
        char* writePtr  = _buffer.GetWritePtr();

        if(size <  eSzPacketMin || _buffer.GetBufferSize() < size) 
        {
            Disconnect();
            return eErrCodeSesBufferFull;
        }

        _socket.async_read_some(boost::asio::mutable_buffer(writePtr, size), IOContext::Instance().BindExecutor(
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

        if(!_buffer.OnPush(recvSize))
        {
            return eErrCodeSessionBufferFull;
        }


        Size    size = 0;
        ErrCode result = 0;
        char*   data = _buffer.Front(size, result);
        if(result != 0)
            return result;

        while(data != nullptr && result == 0)
        {   
            if(size < sizeof(PacketHeader))
            {
                return eErrCodeInvalidSize;
            }

            PacketHeader* header = reinterpret_cast<PacketHeader*>(data);
            result = MessageHandler::Instance().Process(header->_message, header, size, this);
            if(result != 0)
                break;
            
            data = _buffer.Front(size, result);
        }
        if(result != 0)
            return result;

        _buffer.Pop();
        return 0;
    }

    
} // namespace DawnNet
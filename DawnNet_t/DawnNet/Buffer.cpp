
#include <DawnNet/pch.hpp>
#include <DawnNet/Buffer.hpp>
#include <DawnNet/Error.hpp>

namespace DawnNet
{
    Buffer::Buffer(Size size)
        : MAX_SIZE(size), m_UseSize(0), 
          m_ReadIndex(0), m_WriteIndex(0), m_Buffer(nullptr)
    {
        m_Buffer = new char[MAX_SIZE];
        ::memset(m_Buffer, 0, MAX_SIZE);
    }

    Buffer::~Buffer()
    {
        delete[] m_Buffer;
    }

    bool Buffer::Push(const char* data, Size size)
    {
        Size dataSize = static_cast<Size>(sizeof(BufferHeader)) + size;
        if(dataSize > GetUsableSize())
            return false;

        reinterpret_cast<BufferHeader*>(m_Buffer + m_WriteIndex)->dataSize = size;
        //::memcpy_s(buffer_ + write_index_ + sizeof(BufferHeader), get_usable_size() - sizeof(BufferHeader), data, size);
        ::memcpy(m_Buffer + m_WriteIndex + sizeof(BufferHeader), data, size);
        m_UseSize += size + sizeof(BufferHeader);
        m_WriteIndex += static_cast<int>(size) + sizeof(BufferHeader);
        
        return true;
    }

    char* Buffer::Front(Size& size, ErrCode& pErr)
    {
        if(static_cast<int>(m_UseSize) - m_ReadIndex < static_cast<int>(sizeof(BufferHeader)))
            return nullptr;

        pErr = 0;
        char* data = m_Buffer + m_ReadIndex;
        size = reinterpret_cast<BufferHeader*>(data)->dataSize;
        data += sizeof(BufferHeader);

        // 읽을 데이터의 크기가 Buffer에서 보관할 수 있는 최대 크기보다
        // 크다면 Error
        if(size > MAX_SIZE - sizeof(BufferHeader))
        {
            pErr = eErrCodeSessionBufferFull;
            return nullptr;
        }

        // 읽을 데이터의 크기가 실제 데이터 크기와 다르다면
        if(size > m_UseSize - static_cast<Size>(m_ReadIndex) - sizeof(BufferHeader))
        {
            pErr = eErrCodeInvalidSize;
            return nullptr;
        }
        
        m_ReadIndex += (static_cast<int>(size) + static_cast<int>(sizeof(BufferHeader)));
        return data;
    }

    void Buffer::Pop()
    {
        // memmove_s(void *dest, rsize_t destsz, const void *src, rsize_t count);
        // ::memmove_s(buffer_, MAX_SIZE, buffer_ + read_index_, MAX_SIZE - read_index_);
        ::memmove(m_Buffer, m_Buffer + m_ReadIndex, MAX_SIZE - m_ReadIndex);

        m_WriteIndex    -= m_ReadIndex;
        m_UseSize       -= static_cast<int>(m_ReadIndex);
        m_ReadIndex     = 0;

    }

    void Buffer::Clear()
    {
        m_ReadIndex     = 0;
        m_UseSize       = 0;
        m_WriteIndex    = 0;
    }

    bool Buffer::OnPush(Size size)
    {
        if(m_WriteIndex + size > MAX_SIZE)
            return false;

        m_WriteIndex += static_cast<int>(size);
        m_UseSize    += size;

        return true;
    }

    char* Buffer::GetReadPtr()
    {
        if(static_cast<int>(m_UseSize) - m_ReadIndex < static_cast<int>(sizeof(BufferHeader)))
            return nullptr;
        return  m_Buffer + m_ReadIndex;
    }

    char* Buffer::GetWritePtr()
    {
        return &(m_Buffer[m_WriteIndex]);
    }
}
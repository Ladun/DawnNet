#pragma once

#include <DawnNet/Core.hpp>

namespace DawnNet
{ 
    #pragma pack(push, 1)
    class BufferHeader
    {
    public:
        BufferHeader() = default;
        ~BufferHeader() = default;
    public:
        Size dataSize = 0;
    };
    #pragma pack(pop)

    class Buffer
    {
    public:
        Buffer(Size size);
        ~Buffer();

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        Buffer& operator=(const Buffer&&) = delete;

    public:
        bool Push(const char* pData, Size size);
        char* Front(Size& size, ErrCode& pErr);
        void Pop();
        void Clear();
        bool OnPush(Size size);
        char* GetWritePtr();
        char* GetReadPtr();

        Size GetUsingSize() const { return m_UseSize; }
        Size GetUsableSize() const { return MAX_SIZE - m_UseSize; }
        Size GetBufferSize() { return MAX_SIZE; }

        // TODO: remove
        char* GetBuffer() { return m_Buffer; }

    protected:
        const Size      MAX_SIZE;
        Size    m_UseSize;
        int     m_ReadIndex;
        int     m_WriteIndex;
        char*   m_Buffer;
    };
}
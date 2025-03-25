#include "pch.h"
#include "GThread.h"
#include "Allocator.h"
#include "SendBuffer.h"
atomic<bool> SendBufferManager::m_bShutDown = false;

SendBufferManager::SendBufferManager():
    m_Lock{}
{
}

SendBufferManager::~SendBufferManager()
{
    m_bShutDown.store(true);
    m_vecSendBufferChunk.clear();
}

shared_ptr<SendBuffer> SendBufferManager::Open(size_t _size)
{
    if (T_SendBufferChunk == nullptr)
    {
        T_SendBufferChunk = Pop();
        T_SendBufferChunk->Reset();
    }
    
    assert(T_SendBufferChunk->IsOpen() == false);

    if (T_SendBufferChunk->FreeSize() < _size)
    {
        T_SendBufferChunk = Pop();
        T_SendBufferChunk->Reset();
    }

   return T_SendBufferChunk->Open(_size);

}

shared_ptr<SendBufferChunk> SendBufferManager::Pop()
{
    WLock lock(m_Lock);

    if (m_vecSendBufferChunk.empty() == false)
    {
        shared_ptr<SendBufferChunk> sendBuffer = m_vecSendBufferChunk.back();
        m_vecSendBufferChunk.pop_back();
      
        return sendBuffer;
    } 
  
    return shared_ptr<SendBufferChunk>(xnew<SendBufferChunk>(), PushGlobal);  
}

void SendBufferManager::PushGlobal(SendBufferChunk* _pSendBufferChunk)
{
    if (m_bShutDown == true)
        return;

    SendBufferMgr->Push(shared_ptr<SendBufferChunk>(_pSendBufferChunk, PushGlobal));
}

void SendBufferManager::Push(shared_ptr<SendBufferChunk> _pSendBufferChunk)
{
    WLock lock(m_Lock);
    m_vecSendBufferChunk.push_back(_pSendBufferChunk);
}


/*///////////
SendBfferChunk
*////////////

SendBufferChunk::SendBufferChunk() :
    m_bOpen(false),
    m_iUsedPos(0)
{
    m_vecSendBuffer.resize(MAX_SENDBUFFER_SIZE);
}
SendBufferChunk::~SendBufferChunk()
{

}

shared_ptr<SendBuffer> SendBufferChunk::Open(size_t _size)
{
    if (m_bOpen)
        assert(nullptr);

    if (FreeSize() < _size)
        assert(nullptr);

    m_bOpen = true;
  
    return make_shared<SendBuffer>(shared_from_this(), GetBuffer(), _size);
}

void SendBufferChunk::Close(int _iUsedSize)
{
    assert(m_bOpen == true);

    m_bOpen = false;
    m_iUsedPos += _iUsedSize;
}

void SendBufferChunk::Reset()
{
    m_iUsedPos = 0;
    m_bOpen = false;
}

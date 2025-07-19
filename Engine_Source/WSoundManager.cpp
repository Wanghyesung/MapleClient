#include "WSoundManager.h"
#include "WAudioClip.h"
namespace W
{
    RingBuffer<weak_ptr<AudioClip>, 50> SoundManager::m_RingBuffer = {};
    atomic<bool> SoundManager::m_bEvent = {};


    void SoundManager::Update()
    {
        while((m_bEvent.load()))
        {
            weak_ptr<AudioClip> wpClip = {};
            if (m_RingBuffer.Pop(wpClip) == false)
                return;

            if (auto spSound = wpClip.lock())
            {
                eSoundType eType = spSound->GetSoundType();
                switch (eType)
                {
                case W::eSoundType::Play:
                    spSound->Play();
                    break;
                case W::eSoundType::Stop:
                    spSound->Stop();
                    break;
                }
            }

            if (m_RingBuffer.IsFull())
            {
                m_bEvent.store(false);
                break;
            }
        }
    }
    void SoundManager::Push(weak_ptr<AudioClip> _wpAudioCclip)
    {
        m_RingBuffer.Push(_wpAudioCclip);
        m_bEvent.store(true);
    }
}
#include "WAudioSource.h"
#include "WAudioClip.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WSoundManager.h"

namespace W
{
	UINT AudioSource::COMPONENT_ID = 0;

	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, m_wpAudioClip{}
	{

	}

	AudioSource::~AudioSource()
	{

	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Foward();

		if(auto spClip = m_wpAudioClip.lock())
			spClip->Set3DAttributes(pos, foward);
	}

	void AudioSource::Render()
	{

	}

	void AudioSource::Play()
	{
		if (auto spClip = m_wpAudioClip.lock())
		{
			spClip->SetSoundType(eSoundType::Play);
			SoundManager::Push(spClip);
		}
	}
	void AudioSource::Stop()
	{
		if (auto spClip = m_wpAudioClip.lock())
		{
			spClip->SetSoundType(eSoundType::Stop);
			SoundManager::Push(spClip);
		}
	}
	void AudioSource::SetLoop(bool loop)
	{
		if (auto spClip = m_wpAudioClip.lock())
			spClip->SetLoop(loop);
	}
}
#include "WAudioListener.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WFmod.h"

namespace W
{
	UINT AudioListener::COMPONENT_ID = 0;

	AudioListener::AudioListener()
		: Component(eComponentType::AudioListener)
	{

	}

	AudioListener::~AudioListener()
	{

	}

	void AudioListener::Initialize()
	{

	}

	void AudioListener::Update()
	{

	}

	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		const Vector3& pos = tr->GetPosition();
		const Vector3& foward = tr->Foward();
		const Vector3& up = tr->Up();

		const Vector3& vel = { 0.0f, 0.0f, 0.0f };
		Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void AudioListener::Render()
	{

	}
}
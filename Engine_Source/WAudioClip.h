#pragma once
#include "WResource.h"
#include "WFmod.h"
#include "WMath.h"


//#include <Fmod/fmod_studio.hpp>
//#include <Fmod/fmod.hpp>
//#include <Fmod/fmod_common.h>
//#include <Fmod/fmod_codec.h>

//#include "..\External\Include\\DirectXTex\DirectXTex.h"

namespace W
{
	enum class eSoundType
	{
		Play,
		Stop,
		End
	};

	class AudioClip : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		virtual HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Vector3 pos, const Vector3 vel);
		void SetLoop(bool loop) { mbLoop = loop; }

		void SetSoundType(eSoundType _eSoundType) { m_eSoundType = _eSoundType; }
		eSoundType GetSoundType() { return m_eSoundType; }
	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;

		eSoundType m_eSoundType;
	};
}


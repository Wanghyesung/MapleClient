#pragma once
#include "WComponent.h"
#include "WAudioClip.h"

namespace W
{
	class AudioSource : public Component
	{
		DECLARE_COMPONENT_ID;

	public:
		AudioSource();
		virtual ~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		void Play();
		void Stop();
		void SetLoop(bool loop);

		void SetClip(std::shared_ptr<AudioClip> clip) { m_wpAudioClip = clip; }
		std::weak_ptr<AudioClip> GetClip() { return m_wpAudioClip; }

	private:
		std::weak_ptr<AudioClip> m_wpAudioClip;
	};
}

#pragma once
#include "WComponent.h"


namespace W
{
	class AudioListener : public Component
	{
		DECLARE_COMPONENT_ID;

	public:
		AudioListener();
		virtual ~AudioListener();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:

		friend class SoundManager;
	};
}
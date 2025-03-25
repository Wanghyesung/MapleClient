#pragma once
#include "WGameObject.h"

namespace W
{
	class CameraScript;

	class White : public GameObject
	{
	public:
		White();
		virtual ~White();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetFunction(std::function<void()> _func) { m_pCompleteEvent = std::move(_func); }
		void SetEndTime(float _fTime) { m_fEndTime = _fTime; }
	private:
		std::function<void()> m_pCompleteEvent;

		Vector4 m_vColor;

		float m_fEndTime;
	};
}



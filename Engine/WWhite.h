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
		virtual void UpdateState(const wstring& _strStateName, int _iState);

	private:
		Vector4 m_vColor;
	};
}



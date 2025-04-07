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

		
	};
}



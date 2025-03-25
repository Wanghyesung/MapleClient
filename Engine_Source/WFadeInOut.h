#pragma once

#include "WGameObject.h"
namespace W
{
	class FadeInOut : public GameObject
	{
	public:
		FadeInOut();
		virtual ~FadeInOut();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:


	};
}



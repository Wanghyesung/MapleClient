#pragma once
#include "WGameObject.h"

namespace W
{
	class Portal : public GameObject
	{
	public:
		Portal();
		virtual ~Portal();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:

	};
}



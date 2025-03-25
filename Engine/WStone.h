#pragma once
#include "WGameObject.h"

namespace W
{
	class Stone : public GameObject
	{
	public:
		Stone();
		virtual ~Stone();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:

	};
}



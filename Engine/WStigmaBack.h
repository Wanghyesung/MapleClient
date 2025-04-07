#pragma once
#include "WGameObject.h"

namespace W
{
	class StigmaCount;
	class StigmaBack : public GameObject
	{
	public:
		StigmaBack();
		virtual ~StigmaBack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	};

}


#pragma once
#include "WComponent.h"

namespace W
{
	class Script : public Component
	{
		DECLARE_COMPONENT_ID;

	public:
		Script();
		~Script();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}



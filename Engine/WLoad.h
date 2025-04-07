#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class Load : public PlayerAttackObject
	{
	public:
		Load();
		virtual ~Load();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		

	};
}



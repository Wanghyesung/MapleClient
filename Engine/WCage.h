#pragma once
#include "WGameObject.h"

namespace W
{
	class Cage : public GameObject
	{
	public:
		Cage();
		virtual ~Cage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:


	};
}



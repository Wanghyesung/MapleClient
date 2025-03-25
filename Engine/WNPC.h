#pragma once
#include "WGameObject.h"

namespace W
{
	class NPC : public GameObject
	{
	public:
		NPC();
		virtual ~NPC();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}



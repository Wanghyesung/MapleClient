#pragma once
#include "..\Engine_Source\WGameObject.h"

namespace gui
{
	class DebugObject : public W::GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:


	};
}



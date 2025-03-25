#pragma once
#include "..\Engine_Source\WGameObject.h"

namespace gui
{
	class EditorObject : public W::GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}



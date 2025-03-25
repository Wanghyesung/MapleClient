#pragma once
#include "..\Engine_Source\WScene.h"

namespace W
{
	class ValleyScene_2 : public Scene
	{
	public:
		ValleyScene_2();
		virtual ~ValleyScene_2();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void CreateBackground() override;

	private:
		void setobject();
	};
}



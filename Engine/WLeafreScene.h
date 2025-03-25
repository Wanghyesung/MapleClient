#pragma once
#include "..\Engine_Source\WScene.h"

namespace W
{
	class LeafreScene : public Scene
	{
	public:
		LeafreScene();
		virtual ~LeafreScene();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;

	private:
		void setobject();

	};
}



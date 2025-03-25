#pragma once
#include "..\Engine_Source\WScene.h"

namespace W
{
	class MoveScene : public Scene
	{
	public:
		MoveScene();
		virtual ~MoveScene();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;

	private:

	};
}



#pragma once
#include "..\Engine_Source\WScene.h"

namespace W
{
	class CaveScene : public Scene
	{
	public:
		CaveScene();
		virtual ~CaveScene();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;

		virtual void StartSound()override;
		virtual void EndSound()override;

	private:
		void create_object();
		void create_effect();
		void create_monster();
	};
}



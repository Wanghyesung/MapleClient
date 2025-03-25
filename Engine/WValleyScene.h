#pragma once

#include "..\Engine_Source\WScene.h"

namespace W
{
	class ValleyScene : public Scene
	{
	public:
		ValleyScene();
		virtual ~ValleyScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void CreateBackground() override;
		
		virtual void StartSound() override;
		virtual void EndSound() override;

	private:
		void setobject();
		void setmonster();
	};
}





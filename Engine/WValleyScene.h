#pragma once

#include "..\Engine_Source\WScene.h"

namespace W
{
	class ValleyScene : public Scene
	{
	public:
		ValleyScene();
		virtual ~ValleyScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void SendEnter()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;
		
		virtual void StartSound() override;
		virtual void EndSound() override;

	private:
		void setobject();
		void setmonster();
		void create_effect();
	};
}





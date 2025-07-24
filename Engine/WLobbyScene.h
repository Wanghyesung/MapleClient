#pragma once

#include "..\Engine_Source\WScene.h"

namespace W
{
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		virtual ~LobbyScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void SendEnter()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;


	private:
		void start();
	};
}



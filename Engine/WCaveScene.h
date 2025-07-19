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

		virtual void SendEnter()override;

		virtual void CreateBackground() override;

	protected:
		virtual void add_objectpool()override;
		virtual void mapping_resource()override;

	private:
		void create_object();
		
	
	};
}



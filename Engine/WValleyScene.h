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

	protected:
		virtual void add_objectpool()override;
		virtual void mapping_resource()override;

	private:
		void setobject();
	
	};
}





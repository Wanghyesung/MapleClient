#pragma once
#include "..\Engine_Source\WScene.h"
namespace W
{
	
	class DemianScene : public Scene
	{
	public:
		DemianScene();
		virtual ~DemianScene();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;

		virtual void StartSound()override;
		virtual void EndSound()override;

		virtual void SendEnter()override;

	protected:
		virtual void add_objectpool()override;
		virtual void mapping_resource()override;

	private:
		void fadein();
		void phase2();
	private:
		void create_monster();

	private:
		class SharHP* m_pSharHP;

		class White* m_pWhite;
		class StigmaBack* m_pStigmaBack;

		float m_fStigmaTime;
		float m_fCurStigmaTime;
		
		bool m_bEnd;
		UINT m_iFadeCallStack;
	};
}



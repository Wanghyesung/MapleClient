#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class SpawnUltimate : public PlayerAttackObject
	{
	public:
		SpawnUltimate();
		virtual ~SpawnUltimate();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		//void SetDir(UINT _iCount, Vector2 _vVelocity);
		
	private:
		void off();
		void create();
	private:
		//³ª
		float m_fCurActiveTime;
		float m_fActiveTime;

		UINT m_iCurIndex;
		std::vector<UINT> m_vecCreateCount;
		std::vector<std::vector<Vector2>> m_vecShurikenDir;

		float m_fCurCreateTime;
		float m_fCreateTime;

		GameObject* m_pTarget;
	};
}



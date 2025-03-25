#pragma once
#include "WGameObject.h"

namespace W
{
	class Monster;
	class Player;
	class MobZone : public GameObject
	{
	public:
		MobZone();
		virtual ~MobZone();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetOwner(Monster* _pMon) { m_pMonster = _pMon; }
		void SetLevel(UINT _iNum);
	private:
		void attack();
	private:
		Monster* m_pMonster;
		Player* m_pTarget;

		UINT m_iCurLevel;
		tAttackInfo m_tAttackInfo;

		float m_fAttackTime;
		float m_fCurTime;

		
		std::vector<float> m_vecLength;
	};
}



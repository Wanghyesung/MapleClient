#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianKeyAttack : public MonsterAttackObject
	{
	public:
		DemianKeyAttack();
		virtual ~DemianKeyAttack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetTime(float _fTime) { m_fTime = _fTime; }
		
	private:
		void off();

		void wait() { m_bWait = true; }
	private:
		std::wstring m_strCurAnim;
		tMonsterAttack m_tMonsterAttack;

		//실행 시간
		float m_fTime;
		float m_fCurTime;

		UINT m_iCallCount;
		bool m_bWait;
		bool m_bAttack;
	};
}


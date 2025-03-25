#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class White;
	class DemianVine : public MonsterAttackObject
	{
	public:
		DemianVine();
		virtual ~DemianVine();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		bool IsActive() { return m_bActive; }
		void SetActive(bool _bActive) { m_bActive = _bActive; }
	private:
		void start();
		void fadein();
		void off();

		void check_hp();
		void attack();
	private:
		float m_fDeleteTime;
		float m_fDemianHP;

		bool m_bStart;
		bool m_bActive;
		bool m_bClear;

		tAttackInfo m_tAttackInfo;
		White* m_pWhite;
	};
}



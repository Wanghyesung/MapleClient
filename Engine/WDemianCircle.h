#pragma once
#include "WGameObject.h"

namespace W
{
	class DemianCircle : public GameObject
	{
	public:
		DemianCircle();
		virtual ~DemianCircle();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void LevelUp(UINT _iLevel);
		void SetActive(bool _bActive) { m_bActive = _bActive; }
		bool IsActive() { return m_bActive; }
		void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	private:
		//void off();
		void check_enter();
		void move();

	private:
		UINT m_iCurIndex;
		std::vector<Vector2> m_vecColliderSize;

		tMonsterAttack m_tMonsterAttack;
		GameObject* m_pTarget;

		bool m_bActive;
		bool m_bEnter;

		float m_fAttackTime;
		float m_fCurAttackTime;

		float m_fSpeed;
	};
}



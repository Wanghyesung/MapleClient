#pragma once
#include "WGameObject.h"

namespace W
{
	class DamageFont :public GameObject
	{
	public:
		DamageFont();
		virtual ~DamageFont();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void CheckDamage(UINT _iDamage);

	private:
		bool m_bActive;

		float m_fCurTime;
		float m_fDeleteTime;

		Vector4 m_vColor;
		UINT m_iCount;
		static UINT FontCount;

	friend class BattleManager;
	};
}



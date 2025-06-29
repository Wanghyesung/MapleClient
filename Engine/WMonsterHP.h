#pragma once
#include "WGameObject.h"

namespace W
{
	class Monster;
	class MonsterBackHP;

	class MonsterHP : public GameObject
	{
	public:
		MonsterHP();
		virtual ~MonsterHP();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;

	protected:
		float m_fHP;

	private:
		UINT m_iHPCount;
		static UINT HP_COUNT;
		bool m_bBoss;

		friend class MonsterManager;
	};
}



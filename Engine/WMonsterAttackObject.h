#pragma once
#include "WGameObject.h"
#include "WEventManager.h"

namespace W
{
	class Monster;
	class MonsterAttackObject : public GameObject
	{
	public:
		MonsterAttackObject();
		virtual ~MonsterAttackObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	public:
		void SetOnwer(Monster* _pOnwer) { m_pOwner = _pOnwer; }

		//���ͷ� �ٲٱ�
		Monster* GetOwner() { return m_pOwner; }
		

	private:
		Monster* m_pOwner;
	};
}


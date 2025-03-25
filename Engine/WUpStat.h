#pragma once
#include "WGameObject.h"
#include "WBattleManager.h"

namespace W
{
	class UpStat : public GameObject
	{
	public:
		UpStat(float _fAccStat);
		virtual ~UpStat();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetTarget(GameObject* _pObject) { m_pTarget = _pObject; }
		GameObject* GetTarget() { return m_pTarget; }
		void SetDeleteTime(float _fTime) { m_fDeleteTime = _fTime; }
		void SetType(BattleManager::eUpStatType _eType) { m_eType = _eType; }

	protected:
		float m_fAccStat;

	private:
		BattleManager::eUpStatType m_eType;

		GameObject* m_pTarget;
		float m_fDeleteTime;
		float m_fCurTime;
	};
}



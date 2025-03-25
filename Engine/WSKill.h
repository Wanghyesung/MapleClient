#pragma once
#include "WEventManager.h"
#include "WSKillStorage.h"
#include "WIconUI.h"

namespace W
{
	class SKill : public IconUI
	{
	public:
		SKill();
		virtual ~SKill();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		virtual void Using()override;

		Player::ePlayerSkill GetPlayerSkill() { return m_ePlayerSkill; }
		void SetPlayerSkill(Player::ePlayerSkill _eSkill) { m_ePlayerSkill = _eSkill; }

		void SetSkillNuber(SKillStorage::eSkillNuber _eNuber) { m_eSkillNuber = _eNuber; }

		void SetClone(bool _bOn) { m_bClone = _bOn; }
		void SetOwner(SKill* _pSKill) { m_pOwnerClone = _pSKill; }
		bool IsClone() { return m_bClone; }

		SKill* GetClone() { return m_pOwnerClone; }

		void SetNullClone() { m_pSKillClone = nullptr; }
		SKill* GetSkillClone() { return m_pSKillClone; }

	private:
		void create_clone();

		//스킬은 interace만 확인
		void check_interface();
		bool changepos_interface();

	private:
		bool m_bTargetOn;
		bool m_bClone;//클론이면 움직임없이

		//내 클론 UI, 부모
		SKill* m_pSKillClone;
		SKill* m_pOwnerClone;
		Vector2 m_vDragStartPos;
		Vector3 m_vStartPos;

		SKillStorage::eSkillNuber m_eSkillNuber;
		Player::ePlayerSkill m_ePlayerSkill;
	};
}



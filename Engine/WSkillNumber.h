#pragma once
#include "WUI.h"
#include "WSKillStorage.h"

namespace W
{
	class SkillNumber : public UI
	{
	public:
		SkillNumber(SKillStorage::eSkillNuber _eSKillNumber);
		virtual ~SkillNumber();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		void SetActive(bool _bOn);
		bool IsActive() { return m_bActive; }

		SKillStorage::eSkillNuber GetSkillNumber() { return m_eSkillNumber; }

	private:
		bool m_bActive;

		SKillStorage::eSkillNuber m_eSkillNumber;
	};
}





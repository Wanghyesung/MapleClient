#pragma once
#include "WIconUI.h"
namespace W
{
	class Equip : public IconUI
	{
	public:
		enum class EquipType
		{
			//목걸이 모자 신발 바지 장비
			Pandant,
			Hat,
			Top,
			Bottom,
			Shoes,
			Weapon,
			None,
		};

		Equip();
		Equip(const Equip& _pEquip);
		virtual ~Equip();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		virtual Equip* Create_Clone()override;
		virtual void CheckPosition(int _iDir, Vector2 _vDiff)override;

		void SetEquipType(EquipType _eType) { m_eType = _eType; }
		EquipType GetEquipType() { return m_eType; }

		UINT GetCount() { return m_iCount; }

		const std::wstring& GetEquipName() { return m_strEquipName; }
		void SetEquipName(const std::wstring& _strName) { m_strEquipName = _strName; }

	private:
		bool changepos_equipstate();
		bool changepos_inventory();

	private:
		EquipType m_eType;
		UINT m_iCount;
		static UINT COUNT;

		//내 이름만 넘겨주기
		std::wstring m_strEquipName;
	};
}



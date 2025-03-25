#pragma once
#include "WUI.h"
#include "WIconUI.h"

namespace W
{
	class Player;

	class EquipState : public UI
	{
	public:
		EquipState();
		virtual ~EquipState();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		void RenderOn(bool _bOn) { m_bRenderOn = _bOn; }
		bool IsRender() { return m_bRenderOn; }

		void SetEquipPosition(IconUI* _pITem);
		void DisableEquip(Equip* _pEquip);

		Vector2 GetStartPosition() {return m_vUIStartPosition;}
		Vector2 GetEndPosition() { return m_vUIEndPosition; }
		Vector2 GetDiffPosition() { return m_vUIDiffPosition; }

		Vector2 GetPandantPosition() { return m_vPandantPosition; }
		Vector2	GetHatPosition() { return m_vHatPosition; }
		Vector2	GetTopPosition() { return m_vTopPosition; }
		Vector2 GetBottomPosition() { return m_vBottomPosition; }
		Vector2	GetShoesPosition() { return m_vShoesPosition; }
		Vector2	GetWeaponPosition() { return m_vWeaponPosition; }
	
		Equip* GetEquip(Equip::EquipType _eEquipType);

		void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
	private:
		void check_Equip(Equip* _pEquip);

	private:
		Player* m_pPlayer;

		bool m_bRenderOn;
		bool m_bTargetOn;

		Vector2 m_vDragStartPos;

		//std::map<std::wstring, IconUI*> m_mapItems;

		//내 UI좌표
		Vector2 m_vUIStartPosition;
		Vector2 m_vUIEndPosition;
		Vector2 m_vUIDiffPosition;

		//아이템 위치
		Vector2 m_vPandantPosition;
		Vector2	m_vHatPosition;
		Vector2	m_vTopPosition;
		Vector2	m_vBottomPosition;
		Vector2	m_vShoesPosition;
		Vector2	m_vWeaponPosition;

	};
}



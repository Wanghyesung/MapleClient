#pragma once
#include "WGameObject.h"
#include "WEquip.h"
namespace W
{
	class Shadow;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			alert,
			jump,
			ladder,
			pronestab,
			proneattack,
			stab,
			stand,
			swing1,
			swingOF,
			walk,
			dead,
			end
		};

		enum class ePlayerSkill
		{
			luck,
			dark,
			speed,
			jump,
			aven,
			shadow,
			quad,
			raid,
			wind,
			blast,
			load,
			ultimate,
			//
			end
		};

		enum ePlayerPart
		{
			Body,
			Head,
			Arm,
			End,
		};

		Player();
		virtual ~Player();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void UpdateState(const wstring& _strStateName, int _iState) override;

		void SetPlayerCurState(ePlayerState _eState)
		{
			m_ePrevPlayerState = m_ePlayerState;
			m_ePlayerState = _eState;
		}
		ePlayerState GetCurPlayerState() { return m_ePlayerState; }
		ePlayerState GetPrevPlayerState() { return m_ePrevPlayerState; }

		const std::wstring& GetCurStateName() { return m_strCurStateName; }
		void SetCurStateName(const std::wstring& _strName) { m_strCurStateName = _strName; }

		void SetEquip(Equip* _pEquip, bool _bSend = true);
		void SetEquip(Equip::EquipType _eType, const std::wstring& _strEquipName);
		void SetEquip(Equip::EquipType _eType, UINT _iEquipID);

		void DisableEquip(Equip* _pEquip, bool _bSend = true);

		bool IsAlert() { return m_bAlert; }

		template <typename T>
		T* GetPlayerChild(ePlayerPart _ePart)
		{
			return static_cast<T*>(m_vecChildObj[_ePart]);
		}

		UINT GetUserID() { return m_iPlayerID; }
		void SetTargetPlayer(UINT64 _llEquipIDs);
		void SetActiveShadow(bool _bActive) { m_bActiveShadow = _bActive; }

		void SetPlayerEquips(UINT64 _llEquipIDs);
	private:
		void child_render();
		void child_lateupdate();

		void init_attack_object();
		void init_attack_effect();

		void send_equip(Equip* _pEquip, UINT _iPlayerPartID, UINT _iPlayerEquipID);
		void update_shadow(bool _bActiveShadow);
	private:
		Shadow* m_pShadow;

		std::vector<GameObject*> m_vecChildObj;

		ePlayerState m_ePlayerState;
		ePlayerState m_ePrevPlayerState;

		UINT m_iPlayerID;

		bool m_bAlert;
		bool m_bActiveDark;

		bool m_bActiveShadow;
	
		float m_bAlertTime;
		float m_fChangeTime;

		friend class EventManager;
	};
}



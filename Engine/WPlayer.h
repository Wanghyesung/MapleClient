#pragma once
#include "WGameObject.h"
namespace W
{
	class Equip;
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

		//플레이어 리소스 미리 로드하고 연결하기
		void SetEquip(Equip* _pEquip);
		void DisableEquip(Equip* _pEquip);

		bool IsAlert() { return m_bAlert; }

		template <typename T>
		T* GetPlayerChild()
		{
			for (GameObject* pObj : m_vecChildObj)
			{
				T* pTarget = dynamic_cast<T*>(pObj);
				if (pTarget != nullptr)
					return pTarget;
			}
		}

		UINT GetUserID() { return m_iPlayerID; }
		void SetTargetPlayer();
	private:
		void child_render();
		void child_lateupdate();

		void init_attack_object();
		void init_attack_effect();
	private:
		std::vector<GameObject*> m_vecChildObj;

		ePlayerState m_ePlayerState;
		ePlayerState m_ePrevPlayerState;

		UINT m_iPlayerID;

		bool m_bAlert;
		bool m_bActiveDark;
	
		float m_bAlertTime;
		float m_fChangeTime;

		friend class EventManager;
	};
}



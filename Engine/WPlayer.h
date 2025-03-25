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

		void SetDir(int _iDir) { m_iDir = _iDir; }
		int GetDir() { return m_iDir; }
		

		void SetPlayerCurState(ePlayerState _eState) 
		{
			m_ePrevPlayerState = m_ePlayerState; 
			m_ePlayerState = _eState; 
		}
		ePlayerState GetCurPlayerState() { return m_ePlayerState; }
		ePlayerState GetPrevPlayerState() { return m_ePrevPlayerState; }

		void SetPlayerCurSkill(ePlayerSkill _ePlayerSkill) { m_ePlayerSkill = _ePlayerSkill; }
		ePlayerSkill GetCurPlayerSKill() { return m_ePlayerSkill; }

		const std::wstring& GetCurStateName() { return m_strCurStateName; }
		void SetCurStateName(const std::wstring& _strName) { m_strCurStateName = _strName; }

		bool IsShadow() { return m_bActiveShadow; }
		void SetShadow(bool _bActive) { m_bActiveShadow = _bActive; }

		Shadow* GetShadow() { return m_pShadow; }

		void SetDark(bool _bActive){m_bActiveDark = _bActive;}
		bool IsDark() { return m_bActiveDark; }

		//clone
		virtual void SetAlert(bool _bAlert);
		virtual bool IsAlert() { return m_bAlert; }

		void SetEquip(Equip* _pEquip);
		void DisableEquip(Equip* _pEquip);

		template <typename T>
		T* GetPlayerChild()
		{
			for (GameObject* pObj : m_vecChildObj)
			{
				T* pTarget= dynamic_cast<T*>(pObj);
				if (pTarget != nullptr)
					return pTarget;
			}
		}

		void SetAnimLoop(bool _bLoop) { m_bAnimLoop = _bLoop; }
		bool IsLoop() { return m_bAnimLoop; }

		bool IsAnimStop() { return m_bAnimStop; }
		void SetAnimStop(bool _bStop);
		
		void Reset_Animation();

		void SetHair(UINT _iHairNum);
		void SetEye(UINT _iEyeNum);
	private:
		void child_update();
		void child_render();
		void child_lateupdate();

	private:
		Shadow* m_pShadow;

		int m_iDir;

		bool m_bAnimLoop;
		bool m_bAnimStop;
		bool m_bAlert;
		bool m_bActiveDark;
		bool m_bActiveShadow;

		float m_bAlertTime;
		float m_fChangeTime;

		std::vector<GameObject*> m_vecChildObj;
		ePlayerState m_ePlayerState;
		ePlayerState m_ePrevPlayerState;

		ePlayerSkill m_ePlayerSkill;

		std::wstring m_strCurStateName;

	};
}



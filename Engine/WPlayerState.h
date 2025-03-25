#pragma once
#include "WPlayerFSM.h"

namespace W
{
	class PlayerState
	{
	public:
		PlayerState();
		~PlayerState();

		Player::ePlayerState GetType() { return m_ePlayerState; }
		void SetType(Player::ePlayerState _ePlayerState) { m_ePlayerState = _ePlayerState; }

		void SetCurFrame(int _iCurFrame) { m_iCurFrame = _iCurFrame; }
		int GetCurFrame() { return m_iCurFrame; }
		void InitZeroFrame() { m_iCurFrame = 0; }

		virtual void Update() = 0;
		virtual void Enter() = 0;
		virtual void Exit() = 0;

		PlayerFSM* GetFSM() { return m_pOwner; }
		void SetFSM(PlayerFSM* _pFSM) { m_pOwner = _pFSM; }

		Player* GetPlayer() { return GetFSM()->GetPlayer(); }

		void SetStateName(const std::wstring _strName) { m_strStateName = _strName; }
		const std::wstring GetStateName() { return m_strStateName; }
		
		void SetFunction(std::function<void()> _func) { m_pFunction = std::move(_func); }

	protected:
		std::function<void()> m_pFunction;

	private:
		Player::ePlayerState m_ePlayerState;
		PlayerFSM* m_pOwner;

		std::wstring m_strStateName;

		int m_iCurFrame;
	};
}



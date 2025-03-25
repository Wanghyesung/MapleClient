#pragma once
#include "WScript.h"

namespace W
{
	//class Player;
	class CameraScript : public Script
	{
	public:
		enum class eCameraEventType
		{
			Wave,
			None,
		};

		CameraScript();
		virtual ~CameraScript();

		virtual void Update() override;

		void SetPlayer(GameObject* _pPlayer) { m_pPlayer = _pPlayer; }
		void SetEventType(eCameraEventType _eType, float _fEndTime)
		{
			m_eCurEventType = _eType;
			m_fEventEndTime = _fEndTime;
		}
		
	private:
		Vector3 check_map(Vector3 _vPosition);

		void move();
		void move_player();

		void wave();
		
	private:
		bool m_bFadeWhite;
		
		eCameraEventType m_eCurEventType;
		GameObject* m_pPlayer;
		
		float m_fEventCurTime;
		float m_fEventEndTime;

		std::shared_ptr<Texture> m_spFadeInWhite;
	};

}


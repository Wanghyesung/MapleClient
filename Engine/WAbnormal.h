#pragma once
#include "WGameObject.h"

namespace W
{
	class Player;
	class Abnormal : public GameObject
	{
	public:
		Abnormal();
		virtual ~Abnormal();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore();

		void SetTime(float _fTime) { m_fDeleteTime = _fTime; }
		void SetTarget(Player* _pTarget) { m_pTarget = _pTarget; }
		void SetRenderPos(bool _bUp) { m_bRenderPosUp = _bUp; }

	protected:
		Player* m_pTarget;
		
	private:
		float m_fDeleteTime;
		float m_fCurTime;
		bool m_bRender;
		//타겟 위로 그릴지
		bool m_bRenderPosUp;

		friend class BattleManager;
	};
}



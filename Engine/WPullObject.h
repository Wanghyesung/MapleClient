#pragma once
#include "WGameObject.h"

namespace W
{
	class PullObject : public GameObject
	{
	public:
		PullObject();
		virtual ~PullObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetTarget(GameObject* _pTarget) { m_pTarget = _pTarget; }
		void SetPosition(Vector2 _vPosition) { m_vPullPosition = _vPosition; }
		void SetDeleteTime(float _fTime) { m_fDeleteTime = _fTime; }
	private:
		GameObject* m_pTarget;
		Vector2 m_vPullPosition;
		Vector2 m_vForece;

		float m_fCurTime;
		float m_fDeleteTime;
	};
}



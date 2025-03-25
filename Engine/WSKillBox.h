#pragma once

#include "WUI.h"
#include "WSKillStorage.h"

namespace W
{
	class SKillBox : public UI
	{
	public:
		SKillBox();
		virtual ~SKillBox();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();


	private:
		Vector3 m_vUIStartPosition;
		Vector3 m_vUIEndPosition;
		Vector3 m_vUIDiffPosition;
	};
}



#pragma once
#include "WUI.h"

namespace W
{
	class Channel;

	class ServerUI : public UI
	{
	public:
		ServerUI();
		virtual ~ServerUI();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		//void SetNextScene(const std::wstring& _strNextScene) { m_strNextScene = _strNextScene; }
	private:
		Channel* m_pChannel;
		//std::wstring m_strNextScene;

	};
}



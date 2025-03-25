#include "WInput.h"

#include "WApplication.h"
#include "WCamera.h"
#include "WRenderer.h"


extern W::Application application;

namespace W
{
	int ASCII[(UINT)eKeyCode::NONE] =
	{
		VK_LSHIFT,//LSHIFT,
		VK_INSERT,//ins
		VK_HOME,//home
		VK_PRIOR, //page up
		VK_CONTROL,//CTRL,
		VK_DELETE, //delete,
		VK_END,//end,
		VK_NEXT,//pdn,

		0x30,
		0x31,
		0x32,
		0x33,
		0x34,
		0x35,
		0x36,
		0x37,
		0x38,
		0x39,

		'Q', 'W', 'E', 'R', 'T',
		'A', 'S', 'D', 'F', 'G',

		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_RETURN,//ENTER,
		VK_LMENU,//ALT,
		VK_ESCAPE,//ESC,
		VK_SPACE,

		VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT,
		VK_LBUTTON, VK_RBUTTON,

		//WM_VSCROLL
	};


	std::vector<Input::Key> Input::m_vecKeys;
	Vector2 Input::m_vMousePos = Vector2::Zero;

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::NONE; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			m_vecKeys.push_back(keyInfo);
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{

			for (UINT i = 0; i < (UINT)eKeyCode::NONE; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다
					if (m_vecKeys[i].bPressed)
						m_vecKeys[i].state = eKeyState::Pressed;
					else
						m_vecKeys[i].state = eKeyState::Down;

					m_vecKeys[i].bPressed = true;
				}
				else // 현재 프레임에 키가 눌려있지 않다.
				{
					// 이전 프레임에 내키가 눌려있엇다.
					if (m_vecKeys[i].bPressed)
						m_vecKeys[i].state = eKeyState::Up;
					else
						m_vecKeys[i].state = eKeyState::None;

					m_vecKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);

			ScreenToClient(application.GetHwnd(), &mousePos);
			math::Vector3 vMousePos(mousePos.x, mousePos.y, 0.f);

			RECT tRect = {};
			GetClientRect(application.GetHwnd(), &tRect);

			math::Viewport view(0.f, 0.f, tRect.right - tRect.left, tRect.bottom - tRect.top);
			//renderer::MainCamera->GetGpuProjectionMatrix();
			vMousePos = view.Unproject(vMousePos, renderer::UICamera->GetGpuProjectionMatrix(), renderer::UICamera->GetViewMatrix(), Matrix::Identity);

			m_vMousePos.x = vMousePos.x;
			m_vMousePos.y = vMousePos.y;
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::NONE; i++)
			{
				if (eKeyState::Down == m_vecKeys[i].state
					|| eKeyState::Pressed == m_vecKeys[i].state)
				{
					m_vecKeys[i].state = eKeyState::Up;
				}
				else if (eKeyState::Up == m_vecKeys[i].state)
				{
					m_vecKeys[i].state = eKeyState::None;
				}

				m_vecKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}
}


#include "WSpeechBar.h"
#include "WTime.h"
#include "WInput.h"

namespace W
{
	extern int ASCII[(UINT)eKeyCode::NONE];

	SpeechBar::SpeechBar() :
		m_fRepeatTimer(0.5f),
		m_fCurTime(0.f),
		m_bStartBar(false),
		m_bCheckTime(false),
		m_strBaseSpeech(L""),
		m_iMaxSpeechSize(6)
	{
		m_fFontSize = 20.f;
		m_iFontColor = FONT_RGBA(255, 255, 255, 255);
	}
	SpeechBar::~SpeechBar()
	{

	}
	void SpeechBar::Update()
	{
		
	}
	void SpeechBar::LateUpdate()
	{
		if (m_bStartBar == false)
			base_speech();
		else
		{
			check_key();

			if (m_strSpeech.empty())
				repeat_startbar();
			else
				Speech(m_strSpeech, false, true, Vector2{ 30.f,0.f });
		}

		UI::LateUpdate();
	}
	void SpeechBar::Render()
	{

	}

	void SpeechBar::MouseOn()
	{
		UI::MouseOn();
	}
	void SpeechBar::MouseLbtnDown()
	{
		m_bStartBar = true; //Æ÷Ä¿½º

		UI::MouseLbtnDown();
	}
	void SpeechBar::MouseLbtnUp()
	{
		UI::MouseLbtnUp();
	}
	void SpeechBar::MouseLbtnClicked()
	{
		UI::MouseLbtnClicked();
	}
	void SpeechBar::check_time()
	{
		m_fCurTime += Time::DeltaTime();
		if (m_fCurTime >= m_fRepeatTimer)
		{
			m_fCurTime = 0.f;
			m_bCheckTime = !m_bCheckTime;
		}
	}
	void SpeechBar::base_speech()
	{
		Speech(m_strBaseSpeech, false, true, Vector2{ 30.f,0.f });
	}
	void SpeechBar::repeat_startbar()
	{
		check_time();

		if (m_bCheckTime)
			Speech(L"|", false, true, Vector2{ 30.f,0.f });
	}
	void SpeechBar::check_key()
	{
		for (UINT i = (UINT)eKeyCode::Q; i <= (UINT)eKeyCode::L; ++i)
		{
			if (Input::GetKeyDown((eKeyCode)i))
			{
				if (m_strSpeech.size() >= m_iMaxSpeechSize)
					continue;
		
				m_strSpeech += static_cast<WCHAR>(ASCII[i]);
			}
		}
		
		if (Input::GetKeyDown(eKeyCode::BACK_SPACE) && m_strSpeech.empty() == false)
			m_strSpeech.pop_back();
	
	}

}
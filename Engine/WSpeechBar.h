#pragma once
#include "WSpeechObject.h"

namespace W
{

	class SpeechBar : public SpeechObject
	{
	public:
		SpeechBar();
		virtual ~SpeechBar();

	public:
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	public:
		void SetBaseSpeech(const wstring& _strBaseSpeech) { m_strBaseSpeech = _strBaseSpeech; }

		void SetMaxSpeechSize(UINT _iSize) { m_iMaxSpeechSize = _iSize; }
		UINT GetMaxSpeechSize() { return m_iMaxSpeechSize; }


	private:
		void check_time();
		void base_speech();
		void repeat_startbar();

		void check_key();

	private:
		wstring m_strBaseSpeech;
		
		bool m_bStartBar;
		bool m_bCheckTime;

		float m_fRepeatTimer;
		float m_fCurTime;

		UINT m_iMaxSpeechSize;

	};
}
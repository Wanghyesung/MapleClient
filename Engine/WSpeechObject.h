#pragma once
#include "WFontWrapper.h"
#include "WUI.h"


namespace W
{
	class SpeechObject : public UI
	{
	public:
		SpeechObject();
		virtual ~SpeechObject();

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	public:
		void SetFontColor(float r, float g, float b, float a) { m_iFontColor = FONT_RGBA(r, g, b, a); }
		void SetFontSize(float _fSize) { m_fFontSize = _fSize; }
		void SetSpeech(const wstring& _strSpeech) { m_strSpeech = _strSpeech; };

		const wstring& GetSpeech() { return m_strSpeech; }

		float GetFontSize() { return m_fFontSize; }

	protected:
		Vector2 GetOffsetPosition();

		void Speech(const wstring& _strSpeech);
		void Speech(const wstring& _strSpeech, bool _bCenterAlignedX, bool _bCenterAlignedY, const Vector2& _vOffset = Vector2::Zero);

	protected:
		wstring m_strSpeech;
		tFontInfo m_tSpeechInfo;

		UINT m_iFontColor;
		float m_fFontSize;
	};
}
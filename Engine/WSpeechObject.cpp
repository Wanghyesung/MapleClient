#include "WSpeechObject.h"
#include "WApplication.h"


extern W::Application application;
namespace W
{	
	SpeechObject::SpeechObject():
		m_strSpeech{},
		m_tSpeechInfo{},
		m_fFontSize(20.f),
		m_iFontColor(FONT_RGBA(0.f, 0.f, 0.f, 255)),
		m_vOffsetPos{}
	{

	}
	SpeechObject::~SpeechObject()
	{

	}
	void SpeechObject::Update()
	{
	}
	void SpeechObject::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SpeechObject::Render()
	{

	}
	void SpeechObject::MouseOn()
	{
		UI::MouseOn();

	}
	void SpeechObject::MouseLbtnDown()
	{
		UI::MouseLbtnDown();
	}
	void SpeechObject::MouseLbtnUp()
	{
		UI::MouseLbtnUp();

	}
	void SpeechObject::MouseLbtnClicked()
	{
		UI::MouseLbtnClicked();
	}
	Vector2 SpeechObject::GetOffsetPosition()
	{
		Vector2 vWindoPosition = application.GetWindowSize() / 2.f;

		float fX = vWindoPosition.x + m_vOffsetPos.x;
		float fY = vWindoPosition.y + m_vOffsetPos.y;

		Vector2 vWindowPos = Vector2{ fX,fY };
	
		return vWindowPos;
	}
	void SpeechObject::Speech(const wstring& _strSpeech)
	{
		Vector2 vWindowPos = GetOffsetPosition();
		float fOffset = m_fFontSize / 2.f;
		vWindowPos.x -= fOffset;
		vWindowPos.y -= fOffset;

		if (vWindowPos.y < 0)
			return;

		FontWrapper::AddFont(_strSpeech, vWindowPos.x, vWindowPos.y, m_fFontSize, m_iFontColor);
	}
	void SpeechObject::Speech(const wstring& _strSpeech, bool _bCenterAlignedX, bool _bCenterAlignedY, const Vector2& _vOffset)
	{
		Vector3 vTransformScale = GetComponent<Transform>()->GetScale();
		Vector2 vWindowPos = GetOffsetPosition();

		if (_bCenterAlignedX == false)
			vWindowPos.x -= (vTransformScale.x / 2.f);
		if (_bCenterAlignedY == false)
			vWindowPos.y -= (vTransformScale.y / 2.f);

		float fOffset = m_fFontSize / 2.f;
		vWindowPos.x -= fOffset;
		vWindowPos.y -= fOffset;

		vWindowPos += _vOffset;

		if (vWindowPos.y < 0)
			return;

		FontWrapper::AddFont(_strSpeech, vWindowPos.x, vWindowPos.y, m_fFontSize, m_iFontColor);
	}
}



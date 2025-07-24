#include "WFontWrapper.h"
#include "WGraphicDevice_DX11.h"

namespace W
{
	IFW1Factory* FontWrapper::mFW1Factory = nullptr;
	IFW1FontWrapper* FontWrapper::mFontWrapper = nullptr;
	vector<tFontInfo> FontWrapper::m_vecFont = {};

	bool FontWrapper::Initialize()
	{
		if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
			return false;

		ID3D11Device* pDevice = GetDevice()->GetID3D11Device();
		if (FAILED(mFW1Factory->CreateFontWrapper(pDevice, L"Arial", &mFontWrapper)))
			return false;

		return true;
	}

	void FontWrapper::Render()
	{
		for (int i = 0; i < m_vecFont.size(); ++i)
		{
			DrawFont(m_vecFont[i].Str.c_str(), m_vecFont[i].fPosX, m_vecFont[i].fPosY, m_vecFont[i].fFontSize, m_vecFont[i].Color);
		}

		m_vecFont.clear();
	}

	void FontWrapper::DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb)
	{
		//RGB();
		ID3D11DeviceContext* pContext = GetDevice()->GetID3D11DeviceContext();
		mFontWrapper->DrawString(
			pContext,
			str, // String
			size,// Font size
			x,// X position
			y,// Y position
			rgb,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE      // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
		);
	}

	void FontWrapper::Release()
	{
		mFW1Factory->Release();
		mFW1Factory = nullptr;

		mFontWrapper->Release();
		mFontWrapper = nullptr;
	}

	void FontWrapper::AddFont(const wstring& _strString, float _fPosX, float _fPosY, float _fFontSize, UINT _Color)
	{
		tFontInfo tFont = {};
		tFont.Str = _strString;
		tFont.fPosX = _fPosX;
		tFont.fPosY = _fPosY;
		tFont.fFontSize = _fFontSize;
		tFont.Color = _Color;
		m_vecFont.emplace_back(tFont);
	}
}

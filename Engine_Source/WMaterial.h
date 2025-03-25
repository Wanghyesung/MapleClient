#pragma once

#include "WResource.h"
#include "WShader.h"
#include "WTexture.h"

namespace W::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& _strPath);
			
		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<Shader> _pSahder) { m_pShader = _pSahder; }
		void SetTexture(std::shared_ptr<Texture> _pTex) { m_pTex = _pTex; }
		void SetRenderinMode(eRenderingMode _eMode) { m_eMode = _eMode; }
		eRenderingMode GetRenderinMode() { return m_eMode; }

	private:
		std::shared_ptr<Shader> m_pShader;
		std::shared_ptr<Texture> m_pTex;

		eRenderingMode m_eMode;
	};
}



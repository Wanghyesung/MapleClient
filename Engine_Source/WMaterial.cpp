#include "WMaterial.h"


namespace W::graphics
{
	Material::Material() :
		Resource(W::enums::eResourceType::Material),
		m_pShader(nullptr),
		m_pTex(nullptr),
		m_eMode(eRenderingMode::Opaque)
	{
	}
	Material::~Material()
	{
		
	}
	HRESULT Material::Load(const std::wstring& _strPath)
	{
		return E_NOTIMPL;
	}
	void Material::Binds()
	{
		if (m_pTex)
			m_pTex->BindShaderResource(eShaderStage::PS, 0);

		if (m_pShader)
			m_pShader->Binds();
	}
	void Material::Clear()
	{
		m_pTex->Clear();
	}
}
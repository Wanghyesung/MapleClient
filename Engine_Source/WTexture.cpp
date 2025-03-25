#include "WTexture.h"
#include "WGraphicDevice_Dx11.h"

namespace W::graphics
{
	Texture::Texture():
		Resource(enums::eResourceType::Texture),
		m_Image{},
		m_cpTexture(nullptr),
		m_cpSRV(nullptr),
		m_tDesc{}
	{
	}
	Texture::~Texture()
	{
		
	}
	bool Texture::Create(UINT _iWidth, UINT _iHeight, DXGI_FORMAT _format, UINT _iBindFlag)
	{
		if (m_cpTexture == nullptr)
		{
			m_tDesc.BindFlags = _iBindFlag;
			m_tDesc.Usage = D3D11_USAGE_DEFAULT;
			m_tDesc.CPUAccessFlags = 0;
			m_tDesc.Format = _format;
			m_tDesc.Width = _iWidth;
			m_tDesc.Height = _iHeight;
			m_tDesc.ArraySize = 1;

			m_tDesc.SampleDesc.Count = 1;
			m_tDesc.SampleDesc.Quality = 0;

			m_tDesc.MipLevels = 0;
			m_tDesc.MiscFlags = 0;
			
			m_iWidth = _iWidth;
			m_iHeight = _iHeight;

			if (!GetDevice()->CreateTexture2D(&m_tDesc, nullptr, m_cpTexture.GetAddressOf()))
				return false;
		}

		if (_iBindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CreateDepthStencilView(m_cpTexture.Get(), nullptr, m_cpDSV.GetAddressOf()))
				return false;
		}

		if (_iBindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = m_tDesc.Format;
			tSRVDesc.Texture2D.MipLevels = 1;
			tSRVDesc.Texture2D.MostDetailedMip = 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(m_cpTexture.Get(), &tSRVDesc, m_cpSRV.GetAddressOf()))
				return false;
		}
		if (_iBindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = m_tDesc.Format;
			tSRVDesc.Texture2D.MipSlice = 0;
			tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateRenderTargetView(m_cpTexture.Get(), nullptr, m_cpRTV.GetAddressOf()))
				return false;
		}
		if (_iBindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format = m_tDesc.Format;
			tUAVDesc.Texture2D.MipSlice = 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateUnorderedAccessView(m_cpTexture.Get(), nullptr, m_cpUAV.GetAddressOf()))
				return false;
		}

		return false;
	}
	HRESULT Texture::Load(const std::wstring& _strPath)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(_strPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);
		
		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(_strPath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(_strPath.c_str(), nullptr, m_Image)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(_strPath.c_str(), WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, nullptr, m_Image)))
				assert(false);
				//assert(false);
			//WIC_FLAGS_IGNORE_SRGB
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, m_Image.GetImages()
			, m_Image.GetImageCount()
			, m_Image.GetMetadata()
			, m_cpSRV.GetAddressOf()
		);
		m_cpSRV->GetResource((ID3D11Resource**)m_cpTexture.GetAddressOf());
		
		m_iWidth = m_Image.GetMetadata().width;
		m_iHeight = m_Image.GetMetadata().height;

		return S_OK;
	}
	void Texture::BindShaderResource(eShaderStage _eStage, UINT _iStartSlot)
	{
		//픽셀 셰이더와 texture(shaderResource)로 묶어주기 텍스쳐의 픽셀을 출력하기
		//텍스쳐 좌표 uv좌표 셋팅, 이미지와 내 화편의 크기가 다르면 보간이 되어서 와야함 (샘플링) samplerstate(샘플링옵션)
		
		GetDevice()->BindShaderResource(_eStage, _iStartSlot, m_cpSRV.GetAddressOf());
	}
	void Texture::BindUnorderedAccessViews(UINT _iSlot)
	{
		UINT i = -1;
		GetDevice()->BinUnorderedAccess(_iSlot, m_cpUAV.GetAddressOf(), &i);
	}
	void Texture::ClearUnorderedAccessViews(UINT _iSlot)
	{
		ID3D11UnorderedAccessView* p = nullptr;
		UINT i = -1;
		GetDevice()->BinUnorderedAccess(_iSlot, &p, &i);
	}
	void Texture::Clear()
	{
		//전부 nullptr로 묶어서 지우기
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->BindShaderResource(eShaderStage::VS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, 0, &srv);
	}
}


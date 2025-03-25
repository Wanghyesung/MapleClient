#pragma once

#include "WResource.h"
#include "WGraphics.h"

#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "..\External\DirectXTex\Include\DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

//gpu로 계산, 등 gpu를 활용하게
//컴퓨트셰이더 접근에 필요  

namespace W::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		bool Create(UINT _iWidth, UINT _iHeight, DXGI_FORMAT _format, UINT _iBindFlag);
		virtual HRESULT Load(const std::wstring& _strPath);
		void BindShaderResource(eShaderStage _eStage, UINT _iStartSlot);
		void BindUnorderedAccessViews(UINT _iSlot);
		void ClearUnorderedAccessViews(UINT _iSlot);
		void Clear();

		size_t GetWidth() { return m_iWidth; }
		size_t GetHeight() { return m_iHeight; }

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    GetRTV() { return  m_cpRTV; }
		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { m_cpRTV = rtv; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    GetDSV() { return  m_cpDSV; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { m_cpDSV = dsv; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  GetSRV() { return  m_cpSRV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return  m_cpUAV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return m_cpTexture; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { m_cpTexture = texture; }

	private:
		//scratchImage원본이미지의 정보들이 들어있는 확장자
		ScratchImage m_Image;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpTexture;//2d이미지
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cpSRV;//shader접근할 view
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cpRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cpDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_cpUAV;
		UINT m_iWidth;
		UINT m_iHeight;

		D3D11_TEXTURE2D_DESC m_tDesc;
	};

	//텍스쳐(uv좌표)의 픽셀을 하나하나 옮겨가져옴(2dTexture)
	//텍스쳐도 다른 그래픽스 객체와 같이 view를 통해서 접근 shader에서 접근하는 view(shaderview)가 따로 있음 텍스쳐가 shader을 통해서 출력되기 떄문에 
	//shader또한 상수버퍼와 같이 slot을 구분함 버퍼는b 텍스쳐는 t로 구분
}



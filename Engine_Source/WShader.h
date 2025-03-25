#pragma once

#include "WResource.h"

#include "WGraphics.h"
#include "WGraphicDevice_Dx11.h"

namespace W 
{
	using namespace graphics;
	class Shader : public Resource
	{
	public:
		Shader();
		virtual ~Shader();

		virtual HRESULT Load(const std::wstring& path) override;
		
		bool Create(const eShaderStage _eStage, const std::wstring& _wstrFileName, const std::string& _strFuncName);
		void Binds();

		ID3DBlob* GetVSCode() { return m_cpVSBlop.Get();}
		ID3D11InputLayout* GetInputLayout() { return m_tInputLayout; }
		ID3D11InputLayout** GetInputLayoutAddressOf() { return &m_tInputLayout; }

		void SetRSState(eRSType _eType) { m_eRSType = _eType; }
		void SetDSState(eDSType _eType) { m_eDSType = _eType; }
		void SetBSState(eBSType _eType) { m_eBSType = _eType; }

		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _eTopology) { m_eTopology = _eTopology; }
	private:
		ID3D11InputLayout* m_tInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY m_eTopology;

		Microsoft::WRL::ComPtr<ID3DBlob> m_cpVSBlop;
		Microsoft::WRL::ComPtr<ID3DBlob> m_cpHSBlop;
		Microsoft::WRL::ComPtr<ID3DBlob> m_cpDSBlop;
		Microsoft::WRL::ComPtr<ID3DBlob> m_cpGSBlop;
		Microsoft::WRL::ComPtr<ID3DBlob> m_cpPSBlop;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_cpVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> m_cpHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> m_cpDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_cpGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_cpPS;

		eRSType m_eRSType;
		eDSType m_eDSType;
		eBSType m_eBSType;
	};
}



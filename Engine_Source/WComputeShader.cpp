#include "WComputeShader.h"
#include "WGraphicDevice_Dx11.h"
#include "WPathManager.h"

namespace W
{
	ComputeShader::ComputeShader():
		Resource(eResourceType::ComputeShader)
	{
		m_iThreadGroupCountX = 32;
		m_iThreadGroupCountY = 32;
		m_iThreadGroupCountZ = 1;
	}
	ComputeShader::ComputeShader(UINT _ix, UINT _iY, UINT _iZ):
		Resource(eResourceType::ComputeShader)
	{
		m_iThreadGroupCountX = _ix;
		m_iThreadGroupCountY = _iY;
		m_iThreadGroupCountZ = _iZ;
	}
	ComputeShader::~ComputeShader()
	{

	}
	bool ComputeShader::Create(const std::wstring& _strName, const std::string& _strMethdName)
	{
		std::wstring shaderPath = PathManager::GetContentPath();
		shaderPath += L"\\Shader_Source\\";
		shaderPath += _strName;

		ID3DBlob* errorBlob = nullptr;
		GetDevice()->CompileFromfile(shaderPath, _strMethdName, "cs_5_0", m_cpCSBlob.GetAddressOf());
		GetDevice()->CreateComputeShader(m_cpCSBlob->GetBufferPointer()
			, m_cpCSBlob->GetBufferSize(), m_cpCS.GetAddressOf());

		return true;
	}
	void ComputeShader::OnExcute()
	{
		Binds();

		//gpu 스레드 실행
		GetDevice()->BindComputeShader(m_cpCS.Get());
		GetDevice()->Dispatch(m_iGroupX, m_iGroupY, m_iGroupZ);

		Clear();
	}
	void ComputeShader::Binds()
	{

	}
	void ComputeShader::Clear()
	{

	}
}



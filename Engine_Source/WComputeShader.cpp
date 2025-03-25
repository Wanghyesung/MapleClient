#include "WComputeShader.h"
#include "WGraphicDevice_Dx11.h"
namespace W::graphics
{
	ComputeShader::ComputeShader():
		Resource(enums::eResourceType::ComputeShader)
	{
		m_iThreadGroupCountX = 32;
		m_iThreadGroupCountY = 32;
		m_iThreadGroupCountZ = 1;
	}
	ComputeShader::ComputeShader(UINT _ix, UINT _iY, UINT _iZ):
		Resource(enums::eResourceType::ComputeShader)
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
		std::filesystem::path shaderPath
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_Source\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += _strName;

		ID3DBlob* errorBlob = nullptr;
		graphics::GetDevice()->CompileFromfile(fullPath, _strMethdName, "cs_5_0", m_cpCSBlob.GetAddressOf());
		graphics::GetDevice()->CreateComputeShader(m_cpCSBlob->GetBufferPointer()
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



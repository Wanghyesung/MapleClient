#include "WConstantBuffer.h"
#include "WGraphicDevice_Dx11.h"

namespace W::graphics
{
	ConstantBuffer::ConstantBuffer(const eCBType _eType) :
		GpuBuffer(),
		m_eType(_eType)
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{

	}
	bool ConstantBuffer::Create(size_t _size)
	{
		//상속받은 버퍼 구조체
		desc.ByteWidth = _size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		W::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return true;
	}
	void ConstantBuffer::SetData(void* _data)
	{
		W::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), _data, desc.ByteWidth);
	}
	void ConstantBuffer::Bind(eShaderStage _eStage)
	{
		W::graphics::GetDevice()->BindConstantBuffer(_eStage, m_eType, buffer.Get());
	}
}
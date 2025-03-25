#include "WStructedBuffer.h"
#include "WGraphicDevice_Dx11.h"


namespace W::graphics
{
	StructedBuffer::StructedBuffer():
		GpuBuffer(),
		m_eType(eViewType::SRV),
		m_cpSRV(nullptr),
		m_iSize(0),
		m_iStride(0),
		m_iSRVSlot(0),
		m_iUAVSlot(0)
	{

	}

	StructedBuffer::~StructedBuffer()
	{

	}

	bool StructedBuffer::Create(UINT _iSize, UINT _iStride, eViewType _eType, void* _data, bool cpuAccess)
	{
		m_eType = _eType;

		m_iStride = _iStride;
		m_iSize = _iSize;

		desc.ByteWidth = m_iSize * m_iStride;
		desc.StructureByteStride = m_iSize;

		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		//desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정

		if (m_eType == eViewType::UAV)
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE
			| D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;	// Texture Register Binding
			desc.CPUAccessFlags = 0;
		}

		if (_data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = _data;

			if (!(GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, &tSub)))
				return false;
		}

		else
		{
			if (!(GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr)))
				return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = m_iStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, m_cpSRV.GetAddressOf())))
			return false;

		if (m_eType == eViewType::UAV)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Buffer.NumElements = m_iStride;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			if (!GetDevice()->CreateUnorderedAccessView(buffer.Get(), &uavDesc, m_cpUAV.GetAddressOf()))
				return false;
		}

		if (cpuAccess)
			CreateRWbuffer();

		return true;
	}

	bool StructedBuffer::CreateRWbuffer()
	{
		D3D11_BUFFER_DESC wDesc(desc);

		wDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정
		wDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

		wDesc.Usage = D3D11_USAGE_DYNAMIC;
		wDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if(!GetDevice()->CreateBuffer(m_cpWriteBuffer.GetAddressOf(), &wDesc, nullptr))
			return false;

		D3D11_BUFFER_DESC rDesc(desc);

		rDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정
		rDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

		rDesc.Usage = D3D11_USAGE_DEFAULT;
		rDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		if (!GetDevice()->CreateBuffer(m_cpReadBuffer.GetAddressOf(), &rDesc, nullptr))
			return false;

		return true;
	}

	void StructedBuffer::SetData(void* data, UINT bufferCount)
	{
		//쓰고 복사
		//writebuffer -> minabuffer 
		if (m_iStride < bufferCount)
			Create(m_iSize, bufferCount, m_eType, data);
		else
			GetDevice()->BindBuffer(m_cpWriteBuffer.Get(), data, m_iSize * bufferCount);

		GetDevice()->CopyResource(buffer.Get(), m_cpWriteBuffer.Get());
	}

	void StructedBuffer::GetData(void* data, UINT _iSize)
	{
		GetDevice()->CopyResource(m_cpReadBuffer.Get(), buffer.Get());

		if (_iSize == 0)
			GetDevice()->BindBuffer(m_cpReadBuffer.Get(), data, m_iSize * m_iStride);
		else
			GetDevice()->BindBuffer(m_cpReadBuffer.Get(), data, _iSize);

	}

	void StructedBuffer::BindSRV(eShaderStage _eStage, UINT _iSlot)
	{
		m_iSRVSlot = _iSlot;
		GetDevice()->BindShaderResource(_eStage, _iSlot, m_cpSRV.GetAddressOf());
	}

	void StructedBuffer::BindUAV(UINT slot)
	{
		m_iUAVSlot = slot;
		UINT i = -1;
		GetDevice()->BinUnorderedAccess(slot, m_cpUAV.GetAddressOf(),&i);
	}

	void StructedBuffer::Clear()
	{
		// srv clear
		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::VS, m_iSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, m_iSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, m_iSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, m_iSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, m_iSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, m_iSRVSlot, &srv);

		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		GetDevice()->BinUnorderedAccess(m_iUAVSlot, &uav, &i);

		// uav clear
	}

}
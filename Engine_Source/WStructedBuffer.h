#pragma once
#include "WEntity.h"
#include "WGraphics.h"
namespace W::graphics
{
	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		virtual ~StructedBuffer();

		bool Create(UINT _iSize, UINT _iStride, eViewType _eType, void* _data, bool cpuAccess = false);
		bool CreateRWbuffer();

		void SetData(void* data, UINT _ibufferCount);
		void GetData(void* data, UINT _iSize);
		void BindSRV(eShaderStage _eStage, UINT _iSlot);
		void BindUAV(UINT slot);

		void Clear();

		UINT GetSize() { return m_iSize; }
		UINT GetStride() { return m_iStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_cpReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_cpWriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cpSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_cpUAV;
		eViewType m_eType;

		UINT m_iSize;
		UINT m_iStride;

		UINT m_iSRVSlot;
		UINT m_iUAVSlot;
	};
}



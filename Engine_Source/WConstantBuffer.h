#pragma once

#include "WGraphics.h"

namespace W::graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	public:
		ConstantBuffer(const eCBType _eType);
		virtual ~ConstantBuffer();

		bool Create(size_t _size);
		void SetData(void* _data);
		void Bind(eShaderStage _eStage);
	private:
		const eCBType m_eType;

	};
}



#pragma once
#include "WComputeShader.h"
#include "WStructedBuffer.h"

namespace W::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		virtual ~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetParicleBuffer(StructedBuffer* _pParticleBuffer);
		void SetSharedBuffer(StructedBuffer* _pSharedBuffer) { m_pSharedBuffer = _pSharedBuffer; }

	private:
		StructedBuffer* m_pParticleBuffer;
		StructedBuffer* m_pSharedBuffer;
	};
}



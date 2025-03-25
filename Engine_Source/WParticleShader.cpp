#include "WParticleShader.h"
#include "WRenderer.h"
#include "WConstantBuffer.h"
#include "WTime.h"

namespace W::graphics
{
	ParticleShader::ParticleShader():
		ComputeShader(128,1,1),
		m_pParticleBuffer(nullptr)
	{
	}
	ParticleShader::~ParticleShader()
	{
	}
	void ParticleShader::Binds()
	{
		m_pParticleBuffer->BindUAV(0);
		m_pSharedBuffer->BindUAV(1);

		m_iGroupX = m_pParticleBuffer->GetStride() / m_iThreadGroupCountX + 1;
		m_iGroupY = 1;
		m_iGroupZ = 1;
	}
	void ParticleShader::Clear()
	{
		m_pParticleBuffer->Clear();
		m_pSharedBuffer->Clear();
	}
	void ParticleShader::SetParicleBuffer(StructedBuffer* _pParticleBuffer)
	{
		m_pParticleBuffer = _pParticleBuffer;

		ConstantBuffer* pCB = renderer::constantBuffer[(UINT)eCBType::Particle];
		
		static float elapsedTime = 0.f;
		elapsedTime += Time::DeltaTime();

		renderer::ParticleCB data = {};
		data.elementCount = m_pParticleBuffer->GetStride();
		data.elpasedTime = elapsedTime;
		data.deltaTime = Time::DeltaTime();

		pCB->SetData(&data);
		pCB->Bind(eShaderStage::CS);

	}
}

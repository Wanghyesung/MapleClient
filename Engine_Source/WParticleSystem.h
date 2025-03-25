#pragma once
#include "WMeshRenderer.h"
#include "WStructedBuffer.h"
#include "WParticleShader.h"

namespace W
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		graphics::StructedBuffer* m_pBuffer;
		graphics::StructedBuffer* m_pSharedBuffer;

		std::shared_ptr<ParticleShader> m_spCS;

		UINT m_iCount;
		Vector4 m_vStartSize;
		Vector4 m_vEndSize;
		Vector4 m_vStartColor;
		Vector4 m_vEndColor;
		float m_fLifeTime;
		float m_fFrequency;

		float m_fTime;
	};

}


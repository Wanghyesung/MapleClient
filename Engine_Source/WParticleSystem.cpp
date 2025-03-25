#include "WParticleSystem.h"

#include "WTime.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WResources.h"
#include "WTransform.h"
#include "WGameObject.h"
namespace W
{
	ParticleSystem::ParticleSystem():
		m_iCount(0),
		m_vStartColor(Vector4::One),
		m_vEndSize(Vector4::One),
		m_vStartSize(Vector4::One),
		m_vEndColor(Vector4::One),
		m_fLifeTime(0.f),
		m_fTime(0.f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		m_spCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;
			//위치는 gpu에서 랜덤으로

			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i / 10.f * XM_2PI)
					, 0.0f, 1.0f);
			//	Vector4(cosf((float)i * (XM_2PI / (float)1000))
			//		, sinf((float)i * (XM_2PI / 100.f))
			//		, 0.0f, 1.0f);

			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
			particles[i].time = 0.f;
		}

		m_pBuffer = new graphics::StructedBuffer();
		m_pBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, particles);

		//cpu gpu 읽고 쓰기 기능
		m_pSharedBuffer = new graphics::StructedBuffer();
		m_pSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
		
		//ParticleShared shareData = {};
		//shareData.sharedActiveCount = 1000;
		//mSharedBuffer->SetData(&shareData, 1);
		//mBuffer->SetData(particles, 100);
	}

	ParticleSystem::~ParticleSystem()
	{
		if (m_pBuffer != nullptr)
		{
			delete m_pBuffer;
		}

		if (m_pSharedBuffer != nullptr)
		{
			delete m_pSharedBuffer;
		}
	}
	void ParticleSystem::Initialize()
	{
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = 1.0f / 1.0f;
		m_fTime += Time::DeltaTime();

		if (m_fTime > AliveTime)
		{
			float f = (m_fTime / AliveTime);
			UINT AliveCount = (UINT)f;
			m_fTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 2;
			m_pSharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			m_pSharedBuffer->SetData(&shareData, 1);
		}


		m_spCS->SetParicleBuffer(m_pBuffer);
		m_spCS->SetSharedBuffer(m_pSharedBuffer);
		m_spCS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		m_pBuffer->BindSRV(eShaderStage::VS, 14);
		m_pBuffer->BindSRV(eShaderStage::GS, 14);
		m_pBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		m_pBuffer->Clear();
	}
}
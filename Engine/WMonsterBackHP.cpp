#include "WMonsterBackHP.h"
#include "WMonsterHP.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	MonsterBackHP::MonsterBackHP(bool _bBoss)
	{
		std::shared_ptr<Texture> pAtlas;
		if (!_bBoss)
		{
			pAtlas = Resources::Load<Texture>(L"MonBackHP", L"..\\Resources\\Texture\\MonsterUI\\energebar.png");
			GetComponent<Transform>()->SetScale(1.f * 0.7f, 1.f * 0.13f, 0.f);
		}
		else
		{
			pAtlas = Resources::Load<Texture>(L"MonBackBossHP", L"..\\Resources\\Texture\\MonsterUI\\boss_energebar.png");
			GetComponent<Transform>()->SetScale(1.2f * 8.01f, 1.2f * 0.4f, 0.f);
		}
		
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"MonBackHP", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		pMater->SetTexture(pAtlas);

		
	}
	MonsterBackHP::~MonsterBackHP()
	{

	}
	void MonsterBackHP::Initialize()
	{

	}
	void MonsterBackHP::Update()
	{
		
	}
	void MonsterBackHP::LateUpdate()
	{
	
		GameObject::LateUpdate();
	}
	void MonsterBackHP::Render()
	{
	
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectColor = Vector4::One;
		
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}


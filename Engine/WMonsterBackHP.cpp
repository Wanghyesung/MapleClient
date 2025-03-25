#include "WMonsterBackHP.h"
#include "WMonsterHP.h"
#include "WResources.h"
#include "WRenderer.h"

namespace W
{
	MonsterBackHP::MonsterBackHP(bool _bBoss):
		m_pHP(nullptr)
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
		if (!m_pHP->IsActive())
			return;

		Vector3 vPosition = m_pHP->GetComponent<Transform>()->GetPosition();
		vPosition.z += 0.01f;
		if(m_pHP->IsBoss())
			vPosition.x -= 0.2f;

		GetComponent<Transform>()->SetPosition(vPosition);

		GameObject::Update();
	}
	void MonsterBackHP::LateUpdate()
	{
		if (!m_pHP->IsActive())
			return;

		GameObject::LateUpdate();
	}
	void MonsterBackHP::Render()
	{
		if (!m_pHP->IsActive())
			return;

		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectColor = Vector4::One;
		
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}


#include "WCloneMegnus.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRenderer.h"
#include "WMonsterScript.h"
namespace W
{
	CloneMegnus::CloneMegnus():
		m_iCallCount(0),
		m_tMonsterAttack{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"CloneMegnusMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(false);
		
		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_attack1_effect");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Clone_Megnus", pAtlas, Vector2(0.0f, 0.0f), Vector2(408.f, 354.0f), 27, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);

		pAnim->CompleteEvent(L"Clone_Megnus") = std::bind(&CloneMegnus::off, this);
		pAnim->Play(L"Clone_Megnus", true);
	}
	CloneMegnus::~CloneMegnus()
	{

	}
	void CloneMegnus::Initialize()
	{
		float faccAttack = GetOwner()->GetScript<MonsterScript>()->GetAttackInfo().fAttack;
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 1000.f + faccAttack;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = (Vector2(0.2f, 0.2f));
		m_tMonsterAttack.vOffset = Vector2(0.f, -1.f);

		m_tMonsterAttack.iStartFrame = 20;
		m_tMonsterAttack.iEndFrame = 24;
	}
	void CloneMegnus::Update()
	{
		GameObject::Update();
	}
	void CloneMegnus::LateUpdate()
	{
		Animation* pAnim = GetComponent<Animator>()->GetActiveAnimation();

		int iIndex = pAnim->GetCurIndex();
		if (iIndex >= m_tMonsterAttack.iStartFrame && m_iCallCount == 0)
		{
			m_iCallCount = 1;
			//지금 실행중인 데미지 정보 넘기기
			SetMonsterAttack(m_tMonsterAttack);
		}

		if (m_iCallCount == 1 && iIndex >= m_tMonsterAttack.iEndFrame)
		{
			m_iCallCount = 2;
			GetComponent<Collider2D>()->SetActive(false);
		}

		GameObject::LateUpdate();
	}
	void CloneMegnus::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void CloneMegnus::off()
	{
		m_iCallCount = 0;
		EventManager::AddMonsterPool(this);
	}
}
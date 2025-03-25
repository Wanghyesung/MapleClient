#include "WArielLaser.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonsterAttackScript.h"
#include "WMonsterScript.h"
#include "WPlayerScript.h"
#include "WMonster.h"
namespace W
{
	ArielLaser::ArielLaser():
		m_iCallCount(0),
		m_tMonsterAttack{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"ArileStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(false);

		GetComponent<Transform>()->SetScale(8.5f, 8.5f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Ariel_attack0");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Laser", pAtlas, Vector2(0.0f, 0.0f), Vector2(189.f, 847.0f), 20, Vector2(850.f, 850.f), Vector2::Zero, 0.15f);

		pAnim->CompleteEvent(L"Laser") = std::bind(&ArielLaser::off, this);
		pAnim->Play(L"Laser", true);

	}
	ArielLaser::~ArielLaser()
	{

	}
	void ArielLaser::Initialize()
	{
		const tObjectInfo& tInfo = SceneManger::FindPlayer()->GetScript<PlayerScript>()->GetObjectInfo();
		//float faccAttack = GetOwner()->GetAttackInfo().fAttack;
		m_tMonsterAttack.tAttackInfo.fAttackDamage = (tInfo.fMaxHP * (10.f/4.f));

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = (Vector2(0.15f, 1.f));
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);

		m_tMonsterAttack.iStartFrame = 15;
		m_tMonsterAttack.iEndFrame = 16;
	}
	void ArielLaser::Update()
	{
		GameObject::Update();
	}
	void ArielLaser::LateUpdate()
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
	void ArielLaser::Render()
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
	void ArielLaser::off()
	{
		m_iCallCount = 0;
		EventManager::AddMonsterPool(this);
	}
}
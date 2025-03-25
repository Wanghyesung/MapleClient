#include "WSwordExplode.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonsterAttackScript.h"
#include "WMonster.h",
#include "WDemianSword.h"
namespace W
{
	SwordExplode::SwordExplode() :
		m_iCallCount(0),
		m_tMonsterAttack{},
		m_pSword(nullptr),
		m_iExplodeCount(3)
	{
		GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"SwordExplodeMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);


		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"swordExplodeTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"start", pAtlas, Vector2(0.0f, 0.0f), Vector2(614.f, 557.0f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"explode", pAtlas, Vector2(0.0f, 557.0f), Vector2(614.f, 557.0f), 23, Vector2(2000.f, 2000.f), Vector2::Zero, 0.1f);

		pAnim->CompleteEvent(L"explode") = std::bind(&SwordExplode::check, this);
		pAnim->CompleteEvent(L"start") = std::bind(&SwordExplode::start, this);

	}

	SwordExplode::~SwordExplode()
	{

	}

	void SwordExplode::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.18f, 0.1f);
		m_tMonsterAttack.vOffset = Vector2(0.f, -0.6f);

		m_tMonsterAttack.iStartFrame = 16;
		m_tMonsterAttack.iEndFrame = 18;

		GetComponent<Animator>()->Play(L"start", true);
	}

	void SwordExplode::Update()
	{
		GameObject::Update();
	}

	void SwordExplode::LateUpdate()
	{
		Animation* pAnim = GetComponent<Animator>()->GetActiveAnimation();

		int iIndex = pAnim->GetCurIndex();
		if (iIndex >= m_tMonsterAttack.iStartFrame && m_iCallCount == 0)
		{
			m_iCallCount = 1;
			//지금 실행중인 데미지 정보 넘기기
			SetMonsterAttack(m_tMonsterAttack);
			GetComponent<Collider2D>()->SetActive(true);
		}

		if (m_iCallCount == 1 && iIndex >= m_tMonsterAttack.iEndFrame)
		{
			m_iCallCount = 2;
			GetComponent<Collider2D>()->SetActive(false);
		}

		GameObject::LateUpdate();
	}
	void SwordExplode::Render()
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
	void SwordExplode::off()
	{
		m_iExplodeCount = 3;
		m_iCallCount = 0;
		EventManager::AddMonsterPool(this);
		GetScript<MonsterAttackScript>()->InitStack();
	}
	void SwordExplode::start()
	{
		GetComponent<Animator>()->Play(L"explode", true);
	}
	void SwordExplode::check()
	{
		m_iCallCount = 0;
		--m_iExplodeCount;
		if (m_iExplodeCount <= 0)
		{
			m_pSword->restart();

			Vector3 vPosition = GetComponent<Transform>()->GetPosition();
			vPosition.y = -1.85f;
			m_pSword->GetComponent<Transform>()->SetPosition(vPosition);

			off();
		}
	}
}
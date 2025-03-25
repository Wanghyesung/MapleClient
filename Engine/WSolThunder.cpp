#include "WSolThunder.h"
#include "WSceneManger.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	SolThunder::SolThunder():
		m_pTarget(nullptr)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"SolThunderMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();

		GetComponent<Transform>()->SetScale(8.f, 8.f, 0.f);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"Solomon_attack1");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Thunder_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(172.f, 817.0f), 5, Vector2(800.f, 800.f), Vector2::Zero, 0.3f);
	
		pAnim->CompleteEvent(L"Thunder_left") = std::bind(&SolThunder::off, this);
		pAnim->Play(L"Thunder_left", true);

	}

	SolThunder::~SolThunder()
	{

	}

	void SolThunder::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 10.f;

		m_tMonsterAttack.vScale = Vector2(0.2f, 0.2f);
		m_tMonsterAttack.vOffset = Vector2(0.f, -3.f);

		m_tMonsterAttack.iStartFrame = 0;
		m_tMonsterAttack.iEndFrame = 4;

		m_pTarget = SceneManger::FindPlayer();
	}
	void SolThunder::Update()
	{
		if (m_pTarget != nullptr)
		{
			Vector3 vPos = GetComponent<Transform>()->GetPosition();
			Vector3 vPlayerPos = m_pTarget->GetComponent<Transform>()->GetPosition();

			vPlayerPos.y += 3.3f;
			vPlayerPos.z -= 0.5f;
			GetComponent<Transform>()->SetPosition(vPlayerPos);
		}

		GameObject::Update();
	}
	void SolThunder::LateUpdate()
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
	void SolThunder::Render()
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
	void SolThunder::off()
	{
		m_iCallCount = 0;
		EventManager::AddMonsterPool(this);
	}
}
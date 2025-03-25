#include "WJenesis.h"
#include "WResources.h"
#include "WStoneScript.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WMonsterScript.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	Jenesis::Jenesis():
		m_iCallCount(0),
		m_tMonsterAttack{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"ArielJenesisStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(false);

		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"PinkBean_attack0");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"attack0", pAtlas, Vector2(0.0f, 0.0f), Vector2(844.f, 820.0f), 11, Vector2(850.f, 850.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0")->Create(L"attack0", pAtlas, Vector2(0.0f, 820.0f), Vector2(844.f, 820.0f), 11, Vector2(850.f, 850.f), Vector2::Zero, 0.15f);

		pAnim->CompleteEvent(L"attack0") = std::bind(&Jenesis::off, this);
		pAnim->Play(L"attack0", true);

	}
	Jenesis::~Jenesis()
	{

	}
	void Jenesis::Initialize()
	{
		float faccAttack = GetOwner()->GetScript<MonsterScript>()->GetAttackInfo().fAttack;
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 10.f + faccAttack;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = (Vector2(0.7f, 0.2f));
		m_tMonsterAttack.vOffset = Vector2(0.f, -2.2f);

		m_tMonsterAttack.iStartFrame = 9;
		m_tMonsterAttack.iEndFrame = 15;
	}
	void Jenesis::Update()
	{
		GameObject::Update();
	}
	void Jenesis::LateUpdate()
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
	void Jenesis::Render()
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

	void Jenesis::off()
	{
		//몬스터 오브젝트 풀에 넣기
		m_iCallCount = 0;
		EventManager::AddMonsterPool(this);
	}
}
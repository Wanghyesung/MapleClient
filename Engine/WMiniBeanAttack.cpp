#include "WMiniBeanAttack.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonsterAttackScript.h"
#include "WSceneManger.h"
#include "WTime.h"
namespace W
{
	MiniBeanAttack::MiniBeanAttack() :
		m_pTarget(nullptr),
		m_fDeleteTIme(0.1f),
		m_fCurTime(0.f)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"MinibeanAttackMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(true);

		GetComponent<Transform>()->SetScale(2.1f, 2.1f, 0.f);

	}

	MiniBeanAttack::~MiniBeanAttack()
	{

	}

	void MiniBeanAttack::Initialize()
	{
		
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 10.f;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.2f, 0.2f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);

		m_pTarget = SceneManger::FindPlayer();

		SetMonsterAttack(m_tMonsterAttack);

	}

	void MiniBeanAttack::Update()
	{
		m_fCurTime += Time::DeltaTime();
		if (m_fCurTime >= m_fDeleteTIme)
			off();

		if (m_pTarget != nullptr)
		{
			Vector3 vPos = GetComponent<Transform>()->GetPosition();
			Vector3 vPlayerPos = m_pTarget->GetComponent<Transform>()->GetPosition();

			vPlayerPos.z -= 0.5f;
			GetComponent<Transform>()->SetPosition(vPlayerPos);
		}

		GameObject::Update();
	}
	void MiniBeanAttack::LateUpdate()
	{
		MonsterAttackObject::LateUpdate();
	}
	void MiniBeanAttack::Render()
	{
		MonsterAttackObject::Render();
	}
	void MiniBeanAttack::off()
	{
		GetComponent<Collider2D>()->SetActive(false);
		object::Destroy(this);
	}
}
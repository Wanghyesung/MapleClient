#include "WMonsterAttackObject.h"
#include "WMonsterAttackScript.h"
#include "WMonster.h"
#include "WMonsterScript.h"
#include "WEffect.h"
#include "WObject.h"

namespace W
{
	MonsterAttackObject::MonsterAttackObject() :
		m_pOwner(nullptr)
	{
		//AddComponent<Collider2D>();
		//AddComponent<MonsterAttackScript>();

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"pMonsterAttackMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		AddComponent<MonsterAttackScript>();
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetActive(false);
	}

	MonsterAttackObject::~MonsterAttackObject()
	{

	}

	void MonsterAttackObject::Initialize()
	{

	}

	void MonsterAttackObject::Update()
	{
		Vector3 vPosition = m_pOwner->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(vPosition);

		GameObject::Update();
	}

	void MonsterAttackObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void MonsterAttackObject::Render()
	{
		GameObject::Render();
	}

	void MonsterAttackObject::SetMonsterAttack(const tMonsterAttack& _tAttackInfo)
	{
		//데미지
		GetScript<MonsterAttackScript>()->SetAttackInfo(_tAttackInfo.tAttackInfo);
		Transform* pTransform = GetComponent<Transform>();
		
		pTransform->SetPosition(_tAttackInfo.vPosition);
		pTransform->SetRotation(_tAttackInfo.vRoatate);

		//오프셋
		int iDir = m_pOwner->GetDir();
		Collider2D* pCollider = GetComponent< Collider2D>();
		pCollider->SetCenter(Vector2(_tAttackInfo.vOffset.x * iDir, _tAttackInfo.vOffset.y));
		pCollider->SetSize(_tAttackInfo.vScale);

		GetComponent<Collider2D>()->SetActive(true);
	}

}
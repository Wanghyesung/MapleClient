#include "WMonsterMoveAttack.h"
#include "WMonsterScript.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRigidbody.h"
namespace W
{
	MonsterMoveAttack::MonsterMoveAttack():
		m_tMonsterAttack{}
	{
	}
	MonsterMoveAttack::~MonsterMoveAttack()
	{

	}
	void MonsterMoveAttack::Initialize()
	{
		float faccAttack = GetOwner()->GetScript<MonsterScript>()->GetAttackInfo().fAttack;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = (Vector2(2.5f, 2.5f));
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);

		SetMonsterAttack(m_tMonsterAttack);
	}
	void MonsterMoveAttack::Update()
	{
		Rigidbody* pRigidbody = GetOwner()->GetComponent<Rigidbody>();
		int iDir = GetOwner()->GetDir();
		pRigidbody->AddForce(Vector2(8.f * iDir, 0.f));

		GameObject::Update();
	}
	void MonsterMoveAttack::LateUpdate()
	{
		Vector3 vPosition = GetOwner()->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(vPosition);

		GameObject::LateUpdate();
	}
	void MonsterMoveAttack::Render()
	{
		GameObject::Render();
	}

}
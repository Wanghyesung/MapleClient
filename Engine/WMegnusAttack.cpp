#include "WMegnusAttack.h"
#include "WMonster.h"
#include "WMonsterScript.h"
#include "WAnimator.h"
#include "WSceneManger.h"
namespace W
{
	MegnusAttack::MegnusAttack():
		m_iCallCount(0),
		m_tMonsterAttack{}
	{

	}
	MegnusAttack::~MegnusAttack()
	{
	}
	void MegnusAttack::Initialize()
	{
		float faccAttack = GetOwner()->GetScript<MonsterScript>()->GetAttackInfo().fAttack;
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 1000.f + faccAttack;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = (Vector2(2.4f, 2.8f));

		m_tMonsterAttack.iStartFrame = 27;
		m_tMonsterAttack.iEndFrame = 37;

		m_iCallCount = 0;
	}
	void MegnusAttack::Update()
	{
		GameObject::Update();
	}
	void MegnusAttack::LateUpdate()
	{
		Animation* pAnim = GetOwner()->GetComponent<Animator>()->GetActiveAnimation();

		int iIndex = pAnim->GetCurIndex();
		if (iIndex >= m_tMonsterAttack.iStartFrame && m_iCallCount == 0)
		{
			m_iCallCount = 1;
			//지금 실행중인 데미지 정보 넘기기
			SetMonsterAttack(m_tMonsterAttack);
		}

		else if (m_iCallCount == 1 && iIndex >= m_tMonsterAttack.iEndFrame)
		{
			m_iCallCount = 2;
			off();
			return;
		}

		GameObject::LateUpdate();
	}
	void MegnusAttack::Render()
	{
		GameObject::Render();
	}
	void MegnusAttack::SetDir(int _iDir)
	{
		m_tMonsterAttack.vOffset.x = _iDir * 2.5;
	}
	void MegnusAttack::off()
	{
		GetComponent<Collider2D>()->SetActive(false);

		EventManager::AddMonsterPool(this);
	}
}
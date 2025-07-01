#include "WMonsterAttackObject.h"

#include "WMonster.h"

#include "WEffect.h"
#include "WTransform.h"
#include "WResources.h"

namespace W
{
	MonsterAttackObject::MonsterAttackObject() :
		m_pOwner(nullptr)
	{

	}
	MonsterAttackObject::~MonsterAttackObject()
	{

	}

	void MonsterAttackObject::Initialize()
	{

	}

	void MonsterAttackObject::Update()
	{
		
	}

	void MonsterAttackObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void MonsterAttackObject::Render()
	{
		GameObject::Render();
	}

	void MonsterAttackObject::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cDir = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iDir = cDir > 0 ? 1 : -1;
		m_iAnimIdx = cAnimIdx;
	}


}
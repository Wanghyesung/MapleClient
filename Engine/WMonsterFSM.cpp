#include "WMonsterFSM.h"
#include "WMonsterState.h"

namespace W
{
	MonsterFSM::MonsterFSM():
		m_pActiveState(nullptr)
	{

	}
	MonsterFSM::~MonsterFSM()
	{
		std::map<Monster::eMonsterState, MonsterState*>::iterator iter
			= m_mapState.begin();

		for (iter; iter != m_mapState.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	void MonsterFSM::Update()
	{
		m_pActiveState->Update();
	}
	void MonsterFSM::Initialize()
	{
		m_pActiveState->Enter();
	}
	void MonsterFSM::AddState(MonsterState* _pState)
	{
		MonsterState* pState = FindState(_pState->GetType());
		//같은게 또 들어오면
		if (pState != nullptr)
			assert(nullptr);

		m_mapState.insert(std::make_pair(_pState->GetType(), _pState));
		_pState->SetFSM(this);
	}
	MonsterState* MonsterFSM::FindState(Monster::eMonsterState _eMonsterState)
	{
		std::map<Monster::eMonsterState, MonsterState*>::iterator iter
			= m_mapState.find(_eMonsterState);

		if (iter != m_mapState.end())
			return iter->second;

		return nullptr;
	}
	void MonsterFSM::ChangeState(Monster::eMonsterState _eMonsterState)
	{
		if (GetMonster()->IsDead())
			return;

		m_pActiveState->Exit();

		SetActiveState(_eMonsterState);

		m_pOwner->SetMonsterCurState(_eMonsterState);
		m_pOwner->SetCurStateName(m_pActiveState->GetStateName());

		m_pActiveState->Enter();
	}
	void MonsterFSM::SetActiveState(Monster::eMonsterState _eMonsterState)
	{
		m_pActiveState = FindState(_eMonsterState);
		if (m_pActiveState == nullptr)
			assert(nullptr);

		m_eCurState = m_pActiveState->GetType();
	}
}
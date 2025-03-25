#include "WPinkbeanStand.h"
#include "WPinkBean.h"
#include "WEventManager.h"
namespace W
{
	PinkbeanStand::PinkbeanStand()
	{
		SetType(Monster::eMonsterState::wait);
		SetStateName(L"_stand");
	}
	PinkbeanStand::~PinkbeanStand()
	{

	}
	void PinkbeanStand::Update()
	{
		//srand(time(nullptr));
		bool bStart = dynamic_cast<PinkBean*>(GetMonster())->IsStart();
		if(bStart)
			EventManager::ChangeMonsterFSMState(GetFSM(), Monster::eMonsterState::start);
	}
	void PinkbeanStand::Enter()
	{

	}
	void PinkbeanStand::Exit()
	{
		//GetMonster()->GetComponent<Collider2D>()->SetActive(true);
	}
}
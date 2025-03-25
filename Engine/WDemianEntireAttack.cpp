#include "WDemianEntireAttack.h"
#include "WResources.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WEventManager.h"
#include "WInput.h"
#include "WPlayerScript.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
namespace W
{
	DemianEntireAttack::DemianEntireAttack():
		m_iKeyDonwCount(50),
		m_fDeleteTime(5.f),
		m_fCurTime(0.f),
		m_iCallStack(0)
	{
		
	}
	DemianEntireAttack::~DemianEntireAttack()
	{

	}
	void DemianEntireAttack::Initialize()
	{
		
	}
	void DemianEntireAttack::Update()
	{
		m_fCurTime += Time::DeltaTime();

		if (Input::GetKeyDown(eKeyCode::LEFT))
			--m_iKeyDonwCount;
		else if(Input::GetKeyDown(eKeyCode::RIGHT))
			--m_iKeyDonwCount;
		
		if (m_iKeyDonwCount <= 0.f)
		{
			Restore();
		}
		else
		{
			if (m_fCurTime >= m_fDeleteTime)
				Restore();
		}

		GameObject::Update();
	}
	void DemianEntireAttack::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianEntireAttack::Render()
	{
		GameObject::Render();
	}

	void DemianEntireAttack::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::DemianStop);
		object::Destroy(this);
	}
}
#include "WPlayerFSM.h"
#include "WPlayerState.h"
#include "WPlayerStand.h"
#include "WPlayerPronestab.h"
#include "WPlayerWalk.h"
#include "WPlayerJump.h"
#include "WPlayerSwing1.h"
#include "WPlayerProneAttack.h"
#include "WPlayerLadder.h"
#include "WPlayerAlert.h"
#include "WPlayerStab.h"
#include "WPlayerScript.h"

#include "WSceneManger.h"
#include "WShuriken.h"
#include "WPlayerAttackObject.h"
#include "WAttackScript.h"
#include "WEventManager.h"
#include "WShadow.h"

namespace W
{
	PlayerFSM::PlayerFSM():
		m_eCurState(Player::ePlayerState::stand),
		m_ePreState(Player::ePlayerState::stand),
		m_pOwner(nullptr),
		m_pActiveState(nullptr),
		m_mapState{}
	{

	}
	PlayerFSM::~PlayerFSM()
	{
		std::map<Player::ePlayerState, PlayerState*>::iterator iter 
			= m_mapState.begin();
		
		for (iter; iter != m_mapState.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	void PlayerFSM::Update()
	{
		m_pActiveState->Update();
	}
	void PlayerFSM::Initialize()
	{
		PlayerScript* pScript = m_pOwner->GetScript<PlayerScript>();

		AddState(new PlayerStand());
		AddState(new PlayerPronestab());
		AddState(new PlayerWalk());
		AddState(new PlayerJump());

		PlayerSwing1* pPlayerSwing = new PlayerSwing1();
		pPlayerSwing->SetFunction(std::bind(&PlayerFSM::swing_shuriken, this)); 
		AddState(pPlayerSwing); 

		PlayerProneAttack* pProneAttak = new PlayerProneAttack();
		pProneAttak->SetFunction(std::bind(&PlayerFSM::near_attack, this));
		AddState(pProneAttak);
		
		PlayerStab* pStab = new PlayerStab();
		pStab->SetFunction(std::bind(&PlayerFSM::near_attack, this));
		AddState(pStab);
		
		AddState(new PlayerLadder());
		AddState(new PlayerAlert());
		
		
	}

	void PlayerFSM::AddState(PlayerState* _pState)
	{
		PlayerState* pState = FindState(_pState->GetType());
		
		if (pState != nullptr)
			assert(nullptr);

		m_mapState.insert(std::make_pair(_pState->GetType(), _pState));
		_pState->SetFSM(this);
	}

	PlayerState* PlayerFSM::FindState(Player::ePlayerState _ePlayerState)
	{
		std::map<Player::ePlayerState, PlayerState*>::iterator iter
			= m_mapState.find(_ePlayerState);

		if (iter != m_mapState.end())
			return iter->second;

		return nullptr;
	}

	void PlayerFSM::ChangeState(Player::ePlayerState _ePlayerState)
	{
		m_pActiveState->Exit();

		SetActiveState(_ePlayerState);

		m_pOwner->SetPlayerCurState(_ePlayerState);
		m_pOwner->SetCurStateName(m_pActiveState->GetStateName());

		m_pActiveState->Enter();
	}

	void PlayerFSM::SetActiveState(Player::ePlayerState _ePlayerState)
	{
		m_ePreState = m_eCurState;
		m_pActiveState = FindState(_ePlayerState);
		if (m_pActiveState == nullptr)
			assert(nullptr);

		m_eCurState = m_pActiveState->GetType();
	}

	void PlayerFSM::swing_shuriken()
	{
		Player* pPlayer = GetPlayer();
		UINT iCall = 1;
		if (pPlayer->IsShadow())
			iCall *= 2;
		
		PlayerAttackObject* pAttackObj = m_pOwner->GetScript<PlayerScript>()->GetPlayerSkill(L"shuriken");
		Shuriken* pShuriken = dynamic_cast<Shuriken*>(pAttackObj);
		//pShuriken->GetComponent<Collider2D>()->SetActive(true);
		pShuriken->SetDir(m_pOwner->GetDir());

		Transform* pTr = pShuriken->GetComponent<Transform>();
		Vector3 vPosition = m_pOwner->GetComponent<Transform>()->GetPosition();
		vPosition.z += 0.01f;
		vPosition.x += (m_pOwner->GetDir() * 0.6f);

		vPosition.x += pPlayer->GetDir() * 0.7f;
		pTr->SetPosition(vPosition);

		tAttackInfo& tAttack = pShuriken->GetScript<AttackScript>()->GetAttackInfo();
		tAttack.iDamageCount = iCall;

		EventManager::CreateObject(pShuriken, eLayerType::AttackObject);
	}

	void PlayerFSM::near_attack()
	{
		PlayerAttackObject* pAttackObject = m_pOwner->GetScript<PlayerScript>()->CreateAttackObject();

		EventManager::CreateObject(pAttackObject, eLayerType::AttackObject);
	}

}
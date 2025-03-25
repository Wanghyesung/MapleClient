#include "WHorntail.h"
#include "WAnimator.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WMonsterScript.h"
#include "WHorntailHeadA.h"
#include "WHorntailHeadB.h"
#include "WHorntailHeadC.h"
#include "WHorntailLeftHand.h"
#include "WHorntailRightHand.h"
#include "WHorntailLeg.h"
#include "WHorntailWing.h"
#include "WHorntailTail.h"
#include "WSceneManger.h"
#include "WBattleManager.h"
#include "WObject.h"
#include "WCameraScript.h"
#include "WMonsterManager.h"

//수동으로 exe파일에 넣어주기
//속성 -> 빌드이벤트 -> 복사해서 넘기기
namespace W
{
	Horntail::Horntail():
		m_iDeadCount(0)
	{
		m_vecMonster.resize(8);

		MonsterScript* pScript = AddComponent<MonsterScript>();
		pScript->SetBoss();
		pScript->Initialize();

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HorntailStartTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		//pAnim->Create(L"HorntailStart", pAtlas, Vector2(5316.f, 2673.f), Vector2(886.f, 891.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 0.f), Vector2(886.f, 891.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailStart")->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 891.0f), Vector2(886.f, 891.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailStart")->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 1782.f), Vector2(886.f, 891.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailStart")->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 2673.f), Vector2(886.f, 891.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->CompleteEvent(L"HorntailStart") = std::bind(&Horntail::create_child, this);

		pAtlas = Resources::Find<Texture>(L"HorntailDead");
		pAnim->Create(L"HorntailDead", pAtlas, Vector2(0.0f, 0.f), Vector2(731.f, 643.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailDead")->Create(L"HorntailDead", pAtlas, Vector2(0.0f, 643.0f), Vector2(731.f, 643.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailDead")->Create(L"HorntailDead", pAtlas, Vector2(0.0f, 1286.f), Vector2(731.f, 643.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->CompleteEvent(L"HorntailDead") = std::bind(&Horntail::delete_child, this);
	}

	Horntail::~Horntail()
	{

	}

	void Horntail::Initialize()
	{
		HorntailHeadA* pHeadA = new HorntailHeadA(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailHeadA] = pHeadA;
		pHeadA->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, pHeadA);
		//
		HorntailHeadB* pHeadB = new HorntailHeadB(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailHeadB] = pHeadB;
		pHeadB->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, pHeadB);
		
		HorntailHeadC* pHeadC = new HorntailHeadC(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailHeadC] = pHeadC;
		pHeadC->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, pHeadC);
		
		HorntailLeftHand* pLeftHand = new HorntailLeftHand(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailLeftHand] = pLeftHand;
		pLeftHand->Initialize();
		pLeftHand->SetBuff(std::bind(&Horntail::up_defense, this));
		SceneManger::AddGameObject(eLayerType::Monster, pLeftHand);
		//
		HorntailRightHand* pRightHand = new HorntailRightHand(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailRightHand] = pRightHand;
		pRightHand->Initialize();
		pRightHand->SetBuff(std::bind(&Horntail::up_attack, this));
		SceneManger::AddGameObject(eLayerType::Monster, pRightHand);

		HorntailLeg* pLegs = new HorntailLeg(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailLeg] = pLegs;
		pLegs->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, pLegs);

		HorntailWing* pWing = new HorntailWing(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailWing] = pWing;
		pWing->Initialize();
		pWing->SetHeal(std::bind(&Horntail::heal, this));
		SceneManger::AddGameObject(eLayerType::Monster, pWing);
		
		HorntailTail* pTail = new HorntailTail(this);
		m_vecMonster[(UINT)eHorntailChild::HorntailTail] = pTail;
		pTail->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, pTail);

		//정지
		for (UINT i = 0; i < 8; ++i)
			m_vecMonster[i]->SetState(eState::Paused);
	}

	void Horntail::Update()
	{
		if (!m_bStart)
			return;

		Monster::Update();

		update_HP();
	}

	void Horntail::LateUpdate()
	{
		if (!m_bStart)
			return;

		Monster::LateUpdate();
	}

	void Horntail::Render()
	{
		if (!m_bStart)
			return;

		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Horntail::Start()
	{
		m_bStart = true;

		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->Play(L"HorntailStart", true);

		GameObject* pMainCamera = renderer::MainCamera->GetOwner();
		pMainCamera->GetScript<CameraScript>()->SetEventType(CameraScript::eCameraEventType::Wave,4.f);
	}
	void Horntail::dead()
	{
		m_iDeadCount = 1;

		for (UINT i = 0; i < 8; ++i)
			m_vecMonster[i]->SetState(eState::Paused);

		Transform* pTr = GetComponent<Transform>();
		Vector3 vPosition = pTr->GetPosition();
		vPosition.y -= 0.99f;
		vPosition.x += 0.36f;

		pTr->SetPosition(vPosition);

		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->Play(L"HorntailDead", true);

		GetComponent<Animator>()->Stop(false);
		GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
	}

	void Horntail::update_HP()
	{
		float fFinalRatio = 0.f;
		for (UINT i = 0; i < m_vecMonster.size(); ++i)
		{
			if (m_vecMonster[i] == nullptr)
				return;

			tObjectInfo& tInfo = m_vecMonster[i]->GetScript<MonsterScript>()->m_tObjectInfo;
			float fRatio = (tInfo.fHP / tInfo.fMaxHP) * 100.f;

			if (tInfo.fHP <= 0.f)
				continue;
			else
				fFinalRatio += fRatio / 8.f;
		}
		tObjectInfo& tHorntailInfo = GetScript<MonsterScript>()->m_tObjectInfo;
		tHorntailInfo.fHP = fFinalRatio;

		if (tHorntailInfo.fHP <= 0.f)
		{
			if(m_iDeadCount == 0)
				dead();
		}
	}

	void Horntail::create_child()
	{
		GetComponent<Animator>()->Stop(true);
		GetComponent<Animator>()->GetActiveAnimation()->SetIndex(-1);

		GetScript<MonsterScript>()->CreateHP();
		for (UINT i = 0; i < 8; ++i)
			m_vecMonster[i]->SetState(eState::Active);

	}
	void Horntail::delete_child()
	{
		MonsterManager::AddDeleteObject(this);
		for (int i = 0; i < 8; ++i)
			MonsterManager::AddDeleteObject(m_vecMonster[i]);
	}
	void Horntail::up_attack()
	{
		if (!m_vecMonster[(UINT)eHorntailChild::HorntailHeadA]->IsDead())
			BattleManager::Buff_Stat(m_vecMonster[(UINT)eHorntailChild::HorntailHeadA], BattleManager::eUpStatType::Attack, 10.f);

		if (!m_vecMonster[(UINT)eHorntailChild::HorntailHeadC]->IsDead())
			BattleManager::Buff_Stat(m_vecMonster[(UINT)eHorntailChild::HorntailHeadC], BattleManager::eUpStatType::Attack, 10.f);
	}
	void Horntail::up_defense()
	{
		if (!m_vecMonster[(UINT)eHorntailChild::HorntailHeadB]->IsDead())
			BattleManager::Buff_Stat(m_vecMonster[(UINT)eHorntailChild::HorntailHeadB], BattleManager::eUpStatType::Defense, 10.f);

	}
	void Horntail::heal()
	{
		for (UINT i = 0; i < 3; ++i)
		{
			if (!m_vecMonster[i]->IsDead())
			{
				tObjectInfo& tInfo = m_vecMonster[i]->GetScript<MonsterScript>()->m_tObjectInfo;
				float fAccValue = tInfo.fMaxHP - tInfo.fHP;
				if (fAccValue <= 0.f)
					continue;

				fAccValue = (tInfo.fMaxHP * 10/3) + tInfo.fHP;
				if (fAccValue >= tInfo.fMaxHP)
					fAccValue = tInfo.fMaxHP - fAccValue;
				else
					fAccValue = (tInfo.fMaxHP * 10 / 3);

				BattleManager::Buff_Stat(m_vecMonster[i], BattleManager::eUpStatType::Heal, fAccValue);
			}
		}
	}
}

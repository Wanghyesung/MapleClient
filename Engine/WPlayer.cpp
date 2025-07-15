#include "WPlayer.h"

#include "WResources.h"
#include "WRenderer.h"
#include "WInput.h"
#include "WAnimator.h"
#include "WPlayerBody.h"
#include "WPlayerArm.h"
#include "WPlayerHead.h"
#include "WEyes.h"
#include "WPlayerHair.h"
#include "WEquip.h"
#include "WTime.h"
#include "WShadow.h"
#include "WTransform.h"
#include "WThreadPool.h"
#include "WSceneManger.h"
#include "WEquipState.h"
#include "WCameraScript.h"
#include "WShuriken.h"
#include "WObjectPoolManager.h"
#include "WEffect.h"
#include "WAven.h"
#include "WLoad.h"
#include "WAutoShuriken.h"
#include "WBlast.h"
#include "WWind.h"
#include "WUltimateBackground.h"
#include "WUltimateFog.h"
#include "WUltimateObject.h"
#include "WUltimateShuriken.h"
#include "WEventManager.h"
#include "..\IOCP_CLIENT\Equip.pb.h"
#include "WItemManager.h"

namespace W
{
	Player::Player() :
		m_ePlayerState(ePlayerState::stand),
		m_bAlert(false),
		m_bActiveDark(false),
		m_bActiveShadow(false),
		m_bAlertTime(2.f),
		m_fChangeTime(0.25f)
	{
		//SetName(L"Player");
		m_strCurStateName = L"_jump";

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		
		pMater->SetShader(Resources::Find<Shader>(L"PlayerShader"));
		Resources::Insert(L"Player", pMater);
		mr->SetMaterial(pMater);


		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);
		GetComponent<Transform>()->SetPosition(0.f, -5.f, -2.f);

		m_vecChildObj.resize(ePlayerPart::End);

		PlayerBody* pPlayerBody = new PlayerBody();
		pPlayerBody->SetPlayer(this);
		pPlayerBody->Initialize();
		m_vecChildObj[ePlayerPart::Body] = pPlayerBody;

		PlayerHead* pPlayerHead = new PlayerHead();
		pPlayerHead->SetPlayer(this);
		pPlayerHead->Initialize();
		m_vecChildObj[ePlayerPart::Head] = pPlayerHead;

		PlayerArm* pPlayerArm = new PlayerArm();
		pPlayerArm->SetPlayer(this);
		pPlayerArm->Initialize();
		m_vecChildObj[ePlayerPart::Arm] = pPlayerArm;

		init_attack_object();
		init_attack_effect();

		m_pShadow = new Shadow();
		m_pShadow->SetOwner(this);
	}

	Player::~Player()
	{
		for (GameObject* pChildObj : m_vecChildObj)
		{
			delete pChildObj;
			pChildObj = nullptr;
		}

		if (m_pShadow)
		{
			delete m_pShadow;
			m_pShadow = nullptr;
		}
	}

	void Player::Initialize()
	{
		
	}

	void Player::Update()
	{
		if (m_bActiveShadow)
			m_pShadow->Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		if(m_bActiveShadow)
			m_pShadow->LateUpdate();

		child_lateupdate();
	}
	void Player::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vDir.x = m_iDir * -1;
		PlayerCB.vColor = Vector4::One;
		if (m_bActiveDark)
		{
			PlayerCB.vColor = Vector4(0.8f, 0.8f, 0.8f, 0.7f);
		}

		else if (m_bAlert)
		{
			m_fChangeTime -= Time::DeltaTime();
			if (m_fChangeTime <= 0.25f / 3.f)
				PlayerCB.vColor = Vector4(0.5f, 0.5f, 0.5f, 1.f);
			else
				PlayerCB.vColor = Vector4::One;

			if (m_fChangeTime <= 0.f)
				m_fChangeTime = 0.25f;
		}

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();		

		if(m_bActiveShadow)
			m_pShadow->Render();

		child_render();
	}

	void Player::UpdateState(const wstring& _strStateName, int _iState)
	{	
		if (!_strStateName.empty())
			m_strCurStateName = _strStateName;

		UCHAR cShadow = (_iState >> 24) & 0xFF;
		UCHAR cAlert = (_iState >> 16) & 0xFF;
		UCHAR cDir = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		m_bAlert = cAlert > 0 ? true : false;
		m_iDir = cDir > 0 ? 1 : -1;
		m_iAnimIdx = cAnimIdx;

		update_shadow(cShadow);
	}

	void Player::SetEquip(Equip* _pEquip, bool _bSend)
	{
		Equip::EquipType eType = _pEquip->GetEquipType();
		UINT iPlayerPartID = 0; //머리 , 몸, 팔
		UINT iPlayerEquipID = 0; 

		switch (eType)
		{
		case W::Equip::EquipType::Hat:
			GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetEquipHat(_pEquip);
			iPlayerPartID = (UINT)Equip::EquipType::Hat; iPlayerEquipID = 2;
			break;
		case W::Equip::EquipType::Top:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipTop(_pEquip);
			iPlayerPartID = (UINT)Equip::EquipType::Top; iPlayerEquipID = 0;
			break;
		case W::Equip::EquipType::Bottom:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipBottom(_pEquip);
			iPlayerPartID = (UINT)Equip::EquipType::Bottom; iPlayerEquipID = 1;
			break;
		case W::Equip::EquipType::Shoes:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipShoes(_pEquip);
			iPlayerPartID = (UINT)Equip::EquipType::Shoes; iPlayerEquipID = 2;
			break;
		case W::Equip::EquipType::Weapon:
			GetPlayerChild<PlayerArm>(ePlayerPart::Arm)->SetEquipWeapon(_pEquip);
			iPlayerPartID = (UINT)Equip::EquipType::Weapon; iPlayerEquipID = 0;
			break;
		}

		if(_bSend)
			send_equip(_pEquip, iPlayerPartID, iPlayerEquipID);
	}

	void Player::DisableEquip(Equip* _pEquip, bool _bSend)
	{
		Equip::EquipType eType = _pEquip->GetEquipType();
		UINT iPlayerPartID = 0; //머리 , 몸, 팔
		UINT iPlayerEquipID = 0;
		switch (eType)
		{
		case W::Equip::EquipType::Hat:
			GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetEquipHat(nullptr);
			iPlayerPartID = (UINT)Equip::EquipType::Hat; iPlayerEquipID = 2;
			break;
		case W::Equip::EquipType::Top:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipTop(nullptr);
			iPlayerPartID = (UINT)Equip::EquipType::Top; iPlayerEquipID = 0;
			break;
		case W::Equip::EquipType::Bottom:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipBottom(nullptr);
			iPlayerPartID = (UINT)Equip::EquipType::Bottom; iPlayerEquipID = 1;
			break;
		case W::Equip::EquipType::Shoes:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipShoes(nullptr);
			iPlayerPartID = (UINT)Equip::EquipType::Shoes; iPlayerEquipID = 2;
			break;
		case W::Equip::EquipType::Weapon:
			GetPlayerChild<PlayerArm>(ePlayerPart::Arm)->SetEquipWeapon(nullptr);
			iPlayerPartID = (UINT)Equip::EquipType::Weapon; iPlayerEquipID = 0;
			break;
		}

		if(_bSend)
			send_equip(nullptr,iPlayerPartID,iPlayerEquipID);
	}

	void Player::SetEquip(Equip::EquipType _eType, const std::wstring& _strEquipName)
	{
		switch (_eType)
		{
		case Equip::EquipType::Hat:
			GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetEquipHat(_strEquipName);
			break;
		case Equip::EquipType::Top:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipTop(_strEquipName);
			break;
		case Equip::EquipType::Bottom:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipBottom(_strEquipName);
			break;
		case Equip::EquipType::Shoes:
			GetPlayerChild<PlayerBody>(ePlayerPart::Body)->SetEquipShoes(_strEquipName);
			break;
		case Equip::EquipType::Weapon:
			GetPlayerChild<PlayerArm>(ePlayerPart::Arm)->SetEquipWeapon(_strEquipName);
			break;
		}
	}

	void Player::SetEquip(Equip::EquipType _eType, UINT _iEquipID)
	{
		const wstring& strItemName = ItemManager::GetItemName(_iEquipID);
		if (!strItemName.empty())
			SetEquip(_eType, strItemName);
	}
	
	
	void Player::SetTargetPlayer(UINT64 _llEquipIDs)
	{
		renderer::MainCamera->GetOwner()->GetScript<CameraScript>()->SetPlayer(this);

		EquipState* pEquipState = new EquipState();
		pEquipState->SetObjectID(4);
		pEquipState->SetName(L"Equip");
		SceneManger::AddGameObject(eLayerType::UI, pEquipState);
		pEquipState->SetPlayer(this);

		pEquipState->Initialize();

		UINT iHairID = ((_llEquipIDs >> (0 * 8)) & 0xFF);
		UINT iEyeID = ((_llEquipIDs >> (1 * 8)) & 0xFF);

		GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetHair(iHairID);
		GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetEye(iEyeID);

		for (UINT i = 2; i < 7; ++i)
		{
			UINT iItemID = ((_llEquipIDs >> (i * 8)) & 0xFF);
			if (iItemID == 0)
				continue;

			pEquipState->AddPlayerEquip(iItemID);
		}
	}

	void Player::SetPlayerEquips(UINT64 _llEquipIDs)
	{
		UINT iEquipNum = 0;
		UINT iHairID = ((_llEquipIDs >> (iEquipNum++ * 8)) & 0xFF);
		UINT iEyeID = ((_llEquipIDs >> (iEquipNum++ * 8)) & 0xFF);

		GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetHair(iHairID);
		GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetEye(iEyeID);
	
		for (UINT i = (UINT)Equip::EquipType::Hat; i <= (UINT)Equip::EquipType::Weapon; ++i)
		{
			UINT iEquipID = ((_llEquipIDs >> (iEquipNum++ * 8)) & 0xFF);
			if (iEquipID == 0)
				continue;

			SetEquip((Equip::EquipType)i, iEquipID);
		}
	}

	void Player::SetHair(UINT _iHairID)
	{
		GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetHair(_iHairID);
	}

	void Player::SetEye(UINT _iEyeID)
	{
		GetPlayerChild<PlayerHead>(ePlayerPart::Head)->SetEye(_iEyeID);
	}

	void Player::child_render()
	{
		for (GameObject* pObj : m_vecChildObj)
		{
			pObj->Render();
		}
	}

	void Player::child_lateupdate()
	{
		for (GameObject* pObj : m_vecChildObj)
		{
			pObj->LateUpdate();
		}
	}

	void Player::init_attack_object()
	{
		for (int i = 0; i < 5; ++i)
		{
			Shuriken* pShuriken = new Shuriken();
			pShuriken->SetName(L"shuriken");
			ObjectPoolManager::AddObjectPool(pShuriken->GetName(), pShuriken);
		}
		for (int i = 0; i < 12; ++i)
		{
			Shuriken* pShuriken = new Shuriken();
			pShuriken->SetName(L"luck");
			ObjectPoolManager::AddObjectPool(pShuriken->GetName(), pShuriken);
		}

		for (int i = 0; i < 3; ++i)
		{
			Aven* pAven = new Aven();
			pAven->SetName(L"Aven");
			ObjectPoolManager::AddObjectPool(pAven->GetName(), pAven);
		}

		PlayerAttackObject* pAttackObj = new PlayerAttackObject();
		pAttackObj->SetName(L"raid");
		ObjectPoolManager::AddObjectPool(pAttackObj->GetName(), pAttackObj);

		for (int i = 0; i < 24; ++i)
		{
			Shuriken* pShuriken = new Shuriken();
			pShuriken->SetName(L"quad");
			ObjectPoolManager::AddObjectPool(pShuriken->GetName(), pShuriken);
		}

		for (int i = 0; i < 2; ++i)
		{
			Load* pLoad = new Load();
			pLoad->SetName(L"load");
			ObjectPoolManager::AddObjectPool(pLoad->GetName(), pLoad);
		}

		for (int i = 0; i < 50; ++i)
		{
			AutoShuriken* pShuriken = new AutoShuriken();
			pShuriken->SetName(L"autoSuriken");
			ObjectPoolManager::AddObjectPool(pShuriken->GetName(), pShuriken);
		}

		for (int i = 0; i < 10; ++i)
		{
			Blast* pBlast = new Blast();
			pBlast->SetName(L"blast");
			pBlast->GetComponent<Transform>()->SetScale(8.f, 8.f, 0.f);
			ObjectPoolManager::AddObjectPool(pBlast->GetName(), pBlast);
		}
		for (int i = 0; i < 2; ++i)
		{
			Wind* pWind = new Wind();
			pWind->SetName(L"wind");
			ObjectPoolManager::AddObjectPool(pWind->GetName(), pWind);
		}

		for (int i = 0; i < 25; ++i)
		{
			UltimateShuriken* pShuriken = new UltimateShuriken();
			pShuriken->SetName(L"ultimate_suriken");
			pShuriken->GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
			ObjectPoolManager::AddObjectPool(pShuriken->GetName(), pShuriken);
		}

		GameObject* spawn = new GameObject();
		spawn->SetName(L"ultimate_spawn");
		ObjectPoolManager::AddObjectPool(spawn->GetName(), spawn);
	}


	void Player::init_attack_effect()
	{
		Effect* pEffect = nullptr;
		for (int i = 0; i < 8; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"luckhit"), L"luck_hit", Vector2(0.f, 0.f), Vector2(74.f, 74.f), 4, 1,
				Vector2(90.f, 90.f), Vector2::Zero, Vector2(296.f, 74.f), 0.1f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"luckeffect"), L"luckeffect", Vector2(0.f, 0.f), Vector2(112.f, 52.f), 5, 1,
			Vector2(110.f, 110.f), Vector2(0.4f, 0.f), Vector2(560.f, 52.f), 0.1f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);


		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"darkffect"), L"darkffect", Vector2(0.f, 0.f), Vector2(126.f, 129.f), 8, 1,
			Vector2(110.f, 110.f), Vector2(-0.15f, 0.1f), Vector2(1008.f, 129.f), 1.5f / 16.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"speedffect"),L"speedffect", Vector2(0.f, 0.f), Vector2(122.f, 64.f), 9, 1,
			Vector2(200.f, 200.f), Vector2(0.f, 0.0f), Vector2(1098.f, 64.f), 1.f / 18.f);
		pEffect->GetComponent<Transform>()->SetScale(2.f, 2.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"jumpeffect"),L"jumpeffect", Vector2(0.f, 0.f), Vector2(235.5f, 133.f), 8, 1,
			Vector2(200.f, 200.f), Vector2(-1.f, 0.0f), Vector2(1888.f, 133.f), 0.05f);
		pEffect->GetComponent<Transform>()->SetScale(2.f, 2.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"shadowe1ffect"), L"shadowe1ffect", Vector2(0.f, 0.f), Vector2(158.f, 131.f), 11, 1,
			Vector2(150.f, 150.f), Vector2(-0.6f, 0.2f), Vector2(1738.f, 131.f), 0.05f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"shadowe2ffect"), L"shadowe2ffect", Vector2(0.f, 0.f), Vector2(195.f, 180.f), 16, 1,
			Vector2(200.f, 200.f), Vector2(-0.4f, 0.2f), Vector2(3120.f, 180.f), 0.05f);
		pEffect->GetComponent<Transform>()->SetScale(2.2f, 2.2f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"aveneffect"), L"aveneffect", Vector2(0.f, 0.f), Vector2(121.f, 71.f), 14, 1,
			Vector2(110.f, 110.f), Vector2(0.f, 0.f), Vector2(1694.f, 72.f), 0.03f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		for (int i = 0; i < 8; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"quadhit"), L"quad_hit", Vector2(0.f, 0.f), Vector2(146.f, 146.f), 9, 1,
				Vector2(150.f, 150.f), Vector2::Zero, Vector2(1314, 146.f), 0.06f);
			pEffect->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		for (int i = 0; i < 3; ++i)
		{			
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"quadffect"), L"quadffect", Vector2(0.f, 0.f), Vector2(299, 196.f), 9, 1,
				Vector2(300.f, 300.f), Vector2(0.4f, 0.f), Vector2(2691.f, 196.f), 0.06f);
			pEffect->GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"loadeffect"), L"loadeffect", Vector2(0.f, 0.5f), Vector2(1700.f, 1200.f), 5, 3,
			Vector2(1700.f, 1200.f), Vector2(0.5f, 3.f), Vector2(10200.f, 3600.f), 0.03f);
		pEffect->GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		for (int i = 0; i < 30; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"loadhit"), L"load_hit", Vector2(0.f, 0.f), Vector2(315.f, 204.f), 14, 1,
				Vector2(300.f, 300.f), Vector2(0.f, 0.f), Vector2(4410.f, 204.f), 0.07f);
			pEffect->GetComponent<Transform>()->SetScale(3.f, 3.f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"raideffect1"), L"raideffect1", Vector2(0.f, 0.f),
			Vector2(1060.f, 727.f), 10, 3, Vector2(1000.f, 1000.f), Vector2(0.2f, 2.f), Vector2(10600.f, 2181.f), 0.05f);
		pEffect->AddComponent<Light>();//빛처리 기능 넣기 패킷으로 접근
		pEffect->GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);


		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"raideffect2"), L"raideffect2", Vector2(0.f, 0.f), Vector2(880.f, 637.f), 10, 3,
			Vector2(1000.f, 1000.f), Vector2(0.2f, 2.f), Vector2(8800.f, 1911.f), 0.05f);
		pEffect->GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);


		for (int i = 0; i < 7; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"raidhit"), L"raid_hit", Vector2(0.f, 0.f), Vector2(276.f, 252.f), 6, 1,
				Vector2(300.f, 300.f), Vector2(0.f, 0.f), Vector2(1656.f, 252.f), 0.2f);
			pEffect->GetComponent<Transform>()->SetScale(3.5f, 3.5f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"windffect1"), L"windffect1", Vector2(0.f, 0.5f), Vector2(626.f, 508.f), 7, 1,
			Vector2(600.f, 600.f), Vector2(0.5f, 0.f), Vector2(4382.f, 508.f), 0.06f);
		pEffect->GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);


		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"windffect2"), L"windffect2", Vector2(0.f, 0.f),
			Vector2(572.f, 413.f), 11, 1, Vector2(580.f, 580.f), Vector2(0.5f, 0.5f), Vector2(6292.f, 413.f), 0.06f);
		pEffect->GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		for (int i = 0; i < 7; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"windhit"), L"wind_hit", Vector2(0.f, 0.f), Vector2(249.f, 248.f), 6, 1,
				Vector2(250.f, 250.f), Vector2(0.f, 0.2f), Vector2(1494.f, 248.f), 0.07f);
			pEffect->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"blastffect1"), L"blastffect1", Vector2(0.f, 0.f),
			Vector2(752.f, 358.f), 13, 1, Vector2(750.f, 750.f), Vector2(0.f, 0.f), Vector2(9776.f, 358.f), 0.05f);
		pEffect->GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		pEffect = new Effect();
		pEffect->CreateAnimation(Resources::Find<Texture>(L"blastffect2"), L"blastffect2", Vector2(0.f, 0.f),
			Vector2(735.f, 673.f), 9, 1, Vector2(750.f, 750.f), Vector2(0.f, 0.f), Vector2(6615.f, 673.f), 0.05f);
		pEffect->GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		for (int i = 0; i < 25; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"blasthit"), L"blast_hit", Vector2(0.f, 0.f),
				Vector2(285.f, 284.f), 8, 1, Vector2(300.f, 300.f), Vector2(0.f, 0.f), Vector2(2280.f, 284.f), 0.05f);
			pEffect->GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		for (int i = 0; i < 30; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(Resources::Find<Texture>(L"ultimate_hit"), L"ultimate_suriken_hit", Vector2(0.f, 0.f), Vector2(219.f, 209.f), 8, 1,
				Vector2(250.f, 250.f), Vector2(0.f, 0.f), Vector2(1752.f, 209.f), 0.1f);
			pEffect->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 0.f);
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		UltimateBackground* pBackGround = new UltimateBackground();
		pBackGround->SetName(L"ultimate1");
		pBackGround->GetComponent<Transform>()->SetScale(Vector3(15.5f, 15.f, 0.f));
		ObjectPoolManager::AddObjectPool(pBackGround->GetName(), pBackGround);


		UltimateFog* pFog = new UltimateFog();
		pFog->SetName(L"ultimate2");
		pFog->GetComponent<Transform>()->SetScale(Vector3(15.5f, 15.f, 0.f));
		ObjectPoolManager::AddObjectPool(pFog->GetName(), pFog);

		UltimateObject* pUtiObj = new UltimateObject();
		pUtiObj->SetName(L"ultimate0");
		pUtiObj->GetComponent<Transform>()->SetScale(15.5f, 15.5f, 0.f);
		ObjectPoolManager::AddObjectPool(pUtiObj->GetName(), pUtiObj);
	}

	void Player::send_equip(Equip* _pEquip, UINT _iPlayerPartID, UINT _iPlayerEquipID)
	{
		Protocol::C_EQUIP pkt;
		UCHAR cScene = SceneManger::GetActiveScene()->GetSceneID();
		UCHAR cLayer = (UCHAR)eLayerType::Player;
		UCHAR cPlayerID = GetObjectID();
		//UCHAR cEquipType = (UCHAR)_iPlayerPart;
		pkt.set_scene_layer_playerid_equipid((cScene << 24) | (cLayer << 16) | (cPlayerID << 8));
		//아이템 부위 , 장비 부위, 입는건지 해제하는건지, 아이템 아이디
		if (_pEquip != nullptr)
		{
			UINT iItemID = _pEquip->GetItemID();
			pkt.set_item_id((_iPlayerPartID << 24) | (_iPlayerEquipID << 16) | 0 | iItemID);
		}
		else
			pkt.set_item_id((_iPlayerPartID << 24) | (_iPlayerEquipID << 16) | (1<<8) | 0);
		

		shared_ptr<SendBuffer> pBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pBuffer);
	}

	void Player::update_shadow(bool _bActiveShadow)
	{
		//변화 없음
		if (_bActiveShadow == m_bActiveShadow)
			return;

		//애니메이션 다 종료될때까지 대기
		if (m_pShadow->IsActiveOffAnimation())
			return;;

		if (!_bActiveShadow)
			m_pShadow->Off();
		else
			m_pShadow->On();
	}
}
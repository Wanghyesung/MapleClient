#include "WPlayer.h"
#include "WRigidbody.h"
#include "WCollider2D.h"
#include "WPlayerScript.h"
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

namespace W
{
	Player::Player():
		m_pShadow(nullptr),
		m_bAnimLoop(true),
		m_bAlert(false),
		m_bActiveDark(false),
		m_bActiveShadow(false),
		m_iDir(1),
		m_bAlertTime(2.f),
		m_fChangeTime(0.25f),
		m_vecChildObj{},
		m_ePlayerState(ePlayerState::stand),
		m_strCurStateName(L"_jump")
	{
		SetName(L"Player");

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"PlayerShader"));
		Resources::Insert(L"Player", pMater);
		mr->SetMaterial(pMater);
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
		PlayerScript* pPlayerScript = AddComponent<PlayerScript>();
		Collider2D* pCollider = AddComponent<Collider2D>();
		AddComponent<Rigidbody>()->SetGround(false);

		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);
		GetComponent<Transform>()->SetPosition(0.f, -5.f, -2.f);

		pCollider->SetSize(Vector2(0.5f, 0.5f));

		m_vecChildObj.resize(3);


		PlayerBody* pPlayerBody = new PlayerBody();
		pPlayerBody->SetPlayer(this);
		pPlayerBody->Initialize();
		m_vecChildObj[0] = pPlayerBody;

		PlayerHead* pPlayerHead = new PlayerHead();
		pPlayerHead->SetPlayer(this);
		pPlayerHead->Initialize();
		m_vecChildObj[1] = pPlayerHead;

		PlayerArm* pPlayerArm = new PlayerArm();
		pPlayerArm->SetPlayer(this);
		pPlayerArm->Initialize();
		m_vecChildObj[2] = pPlayerArm;

		pPlayerScript->Initialize();

		m_pShadow = new Shadow();
	}
	void Player::Update()
	{
		if (m_bAlert)
		{
			m_bAlertTime -= Time::DeltaTime();

			if (m_bAlertTime <= 0.f)
			{
				SetAlert(false);
			}
		}


		GameObject::Update();

		if (m_pShadow)
			m_pShadow->Update();

		child_update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		if (m_pShadow)
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
			if (m_fChangeTime <= 0.25f /3.f)
				PlayerCB.vColor = Vector4(0.5f, 0.5f, 0.5f, 1.f);
			else
				PlayerCB.vColor = Vector4::One;

			if (m_fChangeTime <= 0.f)
				m_fChangeTime = 0.25f;
		}

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();

		if (m_pShadow)
			m_pShadow->Render();

		child_render();
		
	}
	
	void Player::SetAlert(bool _bAlert)
	{
		dynamic_cast<PlayerHead*>(m_vecChildObj[1])->SetAlert(_bAlert);
		m_bAlert = _bAlert;

		if (m_bAlert)
			m_bAlertTime = 2.f;
	}

	void Player::SetEquip(Equip* _pEquip)
	{
		Equip::EquipType eType = _pEquip->GetEquipType();
		switch (eType)
		{
		case W::Equip::EquipType::Hat:
			GetPlayerChild<PlayerHead>()->SetEquipHat(_pEquip);
			break;
		case W::Equip::EquipType::Top:
			GetPlayerChild<PlayerBody>()->SetEquipTop(_pEquip);
			break;
		case W::Equip::EquipType::Bottom:
			GetPlayerChild<PlayerBody>()->SetEquipBottom(_pEquip);
			break;
		case W::Equip::EquipType::Shoes:
			GetPlayerChild<PlayerBody>()->SetEquipShoes(_pEquip);
			break;
		case W::Equip::EquipType::Weapon:
			GetPlayerChild<PlayerArm>()->SetEquipWeapon(_pEquip);
			break;
		}

		Reset_Animation();
	}

	void Player::DisableEquip(Equip* _pEquip)
	{
		Equip::EquipType eType = _pEquip->GetEquipType();
		switch (eType)
		{
		case W::Equip::EquipType::Hat:
			GetPlayerChild<PlayerHead>()->SetEquipHat(nullptr);
			break;
		case W::Equip::EquipType::Top:
			GetPlayerChild<PlayerBody>()->SetEquipTop(nullptr);
			break;
		case W::Equip::EquipType::Bottom:
			GetPlayerChild<PlayerBody>()->SetEquipBottom(nullptr);
			break;
		case W::Equip::EquipType::Shoes:
			GetPlayerChild<PlayerBody>()->SetEquipShoes(nullptr);
			break;
		case W::Equip::EquipType::Weapon:
			GetPlayerChild<PlayerArm>()->SetEquipWeapon(nullptr);
			break;
		}

		Reset_Animation();
	}

	void Player::SetAnimStop(bool _bStop)
	{
		m_bAnimStop = _bStop;

		dynamic_cast<PlayerBody*>(m_vecChildObj[0])->SetStop(_bStop);
		dynamic_cast<PlayerHead*>(m_vecChildObj[1])->SetStop(_bStop);
		dynamic_cast<PlayerArm*>(m_vecChildObj[2])->SetStop(_bStop);
	}

	void Player::child_update()
	{
		for (GameObject* pObj : m_vecChildObj)
		{
			pObj->Update();
		}
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
	void Player::Reset_Animation()
	{
		dynamic_cast<PlayerBody*>(m_vecChildObj[0])->SetAnimationIndex();
		dynamic_cast<PlayerHead*>(m_vecChildObj[1])->SetAnimationIndex();
		dynamic_cast<PlayerArm*>(m_vecChildObj[2])->SetAnimationIndex();
	}

	void Player::SetHair(UINT _iHairNum)
	{
		dynamic_cast<PlayerHead*>(m_vecChildObj[1])->SetHair(_iHairNum);
		Reset_Animation();
	}
	void Player::SetEye(UINT _iEyeNum)
	{
		dynamic_cast<PlayerHead*>(m_vecChildObj[1])->SetEye(_iEyeNum);
		Reset_Animation();
	}
}
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

namespace W
{
	Player::Player():
		m_iDir(1),
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

		ThreadPool::LoadingResource<Texture>(L"darkffect", L"..\\Resources\\Texture\\Player\\skill\\effect1.png");
		ThreadPool::LoadingResource<Texture>(L"jumpeffect", L"..\\Resources\\Texture\\Player\\skill\\effect2.png");
		ThreadPool::LoadingResource<Texture>(L"luckeffect", L"..\\Resources\\Texture\\Player\\skill\\effect.png");
		ThreadPool::LoadingResource<Texture>(L"luckhit", L"..\\Resources\\Texture\\Player\\skill\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"quadhit", L"..\\Resources\\Texture\\Player\\skill\\hit1.png");
		ThreadPool::LoadingResource<Texture>(L"quadffect", L"..\\Resources\\Texture\\Player\\skill\\effect7.png");
		ThreadPool::LoadingResource<Texture>(L"raideffect1", L"..\\Resources\\Texture\\Player\\skill\\effect8.png");
		ThreadPool::LoadingResource<Texture>(L"raideffect2", L"..\\Resources\\Texture\\Player\\skill\\effect9.png");
		ThreadPool::LoadingResource<Texture>(L"raidhit", L"..\\Resources\\Texture\\Player\\skill\\hit2.png");
		ThreadPool::LoadingResource<Texture>(L"speedffect", L"..\\Resources\\Texture\\Player\\skill\\effect3.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		ThreadPool::LoadingResource<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
		ThreadPool::LoadingResource<Texture>(L"windffect1", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_0.png");
		ThreadPool::LoadingResource<Texture>(L"windffect2", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_1.png");
		ThreadPool::LoadingResource<Texture>(L"wind", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"windTex", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\windshuriken.png");
		ThreadPool::LoadingResource<Texture>(L"avenTex", L"..\\Resources\\Texture\\Player\\skill\\ball.png");
		ThreadPool::LoadingResource<Texture>(L"aveneffect", L"..\\Resources\\Texture\\Player\\skill\\effect4.png");
		ThreadPool::LoadingResource<Texture>(L"blast", L"..\\Resources\\Texture\\Player\\skill\\blast\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"blastffect1", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_0.png");
		ThreadPool::LoadingResource<Texture>(L"blastffect2", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_1.png");
		ThreadPool::LoadingResource<Texture>(L"blast", L"..\\Resources\\Texture\\Player\\skill\\blast\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"blastTex", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_2.png");
		ThreadPool::LoadingResource<Texture>(L"loadeffect", L"..\\Resources\\Texture\\Player\\skill\\load\\start.png");
		ThreadPool::LoadingResource<Texture>(L"load", L"..\\Resources\\Texture\\Player\\skill\\load\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"loadTex", L"..\\Resources\\Texture\\Player\\skill\\load\\load.png");
		ThreadPool::LoadingResource<Texture>(L"shadowTex", L"..\\Resources\\Texture\\Player\\skill\\shadow\\shadow.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate1", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate1.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate2", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate2.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		ThreadPool::LoadingResource<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate_hit", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\hit.png");

		//block
		ThreadPool::Joinable();
	}

	Player::~Player()
	{
		for (GameObject* pChildObj : m_vecChildObj)
		{
			delete pChildObj;
			pChildObj = nullptr;
		}
	}

	void Player::Initialize()
	{
		//PlayerScript* pPlayerScript = AddComponent<PlayerScript>();
		
		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);
		GetComponent<Transform>()->SetPosition(0.f, -5.f, -2.f);

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

	}
	void Player::Update()
	{
		
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		child_lateupdate();
	}
	void Player::Render()
	{
		
		renderer::PlayerCB PlayerCB;
		PlayerCB.vDir.x = m_iDir * -1;
		PlayerCB.vColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();		

		child_render();
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
	
	
}
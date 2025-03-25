#include "WPlayerHead.h"
#include "WAnimator.h"
#include "WTexture.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WPlayerHat.h"
#include "WEyes.h"
#include "WPlayerHair.h"

namespace W
{
	PlayerHead::PlayerHead():
		m_pPlayerHat(nullptr),
		m_pPlayerHair(nullptr),
		m_pPlayerEyes(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
	}
	PlayerHead::~PlayerHead()
	{
		if (m_pPlayerHat)
		{
			delete m_pPlayerHat;
			m_pPlayerHat = nullptr;
		}
		if (m_pPlayerHair)
		{
			delete m_pPlayerHair;
			m_pPlayerHair = nullptr;
		}
		if (m_pPlayerEyes)
		{
			delete m_pPlayerEyes;
			m_pPlayerEyes = nullptr;
		}
	}
	void PlayerHead::Initialize()
	{
		Animator* pAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> pAtlasBdoy
			= Resources::Load<Texture>(L"PlayerheadTex", L"..\\Resources\\Texture\\Player\\head\\Playerhead.png");
		pAnimator->Create(L"head_alert_left", pAtlasBdoy, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_jump_left", pAtlasBdoy, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_ladder_left", pAtlasBdoy, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_pronestab_left", pAtlasBdoy, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_proneattack_left", pAtlasBdoy, Vector2(150.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_stab_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_stand_left", pAtlasBdoy, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swing1_left", pAtlasBdoy, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swing2_left", pAtlasBdoy, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swingOF_left", pAtlasBdoy, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_walk_left", pAtlasBdoy, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"head_swingQS_left")->Create(L"head_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"head_swingQS_left")->Create(L"head_swingQS_left", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

		pAnimator->Create(L"head_alert_right", pAtlasBdoy, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_jump_right", pAtlasBdoy, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_ladder_right", pAtlasBdoy, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_pronestab_right", pAtlasBdoy, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_proneattack_right", pAtlasBdoy, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);

		pAnimator->Create(L"head_stab_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_stand_right", pAtlasBdoy, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swing1_right", pAtlasBdoy, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swing2_right", pAtlasBdoy, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swingOF_right", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_walk_right", pAtlasBdoy, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"head_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"head_swingQS_right")->Create(L"head_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"head_swingQS_right")->Create(L"head_swingQS_right", pAtlasBdoy, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

		Vector3 vScale = m_pPlayer->GetComponent<Transform>()->GetScale();
		GetComponent<Transform>()->SetScale(vScale);

		m_pPlayerHat = new PlayerHat();
		m_pPlayerHat->SetPlayerHead(this);

		m_pPlayerEyes = new Eyes();
		m_pPlayerEyes->SetPlayerHead(this);
		m_pPlayerEyes->Initialize();
		
		
		m_pPlayerHair = new PlayerHair();
		m_pPlayerHair->SetPlayerHead(this);
		m_pPlayerHair->Initialize();
	}

	void PlayerHead::Update()
	{
		GameObject::Update();

		m_pPlayerHair->Update();
		m_pPlayerEyes->Update();
		m_pPlayerHat->Update();
	}
	void PlayerHead::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();
		Vector3 vPlayerPos = m_pPlayer->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(vPlayerPos);

		int iDir = m_pPlayer->GetDir();
		std::wstring strDir;
		std::wstring strState;
		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		strState = m_pPlayer->GetCurStateName();

		std::wstring strAnim = L"head" + strState + strDir;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			bool bLoop = m_pPlayer->IsLoop();
			pAnimator->Play(strAnim, bLoop);
		}

		GameObject::LateUpdate();

		m_pPlayerHair->LateUpdate();
		m_pPlayerEyes->LateUpdate();
		m_pPlayerHat->LateUpdate();
	}
	void PlayerHead::Render()
	{
		GameObject::Render();

		m_pPlayerHair->Render();
		m_pPlayerEyes->Render();
		m_pPlayerHat->Render();
	}

	void PlayerHead::SetAlert(bool _bAlert)
	{
		m_pPlayerEyes->SetAlert(_bAlert);
	}

	void PlayerHead::SetEquipHat(Equip* _pEquip)
	{
		if (_pEquip == nullptr)
			m_pPlayerHair->SetHairDown(false);
		else
			m_pPlayerHair->SetHairDown(true);
		
		m_pPlayerHat->SetPlayerEquip(_pEquip);
	}

	void PlayerHead::SetAnimationIndex()
	{
		if (m_strCurAnim.size() != 0)
			GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
		if (m_pPlayerHair->GetCurAnimName().size() != 0)
			m_pPlayerHair->GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
		if (m_pPlayerEyes->GetCurAnimName().size() != 0)
			m_pPlayerEyes->GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
		if (m_pPlayerHat->GetCurAnimName().size() != 0)
			m_pPlayerHat->GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
	}
	void PlayerHead::SetStop(bool _bStop)
	{
		GetComponent<Animator>()->Stop(_bStop);
		m_pPlayerHair->GetComponent<Animator>()->Stop(_bStop);
		m_pPlayerEyes->GetComponent<Animator>()->Stop(_bStop);
		m_pPlayerHat->GetComponent<Animator>()->Stop(_bStop);
	}

	void PlayerHead::SetHair(UINT _iHairNum)
	{
		m_pPlayerHair->SetHair(_iHairNum);
	}

	void PlayerHead::SetEye(UINT _iEyeNum)
	{
		m_pPlayerEyes->SetEye(_iEyeNum);
	}
	
}
#include "WPlayerArm.h"
#include "WAnimator.h"
#include "WTexture.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WPlayerWeapon.h"
namespace W
{
	PlayerArm::PlayerArm():
		m_pPlayerWeapon(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
	}
	PlayerArm::~PlayerArm()
	{
		if (m_pPlayerWeapon)
		{
			delete m_pPlayerWeapon;
			m_pPlayerWeapon = nullptr;
		}
	}
	void PlayerArm::Initialize()
	{
		Animator* pAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> pAtlasBdoy
			= Resources::Load<Texture>(L"PlayerArmTex", L"..\\Resources\\Texture\\Player\\arm\\PlayerArm.png");
		pAnimator->Create(L"arm_alert_left", pAtlasBdoy, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f),Vector2::Zero,0.18f);
		pAnimator->Create(L"arm_jump_left", pAtlasBdoy, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_ladder_left", pAtlasBdoy, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_pronestab_left", pAtlasBdoy, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_proneattack_left", pAtlasBdoy, Vector2(150.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_stab_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_stand_left", pAtlasBdoy, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swing1_left", pAtlasBdoy, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swing2_left", pAtlasBdoy, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swingOF_left", pAtlasBdoy, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_walk_left", pAtlasBdoy, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"arm_swingQS_left")->Create(L"arm_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"arm_swingQS_left")->Create(L"arm_swingQS_left", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

		pAnimator->Create(L"arm_alert_right", pAtlasBdoy, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_jump_right", pAtlasBdoy, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_ladder_right", pAtlasBdoy, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_pronestab_right", pAtlasBdoy, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_proneattack_right", pAtlasBdoy, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_stab_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_stand_right", pAtlasBdoy, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swing1_right", pAtlasBdoy, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swing2_right", pAtlasBdoy, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swingOF_right", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_walk_right", pAtlasBdoy, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"arm_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"arm_swingQS_right")->Create(L"arm_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"arm_swingQS_right")->Create(L"arm_swingQS_right", pAtlasBdoy, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		Vector3 vScale = m_pPlayer->GetComponent<Transform>()->GetScale();
		GetComponent<Transform>()->SetScale(vScale);

		m_pPlayerWeapon = new PlayerWeapon();
		m_pPlayerWeapon->SetPlayerArm(this);
	}
	void PlayerArm::Update()
	{
		GameObject::Update();

		m_pPlayerWeapon->Update();
	}
	void PlayerArm::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();
		Vector3 vPlayerPos = m_pPlayer->GetComponent<Transform>()->GetPosition();
		//vPlayerPos.x += 2.f;
		GetComponent<Transform>()->SetPosition(vPlayerPos);

		int iDir = m_pPlayer->GetDir();
		std::wstring strDir;
		std::wstring strState;
		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		strState = m_pPlayer->GetCurStateName();

		std::wstring strAnim = L"arm" + strState + strDir;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			bool bLoop = m_pPlayer->IsLoop();
			pAnimator->Play(strAnim, bLoop);
		}

		GameObject::LateUpdate();

		m_pPlayerWeapon->LateUpdate();
	}
	void PlayerArm::Render()
	{
		GameObject::Render();

		m_pPlayerWeapon->Render();
	}

	void PlayerArm::SetEquipWeapon(Equip* _pEquip)
	{
		m_pPlayerWeapon->SetPlayerEquip(_pEquip);
	}

	void PlayerArm::SetAnimationIndex()
	{
		if (m_strCurAnim.size() != 0)
			GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
		if(m_pPlayerWeapon->GetCurAnimName().size() !=0)
			m_pPlayerWeapon->GetComponent<Animator>()->GetActiveAnimation()->SetIndex(0);
	}

	void PlayerArm::SetStop(bool _bStop)
	{
		GetComponent<Animator>()->Stop(_bStop);
		m_pPlayerWeapon->GetComponent<Animator>()->Stop(_bStop);
	}

	
}
#include "WPlayerHat.h"
#include "WAnimator.h"
#include "WTexture.h"
#include "WResources.h"
#include "WPlayerHead.h"
#include "WRenderer.h"
#include "WEquip.h"
#include "WTransform.h"
namespace W
{
	PlayerHat::PlayerHat():
		m_pPlayerHead(nullptr),
		m_strCurAnim{},
		m_strCurEquip{}
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* pAnimator = AddComponent<Animator>();
	}

	PlayerHat::~PlayerHat()
	{

	}
	void PlayerHat::Initialize()
	{
		if (m_strCurEquip.size() == 0)
			return;

		Animator* pAnimator = GetComponent<Animator>();

		std::shared_ptr<Texture> pAtlasBdoy
			= Resources::Load<Texture>(L"Player " + m_strCurEquip + L"Tex", L"..\\Resources\\Texture\\Player\\equip\\" + m_strCurEquip + L".png");

		pAnimator->Create(m_strCurEquip + L"_alert_left", pAtlasBdoy, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3 ,Vector2(120.f,120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_jump_left", pAtlasBdoy, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_ladder_left", pAtlasBdoy, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_pronestab_left", pAtlasBdoy, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_proneattack_left", pAtlasBdoy, Vector2(150.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_stab_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_stand_left", pAtlasBdoy, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swing1_left", pAtlasBdoy, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swing2_left", pAtlasBdoy, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swingOF_left", pAtlasBdoy, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_walk_left", pAtlasBdoy, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(m_strCurEquip + L"_swingQS_left")->Create(m_strCurEquip + L"_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(m_strCurEquip + L"_swingQS_left")->Create(m_strCurEquip + L"_swingQS_left", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		pAnimator->Create(m_strCurEquip + L"_alert_right", pAtlasBdoy, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_jump_right", pAtlasBdoy, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_ladder_right", pAtlasBdoy, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_pronestab_right", pAtlasBdoy, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_proneattack_right", pAtlasBdoy, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_stab_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_stand_right", pAtlasBdoy, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swing1_right", pAtlasBdoy, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swing2_right", pAtlasBdoy, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swingOF_right", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_walk_right", pAtlasBdoy, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(m_strCurEquip + L"_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(m_strCurEquip + L"_swingQS_right")->Create(m_strCurEquip + L"_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(m_strCurEquip + L"_swingQS_right")->Create(m_strCurEquip + L"_swingQS_right", pAtlasBdoy, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		Vector3 vScale = m_pPlayerHead->GetComponent<Transform>()->GetScale();
		GetComponent<Transform>()->SetScale(vScale);
	}
	void PlayerHat::Update()
	{
	
	}
	void PlayerHat::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void PlayerHat::Render()
	{
		GameObject::Render();
	}
	void PlayerHat::SetPlayerEquip(Equip* _pEquip)
	{
		if (_pEquip != nullptr)
			m_strCurEquip = _pEquip->GetEquipName();
		else
			m_strCurEquip = L"";

		Initialize();
	}
}
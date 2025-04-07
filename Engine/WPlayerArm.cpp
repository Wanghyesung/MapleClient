#include "WPlayerArm.h"
#include "WAnimator.h"
#include "WTexture.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WPlayerWeapon.h"
namespace W
{
	PlayerArm::PlayerArm()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
	}
	PlayerArm::~PlayerArm()
	{
		
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

	}
	void PlayerArm::Update()
	{
		GameObject::Update();
	}
	void PlayerArm::LateUpdate()
	{
		
		GameObject::LateUpdate();

	}
	void PlayerArm::Render()
	{
		GameObject::Render();

	}
	
}
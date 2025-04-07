#include "WPlayerBody.h"
#include "WAnimator.h"
#include "WTexture.h"
#include "WResources.h"
#include "WPlayer.h"
#include "WRenderer.h"
#include "WPlayerTop.h"
#include "WPlayerBottom.h"
#include "WPlayerShoes.h"
namespace W
{
	PlayerBody::PlayerBody() 
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
	}
	PlayerBody::~PlayerBody()
	{
	
	}
	void PlayerBody::Initialize()
	{
		Animator* pAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> pAtlasBdoy
			= Resources::Load<Texture>(L"PlayerBodyTex", L"..\\Resources\\Texture\\Player\\body\\PlayerBody.png");
		pAnimator->Create(L"body_alert_left", pAtlasBdoy, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_jump_left", pAtlasBdoy, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_ladder_left", pAtlasBdoy, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_pronestab_left", pAtlasBdoy, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_proneattack_left", pAtlasBdoy, Vector2(150.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);

		pAnimator->Create(L"body_stab_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_stand_left", pAtlasBdoy, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swing1_left", pAtlasBdoy, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swing2_left", pAtlasBdoy, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swingOF_left", pAtlasBdoy, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_walk_left", pAtlasBdoy, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"body_swingQS_left")->Create(L"body_swingQS_left", pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"body_swingQS_left")->Create(L"body_swingQS_left", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

		pAnimator->Create(L"body_alert_right", pAtlasBdoy, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_jump_right", pAtlasBdoy, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_ladder_right", pAtlasBdoy, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_pronestab_right", pAtlasBdoy, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_proneattack_right", pAtlasBdoy, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);

		pAnimator->Create(L"body_stab_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_stand_right", pAtlasBdoy, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swing1_right", pAtlasBdoy, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swing2_right", pAtlasBdoy, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swingOF_right", pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_walk_right", pAtlasBdoy, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"body_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"body_swingQS_right")->Create(L"body_swingQS_right", pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"body_swingQS_right")->Create(L"body_swingQS_right", pAtlasBdoy, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

	}
	void PlayerBody::Update()
	{
		
	}
	void PlayerBody::LateUpdate()
	{
		
		GameObject::LateUpdate();

	}
	void PlayerBody::Render()
	{
		GameObject::Render();

	}

}
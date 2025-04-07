#include "WSkelegon.h"
#include "WAnimator.h"
#include "WResources.h"

#include "WSceneManger.h"
#include "WEffect.h"

namespace W
{
	Skelegon::Skelegon()
	{
		SetName(L"skelegon");

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"skelegonMater", pMater);

		mr->SetMaterial(pMater);

		Animator* pAnimator = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"SkelegonTex", L"..\\Resources\\Texture\\Monster\\skelegon.png");
		pAnimator->Create(L"skelegon_stand_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(600.0f, 200.0f), 6, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_move_left", pAtlas, Vector2(0.0f, 200.0f), Vector2(600.0f, 200.0f), 4, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_attack0_left", pAtlas, Vector2(0.0f, 400.0f), Vector2(600.0f, 200.0f), 11, Vector2(600.f, 200.f), Vector2::Zero, 0.2f);
		pAnimator->Create(L"skelegon_dead_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(600.0f, 200.0f), 8, Vector2(600.f, 200.f), Vector2::Zero, 0.15f);
		pAnimator->Create(L"skelegon_hit_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(600.0f, 200.0f), 1, Vector2(600.f, 200.f));

		pAnimator->Create(L"skelegon_stand_right", pAtlas, Vector2(6000.0f, 0.0f), Vector2(-600.0f, 200.0f), 6, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_move_right", pAtlas, Vector2(6000.0f, 200.0f), Vector2(-600.0f, 200.0f), 4, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_attack0_right", pAtlas, Vector2(6000.0f, 400.0f), Vector2(-600.0f, 200.0f), 11, Vector2(600.f, 200.f), Vector2::Zero, 0.2f);
		pAnimator->Create(L"skelegon_dead_right", pAtlas, Vector2(6000.0f, 600.0f), Vector2(-600.0f, 200.0f), 8, Vector2(600.f, 200.f), Vector2::Zero, 0.15f);
		pAnimator->Create(L"skelegon_hit_right", pAtlas, Vector2(6000.0f, 600.0f), Vector2(-600.0f, 200.0f), 1, Vector2(600.f, 200.f));

		Resources::Load<Texture>(L"sklaserEffect", L"..\\Resources\\Texture\\Monster\\attack1_hit.png");
	}

	Skelegon::~Skelegon()
	{

	}
	void Skelegon::Initialize()
	{
		
	}

	void Skelegon::Update()
	{
		
	}

	void Skelegon::LateUpdate()
	{
		
		Monster::LateUpdate();
	}

	void Skelegon::Render()
	{
		Monster::Render();
	}
}
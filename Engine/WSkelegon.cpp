#include "WSkelegon.h"
#include "WAnimator.h"
#include "WResources.h"

#include "WSceneManger.h"
#include "WEffect.h"
#include "WTransform.h"
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

		GetComponent<Transform>()->SetScale(6.f, 2.f, 0.f);
		Animator* pAnimator = AddComponent<Animator>();

		//std::shared_ptr<Texture> pAtlas = Resources::Load<Texture>(L"SkelegonTex", L"..\\Resources\\Texture\\Monster\\skelegon.png");
		pAnimator->Create(L"skelegon_stand_left", nullptr, Vector2(0.0f, 0.0f), Vector2(600.0f, 200.0f), 6, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f));
		pAnimator->Create(L"skelegon_move_left", nullptr, Vector2(0.0f, 200.0f), Vector2(600.0f, 200.0f), 4, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f));
		pAnimator->Create(L"skelegon_attack0_left", nullptr, Vector2(0.0f, 400.0f), Vector2(600.0f, 200.0f), 11, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f), 0.2f);
		pAnimator->Create(L"skelegon_dead_left", nullptr, Vector2(0.0f, 600.0f), Vector2(600.0f, 200.0f), 8, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f), 0.15f);
		pAnimator->Create(L"skelegon_hit_left", nullptr, Vector2(0.0f, 600.0f), Vector2(600.0f, 200.0f), 1, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f));

		pAnimator->Create(L"skelegon_stand_right", nullptr, Vector2(6000.0f, 0.0f), Vector2(-600.0f, 200.0f), 6, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f));
		pAnimator->Create(L"skelegon_move_right", nullptr, Vector2(6000.0f, 200.0f), Vector2(-600.0f, 200.0f), 4, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f) );
		pAnimator->Create(L"skelegon_attack0_right", nullptr, Vector2(6000.0f, 400.0f), Vector2(-600.0f, 200.0f), 11, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f));
		pAnimator->Create(L"skelegon_dead_right", nullptr, Vector2(6000.0f, 600.0f), Vector2(-600.0f, 200.0f), 8, Vector2(600.f, 200.f), Vector2::Zero, Vector2(6600.f, 800.f));
		pAnimator->Create(L"skelegon_hit_right", nullptr, Vector2(6000.0f, 600.0f), Vector2(-600.0f, 200.0f), 1, Vector2(600.f, 200.f), Vector2::Zero,Vector2(6600.f, 800.f));

		pAnimator->Play(L"skelegon_stand_left", true);
	}

	Skelegon::~Skelegon()
	{

	}
	void Skelegon::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"SkelegonTex");
		Animator* pAnimator = GetComponent<Animator>();

		pAnimator->SetTexture(pAtlas);
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

	void Skelegon::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
}
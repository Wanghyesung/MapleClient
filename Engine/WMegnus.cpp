#include "WMegnus.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WMegnusStone.h"
#include "WCloneMegnus.h"
#include "WMonsterMoveAttack.h"
#include "WMobZone.h"
#include "WSceneManger.h"
#include "WEventManager.h"
#include "WMegnusAttack.h"
#include "WTime.h"
#include "WSleepGas.h"
namespace W
{
	Megnus::Megnus() 
	{
		SetName(L"Megnus");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"MegnuslMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas1 = Resources::Find<Texture>(L"Megnus1");
		std::shared_ptr<Texture> pAtlas2 = Resources::Find<Texture>(L"Megnus2");

		Animator* pAnim = AddComponent<Animator>();

		pAnim->Create(L"Megnus_stand_left", nullptr, Vector2(0.f, 0.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_move_left", nullptr, Vector2(0.f, 550.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack0_left", nullptr, Vector2(0.f, 1100.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_left")->Create(L"Megnus_attack0_left", nullptr, Vector2(0.f, 1650.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_left")->Create(L"Megnus_attack0_left", nullptr, Vector2(0.f, 2200.f), Vector2(1100.f, 550.f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack1_left", nullptr, Vector2(0.f, 2750.f), Vector2(1100, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack1_left")->Create(L"Megnus_attack1_left", nullptr, Vector2(0.f, 3300), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack2_left", nullptr, Vector2(0.f, 3850), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_left")->Create(L"Megnus_attack2_left", nullptr, Vector2(0.f, 4400.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_left")->Create(L"Megnus_attack2_left", nullptr, Vector2(0.f, 4950.f), Vector2(1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack3_left", nullptr, Vector2(0.f, 5500.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", nullptr, Vector2(0.f, 6050), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", nullptr, Vector2(0.f, 6600.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", nullptr, Vector2(0.f, 7150.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", nullptr, Vector2(0.f, 7700), Vector2(1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);

		pAnim->Create(L"Megnus_stand_right", nullptr, Vector2(8800.f, 0.f), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_move_right", nullptr, Vector2(8800.f, 550.f), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack0_right", nullptr, Vector2(8800.f, 1100.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_right")->Create(L"Megnus_attack0_right", nullptr, Vector2(8800.f, 1650.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_right")->Create(L"Megnus_attack0_right", nullptr, Vector2(8800.f, 2200.f), Vector2(-1100.f, 550.f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack1_right", nullptr, Vector2(8800.f, 2750.f), Vector2(-1100, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack1_right")->Create(L"Megnus_attack1_right", nullptr, Vector2(8800.f, 3300), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack2_right", nullptr, Vector2(8800.f, 3850), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_right")->Create(L"Megnus_attack2_right", nullptr, Vector2(8800.f, 4400.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_right")->Create(L"Megnus_attack2_right", nullptr, Vector2(8800.f, 4950.f), Vector2(-1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->Create(L"Megnus_attack3_right", nullptr, Vector2(8800.f, 5500), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", nullptr, Vector2(8800.f, 6050.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", nullptr, Vector2(8800.f, 6600.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", nullptr, Vector2(8800.f, 7150.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", nullptr, Vector2(8800.f, 7700.f), Vector2(-1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 8250.f), 0.15f);

		pAnim->Create(L"Megnus_attack4_left", nullptr, Vector2(0.f, 0.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_left")->Create(L"Megnus_attack4_left", nullptr, Vector2(0.f, 550.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_left")->Create(L"Megnus_attack4_left", nullptr, Vector2(0.f, 1100.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_left")->Create(L"Megnus_attack4_left", nullptr, Vector2(0.f, 1650.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->Create(L"Megnus_attack5_left", nullptr, Vector2(0.f, 2200.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack5_left")->Create(L"Megnus_attack5_left", nullptr, Vector2(0.f, 2750.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->Create(L"Megnus_attack6_left", nullptr, Vector2(0.f, 3300.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack6_left")->Create(L"Megnus_attack6_left", nullptr, Vector2(0.f, 3850.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->Create(L"Megnus_dead_left", nullptr, Vector2(0.f, 4400.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_left")->Create(L"Megnus_dead_left", nullptr, Vector2(0.f, 4950.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_left")->Create(L"Megnus_dead_left", nullptr, Vector2(0.f, 5500.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);

		pAnim->Create(L"Megnus_attack4_right", nullptr, Vector2(8800.f, 0.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_right")->Create(L"Megnus_attack4_right", nullptr, Vector2(8800.f, 550.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_right")->Create(L"Megnus_attack4_right", nullptr, Vector2(8800.f, 1100.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_right")->Create(L"Megnus_attack4_right", nullptr, Vector2(8800.f, 1650.f), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->Create(L"Megnus_attack5_right", nullptr, Vector2(8800.f, 2200.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack5_right")->Create(L"Megnus_attack5_right", nullptr, Vector2(8800.f, 2750.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->Create(L"Megnus_attack6_right", nullptr, Vector2(8800.f, 3300.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_attack6_right")->Create(L"Megnus_attack6_right", nullptr, Vector2(8800.f, 3850.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->Create(L"Megnus_dead_right", nullptr, Vector2(8800.f, 4400.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_right")->Create(L"Megnus_dead_right", nullptr, Vector2(8800.f, 4950.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_right")->Create(L"Megnus_dead_right", nullptr, Vector2(8800.f, 5500.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(9900.f, 6050.f), 0.15f);

	}
	Megnus::~Megnus()
	{
		
	}
	void Megnus::Initialize()
	{
		
	}
	void Megnus::Update()
	{
	}
	void Megnus::LateUpdate()
	{
		Monster::LateUpdate();
	}
	void Megnus::Render()
	{
		Monster::Render();
	}
	
}
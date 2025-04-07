#include "WPinkBean.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WJenesis.h"
#include "WPinkBeanStone.h"
#include "WRoccatBean.h"
#include "WMiniBean.h"
#include "WSolomon.h"
#include "WRex.h"
#include "WMunin.h"
#include "WAriel.h"
#include "WWhiggin.h"
#include "WSharHP.h"
namespace W
{
	PinkBean::PinkBean()
	{
		SetName(L"PinkBean"); 

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"PinkBeanlMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas1 = Resources::Find<Texture>(L"PinkBean1");
		std::shared_ptr<Texture> pAtlas2 = Resources::Find<Texture>(L"PinkBean2");

		Animator* pAnim = AddComponent<Animator>();
		
		pAnim->Create(L"PinkBean_start_left", pAtlas2, Vector2(0.f, 7200.f), Vector2(750.f, 600.f), 4, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_start_right", pAtlas2, Vector2(9750.f, 7200.f), Vector2(-750.f, 600.f), 4, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		//pAnim->StartEvent(L"PinkBean_start_left") = std::bind(&PinkBean::start, this);
		//pAnim->StartEvent(L"PinkBean_start_right") = std::bind(&PinkBean::start, this);

		pAnim->Create(L"PinkBean_stand_left", pAtlas1, Vector2(0.f, 0.f), Vector2(750.f, 600.f), 6, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_move_left", pAtlas1, Vector2(0.f, 600.f), Vector2(750.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack0_left", pAtlas1,  Vector2(0.f, 1200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack1_left", pAtlas1,  Vector2(0.f, 1800.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack1_left")->Create(L"PinkBean_attack1_left", pAtlas1, Vector2(0.f, 2400.f), Vector2(750.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack2_left", pAtlas1,  Vector2(0.f, 3000.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack2_left")->Create(L"PinkBean_attack2_left", pAtlas1, Vector2(0.f, 3600.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack3_left", pAtlas1,  Vector2(0.f, 4200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack3_left")->Create(L"PinkBean_attack3_left", pAtlas1, Vector2(0.f, 4800.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_dead_left", pAtlas1, Vector2(0.f, 5400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_left")->Create(L"PinkBean_dead_left", pAtlas1, Vector2(0.f, 6000.f), Vector2(750.f, 600.f),14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_left")->Create(L"PinkBean_dead_left", pAtlas1, Vector2(0.f, 6600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"PinkBean_stand_right", pAtlas1, Vector2(9750.f, 0.f), Vector2(-750.f, 600.f), 6, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_move_right", pAtlas1, Vector2(9750.f, 600.f), Vector2(-750.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack0_right", pAtlas1, Vector2(9750.f, 1200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack1_right", pAtlas1, Vector2(9750.f, 1800.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack1_right")->Create(L"PinkBean_attack1_right", pAtlas1, Vector2(9750.f, 2400.f), Vector2(-750.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack2_right", pAtlas1, Vector2(9750.f, 3000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack2_right")->Create(L"PinkBean_attack2_right", pAtlas1, Vector2(9750.f, 3600.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack3_right", pAtlas1, Vector2(9750.f, 4200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack3_right")->Create(L"PinkBean_attack3_right", pAtlas1, Vector2(9750.f, 4800.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_dead_right", pAtlas1, Vector2(9750.f, 5400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_right")->Create(L"PinkBean_dead_right", pAtlas1, Vector2(9750.f, 6000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_right")->Create(L"PinkBean_dead_right", pAtlas1, Vector2(9750.f, 6600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		
		//atlas2
		pAnim->Create(L"PinkBean_attack4_left", pAtlas2, Vector2(0.f, 0.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack4_left")->Create(L"PinkBean_attack4_left", pAtlas2, Vector2(0.f, 600.f), Vector2(750.f, 600.f), 3, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack5_left", pAtlas2, Vector2(0.f, 1200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack5_left")->Create(L"PinkBean_attack5_left", pAtlas2, Vector2(0.f, 1800.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack6_left", pAtlas2, Vector2(0.f, 2400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack6_left")->Create(L"PinkBean_attack6_left", pAtlas2, Vector2(0.f, 3000.f), Vector2(750.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack7_left", pAtlas2, Vector2(0.f, 3600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack7_left")->Create(L"PinkBean_attack7_left", pAtlas2, Vector2(0.f, 4200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack8_left", pAtlas2, Vector2(0.f, 4800.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack8_left")->Create(L"PinkBean_attack8_left", pAtlas2, Vector2(0.f, 5400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack9_left", pAtlas2, Vector2(0.f, 6000.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack9_left")->Create(L"PinkBean_attack9_left", pAtlas2, Vector2(0.f, 6600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack10_left", pAtlas2, Vector2(0.f, 7200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		
		pAnim->Create(L"PinkBean_attack4_right", pAtlas2, Vector2(9750.f, 0.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack4_right")->Create(L"PinkBean_attack4_right", pAtlas2, Vector2(9750.f, 600.f), Vector2(-750.f, 600.f), 3, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack5_right", pAtlas2, Vector2(9750.f, 1200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack5_right")->Create(L"PinkBean_attack5_right", pAtlas2, Vector2(9750.f, 1800.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack6_right", pAtlas2, Vector2(9750.f, 2400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack6_right")->Create(L"PinkBean_attack6_right", pAtlas2, Vector2(9750.f, 3000.f), Vector2(-750.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack7_right", pAtlas2, Vector2(9750.f, 3600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack7_right")->Create(L"PinkBean_attack7_right", pAtlas2, Vector2(9750.f, 4200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack8_right", pAtlas2, Vector2(9750.f, 4800.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack8_right")->Create(L"PinkBean_attack8_right", pAtlas2, Vector2(9750.f, 5400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack9_right", pAtlas2, Vector2(9750.f, 6000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack9_right")->Create(L"PinkBean_attack9_right", pAtlas2, Vector2(9750.f, 6600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack10_right", pAtlas2, Vector2(9750.f, 7200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	PinkBean::~PinkBean()
	{
		
	}
	void PinkBean::Initialize()
	{
		
	}
	void PinkBean::Update()
	{
		
	}
	void PinkBean::LateUpdate()
	{
		
		Monster::LateUpdate();

	}
	void PinkBean::Render()
	{
		Monster::Render();
	}


}
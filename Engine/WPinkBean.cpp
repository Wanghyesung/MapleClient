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

	
		Animator* pAnim = AddComponent<Animator>();	
		pAnim->Create(L"PinkBean_start_left", nullptr, Vector2(0.f, 7200.f), Vector2(750.f, 600.f), 4, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_start_right", nullptr, Vector2(9750.f, 7200.f), Vector2(-750.f, 600.f), 4, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		
		pAnim->Create(L"PinkBean_stand_left", nullptr, Vector2(0.f, 0.f), Vector2(750.f, 600.f), 6, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_move_left", nullptr, Vector2(0.f, 600.f), Vector2(750.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack0_left", nullptr,  Vector2(0.f, 1200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f),0.15f);
		pAnim->Create(L"PinkBean_attack1_left", nullptr,  Vector2(0.f, 1800.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f),0.15f);
		pAnim->FindAnimation(L"PinkBean_attack1_left")->Create(L"PinkBean_attack1_left", nullptr, Vector2(0.f, 2400.f), Vector2(750.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack2_left", nullptr,  Vector2(0.f, 3000.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack2_left")->Create(L"PinkBean_attack2_left", nullptr, Vector2(0.f, 3600.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack3_left", nullptr,  Vector2(0.f, 4200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack3_left")->Create(L"PinkBean_attack3_left", nullptr, Vector2(0.f, 4800.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_dead_left", nullptr, Vector2(0.f, 5400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_left")->Create(L"PinkBean_dead_left", nullptr, Vector2(0.f, 6000.f), Vector2(750.f, 600.f),14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_left")->Create(L"PinkBean_dead_left", nullptr, Vector2(0.f, 6600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);

		pAnim->Create(L"PinkBean_stand_right", nullptr, Vector2(9750.f, 0.f), Vector2(-750.f, 600.f), 6, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_move_right", nullptr, Vector2(9750.f, 600.f), Vector2(-750.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack0_right", nullptr, Vector2(9750.f, 1200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack1_right", nullptr, Vector2(9750.f, 1800.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack1_right")->Create(L"PinkBean_attack1_right", nullptr, Vector2(9750.f, 2400.f), Vector2(-750.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack2_right", nullptr, Vector2(9750.f, 3000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack2_right")->Create(L"PinkBean_attack2_right", nullptr, Vector2(9750.f, 3600.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_attack3_right", nullptr, Vector2(9750.f, 4200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack3_right")->Create(L"PinkBean_attack3_right", nullptr, Vector2(9750.f, 4800.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->Create(L"PinkBean_dead_right", nullptr, Vector2(9750.f, 5400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_right")->Create(L"PinkBean_dead_right", nullptr, Vector2(9750.f, 6000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_right")->Create(L"PinkBean_dead_right", nullptr, Vector2(9750.f, 6600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7200.f), 0.15f);
		
		//atlas2
		pAnim->Create(L"PinkBean_attack4_left", nullptr, Vector2(0.f, 0.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack4_left")->Create(L"PinkBean_attack4_left", nullptr, Vector2(0.f, 600.f), Vector2(750.f, 600.f), 3, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack5_left", nullptr, Vector2(0.f, 1200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack5_left")->Create(L"PinkBean_attack5_left", nullptr, Vector2(0.f, 1800.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack6_left", nullptr, Vector2(0.f, 2400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack6_left")->Create(L"PinkBean_attack6_left", nullptr, Vector2(0.f, 3000.f), Vector2(750.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack7_left", nullptr, Vector2(0.f, 3600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack7_left")->Create(L"PinkBean_attack7_left", nullptr, Vector2(0.f, 4200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack8_left", nullptr, Vector2(0.f, 4800.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack8_left")->Create(L"PinkBean_attack8_left", nullptr, Vector2(0.f, 5400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack9_left", nullptr, Vector2(0.f, 6000.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack9_left")->Create(L"PinkBean_attack9_left", nullptr, Vector2(0.f, 6600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack10_left", nullptr, Vector2(0.f, 7200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		
		pAnim->Create(L"PinkBean_attack4_right", nullptr, Vector2(9750.f, 0.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack4_right")->Create(L"PinkBean_attack4_right", nullptr, Vector2(9750.f, 600.f), Vector2(-750.f, 600.f), 3, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack5_right", nullptr, Vector2(9750.f, 1200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack5_right")->Create(L"PinkBean_attack5_right", nullptr, Vector2(9750.f, 1800.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack6_right", nullptr, Vector2(9750.f, 2400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack6_right")->Create(L"PinkBean_attack6_right", nullptr, Vector2(9750.f, 3000.f), Vector2(-750.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack7_right", nullptr, Vector2(9750.f, 3600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack7_right")->Create(L"PinkBean_attack7_right", nullptr, Vector2(9750.f, 4200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack8_right", nullptr, Vector2(9750.f, 4800.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack8_right")->Create(L"PinkBean_attack8_right", nullptr, Vector2(9750.f, 5400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack9_right", nullptr, Vector2(9750.f, 6000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack9_right")->Create(L"PinkBean_attack9_right", nullptr, Vector2(9750.f, 6600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);
		pAnim->Create(L"PinkBean_attack10_right", nullptr, Vector2(9750.f, 7200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10500.f, 7800.f), 0.15f);


		MonsterAttackObject* breath = new MonsterAttackObject();
		breath->SetName(L"icebreath");
		ObjectPoolManager::AddObjectPool(breath->GetName(), breath);

		for (int i = 0; i < 4; ++i)
		{
			Jenesis* pJenesis = new Jenesis();
			pJenesis->SetName(L"PinkBean_attack0");
			ObjectPoolManager::AddObjectPool(pJenesis->GetName(), pJenesis);
		}

		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"PinkBean_attack1");
		ObjectPoolManager::AddObjectPool(attack1->GetName(), attack1);

		for (int i = 0; i < 4; ++i)
		{
			PinkBeanStone* pStone = new PinkBeanStone();
			pStone->SetName(L"PinkBean_attack2");
			ObjectPoolManager::AddObjectPool(pStone->GetName(), pStone);
		}

		//4
		for (int i = 0; i < 4; ++i)
		{
			RoccatBean* pRoccat = new RoccatBean();
			pRoccat->SetName(L"PinkBean_attack3");
			ObjectPoolManager::AddObjectPool(pRoccat->GetName(), pRoccat);
		}

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.1f, -0.4f, -1.5f);
	}
	PinkBean::~PinkBean()
	{
		
	}
	void PinkBean::Initialize()
	{
		std::shared_ptr<Texture> pAtlas1 = Resources::Find<Texture>(L"PinkBean1");
		std::shared_ptr<Texture> pAtlas2 = Resources::Find<Texture>(L"PinkBean2");

		Animator* pAnim = GetComponent<Animator>();
		pAnim->SetTextureBothDir(L"PinkBean_start", pAtlas1);
		pAnim->SetTextureBothDir(L"PinkBean_stand", pAtlas1);
		pAnim->SetTextureBothDir(L"PinkBean_move", pAtlas1);
		pAnim->SetTextureBothDir(L"PinkBean_dead", pAtlas1);

		for (int i = 0; i <= 3; ++i)
			pAnim->SetTextureBothDir(L"PinkBean_attack" + to_wstring(i), pAtlas1);

		for (int i = 4; i <= 10; ++i)
			pAnim->SetTextureBothDir(L"PinkBean_attack" + to_wstring(i), pAtlas2);
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

	void PinkBean::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}

}
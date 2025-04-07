#include "WMiniBean.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WPinkBean.h"

#include "WEffect.h"
#include "WEventManager.h"
#include "WMiniBeanAttack.h"
namespace W
{
	MiniBean::MiniBean()
	{
		SetName(L"MiniBean");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"MiniBeanlMater", pMater);

		pRenderer->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();

		std::shared_ptr<Texture> pminiBean = Resources::Find<Texture>(L"miniBean");

		pAnim->Create(L"MiniBean_start_left", pminiBean, Vector2(0.f, 0.f), Vector2(320.f, 250.f), 6, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_stand_left", pminiBean, Vector2(0.f, 250.f), Vector2(320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_move_left", pminiBean, Vector2(0.f, 250.f), Vector2(320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack0_left", pminiBean, Vector2(0.f, 500.f), Vector2(320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack1_left", pminiBean, Vector2(0.f, 750.f), Vector2(320.f, 250.f), 9, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_dead_left", pminiBean, Vector2(0.f, 1000.f), Vector2(320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
						
		pAnim->Create(L"MiniBean_start_right", pminiBean, Vector2(2880, 0.f), Vector2(-320.f, 250.f), 6, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_stand_right", pminiBean, Vector2(2880, 250.f), Vector2(-320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_move_right", pminiBean, Vector2(2880, 250.f), Vector2(-320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack0_right", pminiBean, Vector2(2880, 500.f), Vector2(-320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack1_right", pminiBean, Vector2(2880, 750.f), Vector2(-320.f, 250.f), 9, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_dead_right", pminiBean, Vector2(2880, 1000.f), Vector2(-320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);

	}
	MiniBean::~MiniBean()
	{
		
	}
	void MiniBean::Initialize()
	{
		
	}
	void MiniBean::Update()
	{


	}
	void MiniBean::LateUpdate()
	{
	
		Monster::LateUpdate();
	}
	void MiniBean::Render()
	{
		Monster::Render();
	}
	
}
#include "WMiniBeanAttack.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WSceneManger.h"
#include "WTime.h"
namespace W
{
	MiniBeanAttack::MiniBeanAttack() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"MinibeanAttackMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(2.1f, 2.1f, 0.f);

	}

	MiniBeanAttack::~MiniBeanAttack()
	{

	}

	void MiniBeanAttack::Initialize()
	{

	}

	void MiniBeanAttack::Update()
	{
		
	}
	void MiniBeanAttack::LateUpdate()
	{
		MonsterAttackObject::LateUpdate();
	}
	void MiniBeanAttack::Render()
	{
		MonsterAttackObject::Render();
	}
}
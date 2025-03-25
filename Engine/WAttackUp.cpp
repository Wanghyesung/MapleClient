#include "WAttackUp.h"
#include "WResources.h"
#include "WMonster.h"

namespace W
{
	AttackUp::AttackUp(float _fAccStat):
		UpStat(_fAccStat)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"AttackUpMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"upattack", L"..\\Resources\\Texture\\Abnormal\\up.png");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(1.f * 0.19f,1.f * 0.23f,0.f);

	}
	AttackUp::~AttackUp()
	{

	}
	void AttackUp::Initialize()
	{

	}
	void AttackUp::Update()
	{
		UpStat::Update();
	}
	void AttackUp::LateUpdate()
	{
		UpStat::LateUpdate();
	}
	void AttackUp::Render()
	{
		UpStat::Render();
	}
}
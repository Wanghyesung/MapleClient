#include "WDefenseUp.h"
#include "WResources.h"
#include "WMonster.h"

namespace W
{
	DefenseUp::DefenseUp(float _fAccStat) :
		UpStat(_fAccStat)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"DefenseMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"defenseTex", L"..\\Resources\\Texture\\Abnormal\\up1.png");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(1.f * 0.19f, 1.f * 0.2f, 0.f);

	}
	DefenseUp::~DefenseUp()
	{

	}
	void DefenseUp::Initialize()
	{

	}
	void DefenseUp::Update()
	{
		UpStat::Update();
	}
	void DefenseUp::LateUpdate()
	{
		UpStat::LateUpdate();
	}
	void DefenseUp::Render()
	{
		UpStat::Render();
	}
}
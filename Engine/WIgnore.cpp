#include "WIgnore.h"
#include "WResources.h"
#include "WMonster.h"

namespace W
{
	Ignore::Ignore(float _fAccStat) :
		UpStat(_fAccStat)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"IgnoreMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"ignoreTex", L"..\\Resources\\Texture\\Abnormal\\ignore.png");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(1.f * 0.34f, 1.f * 0.34f, 0.f);

	}
	Ignore::~Ignore()
	{

	}
	void Ignore::Initialize()
	{

	}
	void Ignore::Update()
	{
		UpStat::Update();
	}
	void Ignore::LateUpdate()
	{
		UpStat::LateUpdate();
	}
	void Ignore::Render()
	{
		UpStat::Render();
	}
}
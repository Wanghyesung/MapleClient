#include "WIgnore.h"
#include "WResources.h"
#include "WMonster.h"

namespace W
{
	Ignore::Ignore() 
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
	}
	Ignore::~Ignore()
	{

	}
	void Ignore::Initialize()
	{

	}
	void Ignore::Update()
	{
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
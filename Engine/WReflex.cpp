#include "WReflex.h"
#include "WResources.h"
#include "WMonster.h"
#include "WMonsterScript.h"
namespace W
{
	Reflex::Reflex(float _fAccStat):
		UpStat(_fAccStat),
		m_fCurHp(0)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"ReflexMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"refexTex", L"..\\Resources\\Texture\\Abnormal\\reflex.png");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(1.f * 0.37f, 1.f * 0.42f, 0.f);

	}
	Reflex::~Reflex()
	{

	}
	void Reflex::Initialize()
	{
		//현재 hp 저장
	}

	void Reflex::Update()
	{
		UpStat::Update();
	}
	void Reflex::LateUpdate()
	{
		UpStat::LateUpdate();
	}
	void Reflex::Render()
	{
		UpStat::Render();
	}
}
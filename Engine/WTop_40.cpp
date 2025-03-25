#include "WTop_40.h"

namespace W
{
	Top_40::Top_40()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"40_topTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item1_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item1_0Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.f, 0.1f * 3.f, 0.f);

		SetEquipType(EquipType::Top);
		SetIconType(eIconType::Equip);
		SetEquipName(L"40_top");
	}

	Top_40::~Top_40()
	{

	}
	void Top_40::Initialize()
	{
		Equip::Initialize();
	}
	void Top_40::Update()
	{
		Equip::Update();
	}
	void Top_40::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Top_40::Render()
	{
		Equip::Render();
	}
	void Top_40::MouseOn()
	{
		Equip::MouseOn();
	}
	void Top_40::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Top_40::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Top_40::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
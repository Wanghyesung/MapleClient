#include "WTop_80.h"

namespace W
{
	Top_80::Top_80()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"80_topTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item2_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item2_0Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.8f, 0.1f * 3.0f, 0.f);

		SetEquipType(EquipType::Top);
		SetIconType(eIconType::Equip);
		SetEquipName(L"80_top");
	}

	Top_80::~Top_80()
	{

	}
	void Top_80::Initialize()
	{
		Equip::Initialize();
	}
	void Top_80::Update()
	{
		Equip::Update();
	}
	void Top_80::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Top_80::Render()
	{
		Equip::Render();
	}
	void Top_80::MouseOn()
	{
		Equip::MouseOn();
	}
	void Top_80::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Top_80::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Top_80::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
#include "WShoes_40.h"

namespace W
{
	Shoes_40::Shoes_40()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"40_shoesTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item1_3.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item1_3Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.8f, 0.1f * 3.0f, 0.f);

		SetEquipType(EquipType::Shoes);
		SetIconType(eIconType::Equip);
		SetEquipName(L"40_shoes");
	}
	Shoes_40::~Shoes_40()
	{
	}
	void Shoes_40::Initialize()
	{
		Equip::Initialize();
	}
	void Shoes_40::Update()
	{
		Equip::Update();
	}
	void Shoes_40::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Shoes_40::Render()
	{
		Equip::Render();
	}
	void Shoes_40::MouseOn()
	{
		Equip::MouseOn();
	}
	void Shoes_40::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Shoes_40::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Shoes_40::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
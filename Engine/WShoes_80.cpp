#include "WShoes_80.h"

namespace W
{
	Shoes_80::Shoes_80()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"80_shoesTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item2_3.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item2_3Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.6f, 0.1f * 3.1f, 0.f);

		SetEquipType(EquipType::Shoes);
		SetIconType(eIconType::Equip);
		SetEquipName(L"80_shoes");
	}
	Shoes_80::~Shoes_80()
	{
	}
	void Shoes_80::Initialize()
	{
		Equip::Initialize();
	}
	void Shoes_80::Update()
	{
		Equip::Update();
	}
	void Shoes_80::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Shoes_80::Render()
	{
		Equip::Render();
	}
	void Shoes_80::MouseOn()
	{
		Equip::MouseOn();
	}
	void Shoes_80::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Shoes_80::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Shoes_80::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
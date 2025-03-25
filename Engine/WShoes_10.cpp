#include "WShoes_10.h"

namespace W
{
	Shoes_10::Shoes_10()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"10_shoesTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item0_3.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item0_3Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.8f, 0.1f * 2.f, 0.f);

		SetEquipType(EquipType::Shoes);
		SetIconType(eIconType::Equip);
		SetEquipName(L"10_shoes");
	}
	Shoes_10::~Shoes_10()
	{
	}
	void Shoes_10::Initialize()
	{
		Equip::Initialize();
	}
	void Shoes_10::Update()
	{
		Equip::Update();
	}
	void Shoes_10::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Shoes_10::Render()
	{
		Equip::Render();
	}
	void Shoes_10::MouseOn()
	{
		Equip::MouseOn();
	}
	void Shoes_10::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Shoes_10::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Shoes_10::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
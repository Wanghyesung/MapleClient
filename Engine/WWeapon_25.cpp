#include "WWeapon_25.h"

namespace W
{
	Weapon_25::Weapon_25()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"25_weaponTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item1_4.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item1_4Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.9f, 0.1f * 2.9f, 0.f);

		SetEquipType(EquipType::Weapon);
		SetIconType(eIconType::Equip);
		SetEquipName(L"25_weapon");
	}
	Weapon_25::~Weapon_25()
	{
	}
	void Weapon_25::Initialize()
	{
		Equip::Initialize();
	}
	void Weapon_25::Update()
	{
		Equip::Update();
	}
	void Weapon_25::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Weapon_25::Render()
	{
		Equip::Render();
	}
	void Weapon_25::MouseOn()
	{
		Equip::MouseOn();
	}
	void Weapon_25::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Weapon_25::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Weapon_25::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
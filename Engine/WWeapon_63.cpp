#include "WWeapon_63.h"

namespace W
{
	Weapon_63::Weapon_63()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"63_weaponTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item2_4.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item2_4Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.9f, 0.1f * 3.0f, 0.f);

		SetEquipType(EquipType::Weapon);
		SetIconType(eIconType::Equip);
		SetEquipName(L"63_weapon");
	}
	Weapon_63::~Weapon_63()
	{
	}
	void Weapon_63::Initialize()
	{
		Equip::Initialize();
	}
	void Weapon_63::Update()
	{
		Equip::Update();
	}
	void Weapon_63::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Weapon_63::Render()
	{
		Equip::Render();
	}
	void Weapon_63::MouseOn()
	{
		Equip::MouseOn();
	}
	void Weapon_63::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Weapon_63::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Weapon_63::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
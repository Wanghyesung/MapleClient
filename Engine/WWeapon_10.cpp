#include "WWeapon_10.h"

namespace W
{
	Weapon_10::Weapon_10()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"10_weaponTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item0_4.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item0_4Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.6f, 0.1f * 2.8f, 0.f);

		SetEquipType(EquipType::Weapon);
		SetIconType(eIconType::Equip);
		SetEquipName(L"10_weapon");
	}
	Weapon_10::~Weapon_10()
	{
	}
	void Weapon_10::Initialize()
	{
		Equip::Initialize();
	}
	void Weapon_10::Update()
	{
		Equip::Update();
	}
	void Weapon_10::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Weapon_10::Render()
	{
		Equip::Render();
	}
	void Weapon_10::MouseOn()
	{
		Equip::MouseOn();
	}
	void Weapon_10::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Weapon_10::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Weapon_10::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
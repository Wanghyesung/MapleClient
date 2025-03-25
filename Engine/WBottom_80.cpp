#include "WBottom_80.h"

namespace W
{
	Bottom_80::Bottom_80()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"80_bottomTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item2_1.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item2_1Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.6f, 0.1f * 2.6f, 0.f);

		SetEquipType(EquipType::Bottom);
		SetIconType(eIconType::Equip);

		SetEquipName(L"80_bottom");
	}
	Bottom_80::~Bottom_80()
	{

	}
	void Bottom_80::Initialize()
	{
		Equip::Initialize();
	}
	void Bottom_80::Update()
	{
		Equip::Update();
	}
	void Bottom_80::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Bottom_80::Render()
	{
		Equip::Render();
	}
	void Bottom_80::MouseOn()
	{
		Equip::MouseOn();
	}
	void Bottom_80::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Bottom_80::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Bottom_80::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
#include "WHat_80.h"

namespace W
{
	Hat_80::Hat_80()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"80_hatTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item2_2.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item2_2Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.2f, 0.1f * 3.0f, 0.f);

		SetEquipType(EquipType::Hat);
		SetIconType(eIconType::Equip);
		SetEquipName(L"80_hat");
	}
	Hat_80::~Hat_80()
	{

	}
	void Hat_80::Initialize()
	{
		Equip::Initialize();
	}
	void Hat_80::Update()
	{
		Equip::Update();
	}
	void Hat_80::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Hat_80::Render()
	{
		Equip::Render();
	}
	void Hat_80::MouseOn()
	{
		Equip::MouseOn();
	}
	void Hat_80::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Hat_80::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Hat_80::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
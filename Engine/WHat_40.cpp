#include "WHat_40.h"

namespace W
{
	Hat_40::Hat_40()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"40_hatTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item1_2.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item1_2Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.2f, 0.1f * 3.0f, 0.f);

		SetEquipType(EquipType::Hat);
		SetIconType(eIconType::Equip);
		SetEquipName(L"40_hat");
	}
	Hat_40::~Hat_40()
	{

	}
	void Hat_40::Initialize()
	{
		Equip::Initialize();
	}
	void Hat_40::Update()
	{
		Equip::Update();
	}
	void Hat_40::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Hat_40::Render()
	{
		Equip::Render();
	}
	void Hat_40::MouseOn()
	{
		Equip::MouseOn();
	}
	void Hat_40::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Hat_40::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Hat_40::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
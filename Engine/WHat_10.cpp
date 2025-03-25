#include "WHat_10.h"

namespace W
{
	Hat_10::Hat_10()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"10_hatTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item0_2.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item0_2Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.0f, 0.1f * 2.2f, 0.f);

		SetEquipType(EquipType::Hat);
		SetIconType(eIconType::Equip);
		SetEquipName(L"10_hat");
	}
	Hat_10::~Hat_10()
	{

	}
	void Hat_10::Initialize()
	{
		Equip::Initialize();
	}
	void Hat_10::Update()
	{
		Equip::Update();
	}
	void Hat_10::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Hat_10::Render()
	{
		Equip::Render();
	}
	void Hat_10::MouseOn()
	{
		Equip::MouseOn();
	}
	void Hat_10::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Hat_10::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Hat_10::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
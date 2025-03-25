#include "WTop_10.h"

namespace W
{
	Top_10::Top_10()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"10_topTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item0_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item0_0Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.6f, 0.1f * 2.8f, 0.f);

		SetEquipType(EquipType::Top);
		SetIconType(eIconType::Equip);
		SetEquipName(L"10_top");
	}

	Top_10::~Top_10()
	{

	}
	void Top_10::Initialize()
	{
		Equip::Initialize();
	}
	void Top_10::Update()
	{
		Equip::Update();
	}
	void Top_10::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Top_10::Render()
	{
		Equip::Render();
	}
	void Top_10::MouseOn()
	{
		Equip::MouseOn();
	}
	void Top_10::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Top_10::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Top_10::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
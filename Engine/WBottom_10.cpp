#include "WBottom_10.h"

namespace W
{
	Bottom_10::Bottom_10()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"10_bottomTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item0_1.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item0_1Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.6f, 0.1f * 2.8f, 0.f);

		SetEquipType(EquipType::Bottom);
		SetIconType(eIconType::Equip);

		SetEquipName(L"10_bottom");
	}
	Bottom_10::~Bottom_10()
	{

	}
	void Bottom_10::Initialize()
	{
		Equip::Initialize();
	}
	void Bottom_10::Update()
	{
		Equip::Update();
	}
	void Bottom_10::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Bottom_10::Render()
	{
		Equip::Render();
	}
	void Bottom_10::MouseOn()
	{
		Equip::MouseOn();
	}
	void Bottom_10::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Bottom_10::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Bottom_10::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
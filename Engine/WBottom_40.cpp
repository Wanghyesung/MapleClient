#include "WBottom_40.h"

namespace W
{
	Bottom_40::Bottom_40()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"40_bottomTex", L"..\\Resources\\Texture\\UI\\ItemUI\\item1_1.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"item1_1Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.6f, 0.1f * 3.0f, 0.f);

		SetEquipType(EquipType::Bottom);
		SetIconType(eIconType::Equip);

		SetEquipName(L"40_bottom");
	}
	Bottom_40::~Bottom_40()
	{

	}
	void Bottom_40::Initialize()
	{
		Equip::Initialize();
	}
	void Bottom_40::Update()
	{
		Equip::Update();
	}
	void Bottom_40::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void Bottom_40::Render()
	{
		Equip::Render();
	}
	void Bottom_40::MouseOn()
	{
		Equip::MouseOn();
	}
	void Bottom_40::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void Bottom_40::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void Bottom_40::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
#include "WHorntailItem.h"

namespace W
{
	HorntailItem::HorntailItem()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"horntailItemTex", L"..\\Resources\\Texture\\UI\\ItemUI\\horntailItem.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"horntailItemMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f);

		SetEquipType(EquipType::Pandant);
		SetIconType(eIconType::Equip);
	}
	HorntailItem::~HorntailItem()
	{
		Equip::Initialize();
	}
	void HorntailItem::Initialize()
	{

	}
	void HorntailItem::Update()
	{
		Equip::Update();
	}
	void HorntailItem::LateUpdate()
	{
		Equip::LateUpdate();
	}
	void HorntailItem::Render()
	{
		Equip::Render();
	}
	void HorntailItem::MouseOn()
	{
		Equip::MouseOn();
	}
	void HorntailItem::MouseLbtnDown()
	{
		Equip::MouseLbtnDown();
	}
	void HorntailItem::MouseLbtnUp()
	{
		Equip::MouseLbtnUp();
	}
	void HorntailItem::MouseLbtnClicked()
	{
		Equip::MouseLbtnClicked();
	}
}
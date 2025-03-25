#include "WShopUI.h"

namespace W
{
	ShopUI::ShopUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"ShopTex1", L"..\\Resources\\Texture\\UI\\Interface\\shop.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"ShopMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	ShopUI::~ShopUI()
	{
	}
	void ShopUI::Initialize()
	{
	}
	void ShopUI::Update()
	{
		UI::Update();
	}
	void ShopUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ShopUI::Render()
	{
		UI::Render();
	}
	void ShopUI::MouseOn()
	{
	}
	void ShopUI::MouseLbtnDown()
	{
	}
	void ShopUI::MouseLbtnUp()
	{
	}
	void ShopUI::MouseLbtnClicked()
	{
	}
}
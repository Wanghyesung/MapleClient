#include "WMenuUI.h"

namespace W
{
	MenuUI::MenuUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"MenuTex1", L"..\\Resources\\Texture\\UI\\Interface\\menu.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"MenuMater1", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	MenuUI::~MenuUI()
	{
	}
	void MenuUI::Initialize()
	{
	}
	void MenuUI::Update()
	{
		UI::Update();
	}
	void MenuUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void MenuUI::Render()
	{
		UI::Render();
	}
	void MenuUI::MouseOn()
	{
	}
	void MenuUI::MouseLbtnDown()
	{
	}
	void MenuUI::MouseLbtnUp()
	{
	}
	void MenuUI::MouseLbtnClicked()
	{
	}
}
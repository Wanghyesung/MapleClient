#include "WSystemUI.h"
namespace W
{
	SystemUI::SystemUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"SystemTex1", L"..\\Resources\\Texture\\UI\\Interface\\system.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"SystemMater1", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	SystemUI::~SystemUI()
	{
	}
	void SystemUI::Initialize()
	{
	}
	void SystemUI::Update()
	{
		UI::Update();
	}
	void SystemUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SystemUI::Render()
	{
		UI::Render();
	}
	void SystemUI::MouseOn()
	{
	}
	void SystemUI::MouseLbtnDown()
	{
	}
	void SystemUI::MouseLbtnUp()
	{
	}
	void SystemUI::MouseLbtnClicked()
	{
	}
}
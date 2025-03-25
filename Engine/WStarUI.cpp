#include "WStarUI.h"

namespace W
{
	StarUI::StarUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"StarTex1", L"..\\Resources\\Texture\\UI\\Interface\\star.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"StarMater1", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	StarUI::~StarUI()
	{
	}
	void StarUI::Initialize()
	{
	}
	void StarUI::Update()
	{
		UI::Update();
	}
	void StarUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void StarUI::Render()
	{
		UI::Render();
	}
	void StarUI::MouseOn()
	{
	}
	void StarUI::MouseLbtnDown()
	{
	}
	void StarUI::MouseLbtnUp()
	{
	}
	void StarUI::MouseLbtnClicked()
	{
	}
}
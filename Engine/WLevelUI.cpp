#include "WLevelUI.h"

namespace W
{
	LevelUI::LevelUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"LevelTex0", L"..\\Resources\\Texture\\UI\\Interface\\level_back_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"LevelMater0", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	LevelUI::~LevelUI()
	{
	}
	void LevelUI::Initialize()
	{
	}
	void LevelUI::Update()
	{
		UI::Update();
	}
	void LevelUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void LevelUI::Render()
	{
		UI::Render();
	}
	void LevelUI::MouseOn()
	{
	}
	void LevelUI::MouseLbtnDown()
	{
		int a = 10;
	}
	void LevelUI::MouseLbtnUp()
	{
	}
	void LevelUI::MouseLbtnClicked()
	{
	}
}
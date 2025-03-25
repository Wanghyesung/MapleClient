#include "WCharUI.h"

namespace W
{
	CharUI::CharUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"charBtTex0", L"..\\Resources\\Texture\\UI\\Interface\\charBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"charBtMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	CharUI::~CharUI()
	{
	}
	void CharUI::Initialize()
	{
	}
	void CharUI::Update()
	{
		UI::Update();
	}
	void CharUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void CharUI::Render()
	{
		UI::Render();
	}
	void CharUI::MouseOn()
	{
	}
	void CharUI::MouseLbtnDown()
	{
	}
	void CharUI::MouseLbtnUp()
	{
	}
	void CharUI::MouseLbtnClicked()
	{
	}
}
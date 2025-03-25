#include "WSKillUI.h"
#include "WSKillStorage.h"
#include "WSceneManger.h"
namespace W
{
	SKillUI::SKillUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"SkillTex0", L"..\\Resources\\Texture\\UI\\Interface\\SkillBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"SkillMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	SKillUI::~SKillUI()
	{
	}
	void SKillUI::Initialize()
	{

	}
	void SKillUI::Update()
	{
		UI::Update();
	}
	void SKillUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SKillUI::Render()
	{
		UI::Render();
	}
	void SKillUI::MouseOn()
	{

	}
	void SKillUI::MouseLbtnDown()
	{

		SKillStorage* pSKillUI = SceneManger::GetUI<SKillStorage>();
		if (pSKillUI != nullptr)
		{
			bool bRender = pSKillUI->IsRender();
			if (!bRender)
				pSKillUI->RenderOn(true);
			else
				pSKillUI->RenderOn(false);
		}
	}
	void SKillUI::MouseLbtnUp()
	{

	}
	void SKillUI::MouseLbtnClicked()
	{

	}

	
}
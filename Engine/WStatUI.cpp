#include "WStatUI.h"
#include "WStat.h"
#include "WSceneManger.h"
namespace W
{
	StatUI::StatUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"statBtTex0", L"..\\Resources\\Texture\\UI\\Interface\\statBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"statMater0", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	StatUI::~StatUI()
	{
	}
	void StatUI::Initialize()
	{

	}
	void StatUI::Update()
	{
		UI::Update();
	}
	void StatUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void StatUI::Render()
	{
		UI::Render();
	}
	void StatUI::MouseOn()
	{

	}
	void StatUI::MouseLbtnDown()
	{
		Stat* pStat = SceneManger::GetUI<Stat>();
		
		bool bRenderOn = pStat->IsRender();
		if (bRenderOn)
			pStat->RenderOn(false);
		else
			pStat->RenderOn(true);

	}
	void StatUI::MouseLbtnUp()
	{

	}
	void StatUI::MouseLbtnClicked()
	{

	}
}
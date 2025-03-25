#include "WCoverGaugeUI.h"

namespace W
{
	CoverGaugeUI::CoverGaugeUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"gauge_back1Tex", L"..\\Resources\\Texture\\UI\\Interface\\gauge_back_1.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"gauge_back1Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	CoverGaugeUI::~CoverGaugeUI()
	{
	}
	void CoverGaugeUI::Initialize()
	{
	}
	void CoverGaugeUI::Update()
	{
		UI::Update();
	}
	void CoverGaugeUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void CoverGaugeUI::Render()
	{
		UI::Render();
	}
	void CoverGaugeUI::MouseOn()
	{
	}
	void CoverGaugeUI::MouseLbtnDown()
	{
	}
	void CoverGaugeUI::MouseLbtnUp()
	{
	}
	void CoverGaugeUI::MouseLbtnClicked()
	{
	}
}
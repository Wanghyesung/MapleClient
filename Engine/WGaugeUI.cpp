#include "WGaugeUI.h"
#include "WHP.h"
#include "WMP.h"
#include "WEXP.h"
#include "WTransform.h"
#include "WCoverGaugeUI.h"

namespace W
{
	GaugeUI::GaugeUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"gaugeTex0", L"..\\Resources\\Texture\\UI\\Interface\\gauge_back_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"gaugeMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	GaugeUI::~GaugeUI()
	{
	}
	void GaugeUI::Initialize()
	{
		HP* pHP = new HP();
		pHP->GetComponent<Transform>()->SetPosition(-0.69f,0.072f,-0.2f);
		pHP->GetComponent<Transform>()->SetScale(7.1f * 0.195f, 0.7f * 0.195f, -0.1f); //71 : 7
		pHP->Initialize();
		AddChildUI(pHP);

		MP* pMP = new MP();
		pMP->GetComponent<Transform>()->SetPosition(0.96f, 0.072f, -0.2f);
		pMP->GetComponent<Transform>()->SetScale(7.1f * 0.195f, 0.7f * 0.195f, -0.1f); //71 : 7
		pMP->Initialize();
		AddChildUI(pMP);

		EXP* pEXP = new EXP();
		pEXP->GetComponent<Transform>()->SetPosition(0.135f, -0.088f, -0.2f);
		pEXP->GetComponent<Transform>()->SetScale(21.f * 0.145f, 1.f * 0.145f, -0.1f); //71 : 7
		pEXP->Initialize();
		AddChildUI(pEXP);

		CoverGaugeUI* pCover = new CoverGaugeUI();
		pCover->GetComponent<Transform>()->SetPosition(0.125f,0.f, -0.4f);
		pCover->GetComponent<Transform>()->SetScale(11.f* 0.273f,1.f * 0.273f,0.f); //11 : 1
		AddChildUI(pCover);

	}
	void GaugeUI::Update()
	{
		UI::Update();
	}
	void GaugeUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void GaugeUI::Render()
	{
		UI::Render();
	}
	void GaugeUI::MouseOn()
	{
	}
	void GaugeUI::MouseLbtnDown()
	{
	}
	void GaugeUI::MouseLbtnUp()
	{
	}
	void GaugeUI::MouseLbtnClicked()
	{
	}
}
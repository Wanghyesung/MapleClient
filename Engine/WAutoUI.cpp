#include "WAutoUI.h"

namespace W
{
	AutoUI::AutoUI()
	{
		//default
		std::shared_ptr<Texture> pAutoTex =
			Resources::Load<Texture>(L"AutoTex1", L"..\\Resources\\Texture\\UI\\StatUI\\auto_1.png");
		//down
		pAutoTex = Resources::Load<Texture>(L"AutoTex0", L"..\\Resources\\Texture\\UI\\StatUI\\auto_0.png");
		

		std::shared_ptr<Material> pAutoMater = std::make_shared<Material>();
		pAutoMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pAutoMater->SetTexture(pAutoTex);
		Resources::Insert(L"AutoMater", pAutoMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pAutoMater);
	}
	AutoUI::~AutoUI()
	{

	}
	void AutoUI::Initialize()
	{

	}
	void AutoUI::Update()
	{
		UI::Update();
	}
	void AutoUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void AutoUI::Render()
	{
		UI::Render();
	}
	void AutoUI::MouseOn()
	{

	}
	void AutoUI::MouseLbtnDown()
	{
		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"AutoMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"AutoTex1"));
	}
	void AutoUI::MouseLbtnUp()
	{
		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"AutoMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"AutoTex0"));
	}
	void AutoUI::MouseLbtnClicked()
	{

	}
}
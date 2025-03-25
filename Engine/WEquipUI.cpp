#include "WEquipUI.h"
#include "WEquipState.h"
#include "WSceneManger.h"
namespace W
{
	EquipUI::EquipUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"EquipBtTex0", L"..\\Resources\\Texture\\UI\\Interface\\EquipBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"EquipBtMater0", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	EquipUI::~EquipUI()
	{

	}
	void EquipUI::Initialize()
	{
		//Transform* pTransform = GetComponent<Transform>();
		//pTransform->SetPosition(0.f, 0.f, -0.25f);
		//pTransform->SetScale(0.518f * 3.8f, 1.f * 3.8f, 0.f); //0.518 : 1
	}
	void EquipUI::Update()
	{
		UI::Update();
	}
	void EquipUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void EquipUI::Render()
	{
		UI::Render();
	}
	void EquipUI::MouseOn()
	{

	}
	void EquipUI::MouseLbtnDown()
	{
		EquipState* pInven = SceneManger::GetUI<EquipState>();
		if (pInven != nullptr)
		{
			bool bRender = pInven->IsRender();
			if (!bRender)
				pInven->RenderOn(true);
			else
				pInven->RenderOn(false);
		}
	}
	void EquipUI::MouseLbtnUp()
	{
	}
	void EquipUI::MouseLbtnClicked()
	{
	}
}
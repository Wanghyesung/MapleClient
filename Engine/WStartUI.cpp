#include "WStartUI.h"
#include "WSceneManger.h"

namespace W
{
	UINT StartUI::COUNT = 0;

	StartUI::StartUI():
		m_iBtnNumber(COUNT)
	{
		++COUNT;
		std::wstring strNum = std::to_wstring(m_iBtnNumber);

		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"start_1Tex", L"..\\Resources\\Texture\\UI\\StartUI\\start_1.png");

		pTex =
			Resources::Load<Texture>(L"start_0Tex", L"..\\Resources\\Texture\\UI\\StartUI\\start_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"startUIMater" + strNum, pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	StartUI::~StartUI()
	{

	}
	void StartUI::Initialize()
	{

	}
	void StartUI::Update()
	{
		UI::Update();
	}
	void StartUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void StartUI::Render()
	{
		UI::Render();
	}

	void StartUI::MouseOn()
	{

	}

	void StartUI::MouseLbtnDown()
	{
		std::wstring strNum = std::to_wstring(m_iBtnNumber);
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"startUIMater"+ strNum);
		pMater->SetTexture(Resources::Find<Texture>(L"start_1Tex"));
	}

	void StartUI::MouseLbtnUp()
	{
		std::wstring strNum = std::to_wstring(m_iBtnNumber);
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"startUIMater"+ strNum);
		pMater->SetTexture(Resources::Find<Texture>(L"start_1Tex"));
	}

	void StartUI::MouseLbtnClicked()
	{
		SceneManger::LoadScene(m_strNextScene);
	}
}
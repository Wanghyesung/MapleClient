#include "WServerUI.h"
#include "WSceneManger.h"
#include "WChannel.h"
namespace W
{
	ServerUI::ServerUI():
		m_pChannel(nullptr)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"sky_1Tex", L"..\\Resources\\Texture\\UI\\StartUI\\sky_1.png");

		pTex =
			Resources::Load<Texture>(L"sky_0Tex", L"..\\Resources\\Texture\\UI\\StartUI\\sky_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"skyMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	ServerUI::~ServerUI()
	{

	}
	void ServerUI::Initialize()
	{
		GetComponent<Transform>()->SetPosition(0.f, 2.38f, -0.01f);
		GetComponent<Transform>()->SetScale(0.185f * 5.5f, 0.063f * 5.5f, 1.f);

		m_pChannel = new Channel();
		AddChildUI(m_pChannel);
		m_pChannel->Initialize();

	}
	void ServerUI::Update()
	{
		UI::Update();

	}
	void ServerUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ServerUI::Render()
	{
		UI::Render();
	}
	void ServerUI::MouseOn()
	{

	}
	void ServerUI::MouseLbtnDown()
	{
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"skyMater");
		pMater->SetTexture(Resources::Find<Texture>(L"sky_1Tex"));
	}
	void ServerUI::MouseLbtnUp()
	{
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"skyMater");
		pMater->SetTexture(Resources::Find<Texture>(L"sky_0Tex"));
	}
	void ServerUI::MouseLbtnClicked()
	{
		bool bRender = m_pChannel->IsRender();

		if (!bRender)
			m_pChannel->SetRender(true);
		else
			m_pChannel->SetRender(false);

		//SceneManger::LoadScene(m_strNextScene);
	}
}
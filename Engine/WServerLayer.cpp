#include "WServerLayer.h"
#include "WServerUI.h"
namespace W
{
	ServerLayer::ServerLayer()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"layerTex", L"..\\Resources\\Texture\\UI\\StartUI\\layer.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"layerMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	ServerLayer::~ServerLayer()
	{

	}
	void ServerLayer::Initialize()
	{
		GetComponent<Transform>()->SetPosition(5.f,0.f,0.f);
		GetComponent<Transform>()->SetScale(0.257f * 5.5f , 1.f * 5.5f ,1.f);

		ServerUI* pServerUI = new ServerUI();
		pServerUI->Initialize();
		//pServerUI->SetNextScene(L"CharScene");
		AddChildUI(pServerUI);
	}
	void ServerLayer::Update()
	{
		UI::Update();
	}
	void ServerLayer::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ServerLayer::Render()
	{
		UI::Render();
	}
	void ServerLayer::MouseOn()
	{

	}
	void ServerLayer::MouseLbtnDown()
	{

	}
	void ServerLayer::MouseLbtnUp()
	{

	}
	void ServerLayer::MouseLbtnClicked()
	{

	}
}
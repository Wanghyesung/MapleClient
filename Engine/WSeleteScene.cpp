#include "WSeleteScene.h"

#include "WResources.h"
#include "WRenderer.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WServerLayer.h"

namespace W
{
	SeleteScene::SeleteScene()
	{
		std::shared_ptr<Texture> pBackTex =
			Resources::Load<Texture>(L"start_logo_2Tex", L"..\\Resources\\Texture\\background\\start_logo_2.png");

		std::shared_ptr<Material> pBackMater = std::make_shared<Material>();
		pBackMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pBackMater->SetTexture(pBackTex);
		Resources::Insert(L"start_logo_2Mater", pBackMater);

	}
	SeleteScene::~SeleteScene()
	{

	}
	void SeleteScene::Initialize()
	{

		ServerLayer* pServerLayer = new ServerLayer();
		pServerLayer->Initialize();
		AddGameObject(eLayerType::UI, pServerLayer);

		CreateBackground();
		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* pCameraScript = pCamera->AddComponent<CameraScript>();
			//renderer::MainCamera = pCameraComp;
		}

		//ui camera
		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			//renderer::UICamera = pCameraComp;
		}
	}
	void SeleteScene::Update()
	{
		Scene::Update();
	}
	void SeleteScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void SeleteScene::Render()
	{
		Scene::Render();
	}
	void SeleteScene::Destroy()
	{
	}
	void SeleteScene::OnEnter()
	{
	}
	void SeleteScene::OnExit()
	{

	}
	void SeleteScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"start_logo_2Mater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.2f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(4 * 3.5f, 3.f * 2.7f, 1.f);
	}
}
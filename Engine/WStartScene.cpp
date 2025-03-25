#include "WStartScene.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WStartUI.h"
namespace W
{
	StartScene::StartScene()
	{
		std::shared_ptr<Texture> pBackTex =
			Resources::Load<Texture>(L"start_logoTex", L"..\\Resources\\Texture\\background\\start_logo.png");

		std::shared_ptr<Material> pBackMater = std::make_shared<Material>();
		pBackMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pBackMater->SetTexture(pBackTex);
		Resources::Insert(L"start_logoMater", pBackMater);

	}
	StartScene::~StartScene()
	{

	}
	void StartScene::Initialize()
	{
		StartUI* pStartUI = new StartUI();
		AddGameObject(eLayerType::UI, pStartUI);

		pStartUI->SetNextScene(L"SeleteScene");
		pStartUI->GetComponent<Transform>()->SetPosition(0.f,-1.5f,0.f);
		pStartUI->GetComponent<Transform>()->SetScale(2.692f * 0.7f, 1.f*0.7f , 0.f);

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
	void StartScene::Update()
	{
		Scene::Update();
	}
	void StartScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void StartScene::Render()
	{
		Scene::Render();
	}
	void StartScene::Destroy()
	{
	}
	void StartScene::OnEnter()
	{
	}
	void StartScene::OnExit()
	{

	}
	void StartScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"start_logoMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.2f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(4 * 3.5f, 3.f * 2.7f, 1.f);
	}
}
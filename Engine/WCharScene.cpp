#include "WCharScene.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WInput.h"
#include "WSceneManger.h"
namespace W
{
	CharScene::CharScene()
	{
		std::shared_ptr<Texture> pBackTex =
			Resources::Load<Texture>(L"start_charTex", L"..\\Resources\\Texture\\background\\start_char.png");

		std::shared_ptr<Material> pBackMater = std::make_shared<Material>();
		pBackMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pBackMater->SetTexture(pBackTex);
		Resources::Insert(L"start_charMater", pBackMater);

	}
	CharScene::~CharScene()
	{

	}
	void CharScene::Initialize()
	{
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
	void CharScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Valley");
		}
	}
	void CharScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void CharScene::Render()
	{
		Scene::Render();
	}
	void CharScene::Destroy()
	{
	}
	void CharScene::OnEnter()
	{
	}
	void CharScene::OnExit()
	{

	}
	void CharScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"start_charMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.2f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(4 * 3.5f, 3.f * 3.f, 1.f);
	}
}
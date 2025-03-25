#include "WCaveStartScene.h"
#include "WShader.h"
#include "WGameObject.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WResources.h"
#include "WNPC.h"
#include "WUI.h"
#include "WInterfaceUI.h"
namespace W
{
	CaveStartScene::CaveStartScene()
	{
		std::shared_ptr<Texture> pBackTex =
			Resources::Load<Texture>(L"Start1Tex", L"..\\Resources\\Texture\\background\\start1_tem.png");

		std::shared_ptr<Material> pBackMater = std::make_shared<Material>();
		pBackMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pBackMater->SetTexture(pBackTex);
		Resources::Insert(L"Start1Mater", pBackMater);

		SetMapSize(-0.5f, 0.f, 0.5f, 0.f);

	}
	CaveStartScene::~CaveStartScene()
	{
	}
	void CaveStartScene::Initialize()
	{
		CreateBackground();
		//16 : 1
		//object camera
		{
			GameObject* pCamera = new GameObject();
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			pCamera->AddComponent<CameraScript>();
		}

		//ui camera
		{
			GameObject* pCamera = new GameObject();
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::Background, false);
			//pCamera->AddComponent<CameraScript>();
		}
	}
	void CaveStartScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Start2");
		}
	}
	void CaveStartScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void CaveStartScene::Render()
	{
		Scene::Render();
	}
	void CaveStartScene::OnEnter()
	{

	}
	void CaveStartScene::OnExit()
	{

	}
	void CaveStartScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"Start1Mater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//1.867 : 1
		pBackGround->GetComponent<Transform>()->SetScale(1.867f * 8.f, 1.f * 8.f, 1.f);
	}
}
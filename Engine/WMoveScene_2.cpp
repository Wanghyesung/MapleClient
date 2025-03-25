#include "WMoveScene_2.h"
#include "WResources.h"
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

namespace W
{
	MoveScene_2::MoveScene_2()
	{
		std::shared_ptr<Texture> pBackTex =
			Resources::Load<Texture>(L"Move2Tex", L"..\\Resources\\Texture\\background\\move2.png");

		std::shared_ptr<Material> pBackMater = std::make_shared<Material>();
		pBackMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pBackMater->SetTexture(pBackTex);
		Resources::Insert(L"Move2Mater", pBackMater);

		SetMapSize(-3.f, 1.f, 3.f, -1.f);
	}

	MoveScene_2::~MoveScene_2()
	{

	}
	void MoveScene_2::Initialize()
	{
		CreateBackground();

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			pCamera->AddComponent<CameraScript>();
		}

		//ui camera
		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			//pCamera->AddComponent<CameraScript>();
		}
	}
	void MoveScene_2::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Start1");
		}
	}
	void MoveScene_2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MoveScene_2::Render()
	{
		Scene::Render();
	}
	void MoveScene_2::OnEnter()
	{

	}
	void MoveScene_2::OnExit()
	{

	}
	void MoveScene_2::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"Move2Mater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.f * 10.f, 1.f * 10.f, 1.f);
	}
}
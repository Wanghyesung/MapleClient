#include "WTempleScene.h"
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
#include "WNPC.h"

namespace W
{
	TempleScene::TempleScene()
	{
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex3", L"..\\Resources\\Texture\\NPC\\npc3.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPCMater3", pNPCMater);

		SetMapSize(-3.f, 0.f, 3.f, 0.f);
	}
	TempleScene::~TempleScene()
	{

	}
	void TempleScene::Initialize()
	{
		CreateBackground();

		NPC* pNPC = new NPC();
		MeshRenderer* pMeshRenderer = pNPC->AddComponent<MeshRenderer>();
		AddGameObject(eLayerType::NPC, pNPC);
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRenderer->SetMaterial(Resources::Find<Material>(L"NPCMater3"));
		pNPC->GetComponent<Transform>()->SetPosition(-8.f, -1.85f, -0.2f);
		pNPC->GetComponent<Transform>()->SetScale(0.7f * 1.1f, 1.f * 1.1f, 0.f);
		//0.7 : 1



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
	void TempleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Valley2");
		}

	}
	void TempleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleScene::Render()
	{
		Scene::Render();
	}

	void TempleScene::OnEnter()
	{

	}
	void TempleScene::OnExit()
	{

	}
	void TempleScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2.5 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.5f * 8.f, 1.f * 8.f, 1.f);
	}
}
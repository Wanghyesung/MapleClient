#include "WTempleStartScene.h"
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

namespace W
{
	TempleStartScene::TempleStartScene()
	{
		std::shared_ptr<Texture> pBackTex =
			Resources::Load<Texture>(L"Start2Tex", L"..\\Resources\\Texture\\background\\start2.png");

		std::shared_ptr<Material> pBackMater = std::make_shared<Material>();
		pBackMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pBackMater->SetTexture(pBackTex);
		Resources::Insert(L"Start2Mater", pBackMater);


		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex5", L"..\\Resources\\Texture\\NPC\\npc5.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPCMater5", pNPCMater);
	}
	TempleStartScene::~TempleStartScene()
	{

	}
	void TempleStartScene::Initialize()
	{
		CreateBackground();

		NPC* pNPC = new NPC();
		AddGameObject(eLayerType::NPC, pNPC);
		MeshRenderer* pMeshRender = pNPC->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"NPCMater5"));
		pNPC->GetComponent<Transform>()->SetPosition(-4.5f, -2.3f, -1.f);
		pNPC->GetComponent<Transform>()->SetScale(0.547f * 1.4f, 1.f * 1.4f, 0.f);
		pNPC->GetComponent<Transform>()->SetRotation(0.f,0.f,0.f);
		//0.547 : 1


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
	void TempleStartScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Leafre");
		}
	}
	void TempleStartScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleStartScene::Render()
	{
		Scene::Render();
	}
	void TempleStartScene::OnEnter()
	{

	}
	void TempleStartScene::OnExit()
	{

	}
	void TempleStartScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"Start2Mater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//16 : 9
		pBackGround->GetComponent<Transform>()->SetScale(16.f * 1.f, 9.f * 1.f, 1.f);
	}
}
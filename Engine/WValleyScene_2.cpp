#include "WValleyScene_2.h"
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
#include "WLadder.h"
#include "WNPC.h"

namespace W
{
	ValleyScene_2::ValleyScene_2()
	{
		std::shared_ptr<Texture> pLadder9 =
			Resources::Load<Texture>(L"Ladder9BaseTex", L"..\\Resources\\Texture\\Object\\ladder\\9_base.png");

		std::shared_ptr<Material> pLadderMater9 = std::make_shared<Material>();
		pLadderMater9->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater9->SetTexture(pLadder9);
		Resources::Insert(L"LadderBaseMater9", pLadderMater9);

		std::shared_ptr<Texture> pNPCTex4 =
			Resources::Load<Texture>(L"NPCTex4", L"..\\Resources\\Texture\\NPC\\npc4.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex4);
		Resources::Insert(L"NPCMater4", pNPCMater);

		SetMapSize(-1.f, 0.f, 1.f, 0.f);
	}
	ValleyScene_2::~ValleyScene_2()
	{

	}
	void ValleyScene_2::Initialize()
	{
		CreateBackground();
		setobject();

		NPC* pNPC = new NPC();
		AddGameObject(eLayerType::NPC, pNPC);
		MeshRenderer* pNPCRenderer = pNPC->AddComponent<MeshRenderer>();
		pNPCRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pNPCRenderer->SetMaterial(Resources::Find<Material>(L"NPCMater4"));
		pNPC->GetComponent<Transform>()->SetPosition(6.f, 2.48f, -1.f);
		pNPC->GetComponent<Transform>()->SetScale(1.147f * 1.f, 1.f * 1.f, 0.f);
		//1.147 : 1

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
	void ValleyScene_2::Update()
	{
		Scene::Update();
		
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Temple2");
		}
	}
	void ValleyScene_2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene_2::Render()
	{
		Scene::Render();
	}
	void ValleyScene_2::OnEnter()
	{

	}
	void ValleyScene_2::OnExit()
	{

	}
	void ValleyScene_2::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater2"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2 * 8.f, 1.f * 8.f, 1.f);
	}
	void ValleyScene_2::setobject()
	{
		Ladder* pLadder0 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder0);
		MeshRenderer* pLadderMeshRender0 = pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRender0->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender0->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9"));
		pLadder0->GetComponent<Transform>()->SetPosition(-2.f,-0.6f,-1.f);
		pLadder0->GetComponent<Transform>()->SetScale(1.f * 0.5f, 4.f * 0.7f, 0.f);

	}
}
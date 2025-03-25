#include "WLeafreScene.h"
#include "WShader.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WResources.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WLadder.h"
#include "WNPC.h"

namespace W
{
	LeafreScene::LeafreScene()
	{
		//ladder
		std::shared_ptr<Texture> pLadder7 =
			Resources::Load<Texture>(L"LadderTex7", L"..\\Resources\\Texture\\Object\\ladder\\7_base.png");

		std::shared_ptr<Material> pLadderMater7 = std::make_shared<Material>();
		pLadderMater7->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater7->SetTexture(pLadder7);
		Resources::Insert(L"LadderMater7", pLadderMater7);

		std::shared_ptr<Texture> pLadder7_ =
			Resources::Load<Texture>(L"LadderTex7_", L"..\\Resources\\Texture\\Object\\ladder\\7base.png");

		std::shared_ptr<Material> pLadderMater7_ = std::make_shared<Material>();
		pLadderMater7_->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater7_->SetTexture(pLadder7_);
		Resources::Insert(L"LadderMater7_", pLadderMater7_);


		//npc
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex0", L"..\\Resources\\Texture\\NPC\\npc0.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPCMater0", pNPCMater);

		std::shared_ptr<Texture> pNPCTex2 =
			Resources::Load<Texture>(L"NPCTex2", L"..\\Resources\\Texture\\NPC\\npc2.png");

		std::shared_ptr<Material> pNPCMater2 = std::make_shared<Material>();
		pNPCMater2->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater2->SetTexture(pNPCTex2);
		Resources::Insert(L"NPCMater2", pNPCMater2);


		SetMapSize(-4.8f,2.f,4.8f,-2.5f);
	}
	LeafreScene::~LeafreScene()
	{

	}
	void LeafreScene::Initialize()
	{
		CreateBackground();
		setobject();
		
		NPC* pNPC = new NPC();
		AddGameObject(eLayerType::NPC, pNPC);
		MeshRenderer* pNPCRenderer = pNPC->AddComponent<MeshRenderer>();
		pNPCRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pNPCRenderer->SetMaterial(Resources::Find<Material>(L"NPCMater0"));
		pNPC->GetComponent<Transform>()->SetPosition( -0.3f, -2.7f, -0.03f);
		pNPC->GetComponent<Transform>()->SetScale(0.69 * 1.3f, 0.89 * 1.3f,0.f);

		NPC* pNPC2 = new NPC();
		AddGameObject(eLayerType::NPC, pNPC2);
		MeshRenderer* pNPCRenderer2 = pNPC2->AddComponent<MeshRenderer>();
		pNPCRenderer2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pNPCRenderer2->SetMaterial(Resources::Find<Material>(L"NPCMater2"));
		pNPC2->GetComponent<Transform>()->SetPosition(-7.f, -3.85f, -0.03f);
		pNPC2->GetComponent<Transform>()->SetScale(0.763 * 1.1f, 1.f * 1.1f, 0.f);
		//0.763 : 1
		
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
	void LeafreScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Valley");
		}
	}
	void LeafreScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void LeafreScene::Render()
	{
		Scene::Render();
	}
	void LeafreScene::OnEnter()
	{

	}
	void LeafreScene::OnExit()
	{

	}
	void LeafreScene::CreateBackground()
	{
		//바탕
		{
			GameObject* pBackGround = new GameObject();
			AddGameObject(eLayerType::Background, pBackGround);
			MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
			pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRender->SetMaterial(Resources::Find<Material>(L"LeafeMater"));
			pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
			//1.829 : 1
			pBackGround->GetComponent<Transform>()->SetScale(1.829f * 13.f, 1.f * 13.f, 1.f);
		}
	}
	void LeafreScene::setobject()
	{
		Ladder* pLadder0 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder0);
		MeshRenderer* pLadderMeshRender0 =  pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRender0->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender0->SetMaterial(Resources::Find<Material>(L"LadderMater7"));
		pLadder0->GetComponent<Transform>()->SetPosition(-4.f, -1.6f, -0.02f);
		pLadder0->GetComponent<Transform>()->SetScale(0.4f * 1.8f, 1.5f * 1.5f, 0.f);

		Ladder* pLadder1 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder1);
		MeshRenderer* pLadderMeshRender1 = pLadder1->AddComponent<MeshRenderer>();
		pLadderMeshRender1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender1->SetMaterial(Resources::Find<Material>(L"LadderMater7_"));
		pLadder1->GetComponent<Transform>()->SetPosition(3.6f, -1.37f, -0.02f);
		pLadder1->GetComponent<Transform>()->SetScale(0.4f * 1.8f, 1.5f * 1.5f, 0.f);
	}
}
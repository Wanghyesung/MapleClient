#include "WTempleScene_2.h"
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
#include "WTexture.h"
#include "WSceneManger.h"
#include "WLadder.h"




namespace W
{
	TempleScene_2::TempleScene_2()
	{
		std::shared_ptr<Texture> pLadder0 =
			Resources::Load<Texture>(L"LadderTex4", L"..\\Resources\\Texture\\Object\\ladder\\4base.png");

		std::shared_ptr<Material> pLadderMater0 = std::make_shared<Material>();
		pLadderMater0->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater0->SetTexture(pLadder0);
		Resources::Insert(L"LadderMater0", pLadderMater0);

		std::shared_ptr<Texture> pLadder1 =
			Resources::Load<Texture>(L"LadderTex4_", L"..\\Resources\\Texture\\Object\\ladder\\4_base.png");

		std::shared_ptr<Material> pLadderMater1 = std::make_shared<Material>();
		pLadderMater1->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater1->SetTexture(pLadder1);
		Resources::Insert(L"LadderMater1", pLadderMater1);

		SetMapSize(-5.f,4.f,5.f,-4.f);
	}
	TempleScene_2::~TempleScene_2()
	{
	}
	void TempleScene_2::Initialize()
	{
		CreateBackground();
		setobject();



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
	void TempleScene_2::Update()
	{
		Scene::Update();


		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"TempleBoss");
		}
	}
	void TempleScene_2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleScene_2::Render()
	{
		Scene::Render();
	}
	void TempleScene_2::OnEnter()
	{
	}
	void TempleScene_2::OnExit()
	{
	}
	void TempleScene_2::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleMater2"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//3 : 2
		pBackGround->GetComponent<Transform>()->SetScale(3.f * 8.f, 2.f * 8.f, 0.f);
	}
	void TempleScene_2::setobject()
	{
		Ladder* pLadder0 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder0);
		MeshRenderer* pLadderMeshRenderer = pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRenderer->SetMaterial(Resources::Find<Material>(L"LadderMater0"));
		pLadder0->GetComponent<Transform>()->SetPosition(-7.f,-0.02f,-1.f);
		pLadder0->GetComponent<Transform>()->SetScale(1.f * 0.5f, 5.f * 0.4f, 0.f);

		Ladder* pLadder1 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder1);
		MeshRenderer* pLadderMeshRenderer1 = pLadder1->AddComponent<MeshRenderer>();
		pLadderMeshRenderer1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRenderer1->SetMaterial(Resources::Find<Material>(L"LadderMater1"));
		pLadder1->GetComponent<Transform>()->SetPosition(7.f, -0.02f, -1.f);
		pLadder1->GetComponent<Transform>()->SetScale(1.f * 0.5f, 5.f * 0.4f, 0.f);


		Ladder* pLadder2 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder2);
		MeshRenderer* pLadderMeshRenderer2 = pLadder2->AddComponent<MeshRenderer>();
		pLadderMeshRenderer2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRenderer2->SetMaterial(Resources::Find<Material>(L"LadderMater0"));
		pLadder2->GetComponent<Transform>()->SetPosition(-6.f, -4.0f, -1.f);
		pLadder2->GetComponent<Transform>()->SetScale(1.f * 0.5f, 5.f * 0.4f, 0.f);

		Ladder* pLadder3 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder3);
		MeshRenderer* pLadderMeshRenderer3 = pLadder3->AddComponent<MeshRenderer>();
		pLadderMeshRenderer3->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRenderer3->SetMaterial(Resources::Find<Material>(L"LadderMater1"));
		pLadder3->GetComponent<Transform>()->SetPosition(6.f, -3.9f, -1.f);
		pLadder3->GetComponent<Transform>()->SetScale(1.f * 0.5f, 5.f * 0.4f, 0.f);
	}
}
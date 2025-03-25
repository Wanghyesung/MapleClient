#include "WPlayScene.h"
#include "WTransform.h"
#include "WResources.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WCameraScript.h"
#include "WCamera.h"
#include "WGridScript.h"
#include "WObject.h"
#include "WPlayer.h"
#include "WRenderer.h"
#include "WCollider2D.h"
#include "WPlayerScript.h"
#include "WRigidbody.h"
#include "WCollisionManager.h"
#include "WAnimator.h"
#include "WLight.h"
#include "WPaintShader.h"
#include "WAnimator.h"
#include "WParticleSystem.h"
namespace W
{
	PlayScene::PlayScene()
	{
		SetMapSize(-10.f, 5.f, 10.f, -5.f);
		SetMapPossibleSize(-10.f, 10.f);
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();

		//{
		//
		//	GameObject* player
		//		= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
		//
		//	player->SetName(L"Zelda");
		//
		//	Collider2D* cd = player->AddComponent<Collider2D>();
		//	cd->SetSize(Vector2(1.0f, 1.0f));
		//
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		//
		//	const float pi = 3.141592f;
		//	float degree = pi / 8.0f;
		//
		//	player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
		//	//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		//
		//	std::shared_ptr<Texture> atlas
		//		= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");
		//
		//	Animator* at = player->AddComponent<Animator>();
		//	at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3 , Vector2(100.f,100.f));
		//
		//	//at->CompleteEvent(L"Idle") = std::bind();
		//
		//	at->Play(L"Idle", true);
		//	player->AddComponent<PlayerScript>();
		//}

		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::Monster, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		//	Collider2D* cd = player->AddComponent<Collider2D>();
		//	//cd->SetSize(Vector2(1.2f, 1.2f));
		//	//player->AddComponent<PlayerScript>();
		//}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Particle");
			AddGameObject(eLayerType::Monster, player);
			ParticleSystem* mr = player->AddComponent<ParticleSystem>();
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 0.2f));
			//Collider2D* cd = player->AddComponent<Collider2D>();
			//cd->SetSize(Vector2(1.2f, 1.2f));
			//player->AddComponent<PlayerScript>();
		}

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
			lightComp->SetRadius(3.0f);
		}
		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::UI, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();// ->SetPlayer(player);
			renderer::m_vecCameras.push_back(cameraComp);
			renderer::MainCamera = cameraComp;
		}

		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			renderer::UICamera = pCameraComp;
		}
		
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
}

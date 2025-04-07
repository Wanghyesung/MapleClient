#include "WValleyScene.h"
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
#include "WCage.h"
#include "WInterfaceUI.h"
#include "WEquipState.h"
#include "WAlixirUI.h"
#include "WPlayer.h"
#include "WObject.h"
#include "WRenderer.h"
#include "WGround.h"
#include "WTexture.h"
#include "WSkelegon.h"

#include "WBossUI.h"
#include "WAudioClip.h"
#include "WAudioSource.h"
namespace W
{
	ValleyScene::ValleyScene()
	{
		std::shared_ptr<Texture> pValleyTex =
			Resources::Load<Texture>(L"dragonValleyTex", L"..\\Resources\\Texture\\background\\dragonValley.png");
		std::shared_ptr<Material> pValleyMater = std::make_shared<Material>();
		pValleyMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pValleyMater->SetTexture(pValleyTex);
		//pValleyMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"dragonValleyMater", pValleyMater);


		//npc
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex1", L"..\\Resources\\Texture\\NPC\\npc1.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPCMater1", pNPCMater);

		SetMapSize(0.f, 7.f, 0.f, -7.f);
		SetMapPossibleSize(-4.37f, 4.37f);
	}
	ValleyScene::~ValleyScene()
	{

	}
	void ValleyScene::Initialize()
	{
		CreateBackground();
		setobject();
		setmonster();

		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);
		pPlayer->Initialize();


	
		EquipState* pEquipState = new EquipState();
		SceneManger::AddGameObject(eLayerType::UI, pEquipState);
		pEquipState->SetPlayer(pPlayer);
		pEquipState->Initialize();

		InterfaceUI* pInterUI = new InterfaceUI();
		AddGameObject(eLayerType::UI, pInterUI);
		pInterUI->Initialize();

		BossUI* pBossUI = new BossUI();
		AddGameObject(eLayerType::UI, pBossUI);
		pBossUI->Initialize();

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* pCameraScript = pCamera->AddComponent<CameraScript>();
			renderer::MainCamera = pCameraComp;
			pCameraScript->SetPlayer(pPlayer);
		}

		//ui camera
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
	void ValleyScene::Update()
	{
		Scene::Update();
	}
	void ValleyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene::Render()
	{
		Scene::Render();
	}
	void ValleyScene::OnEnter()
	{

	}
	void ValleyScene::OnExit()
	{
		EndSound();

	}
	void ValleyScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		std::shared_ptr<AudioClip> pAudioClip = Resources::Load<AudioClip>(L"valleysound", L"..\\Resources\\sound\\DragonNest.mp3");
	
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.2f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(25 * 0.35f,  25.f * 1.f, 1.f);
	}

	void ValleyScene::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Play();
	}

	void ValleyScene::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
	}

	void ValleyScene::setobject()
	{

	}
	void ValleyScene::setmonster()
	{
		//Skelegon* pSkelegon = object::Instantiate<Skelegon>(Vector3(3.f, 1.2f, -1.5f), eLayerType::Monster);
		//pSkelegon->Initialize();
		//Light* lightComp = pSkelegon->AddComponent<Light>();
		//lightComp->SetType(eLightType::FadeOut);
		//lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.0f));
		//lightComp->SetRadius(2.0f);

	}
}

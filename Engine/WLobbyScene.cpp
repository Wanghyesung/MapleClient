#include "WLobbyScene.h"
#include "WRenderer.h"
#include "WSpeechBar.h"
#include "WApplication.h"
#include "WSceneManger.h"

extern W::Application application;

namespace W
{
	LobbyScene::LobbyScene()
	{
	}
	LobbyScene::~LobbyScene()
	{

	}
	void LobbyScene::Initialize()
	{
		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			pUICamera->SetObjectID(1);
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			renderer::UICamera = pCameraComp;
		}

		SpeechBar* pLoginBar = new SpeechBar();
		pLoginBar->SetBaseSpeech(L"ID 입력 후 ENTER");
		pLoginBar->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		pLoginBar->GetComponent<Transform>()->SetScale(Vector3(200.f,100.f,-1.f));
		pLoginBar->SetObjectID(0);
		AddGameObject(eLayerType::UI , pLoginBar);

		pLoginBar->SetSendPktFunc(
			[this, pLoginBar]() 
			{
				PLAYER_NAME = WstringToString(pLoginBar->GetSpeech());
				start();
			});
	}
	void LobbyScene::Update()
	{
		Scene::Update();
	}
	void LobbyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void LobbyScene::Render()
	{
		
	}
	void LobbyScene::SendEnter()
	{

	}
	void LobbyScene::OnEnter()
	{

	}
	void LobbyScene::OnExit()
	{

	}
	void LobbyScene::start()
	{
		GClientService->Connect();
		SceneManger::Start();
	}
}
#include "WLobbyScene.h"
#include "WRenderer.h"
#include "WSpeechBar.h"
#include "WApplication.h"
#include "WSceneManger.h"
#include "WStartUI.h"
extern W::Application application;

namespace W
{
	LobbyScene::LobbyScene()
	{
		std::shared_ptr<Shader> pLoadingShader = Resources::Find<Shader>(L"FullScreenShader");
		shared_ptr<Material> pMater = make_shared<Material>();
		pMater->SetShader(pLoadingShader);
		pMater->SetTexture(Resources::Load<Texture>(L"StartBackGround", L"..\\Resources\\Texture\\UI\\StartUI\\Start.png"));
		Resources::Insert(L"StartScreenMaterial", pMater);

	}
	LobbyScene::~LobbyScene()
	{

	}
	void LobbyScene::Initialize()
	{

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			pCamera->SetObjectID(0);
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			renderer::MainCamera = pCameraComp;
		}

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

		create_object();
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
	void LobbyScene::create_object()
	{
		StartUI* pStartUI = new StartUI();
		pStartUI->SetClientObject(true);
		pStartUI->SetObjectID(0);
		pStartUI->GetComponent<Transform>()->SetPosition(3.0f,-0.75f,-0.1f);
		pStartUI->GetComponent<Transform>()->SetScale(1.4f * 1.f, 0.52f * 1.f, -0.1f);
		AddGameObject(eLayerType::UI, pStartUI);

		SpeechBar* pLoginBar = new SpeechBar();
		pLoginBar->SetBaseSpeech(L"ID 입력 후 게임 시작");
		pLoginBar->SetOffsetPosition(Vector2(180.f, -47.f));
		pLoginBar->GetComponent<Transform>()->SetPosition(Vector3(3.0f,0.4f,0.f));
		pLoginBar->GetComponent<Transform>()->SetScale(Vector3(1.5f, 0.3f, -1.f));
		pLoginBar->SetObjectID(1);
		AddGameObject(eLayerType::UI, pLoginBar);


		pStartUI->SetFunction([this, pLoginBar]()
			{
				const wstring& strPlayerID = pLoginBar->GetSpeech();
				if (strPlayerID.empty())
				{
					MessageBox(nullptr, L"로그인 요청 실패, ID를 입력해주세요", L"로그인 실패", MB_OK);
					return;
				}
				PLAYER_NAME = WstringToString(pLoginBar->GetSpeech());
				start();
			});
		

		GameObject* pBackGround = new GameObject();
		pBackGround->SetClientObject(true);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"StartScreenMaterial"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 5.f);
		AddGameObject(eLayerType::Background, pBackGround);
	}
}
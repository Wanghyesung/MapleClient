#include "WSceneManger.h"
#include "WCamera.h"
#include "WRenderer.h"
#include "..\Engine\WDamageFont.h"
#include "..\Engine\WPlayer.h"
#include "..\Engine\WCameraScript.h"
#include "..\Engine\WItemManager.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WObjectPoolManager.h"
#include "..\Engine_Source\WThreadPool.h"
namespace W
{
	Scene* SceneManger::m_pActiveScene = nullptr;
	atomic<bool> SceneManger::m_bWaitForMapData = false;

	std::unordered_map<UINT, Scene*> SceneManger::m_hashSceneID = {};

	void SceneManger::Initialize()
	{
		ThreadPool::LoadingResource<Texture>(L"shurikenTex", L"..\\Resources\\Texture\\Player\\shuriken\\shuriken.png");
		ThreadPool::LoadingResource<Texture>(L"darkffect", L"..\\Resources\\Texture\\Player\\skill\\effect1.png");
		ThreadPool::LoadingResource<Texture>(L"jumpeffect", L"..\\Resources\\Texture\\Player\\skill\\effect2.png");
		ThreadPool::LoadingResource<Texture>(L"luckeffect", L"..\\Resources\\Texture\\Player\\skill\\effect.png");
		ThreadPool::LoadingResource<Texture>(L"luckhit", L"..\\Resources\\Texture\\Player\\skill\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"quadhit", L"..\\Resources\\Texture\\Player\\skill\\hit1.png");
		ThreadPool::LoadingResource<Texture>(L"quadffect", L"..\\Resources\\Texture\\Player\\skill\\effect7.png");
		ThreadPool::LoadingResource<Texture>(L"raideffect1", L"..\\Resources\\Texture\\Player\\skill\\effect8.png");
		ThreadPool::LoadingResource<Texture>(L"raideffect2", L"..\\Resources\\Texture\\Player\\skill\\effect9.png");
		ThreadPool::LoadingResource<Texture>(L"raidhit", L"..\\Resources\\Texture\\Player\\skill\\hit2.png");
		ThreadPool::LoadingResource<Texture>(L"speedffect", L"..\\Resources\\Texture\\Player\\skill\\effect3.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		ThreadPool::LoadingResource<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
		ThreadPool::LoadingResource<Texture>(L"windffect1", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_0.png");
		ThreadPool::LoadingResource<Texture>(L"windffect2", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_1.png");
		ThreadPool::LoadingResource<Texture>(L"windhit", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"windTex", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\windshuriken.png");
		ThreadPool::LoadingResource<Texture>(L"avenTex", L"..\\Resources\\Texture\\Player\\skill\\ball.png");
		ThreadPool::LoadingResource<Texture>(L"aveneffect", L"..\\Resources\\Texture\\Player\\skill\\effect4.png");
		ThreadPool::LoadingResource<Texture>(L"blastffect1", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_0.png");
		ThreadPool::LoadingResource<Texture>(L"blastffect2", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_1.png");
		ThreadPool::LoadingResource<Texture>(L"blasthit", L"..\\Resources\\Texture\\Player\\skill\\blast\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"blast", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_2.png");
		ThreadPool::LoadingResource<Texture>(L"loadeffect", L"..\\Resources\\Texture\\Player\\skill\\load\\start.png");
		ThreadPool::LoadingResource<Texture>(L"loadhit", L"..\\Resources\\Texture\\Player\\skill\\load\\hit.png");
		ThreadPool::LoadingResource<Texture>(L"loadTex", L"..\\Resources\\Texture\\Player\\skill\\load\\load.png");
		ThreadPool::LoadingResource<Texture>(L"shadowTex", L"..\\Resources\\Texture\\Player\\skill\\shadow\\shadow.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate1", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate1.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate2", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate2.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		ThreadPool::LoadingResource<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
		ThreadPool::LoadingResource<Texture>(L"ultimate_hit", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\hit.png");

		ThreadPool::LoadingResource<Texture>(L"shadowe1ffect", L"..\\Resources\\Texture\\Player\\skill\\effect5.png");
		ThreadPool::LoadingResource<Texture>(L"shadowe2ffect", L"..\\Resources\\Texture\\Player\\skill\\effect6.png");

		for (int i = 0; i <= 9; ++i)
		{
			wstring strNum = to_wstring(i);
			ThreadPool::LoadingResource<Texture>(L"Number_" + strNum, L"..\\Resources\\Texture\\Damage\\" + strNum + L".png");
		}

		//block
		ThreadPool::Joinable();

		//최대 동접자의 3/5만 미리 할당
		for (int i = 0; i < 3; ++i)
		{
			Player* pPlayer = new Player();
			pPlayer->SetName(L"Player");
			ObjectPoolManager::AddObjectPool(pPlayer->GetName(), pPlayer);
		}

		
		for (int i = 0; i < 150; ++i)
		{
			DamageFont* pDamage = new DamageFont();
			pDamage->SetName(L"DamageFont");
			ObjectPoolManager::AddObjectPool(pDamage->GetName(), pDamage);
		}
	}
	void SceneManger::Update()
	{
		m_pActiveScene->Update();
	}
	void SceneManger::LateUpdate()
	{
		m_pActiveScene->LateUpdate();
	}
	void SceneManger::Render()
	{
		m_pActiveScene->Render();
	}

	void SceneManger::Release()
	{
		for (auto &iter : m_hashSceneID)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		ObjectPoolManager::Release();
		ItemManager::Release();
	}

	void SceneManger::Erase(GameObject* _pGameObject)
	{
		m_pActiveScene->EraseObject(_pGameObject->GetLayerType(),_pGameObject);
	}
	Scene* SceneManger::LoadScene(UINT _iSceneID)
	{
		m_pActiveScene->OnExit();

		auto iter = m_hashSceneID.find(_iSceneID);

		if (iter == m_hashSceneID.end())
			return nullptr;

		SwapUI(m_pActiveScene, iter->second);	
		SwapObject(m_pActiveScene, iter->second, FindPlayer());
		PushObjectPool(m_pActiveScene);

		m_pActiveScene = iter->second;
		m_pActiveScene->OnEnter();

		SwapCamera();

		return iter->second;
	}

	GameObject* SceneManger::FindPlayer()
	{		
		std::unordered_map<UINT, GameObject*> vecObjs = 
			m_pActiveScene->GetLayer(eLayerType::Player)->GetGameObjects();

		return vecObjs[PLAYER_ID];
	}

	GameObject* SceneManger::FindObject(UINT _ID, eLayerType _eLayerType)
	{
		GameObject* pObj = m_pActiveScene->GetLayer(_eLayerType)->FindObject(_ID);
		if(!pObj)
			return nullptr;

		return pObj;
	}

	GameObject* SceneManger::FindObject(Scene* _pScene, UINT _ID, eLayerType _eLayerType)
	{
		GameObject* pObj = _pScene->GetLayer(_eLayerType)->FindObject(_ID);

		if (!pObj)
			return nullptr;
		return pObj;
	}

	void SceneManger::PushObjectPool(Scene* _pScene)
	{	
		_pScene->PushObjectPool();
	}

	Scene* SceneManger::FindScene(UINT _iSceneID)
	{
		auto iter = m_hashSceneID.find(_iSceneID);
		if (iter == m_hashSceneID.end())
			return nullptr;

		return iter->second;
	}

	Scene* SceneManger::FindScene(const wstring& _strSceneName)
	{
		auto iter = m_hashSceneID.begin();

		for(iter; iter!= m_hashSceneID.end(); ++iter)
		{
			if(iter->second->GetName() == _strSceneName)
				return iter->second;

		}
		return nullptr;
	}

	void SceneManger::SwapObject(Scene* _pPrevScene, Scene* _pNextScene, GameObject* _pGameObject)
	{
		eLayerType eType = _pGameObject->GetLayerType();
		
		_pPrevScene->EraseObject(eType, _pGameObject);
		_pNextScene->AddGameObject(eType, _pGameObject);
	}

	void SceneManger::SwapObject(Scene* _pPrevScene, Scene* _pNextScene, const std::wstring& _strGameName, eLayerType _eLayerType)
	{
		GameObject* pGameObject = _pPrevScene->GetLayer(_eLayerType)->FindObjectByName(_strGameName);
		if (pGameObject == nullptr)
			assert(nullptr);

		eLayerType eType = pGameObject->GetLayerType();

		_pPrevScene->EraseObject(eType, pGameObject);
		_pNextScene->AddGameObject(eType, pGameObject);
	}

	void SceneManger::SwapUI(Scene* _pPrevScene, Scene* _pNextScene)
	{
		SwapObject(_pPrevScene, _pNextScene, L"Equip", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Interface", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Boss", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Inven", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Skill", eLayerType::UI);	
	}
	
	void SceneManger::SwapCamera()
	{

		std::unordered_map<UINT, GameObject*> hashObj =
			m_pActiveScene->GetLayer(eLayerType::Camera)->GetGameObjects();
		
		////1 main , 2 UI
		renderer::MainCamera = hashObj[0]->GetComponent<Camera>();
		renderer::UICamera = hashObj[1]->GetComponent<Camera>();

		hashObj[0]->GetScript<CameraScript>()->SetPlayer(FindPlayer());
	}

	void SceneManger::SendEnter()
	{
		m_pActiveScene->SendEnter();
	}

}

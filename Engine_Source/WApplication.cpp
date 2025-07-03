#include "WApplication.h"

#include "WTime.h"
#include "WInput.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "UIManager.h"
#include "..\Engine\WEventManager.h"

#include "..\Engine\WItemManager.h"
#include "..\Engine_Source\WThreadPool.h"
#include "..\Engine\WGameObjectManager.h"
#include "..\IOCP_CLIENT\ServerPacketHandler.h"
#include "WPathManager.h"
#include "WFmod.h"
#include "WFontWrapper.h"

namespace W
{
	//0,0의 해상도도 있음
	Application::Application()
		:graphicDevice(nullptr),
		m_hHwnd(NULL),
		m_iWidth(-1),
		m_iHeight(-1)
	{

	}

	Application::~Application()
	{

	}

	void Application::Start()
	{
		SceneManger::GetActiveScene()->OnEnter();
	}
	void Application::Run()
	{
		if (SceneManger::GetActiveScene()->IsLoading())
		{
			RenderLoading();

			if (ThreadPool::IsWork() == false) //리소스 로딩이 다 끄나면
			{
				SceneManger::GetActiveScene()->CompletedLoading();

				SceneManger::SendEnter();
			}
		}
		else if (SceneManger::IsWaitForMapData())
		{
			RenderLoading();
		}
		else
		{
			Update();
			LateUpdate();
			Render();
			UIManager::LateUpdate();

			EventManager::Update();
		}
	}


	void Application::Initialize()
	{
		Time::Initiailize();
		PathManager::Initialize();
		ThreadPool::Initiailize(4);
		Input::Initialize();
	
		renderer::Initialize();
		ItemManager::Initialize();

		EventManager::Initialize();
		GameObjectManager::Initialize();
		
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		
		SceneManger::Update();
		UIManager::Update();
	
	}

	void Application::LateUpdate()
	{
		SceneManger::LateUpdate();
	}

	void Application::Render()
	{
		//graphicDevice->Draw();
		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		Time::Render();

		renderer::Render();
	
	}

	
	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::RenderLoading()
	{
		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();

		SceneManger::GetActiveScene()->RenderLoading();

		//리소스 로딩시간이 길이져 소켓인 끊기지 않기를 방지
		static auto last = chrono::steady_clock::now();
		if (chrono::steady_clock::now() - last >= chrono::seconds(2))
		{
			Protocol::C_EXIT pkt;
			shared_ptr<SendBuffer> pSendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
			GClientService->GetClientSession()->Send(pSendBuffer);
			last = chrono::steady_clock::now();
		}
	}

	void Application::SetWindow(HWND _hHwnd, UINT _iWidth, UINT _iHeight)
	{
		//한번만 호출되게
		if (graphicDevice == nullptr)
		{
			m_hHwnd = _hHwnd;
			m_iWidth = _iWidth;
			m_iHeight = _iHeight;
		
			m_vWindowSize = Vector2(m_iWidth, m_iHeight);
			graphicDevice = std::make_unique<W::GraphicDevice_Dx11>();
			//제일먼저 호출될때 graphicDevice할당
			W::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)_iWidth , (LONG)_iHeight };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(m_hHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(m_hHwnd, true);
		UpdateWindow(m_hHwnd);
	}

	
}
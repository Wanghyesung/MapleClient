#pragma once
#include "..\Engine_Source\WSceneManger.h"
#include "WValleyScene.h"
#include "WCaveScene.h"
#include "WTempleBossScene.h"
#include "WHelisiumBoss.h"
#include "WDemianScene.h"
#ifdef _DEBUG
#pragma comment (lib,"..\\x64\\Debug\\Engine.lib")

#else
#pragma comment (lib, "..\\x64\\Release\\Engine.lib")
#endif


namespace W
{
	void InitializeScenes()
	{

		SceneManger::CreateScene<CaveScene>(L"Cave");
	
		SceneManger::CreateScene<TempleBossScene>(L"TempleBoss");
		SceneManger::CreateScene<HelisiumBoss>(L"Helisium");
		SceneManger::CreateScene<DemianScene>(L"DemianScene");
		SceneManger::CreateScene<ValleyScene>(L"Valley");
		SceneManger::GetActiveScene()->OnEnter();
		
	}
}
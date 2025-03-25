#include "WStop.h"
#include "WResources.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WEventManager.h"
namespace W
{
	Stop::Stop()
	{
		//std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		////pMater->SetTexture(pTex);
		//Resources::Insert(L"faintSkillMater", pMater);
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		//
		//MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		//pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//pRenderer->SetMaterial(pMater);

	}
	Stop::~Stop()
	{

	}
	void Stop::Initialize()
	{

	}
	void Stop::Update()
	{
		Abnormal::Update();
	}
	void Stop::LateUpdate()
	{
		Abnormal::LateUpdate();

	}
	void Stop::Render()
	{
		//Abnormal::Render();
	}
	void Stop::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::Stop);

		//BattleManager::Restore_move(m_pTarget, BattleManager::eAbnormalType::Stop);
	}
}
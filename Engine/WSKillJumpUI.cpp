#include "WSKillJumpUI.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WSceneManger.h"
#include "WSkillManager.h"

namespace W
{
	SKillJumpUI::SKillJumpUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::jump);
		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillJumpUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\2\\jump\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillJumpUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\2\\jump\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillJumpUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\2\\jump\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillJumpMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SKillJumpUI::~SKillJumpUI()
	{

	}
	void SKillJumpUI::Initialize()
	{

	}
	void SKillJumpUI::Update()
	{
		SKill::Update();
	}
	void SKillJumpUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SKillJumpUI::Render()
	{
		SKill::Render();
	}
	void SKillJumpUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SKillJumpUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillJumpMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillJumpUI1"));
	}
	void SKillJumpUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillJumpMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillJumpUI0"));
	}

	void SKillJumpUI::MouseLbtnClicked()
	{

	}
	void SKillJumpUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::jump);
	}
}
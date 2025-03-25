#include "WSkillLuckUI.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WSkillManager.h"

namespace W
{
	SkillLuckUI::SkillLuckUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::luck);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillluckUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\luck\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillluckUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\luck\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillluckUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\luck\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillLuckMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillLuckUI::~SkillLuckUI()
	{

	}
	void SkillLuckUI::Initialize()
	{

	}
	void SkillLuckUI::Update()
	{
		SKill::Update();
	}
	void SkillLuckUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillLuckUI::Render()
	{
		SKill::Render();
	}
	void SkillLuckUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillLuckUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillLuckMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillluckUI1"));
	}

	void SkillLuckUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillLuckMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillluckUI0"));
	}
	void SkillLuckUI::MouseLbtnClicked()
	{
		SKill::MouseLbtnClicked();
	}

	void SkillLuckUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::luck);
	}
}
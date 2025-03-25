#include "WSkillRaidUI.h"
#include "WSkillManager.h"

namespace W
{
	SkillRaidUI::SkillRaidUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::raid);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillRadeUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\4\\rade\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillRadeUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\4\\rade\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillRadeUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\4\\rade\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillRadeMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillRaidUI::~SkillRaidUI()
	{

	}
	void SkillRaidUI::Initialize()
	{

	}
	void SkillRaidUI::Update()
	{
		SKill::Update();
	}
	void SkillRaidUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillRaidUI::Render()
	{
		SKill::Render();
	}
	void SkillRaidUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillRaidUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillRadeMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillRadeUI1"));
	}
	void SkillRaidUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillRadeMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillRadeUI0"));
	}

	void SkillRaidUI::MouseLbtnClicked()
	{

	}

	void SkillRaidUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::raid);
	}
}
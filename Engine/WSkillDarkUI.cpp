#include "WSkillDarkUI.h"
#include "WInput.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WSceneManger.h"
#include "WSkillManager.h"

namespace W
{
	SkillDarkUI::SkillDarkUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::dark);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillDarkUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\dark\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillDarkUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\dark\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillDarkUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\dark\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillDarkMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillDarkUI::~SkillDarkUI()
	{

	}
	void SkillDarkUI::Initialize()
	{

	}
	void SkillDarkUI::Update()
	{
		SKill::Update();
	}
	void SkillDarkUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillDarkUI::Render()
	{
		SKill::Render();
	}
	void SkillDarkUI::MouseOn()
	{

		SKill::MouseOn();
	}
	void SkillDarkUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillDarkMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillDarkUI1"));
	}
	void SkillDarkUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillDarkMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillDarkUI0"));
	}

	void SkillDarkUI::MouseLbtnClicked()
	{

	}

	void SkillDarkUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::dark);
	}
	
}
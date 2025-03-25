#include "WSkillAvenUI.h"
#include "WSkillManager.h"
#include "WPlayer.h"

namespace W
{
	SkillAvenUI::SkillAvenUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::aven);
		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillAvenUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\3\\aven\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillAvenUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\3\\aven\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillAvenUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\3\\aven\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillAvenMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillAvenUI::~SkillAvenUI()
	{

	}
	void SkillAvenUI::Initialize()
	{

	}
	void SkillAvenUI::Update()
	{
		SKill::Update();
	}
	void SkillAvenUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillAvenUI::Render()
	{
		SKill::Render();
	}
	void SkillAvenUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillAvenUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillAvenMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillAvenUI1"));
	}
	void SkillAvenUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillAvenMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillAvenUI0"));
	}

	void SkillAvenUI::MouseLbtnClicked()
	{

	}
	void SkillAvenUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::aven);
	}
}
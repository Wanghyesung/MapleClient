#include "WSkillShadowUI.h"
#include "WPlayer.h"
#include "WSkillManager.h"

namespace W
{
	SkillShadowUI::SkillShadowUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::shadow);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillShadowUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\3\\shadow\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillShadowUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\3\\shadow\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillShadowUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\3\\shadow\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillShadowMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillShadowUI::~SkillShadowUI()
	{

	}
	void SkillShadowUI::Initialize()
	{

	}
	void SkillShadowUI::Update()
	{
		SKill::Update();
	}
	void SkillShadowUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillShadowUI::Render()
	{
		SKill::Render();
	}
	void SkillShadowUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillShadowUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillShadowMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillShadowUI1"));
	}
	void SkillShadowUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillShadowMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillShadowUI0"));
	}

	void SkillShadowUI::MouseLbtnClicked()
	{

	}

	void SkillShadowUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::shadow);
	}
}
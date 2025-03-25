#include "WSkillQSUI.h"
#include "WSkillManager.h"

namespace W
{
	SkillQSUI::SkillQSUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::quad);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillQSUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\4\\qs\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillQSUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\4\\qs\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillQSUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\4\\qs\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillQSMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);


	}
	SkillQSUI::~SkillQSUI()
	{

	}
	void SkillQSUI::Initialize()
	{

	}
	void SkillQSUI::Update()
	{
		SKill::Update();
	}
	void SkillQSUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillQSUI::Render()
	{
		SKill::Render();
	}
	void SkillQSUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillQSUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillQSMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillQSUI1"));
	}
	void SkillQSUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillQSMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillQSUI0"));
	}

	void SkillQSUI::MouseLbtnClicked()
	{

	}

	void SkillQSUI::Using()
	{
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::quad);
	}
}